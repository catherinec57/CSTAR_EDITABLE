
//basic imports
#include "Arduino.h"
#include "BluetoothSerial.h"

//our imports
#include "Audio.h"
#include "Bluetooth.h"
#include "IO.h"
#include "Queue.h"
#include "UART.h"


//task handlers for tasks
TaskHandle_t audio_task_handle = NULL;
TaskHandle_t bluetooth_task_handle = NULL;
TaskHandle_t io_task_handle = NULL;
TaskHandle_t uart_task_handle = NULL;

// define queue objects for pipelining data between tasks
IntQueue audio_q = IntQueue(1000);
IntQueue position_queue = IntQueue(1000);

//define any state variables that need to be shared between tasks
int state = 0; // IDLE -> 0, RUNNING -> 1, ERROR -> 2

// object definitions for everything in hardware
Audio audio = Audio(state, audio_q);
BluetoothController bluetooth_controller = BluetoothController(state, audio_q, position_queue);
IO io = IO(state);
UART_Handler uart = UART_Handler(state, position_queue);


// we should create a wrapper for every task that we create as the method cannot be directly passed to the task handler (id really get this)
void audioMainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        audio.main(); // call the proper lidar method that we can't pass to xTaskCreate
        // if you were using input parameters, you could do it by using:
        // int *pValue = (int*)pvParameters
        // this creates a pointer and casts the input as that type to save it
        vTaskDelay(1); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
  }

void bluetoothMainWrapper(void *pvParameters) {
  while (1) {
    bluetooth_controller.main();
    vTaskDelay(100);
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
    vTaskDelay(100);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // create all tasks!!!!

  // audio task 
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
    0                   // Core where the task should run
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
    0                   // Core where the task should run
  );


}



void loop() { // we're not putting things here are we are using FreeRTOS
}
