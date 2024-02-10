#include <Arduino.h>

// Task handles for managing tasks
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

// Function prototypes
void blinkLED1(void *parameter);
void blinkLED2(void *parameter);

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Create tasks that run in parallel
  xTaskCreatePinnedToCore(
    sendSerial1,          // Task function
    "Serial Messager 1",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &task1Handle,       // Task handle
    0                   // Core where the task should run
  );

  xTaskCreatePinnedToCore(
    sendSerial2,          // Task function
    "Serial Messager 2",    // Name of the task (for debugging)
    1000,               // Stack size (bytes)
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &task2Handle,       // Task handle
    1                   // Core where the task should run
  );
}

void loop() {
  // Empty loop since we are using FreeRTOS tasks
}

// Task function for blinking LED1
void sendSerial1(void *parameter) {
  while(1) {
    Serial.println("Serial Messager # 1");
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for a second, RTOS will do other things during this time
  }
}

// Task function for blinking LED2
void sendSerial2(void *parameter) {
  while(1) {
    Serial.println("Serial Messager # 2");
    vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 5 secs
  }
}