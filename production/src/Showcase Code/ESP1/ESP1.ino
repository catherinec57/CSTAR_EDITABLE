#include <Arduino.h>
#include <BluetoothSerial.h>
#include <SoftwareSerial.h>

#include "soc/rtc_cntl_reg.h"
#include "soc/rtc.h"
#include "soc/syscon_reg.h"
#include "soc/rtc_cntl_struct.h"
#include "driver/i2s.h" 

// Pin values from MCU Schematic
#define red_pin 21
#define green_pin 23
#define blue_pin 33

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define RX 12
#define TX 27
SoftwareSerial SwSerial(RX, TX); // 14, 12 on pins
BluetoothSerial SerialBT;
int msg;

void setGreen() {         // Running = Green
    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, HIGH);
    digitalWrite(blue_pin, LOW);
}

// audio port
static const i2s_port_t i2s_num = I2S_NUM_0;

static const i2s_config_t i2s_config = { 
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_24BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // high interrupt priority
    .dma_buf_count = 8,                             // 8 buffers
    .dma_buf_len = 1024,                            // 1K per buffer, so 8K of buffer space
    .use_apll=0,
    .tx_desc_auto_clear= true, 
    .fixed_mclk=-1    
};

static const i2s_pin_config_t pin_config = {
    .bck_io_num = 19,                                 // The bit clock connectiom, goes to pin 27 of ESP32 1 BCLK
    .ws_io_num = 14,                                  // Word select, also known as word select or left right clock 26 2 LRCK
    .data_out_num = I2S_PIN_NO_CHANGE,                // Data out from the ESP32, connect to DIN on 38357A 25 3 I2S_PIN_NO_CHANGE
    .data_in_num = 26                                 // we are not interested in I2S data into the ESP32 I2S_PIN_NO_CHANGE SDTO 25
};


void setup() {

  // define all pins
  // SerialBT.begin("ESP32testing"); //Bluetooth device name
  SwSerial.begin(38400);
  Serial.begin(115200);
  // SerialBT.begin("ESP32testing"); //Bluetooth device name
  // Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);

  // set up pin colors
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);

  // begin bluetooth
  SerialBT.begin("CSTAR Robot2"); //Bluetooth device name

  // set up i2s
  i2s_driver_install(i2s_num, &i2s_config, 0, NULL);        // ESP32 will allocated resources to run I2S
  i2s_set_pin(i2s_num, &pin_config);    

  const int ledPin = 18; // GPIO pin connected to the LED or other PWM device
  const int ledChannel = 0; // LEDC channel (0-15)

  // Setup PWM properties
  const int freq = 40000; // Frequency in Hertz (40 kHz is high but still common)
  const int resolution = 8; // Resolution in bits (1-16, 8 bits gives 0-255 range for duty cycle)

  // Configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // Attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);

  // Set the duty cycle (0-255) due to 8-bit resolution
  ledcWrite(ledChannel, 127); // 50% duty cycle

}

void loop() {
  // put your main code here, to run repeatedly:

  // set led green
  setGreen(); 
  
  // read from bluetooth
  if (SerialBT.available()) {
    msg = SerialBT.read();
    Serial.write(msg);
    SwSerial.write(msg);
  }

  uint32_t audioData; // Assuming you're reading 24-bit samples
  size_t bytesRead;
  // Read data from the I2S interface
  analogWrite(18, 128);
  i2s_read(i2s_num, &audioData, sizeof(audioData), &bytesRead, portMAX_DELAY);
  
  // Print the number of bytes read
  // transmit audio data
  if (audioData != 0) {
    Serial.println(audioData);
    SerialBT.println(audioData);
  }
  //SerialBT.println(audioData);
  
}
