#include <Arduino.h>
#include <Wire.h>
#include <ESP32Encoder.h>
#define CH_A_PIN 33 // Encoder channel A pin
#define CH_B_PIN 27
#define MOTOR1_IN1 4 // Motor IN1 pin
#define MOTOR1_IN2 22 // Motor IN2 pin
#define SDA 13
#define SCL 14
#define GPIO_Address 0x20
#define OUTPUT_REGISTER 0x01
#define CONFIG_REGISTER 0x03

volatile int encoderPosition = 0;

void handleChannelA() {
   if (digitalRead(CH_B_PIN) == LOW) {
     encoderPosition++; // If the B channel is low (0) when the A channel changes, the encoder is rotating in the positive direction, so the encoderPosition is incremented.
   } else {
     encoderPosition--; // If the B channel is high (1) when the A channel changes, the encoder is rotating in the negative direction, so the encoderPosition is decremented.
   }
 }
// void handleChannelB() {
//    if (digitalRead(CH_A_PIN) == HIGH) {
//      encoderPosition++; // If the B channel is low (0) when the A channel changes, the encoder is rotating in the positive direction, so the encoderPosition is incremented.
//    } else {
//      encoderPosition--; // If the B channel is high (1) when the A channel changes, the encoder is rotating in the negative direction, so the encoderPosition is decremented.
//    }
// }

void setup(){
	
	Serial.begin(9600);

  pinMode(CH_A_PIN, INPUT_PULLDOWN);
  pinMode(CH_B_PIN, INPUT_PULLDOWN);
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(CH_A_PIN), handleChannelA, RISING);
  // attachInterrupt(digitalPinToInterrupt(CH_B_PIN), handleChannelB, RISING);
	
  Wire.begin(SDA, SCL);
//   // define I2C bus
   Wire.beginTransmission(GPIO_Address);
   Wire.write(CONFIG_REGISTER);
   Wire.write(0x00);
   Wire.endTransmission();

   Wire.beginTransmission(GPIO_Address);
   Wire.write(CONFIG_REGISTER);
   if (Wire.endTransmission()) {
     Serial.println("Error!");
   }
   // scan the I2C bus to see if the device is connected
   // check to make sure the output register is set correctly
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
  while ((encoderPosition/4) < 537) {
    analogWrite(MOTOR1_IN1, 0);
    analogWrite(MOTOR1_IN2, 20);
    Serial.println(encoderPosition/4);
  }
	analogWrite(MOTOR1_IN1, 0);
  analogWrite(MOTOR1_IN2, 0);
  Serial.println(encoderPosition/4);
}
