
//basic imports
#include "Arduino.h"
#include "BluetoothSerial.h"
#include <utility>
#include <queue>

//our imports
#include "Audio.h"
#include "Bluetooth.h"
#include "IO.h"
#include "UART.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define RX 12
#define TX 27

// define SerialBT object from the library

using IntPair = std::pair<int, int>;

TaskHandle_t audio_task_handle = NULL;
TaskHandle_t bluetooth_task_handle = NULL;
TaskHandle_t io_task_handle = NULL;
TaskHandle_t uart_task_handle = NULL;

// define queue objects for pipelining data between tasks
std::queue<int> audio_q; // queue for storing audio data
std::queue<IntPair> command_queue; 
BluetoothSerial SerialBT;
SoftwareSerial SwSerial(RX, TX); // 14, 12 on pins


//define any state variables that need to be shared between tasks
int state = 0; // IDLE -> 0, RUNNING -> 1, ERROR -> 2
IntPair current_position = std::make_pair(0, 0); // x, y position of the robot

// object definitions for everything in hardware
Audio audio = Audio(state, audio_q);
UART_Handler uart(state, command_queue, current_position, SwSerial);
BluetoothController bluetooth_controller = BluetoothController(state, audio_q, command_queue, SerialBT, current_position);
IO io = IO(state);



// we should create a wrapper for every task that we create as the method cannot be directly passed to the task handler (id really get this)
void audioMainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        audio.main(); // call the proper lidar method that we can't pass to xTaskCreate
        // if you were using input parameters, you could do it by using:
        // int *pValue = (int*)pvParameters
        // this creates a pointer and casts the input as that type to save it
        vTaskDelay(100); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
  }

void bluetoothMainWrapper(void *pvParameters) {
  while (1) {
    bluetooth_controller.main();
    vTaskDelay(10);
  }
}

void ioMainWrapper(void *pvParameters) {
  while (1) {
    io.main();
    vTaskDelay(500);
  }
}

void uartMainWrapper(void *pvParameters) {
  while (1) {
    uart.main();
    vTaskDelay(10);
  }
}

void setup() {
  //task handlers for tasks
  Serial.begin(115200);
  if (!SerialBT.begin("CSTAR Robot")) {
        Serial.println("An error occurred initializing Bluetooth");
    } else {
        Serial.println("Bluetooth initialized");
    }
  
  // put your setup code here, to run once:
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);

  // create all tasks!!!!

  //audio task 
  xTaskCreatePinnedToCore(
    audioMainWrapper,          // Task function, in this case object.method
    "Audio Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &audio_task_handle,       // Task handle
    1                   // Core where the task should run
  );

  //bluetooth task
  xTaskCreatePinnedToCore(
     bluetoothMainWrapper,          // Task function, in this case object.method
    "Bluetooth Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &bluetooth_task_handle,       // Task handle
    4                   // Core where the task should run
  );

  //IO task
  xTaskCreatePinnedToCore(
    ioMainWrapper,          // Task function, in this case object.method
    "IO Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    0,                  // Priority of the task
    &io_task_handle,       // Task handle
    0                   // Core where the task should run
  );

  //UART task
  xTaskCreatePinnedToCore(
    uartMainWrapper,          // Task function, in this case object.method
    "UART Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    0,                  // Priority of the task
    &uart_task_handle,       // Task handle
    4                   // Core where the task should run
  );


}



void loop() { // we're not putting things here are we are using FreeRTOS
}

