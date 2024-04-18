
//basic imports
#include "Arduino.h"
#include <utility>
#include <queue>

//our imports
#include "Motor_Drive.h"
#include "UltraSonic.h"
#include "LiDAR.h"
#include "UART_2.h"
#include "SensorFusion.h"
#include "Encoder.h"


//task handlers for tasks
TaskHandle_t lidar_task_handle = NULL;
TaskHandle_t motor_task_handle = NULL;
TaskHandle_t sensor_fusion_task_handle = NULL;
TaskHandle_t uart_2_task_handle = NULL;
TaskHandle_t ultrasonic_task_handle = NULL;
TaskHandle_t encoder_task_handle = NULL;

using IntPair = std::pair<int, int>;
// define queue objects for pipelining data between tasks
std::queue<IntPair> AngleDistanceQueue; // queue for storing LiDAR data
std::queue<IntPair> DirectionsQueue; // queue for storing x, y coordinates as commands to execute. 

// we should talk about how encoders are going to give data to the sensor fusion task??
std::queue<IntPair> EncoderQueue; // queue for encoder task to store data in, for sensor fusion to verify before changing current position

//define any state variables that need to be shared between tasks
int state = 0; // IDLE -> 0, RUNNING -> 1, ERROR -> 2
float velocity = 0.0; // velocity of the robot
int angle = 0; //current angle of the robot in degrees
IntPair current_position = IntPair(0, 0); // current position of the robot in x, y coordinates

// object definitions for everything in hardware
LiDAR lidar = LiDAR(state, AngleDistanceQueue);
Motor motor = Motor(state, DirectionsQueue, current_position, angle, velocity);
SensorFusion sensor_fusion = SensorFusion(state, AngleDistanceQueue, EncoderQueue, current_position, angle, velocity);
UART_2 uart_2 = UART_2(state, DirectionsQueue);`
Ultrasonic ultrasonic = Ultrasonic(state);
Encoder encoder = Encoder(state, EncoderQueue, angle);


// we should create a wrapper for every task that we create as the method cannot be directly passed to the task handler (id really get this)
void lidarMainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        lidar.main(); // call the proper lidar method that we can't pass to xTaskCreate
        // if you were using input parameters, you could do it by using:
        // int *pValue = (int*)pvParameters
        // this creates a pointer and casts the input as that type to save it
        vTaskDelay(10); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
  }

void motorMainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        motor.main(); // call the proper motor method that we can't pass to xTaskCreate
        vTaskDelay(1000); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
  }

void sensorFusionMainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        sensor_fusion.main(); // call the proper sensor_fusion method that we can't pass to xTaskCreate
        vTaskDelay(10); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
  }

void uart_2MainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        uart_2.main(); // call the proper uart_2 method that we can't pass to xTaskCreate
        vTaskDelay(1000); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
  }

void ultrasonicMainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        ultrasonic.main(); // call the proper ultrasonic method that we can't pass to xTaskCreate
        vTaskDelay(1000); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
  }

void encoderMainWrapper(void *pvParameters) { // NULL is passed no matter what, so we have to require something even if its unused
      while(1) { // we want to run this task forever!!!!
        encoder.main(); // call the proper encoder method that we can't pass to xTaskCreate
        vTaskDelay(1000); // THIS IS NECESSARY WE WANT THIS TASK TO GO FOREVER BUT HAVE A DELAY
      }
  }



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // create all tasks!!!!

  // motor encoder and positioning task
  xTaskCreatePinnedToCore(
    lidarMainWrapper,          // Task function, in this case object.method
    "LiDAR Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &lidar_task_handle,       // Task handle
    1                   // Core where the task should run
  );

  // motor encoder and positioning task
  xTaskCreatePinnedToCore(
    motorMainWrapper,          // Task function, in this case object.method
    "Motor Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &motor_task_handle,       // Task handle
    1                   // Core where the task should run
  );

  // sensor fusion task
  xTaskCreatePinnedToCore(
    sensorFusionMainWrapper,          // Task function, in this case object.method
    "Sensor Fusion Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &sensor_fusion_task_handle,       // Task handle
    0                   // Core where the task should run
  );

  // uart task
  xTaskCreatePinnedToCore(
    uart_2MainWrapper,          // Task function, in this case object.method
    "UART_2 Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &uart_2_task_handle,       // Task handle
    0                   // Core where the task should run
  );

  // ultrasonic task
  xTaskCreatePinnedToCore(
    ultrasonicMainWrapper,          // Task function, in this case object.method
    "Ultrasonic Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &ultrasonic_task_handle,       // Task handle
    0                   // Core where the task should run
  );

  // encoder task
  xTaskCreatePinnedToCore(
    encoderMainWrapper,          // Task function, in this case object.method
    "Encoder Main Task",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &encoder_task_handle,       // Task handle
    1                   // Core where the task should run
  );
}



void loop() { // we're not putting things here are we are using FreeRTOS
}

