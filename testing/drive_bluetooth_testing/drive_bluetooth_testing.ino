// i found most of this online - Kaden

#include <Arduino.h>
#include <SoftwareSerial.h>
// #include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// BluetoothSerial SerialBT; // define SerialBT object from the library

//definitions
#define RX 12
#define TX 27
SoftwareSerial SwSerial(RX, TX); // 14, 12 on pins

int msg;

void setup() {

  // define all pins
  // SerialBT.begin("ESP32testing"); //Bluetooth device name
  SwSerial.begin(38400);
  Serial.begin(115200);
  // SerialBT.begin("ESP32testing"); //Bluetooth device name
  // Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
}



void loop() {
  // send a command over bluetooth
  // SerialBT.write(0xFF);

  // Serial.println("looping");
  // check if bluetooth is connected
  // if (SerialBT.connected()) {
  //   Serial.println("Connected");
  // }
  // else {
  //   Serial.println("Not connected");
  //   // advertise bluetooth
  //   SerialBT.begin("ESP32testing");
  // }

  // // put your main code here, to run repeatedly:
  // // read from Bluetooth Serial
  Serial.println("looping?...");
  // if (Serial.available()) {
  //   // save data into variable
  //   char data = Serial.read();
  //   // print data
  //   // process the data, if "ROTATE" 
  //   if (data == 'R') {
  //     Serial.println("R");
  //     SwSerial.write('R');
  //   }
  //   else if (data == 'F') {
  //     Serial.println("F");
  //     SwSerial.write('F');
  //   }
  SwSerial.println("R");
  // Serial.println("F");
    
  // }


}
