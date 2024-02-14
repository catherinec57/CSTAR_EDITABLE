
//basic imports
#include "Arduino.h"
// #include "BluetoothSerial.h"

//our imports
#include "LiDAR.h"
#include "Audio.h"
#include "Motor.h"
#include "Ultrasonic.h"
#include "IO.h"


//task handlers for tasks
TaskHandle_t lidar_task_handle = NULL;

// object definitions for everything in hardware
LiDAR lidar(1);

// we should create a wrapper for every task that we create as the method cannot be directly passed to the task handler (id really get this)
void lidarMainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        lidar.doSomething(); // call the proper lidar method that we can't pass to xTaskCreate
        // if you were using input parameters, you could do it by using:
        // int *pValue = (int*)pvParameters
        // this creates a pointer and casts the input as that type to save it
        vTaskDelay(1000); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
      
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);


  // create all tasks!!!!
  xTaskCreatePinnedToCore(
    lidarMainWrapper,          // Task function, in this case object.method
    "LiDAR doing something",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &lidar_task_handle,       // Task handle
    0                   // Core where the task should run
  );
}

void loop() { // we're not putting things here are we are using FreeRTOS
}

