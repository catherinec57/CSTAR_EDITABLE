#include <Arduino.h>
#include <Wire.h>
#include "FastInterruptEncoder.h"
#define CH_A_PIN 33 // Encoder channel A pin
#define CH_B_PIN 27
#define MOTOR1_IN1 4 // Motor IN1 pin
#define MOTOR1_IN2 22 // Motor IN2 pin
#define SDA 13
#define SCL 14
#define GPIO_Address 0x20
#define OUTPUT_REGISTER 0x01
#define CONFIG_REGISTER 0x03

Encoder enc(CH_A_PIN, CH_B_PIN, HALFQUAD, 250);

unsigned long encodertimer = 0;

/* create a hardware timer */
hw_timer_t * timer = NULL;

void IRAM_ATTR Update_IT_callback()
{ 
  enc.loop(); 
}

void setup(){
	
	Serial.begin(115200);

	if (enc.init()) {
    Serial.println("Encoder Initialization OK");
  } else {
    Serial.println("Encoder Initialization Failed");
    while(1);
  }

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

  /* Use 1st timer of 4 */
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);
  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &Update_IT_callback, true);
  /* Set alarm to call onTimer function every 100 ms -> 100 Hz */
  timerAlarmWrite(timer, 10000, true);
  /* Start an alarm */
  timerAlarmEnable(timer);
}

void loop() {
	// Loop and read the count
	analogWrite(MOTOR1_IN1, 20);
  analogWrite(MOTOR1_IN2, 0);
  if ((millis() > (encodertimer + 1000)) || (millis() < encodertimer)) {
    Serial.println(enc.getTicks());
    encodertimer = millis();
  }
}
