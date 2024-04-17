#include "LiDAR.h" // make sure to include header !!!
#include <Arduino.h>
#include <queue>
#include <utility>
#include <HardwareSerial.h>
#include <cstdint> // Added for uint8_t
#include <string> // Added for std::string

#define SYNC_BYTE 0xA5
#define SYNC_BYTE2 0x5A

#define GET_INFO_BYTE 0x50
#define GET_HEALTH_BYTE 0x52

#define STOP_BYTE 0x25
#define RESET_BYTE 0x40

const uint8_t SCAN_TYPE_NORMAL = 0x20;
const uint8_t SCAN_TYPE_FORCE = 0x21;
const uint8_t SCAN_TYPE_EXPRESS = 0x82;

#define MAX_MOTOR_PWM 1023
#define DEFAULT_MOTOR_PWM 660
#define SET_PWM_BYTE 0xF0

#define DESCRIPTOR_LEN 7
#define INFO_LEN 20
#define HEALTH_LEN 3

#define INFO_TYPE 4
#define HEALTH_TYPE 6

// Define the RX and TX pins
#define RX_PIN 16
#define TX_PIN 17

#define DEBUG true // Set to true to enable debug output

const char HEALTH_STATUSES[][10] = {"Good", "Warning", "Error"};

bool scanning = false; // Initialize scanning flag to false

HardwareSerial mySerial(2); // Use hardware serial port 2

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  mySerial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
}

using IntPair = std::pair<int, int>;

LiDAR::LiDAR(int& state, std::queue<IntPair>& AngleDistanceQueue) : 
  AngleDistanceQueue(AngleDistanceQueue),
  state(state) {  
  // Initialization code here
}

void LiDAR::main() {
  // Implement your function here
  int angle = 1;
  int distance = 2;
  AngleDistanceQueue.push(IntPair(angle, distance)); // add some data in the form of a pair to the queue
  Serial.println("LiDAR Task Running");
}

bool LiDAR::_process_scan(uint8_t* raw, bool& new_scan, int& quality, float& angle, float& distance) {
  new_scan = bool(raw[0] & 0b1);
  bool inversed_new_scan = bool((raw[0] >> 1) & 0b1);
  quality = raw[0] >> 2;
  if (new_scan == inversed_new_scan) {
    // Handle new scan flags mismatch
    Serial.println("New scan flag mismatch");
    return false;
  }
  int check_bit = raw[1] & 0b1;
  if (check_bit != 1) {
    // Handle check bit not equal to 1
    Serial.println("Check bit not equal to 1");
    return false;
  }
  angle = (float)((raw[1] >> 1) + (raw[2] << 7)) / 64.0;
  distance = (float)((raw[3]) + (raw[4] << 8)) / 4.0;
  return true;
}


bool _process_express_scan(ExpressPacket& data, float new_angle, int trame, bool& new_scan, float& angle, float& distance) {
    new_scan = (new_angle < data.start_angle) && (trame == 1);
    angle = (data.start_angle + (((new_angle - data.start_angle) + 360.0) / 32.0 * trame) - data.angle[trame - 1]) + 360.0;
    angle = fmod(angle, 360.0); // Ensure angle is within [0, 360) range
    distance = data.distance[trame - 1];
    return true;
}

void LiDAR::_send_payload_cmd(uint8_t cmd, uint8_t* payload, uint8_t payload_size) {
  // Send command with payload to the sensor
  uint8_t size = payload_size;
  uint8_t req[DESCRIPTOR_LEN + size + 1];
  req[0] = SYNC_BYTE;
  req[1] = cmd;
  req[2] = size;
  for (int i = 0; i < size; i++) {
    req[3 + i] = payload[i];
  }
  uint8_t checksum = 0;
  for (int i = 0; i < DESCRIPTOR_LEN + size; i++) {
    checksum ^= req[i];
  }
  req[DESCRIPTOR_LEN + size] = checksum;
  mySerial.write(req, DESCRIPTOR_LEN + size + 1);
  if (DEBUG) {
    Serial.print("Command sent: ");
    for (int i = 0; i < DESCRIPTOR_LEN + size + 1; i++) {
      Serial.print(req[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void LiDAR::_send_cmd(uint8_t cmd) {
  // Send command to the sensor
  uint8_t req[DESCRIPTOR_LEN];
  req[0] = SYNC_BYTE;
  req[1] = cmd;
  mySerial.write(req, DESCRIPTOR_LEN);
  if (DEBUG) {
    Serial.print("Command sent: ");
    for (int i = 0; i < DESCRIPTOR_LEN; i++) {
      Serial.print(req[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}

std::pair<int, bool> LiDAR::_read_descriptor() {
  // Read descriptor packet
  uint8_t descriptor[DESCRIPTOR_LEN];
  mySerial.readBytes(descriptor, DESCRIPTOR_LEN);
  if (DEBUG) {
    Serial.print("Received descriptor: ");
    for (int i = 0; i < DESCRIPTOR_LEN; i++) {
      Serial.print(descriptor[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  if (descriptor[0] != SYNC_BYTE || descriptor[1] != SYNC_BYTE2) {
    throw "Incorrect descriptor starting bytes";
  }
  bool is_single = descriptor[5] == 0;
  return std::make_pair(descriptor[2], is_single);
}

uint8_t* LiDAR::_read_response(int dsize) {
  // Read response packet with length of `dsize` bytes
  uint8_t* data = (uint8_t*)malloc(dsize);
  while (mySerial.available() < dsize) {
    delay(1);
  }
  mySerial.readBytes(data, dsize);
  if (DEBUG) {
    Serial.print("Received data: ");
    for (int i = 0; i < dsize; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  return data;
}

void LiDAR::getHealth(String& status, int& errorCode) {
    if (mySerial.available() > 0) {
        status = "Data in buffer, you can't have info! Run clean_input() to empty the buffer.";
        errorCode = -1; // Set error code to -1 to indicate buffer data error
        return;
    }

    // Sending command to get health
    _send_cmd(GET_HEALTH_BYTE);

    // Reading descriptor
    uint8_t dsize, dtype;
    bool is_single;
    std::tie(dsize, is_single) = _read_descriptor();

    if (dsize != HEALTH_LEN) {
        status = "Wrong get_info reply length";
        errorCode = -1; // Set error code to -1 to indicate wrong reply length error
        return;
    }

    if (!is_single) {
        status = "Not a single response mode";
        errorCode = -1; // Set error code to -1 to indicate single response mode error
        return;
    }

    // Reading response
    uint8_t* raw = _read_response(dsize);
    
    // Parsing health status and error code
    status = HEALTH_STATUSES[raw[0]];
    errorCode = (raw[1] << 8) + raw[2];

    free(raw);

}

void LiDAR::start(char scan_type, int& express_trame) {
  // Start the scanning process
  if (scanning) {
    Serial.println("Scanning already running !");
    return;
  }
  // Start the scanning process, enable laser diode and the measurement system
  std::pair<int, int> health;
  String status;
  int errorCode;
  getHealth(status, errorCode);
  if (health.first == 2) {
    Serial.print("Trying to reset sensor due to the error. Error code: ");
    Serial.println(health.second);
    // reset();
    getHealth(status, errorCode);
    if (health.first == 2) {
      throw "RPLidar hardware failure.";
    }
  } else if (health.first == 1) {
    Serial.print("Warning sensor status detected! Error code: ");
    Serial.println(health.second);
  }
  uint8_t cmd = scan_type == 'express' ? SCAN_TYPE_EXPRESS : SCAN_TYPE_NORMAL;
  Serial.print("Starting scan process in ");
  Serial.print(scan_type);
  Serial.println(" mode");
  if (scan_type == 'express') {
    uint8_t payload[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    _send_payload_cmd(cmd, payload, sizeof(payload));
  } else {
    _send_cmd(cmd);
  }
  std::pair<int, bool> descriptor = _read_descriptor();
  if (descriptor.first != (scan_type == 'express' ? 5 : 5)) {
    throw "Wrong get_info reply length";
  }
  if (descriptor.second) {
    throw "Not a multiple response mode";
  }

  scanning = true;
}

void LiDAR::iter_measures(char scan_type, int max_buf_meas,ExpressPacket& express_data, ExpressPacket& express_old_data, int& express_trame) {
  // Initialize flag to track initialization status
  static bool express_data_initialized = false;

  // Iterate over measures
  if (!scanning) {
    start(scan_type, express_trame);
  }
  while (true) {
    int dsize = scanning;
    if (max_buf_meas) {
      int data_in_buf = mySerial.available();
      if (data_in_buf > max_buf_meas) {
        Serial.print("Too many bytes in the input buffer: ");
        Serial.print(data_in_buf);
        Serial.print("/");
        Serial.print(max_buf_meas);
        Serial.println(". Cleaning buffer...");
        // stop(); 
      }
    }

    if (scanning == 'normal') {
      uint8_t* raw = _read_response(dsize);
      bool new_scan;
      int quality;
      float angle, distance;
      // Process raw data
      _process_scan(raw, new_scan, quality, angle, distance);
      free(raw);
    } else if (scan_type == 'express') {
      if (scan_type == 'express') {
        if (!express_data_initialized) { // Check if express_data is initialized
          Serial.println("Express data not initialized.");
       }
      if (express_trame == 32) {
        express_trame = 0;
        if (!express_data_initialized) {
        Serial.println("reading first time bytes");
        // express_data = ExpressPacket.from_string(_read_response(dsize));
        express_data_initialized = true; // Set the flag to true upon initialization
      }
        express_old_data = express_data;
        Serial.print("set old_data with start_angle ");
        Serial.println(express_old_data.start_angle);
        // express_data = ExpressPacket.from_string(_read_response(dsize));
        Serial.print("set new_data with start_angle ");
        Serial.println(express_data.start_angle);
      }

      express_trame++;
      Serial.print("process scan of frame ");
      Serial.print(express_trame);
      Serial.print(" with angle : ");
      Serial.print(express_old_data.start_angle);
      Serial.print(" and angle new : ");
      Serial.println(express_data.start_angle);
      // _process_express_scan(express_old_data, express_data.start_angle, express_trame);
      }
    }
  }
}

