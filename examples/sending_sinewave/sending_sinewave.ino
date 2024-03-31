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
String finalArray;

void sineWave(String& finalArray);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

}

void loop() {
  
  //write either over bluetooth or serial based on receive messages
  sineWave(finalArray);
  Serial.println(finalArray);
  SerialBT.print(finalArray); //write any serial message to bluetooth device
  //SerialBT.write()
  Serial.print(finalArray); // echo message for my sanity

  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); //read any bluetooth message available
  }

  
  delay(20);
}
void sineWave(String& finalArray) {
  for (int i = 0; i < numSamples; i++) {
    int value = amplitude * sin(2 * PI * frequency * i / sampleRate);
    String strvalue = String(value);
    finalArray.concat(strvalue);
    if (i < numSamples - 1) {
      finalArray.concat(",");
    }
  }
  //Serial.println(finalArray);
  //Serial.println(); 
  delay(1000); 
}
