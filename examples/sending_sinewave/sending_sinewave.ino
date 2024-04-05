#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // define SerialBT object from the library

//definitions
const int sampleRate = 2000;  
const int frequency = 440;    
const int numSamples = 800;   
const float amplitude = 1023; 
String finalData;

void sineWave(String& finalData);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

}

void loop() {
  
  //write either over bluetooth or serial based on receive messages
  sineWave(finalData);
  Serial.println(finalData);
  SerialBT.print(finalData); //write any serial message to bluetooth device
  Serial.print(finalData); // echo message for my sanity

  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); //read any bluetooth message available
  }

  
  delay(20);
}
void sineWave(String& finalData) {
  for (int i = 0; i < numSamples; i++) {
    int value = amplitude * sin(2 * PI * frequency * i / sampleRate);
    String strvalue = String(value);
    finalData.concat(strvalue);
    if (i < numSamples - 1) {
      finalData.concat(",");
    }
  } 
  delay(1000); 
}
