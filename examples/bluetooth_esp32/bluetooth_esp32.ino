// i found most of this online - Kaden

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // define SerialBT object from the library

//definitions

int msg;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("CSTAR Testing"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

}


void loop() {
  
  
  //write either over bluetooth or serial based on receive messages
  if (Serial.available()) {
    msg = Serial.read();
    SerialBT.write(msg); //write any serial message to bluetooth device
    //SerialBT.write()
    Serial.write(msg); // echo message for my sanity
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); //read any bluetooth message available
  }

  
  delay(20);
}