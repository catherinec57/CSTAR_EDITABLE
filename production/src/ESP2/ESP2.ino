
//basic imports
#include "Arduino.h"
#include "BluetoothSerial.h"

//our imports
#include "Queue.h"
#include "Motor.h"
#include "UltraSonic.h"
#include "LiDAR.h"
#include "UART_2.h"


//task handlers for tasks
// TaskHandle_t audio_task_handle = NULL;


// define queue objects for pipelining data between tasks


//define any state variables that need to be shared between tasks
int state = 0; // IDLE -> 0, RUNNING -> 1, ERROR -> 2

// object definitions for everything in hardware


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



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // create all tasks!!!!

  // motor encoder and positioning task
  xTaskCreatePinnedToCore(
    audioMainWrapper,          // Task function, in this case object.method
    "Audio Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &audio_task_handle,       // Task handle
    1                   // Core where the task should run
  );




}



void loop() { // we're not putting things here are we are using FreeRTOS
}

