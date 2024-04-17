#include "BluetoothSerial.h"
#include "FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // define SerialBT object from the library

// Definitions
const int sampleRate = 2000;
const int frequency = 440;
const int numSamples = 800;
const float amplitude = 1023;
String finalData;

void sineWave(String& finalData);

// Function prototypes for FreeRTOS tasks
void TaskBluetooth(void *parameter);
void TaskSineWave(void *parameter);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("CSTAR Robot"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  // Create tasks for Bluetooth communication and sine wave generation
  xTaskCreate(TaskBluetooth, "BluetoothTask", 10000, NULL, 1, NULL, 1);
  xTaskCreate(TaskSineWave, "SineWaveTask", 10000, NULL, 1, NULL, 1);
}

void loop() {
  // In an RTOS, the loop function is usually empty.
}

void TaskBluetooth(void *parameter) {
  for (;;) {
    if (SerialBT.available()) {
      Serial.write(SerialBT.read()); // Read and forward any received Bluetooth message
    }
    
    // Bluetooth and Serial output of sine wave data
    if (finalData.length() > 0) {
      SerialBT.print(finalData); // Write to Bluetooth device
      Serial.println(finalData); // Echo to Serial for debugging
      finalData = ""; // Reset the data string after sending
    }
    
    vTaskDelay(20 / portTICK_PERIOD_MS); // Slight delay to prevent task from hogging CPU
  }
}

void TaskSineWave(void *parameter) {
  for (;;) {
    sineWave(finalData);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // 1-second delay between sine wave updates
  }
}

void sineWave(String& finalData) {
  finalData = ""; // Clear previous data
  for (int i = 0; i < numSamples; i++) {
    int value = amplitude * sin(2 * PI * frequency * i / sampleRate);
    finalData.concat(String(value));
    if (i < numSamples - 1) {
      finalData.concat(",");
    }
  }
}
