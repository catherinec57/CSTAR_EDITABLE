#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <iostream>
#include <cstring>
#include <string>
#define CH_A_PIN 33 // Encoder channel A pin
#define CH_B_PIN 27
#define MOTOR1_IN1 4 // Motor IN1 pin
#define MOTOR1_IN2 22 // Motor IN2 pin
#define MOTOR2_IN1 32
#define MOTOR2_IN2 5
#define MOTO
#define SDA 13
#define SCL 14
#define GPIO_Address 0x20
#define OUTPUT_REGISTER 0x01
#define CONFIG_REGISTER 0x03
#define RX 36
#define TX 19
// SoftwareSerial SwSerial(RX, TX);
void setup() {
  // put your setup code here, to run once:
  // sertup UART comms channel
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);
  pinMode(MOTOR2_IN2, OUTPUT);
  // define Sofware Serial on pins 34, and 35
  // SwSerial.begin(38400);
  Serial.begin(115200);
  // setup motor control pins
  Wire.begin(SDA, SCL);
  Wire.beginTransmission(GPIO_Address);
  Wire.write(CONFIG_REGISTER);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(GPIO_Address);
  Wire.write(CONFIG_REGISTER);
  if (Wire.endTransmission()) {
    Serial.println("Error!");
  }
  Wire.beginTransmission(GPIO_Address);
  Wire.write(0x01); // Point to the Output register of Port 0
  Wire.write(0xFF);
  int output;
  output = Wire.endTransmission();
  if (output) {
    Serial.println("Error!");
    Serial.println(output);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  // read from serial, if there is
  //Serial.println("looping...");
  if (Serial.available()) {
    // read from SwSerial until \n is seen, store in String dta
    String data = Serial.readStringUntil('\n');
    // save data into variable
    // String data = SwSerial.read();
    Serial.println(data);
    // separate string data into 4 separate string variables using a comma as a delimiter
    int commaIndex = data.indexOf(',');
    // save until the first comma as command
    String command = data.substring(0, commaIndex);
    // 
    data = data.substring(commaIndex + 1);
    commaIndex = data.indexOf(',');
    String direction = data.substring(0, commaIndex);
    data = data.substring(commaIndex + 1);
    commaIndex = data.indexOf(',');
    String velocity = data.substring(0, commaIndex);
    String time = data.substring(commaIndex + 1);
    // String command = data.substr(0, data.find(‘,’));
    // String direction = data.substr(data.find(‘,’) + 1);
    // String velocity = data.substr(data.find(‘,’) + 1);
    // String time = data.substr(data.find(‘,’) + 1);
     Serial.println(command);
     Serial.println(direction);
     Serial.println(velocity);
     Serial.println(time);
    int velocityInt = velocity.toInt();
    int timeInt = time.toInt();
    timeInt = timeInt * 1000;
    Serial.println(timeInt);
          // process the data, if “ROTATE”
          if (command == "R") {
            if (direction == "CW") {
              Serial.println("Rotating motor clockwise...");
              int start = millis();
              Serial.println(start);
              while (millis() - start < timeInt) {
                Serial.println("RUNNING");
                analogWrite(MOTOR1_IN1, 0);
                analogWrite(MOTOR1_IN2, velocityInt);
                analogWrite(MOTOR2_IN1, 0);
                analogWrite(MOTOR2_IN2, velocityInt);
              }
              analogWrite(MOTOR1_IN1, 0);
              analogWrite(MOTOR1_IN2, 0);
              analogWrite(MOTOR2_IN1, 0);
              analogWrite(MOTOR2_IN2, 0);
            } else {
              Serial.println("Rotating motor counterclockwise...");
              int start = millis();
              Serial.println(start);
              while (millis() - start < timeInt) {
                Serial.println("RUNNING");
                analogWrite(MOTOR1_IN1, velocityInt);
                analogWrite(MOTOR1_IN2, 0);
                analogWrite(MOTOR2_IN1, velocityInt);
                analogWrite(MOTOR2_IN2, 0);
              }
              analogWrite(MOTOR1_IN1, 0);
              analogWrite(MOTOR1_IN2, 0);
              analogWrite(MOTOR2_IN1, 0);
              analogWrite(MOTOR2_IN2, 0);
            }
          } else {
            if (command == "M") {
              if (direction == "F") {
                Serial.println("Driving motor forward...");
                int start = millis();
                Serial.println(start);
                while (millis() - start < timeInt) {
                  Serial.println("RUNNING");
                  analogWrite(MOTOR1_IN1, 0);
                  analogWrite(MOTOR1_IN2, velocityInt);
                  analogWrite(MOTOR2_IN1, velocityInt);
                  analogWrite(MOTOR2_IN2, 0);
                }
                analogWrite(MOTOR1_IN1, 0);
                analogWrite(MOTOR1_IN2, 0);
                analogWrite(MOTOR2_IN1, 0);
                analogWrite(MOTOR2_IN2, 0);
              } else {
                Serial.println("Driving motor backward...");
                int start = millis();
                Serial.println(start);
                while (millis() - start < timeInt) {
                  Serial.println("RUNNING");
                  analogWrite(MOTOR1_IN1, velocityInt);
                  analogWrite(MOTOR1_IN2, 0);
                  analogWrite(MOTOR2_IN1, 0);
                  analogWrite(MOTOR2_IN2, velocityInt);
                }
                analogWrite(MOTOR1_IN1, 0);
                analogWrite(MOTOR1_IN2, 0);
                analogWrite(MOTOR2_IN1, 0);
                analogWrite(MOTOR2_IN2, 0);
            }
          }
        }
  //   //   int start = millis();
  //   //   Serial.println(start);
  //   //   analogWrite(MOTOR1_IN1, 200);
  //   //     analogWrite(MOTOR1_IN2, 0);
  //   //     analogWrite(MOTOR2_IN1, 0);
  //   //     analogWrite(MOTOR2_IN2, 200);
  //   //   while (millis() - start < 2000) {
  //   //     int x = 0;
  //   //   }
  //   //   analogWrite(MOTOR1_IN1, 0);
  //   //   analogWrite(MOTOR1_IN2, 0);
  //   //   analogWrite(MOTOR2_IN2, 0);
  //   //   analogWrite(MOTOR2_IN1, 0);
  //   // }
  //   // else if (data == ‘R, CCW’) {
  //   //   Serial.println(“Driving Motor”);
  //   //   int start = millis();
  //   //   Serial.println(start);
  //   //   analogWrite(MOTOR1_IN1, 200);
  //   //   analogWrite(MOTOR1_IN2, 0);
  //   //   analogWrite(MOTOR2_IN2, 200);
  //   //   analogWrite(MOTOR2_IN1, 0);
  //   //   while (millis() - start < 2000) {
  //   //     int x = 0;
  //   //   }
  //   //   analogWrite(MOTOR1_IN1, 0);
  //   //   analogWrite(MOTOR1_IN2, 0);
  //   //   analogWrite(MOTOR2_IN2, 0);
  //   //   analogWrite(MOTOR2_IN1, 0);
  //   // }
  //   // else if (data == ‘F’) {
  //   //   Serial.println(“Driving Motor”);
  //   //   int start = millis();
  //   //   Serial.println(start);
  //   //   analogWrite(MOTOR1_IN1, 0);
  //   //   analogWrite(MOTOR1_IN2, 200);
  //   //   analogWrite(MOTOR2_IN2, 0);
  //   //   analogWrite(MOTOR2_IN1, 200);
  //   //   while (millis() - start < 2000) {
  //   //     int x = 0;
  //   //   }
  //   //   analogWrite(MOTOR1_IN1, 0);
  //   //   analogWrite(MOTOR1_IN2, 0);
  //   //   analogWrite(MOTOR2_IN2, 0);
  //   //   analogWrite(MOTOR2_IN1, 0);
  //   // }
  // }
  analogWrite(MOTOR1_IN1, 0);
  analogWrite(MOTOR1_IN2, 0);
  analogWrite(MOTOR2_IN2, 0);
  analogWrite(MOTOR2_IN1, 0);
}
}
