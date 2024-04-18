#include <Arduino.h>
#include <BluetoothSerial.h>
#include <SoftwareSerial.h>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define RX 12
#define TX 27
SoftwareSerial SwSerial(RX, TX); // 14, 12 on pins
BluetoothSerial SerialBT;
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

  // begin bluetooth
  SerialBT.begin("CSTAR Robot"); //Bluetooth device name
}

void loop() {
  // put your main code here, to run repeatedly:
  // read from bluetooth
  if (SerialBT.available()) {
    msg = SerialBT.read();
    Serial.write(msg);
    SwSerial.write(msg);
  }

  // transmit audio data
  SerialBT.println("No data to send!");

}
