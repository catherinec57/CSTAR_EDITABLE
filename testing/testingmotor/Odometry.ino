// #include <Arduino.h>
// #include <Wire.h>

// #define CH_A_PIN 33 // Encoder channel A pin
// #define CH_B_PIN 27 // Encoder channel B pin
// #define MOTOR1_IN1 4 // Motor IN1 pin
// #define MOTOR1_IN2 22 // Motor IN2 pin
// #define MOTOR2_IN1 32
// #define MOTOR2_IN2 5
// #define SDA 13
// #define SCL 14
// #define GPIO_Address 0x20
// #define OUTPUT_REGISTER 0x01
// #define CONFIG_REGISTER 0x03

// volatile int encoderPosition = 0; // Encoder position variable

// // Interrupt service routines for encoder A and B

// void encoder_isr() {
//   // Reading the current state of encoder A and B
//   int A = digitalRead(CH_A_PIN);
//   int B = digitalRead(CH_B_PIN);
//   // If the state of A changed, it means the encoder has been rotated
//   if ((A == HIGH) != (B == LOW)) {
//     encoderPosition--;
//   } else {
//     encoderPosition++;
//   }
// }
// // void IRAM_ATTR handleChannelA() {
// //   if (digitalRead(CH_B_PIN) == LOW) {
// //     encoderPosition++; // If the B channel is low (0) when the A channel changes, the encoder is rotating in the positive direction, so the encoderPosition is incremented.
// //   } else {
// //     encoderPosition--; // If the B channel is high (1) when the A channel changes, the encoder is rotating in the negative direction, so the encoderPosition is decremented.
// //   }
// // }

// // void IRAM_ATTR handleChannelB() {
// //   if (digitalRead(CH_A_PIN) == LOW) {
// //     encoderPosition--; // If the A channel is low (0) when the B channel changes, the encoder is rotating in the negative direction, so the encoderPosition is decremented.
// //   } else {
// //     encoderPosition++; // If the A channel is high (1) when the B channel changes, the encoder is rotating in the positive direction, so the encoderPosition is incremented.
// //   }
// // }

// // int getPosition() {
// //   return encoderPosition; // Returns the current position of the Encoder
// // }

// // void Reset() {
// //   encoderPosition = 0; // Resets the position of the encoder to zero
// // }

// void setup() {

//   Serial.begin(115200);

//   // Set encoder pins as input with internal pull-ups
//   pinMode(CH_A_PIN, INPUT_PULLUP);
//   pinMode(CH_B_PIN, INPUT_PULLUP);
//   pinMode(MOTOR1_IN1, OUTPUT);
//   pinMode(MOTOR1_IN2, OUTPUT);

//   encoderPosition = 0;
//   Serial.println("Yay");

//   // Attach interrupt service routines to encoder pins
//   // attachInterrupt(CH_A_PIN, handleChannelA, RISING);
//   // attachInterrupt(digitalPinToInterrupt(CH_B_PIN), handleChannelB, CHANGE);
//    attachInterrupt(digitalPinToInterrupt(CH_A_PIN), encoder_isr, CHANGE);

//   Wire.begin(SDA, SCL);
//   // define I2C bus
//   Wire.beginTransmission(GPIO_Address);
//   Wire.write(CONFIG_REGISTER);
//   Wire.write(0x00);
//   Wire.endTransmission();

//   Wire.beginTransmission(GPIO_Address);
//   Wire.write(CONFIG_REGISTER);
//   if (Wire.endTransmission()) {
//     Serial.println("Error1!");
//   }
//   // scan the I2C bus to see if the device is connected
//   // check to make sure the output register is set correctly
//   Wire.beginTransmission(GPIO_Address);
//   Wire.write(0x01); // Point to the Output register of Port 0
//   Wire.write(0xFF);
//   int output;
//   output = Wire.endTransmission();
//   if (output) {
//     Serial.println("Error2!");
//     Serial.println(output);
//   }
// }

// int i = 0;
// void loop() {
  
//   // encoderPosition = 0;
//   analogWrite(MOTOR1_IN1, i);
//   analogWrite(MOTOR1_IN2, 0);
//   analogWrite(MOTOR2_IN1, i);
//   analogWrite(MOTOR2_IN2, 0);
//   Serial.println(i);
//   i++;
//   i = i % 255;
//   if (i < 0) {
//     i = -i;
//   }
//   //delay(100);
//   Serial.println(encoderPosition);

// }




// // // ENCODER.h

// // #ifndef ENCODER_H
// // #define ENCODER_H

// // class Encoder {
// // public:
// //     Encoder(int CH_A_PIN, int CH_B_PIN);
// //     int getPosition();
// //     void Reset();

// // private:
// //     int _CH_A_PIN;
// //     int _CH_B_PIN;
// //     volatile int encoderPosition;
// //     static void handleChannelA();
// //     static void handleChannelB();
// // };

// // #endif



// // // ENCODER.cpp

// // #include "Encoder.h"
// // #include <Arduino.h>

// // Encoder::Encoder(int CH_A_PIN, int CH_B_PIN) {
// //     _CH_A_PIN = CH_A_PIN;
// //     _CH_B_PIN = CH_B_PIN;
// //     encoderPosition = 0;

// //     pinMode(CH_A_PIN, INPUT_PULLUP);
// //     pinMode(CH_B_PIN, INPUT_PULLUP);

// //     attachInterrupt(digitalPinToInterrupt(_CH_A_PIN), handleChannelA, CHANGE);
// //     attachInterrupt(digitalPinToInterrupt(_CH_B_PIN), handleChannelB, CHANGE);
// // }

// // int Encoder::getPosition() {
// //     return encoderPosition;
// // }

// // void Encoder::Reset() {
// //     encoderPosition = 0;
// // }

// // void handleChannelA() {
// //   if (digitalRead(CH_B_PIN) == LOW) {
// //     encoderPosition++; // If the B channel is low (0) when the A channel changes, the encoder is rotating in the positive direction, so the encoderPosition is incremented.
// //   } else if (digitalRead(CH_B_PIN) == HIGH) {
// //     encoderPosition--; // If the B channel is high (1) when the A channel changes, the encoder is rotating in the negative direction, so the encoderPosition is decremented.
// //   } else {
// //     ;
// //   }
// // }

// // void handleChannelB() {
// //   if (digitalRead(CH_A_PIN) == LOW) {
// //     encoderPosition--; // If the A channel is low (0) when the B channel changes, the encoder is rotating in the negative direction, so the encoderPosition is decremented.
// //   } else if (digitalRead(CH_A_PIN) == HIGH) {
// //     encoderPosition++; // If the A channel is high (1) when the B channel changes, the encoder is rotating in the positive direction, so the encoderPosition is incremented.
// //   } else {
// //     ;
// //   }
// // }

// // // MOTOR.h

// // #ifndef MOTOR_H
// // #define MOTOR_H

// // #include "Arduino.h"

// // class Motor {
// //   public: 
// //     Motor(int SIGNAL_A, int SIGNAL_B);
// //     void Move(int speed, bool clockwise);
// //     void Stop();

// //   private:
// //     int _SIGNAL_A;
// //     int _SIGNAL_B;
// // };

// // #endif

// // // MOTOR.cpp

// // #include "Motor.h"
// // #include <Arduino.h>

// // Motor::Motor(int SIGNAL_A, int SIGNAL_B) {
// //     _SIGNAL_A = SIGNAL_A;
// //     _SIGNAL_B = SIGNAL_B;

// //     pinMode(_SIGNAL_A, OUTPUT);
// //     pinMode(_SIGNAL_B, OUTPUT);
// // }

// // void Motor::Move(int speed, bool clockwise) {
// //   if (clockwise) {
// //     analogWrite(_SIGNAL_A, speed);
// //     analogWrite(_SIGNAL_B, 0);
// //   }
// //   else {
// //     analogWrite(_SIGNAL_A, 0);
// //     analogWrite(_SIGNAL_B, speed);
// //   }
// // }

// // void Motor::Stop() {
// //     analogWrite(_SIGNAL_A, 0);
// //     analogWrite(_SIGNAL_B, 0);
// // }

// // //

// // #include "Motor_Drive.h"
// // #include "Encoder.h"
// // #include "Motor.h"
// // #include <math.h>
// // #include <Arduino.h>

// // // Encoder and motor objects
// //     Encoder leftEncoder(2, 3);
// //     Encoder rightEncoder(4, 5);
// //     Motor leftMotor(6, 7);
// //     Motor rightMotor(8, 9);

// // double x = 0.0, y = 0.0, theta = 0.0;
// // double startX = 0.0, startY = 0.0, startTheta = 0.0;

// // void updateOdometry() {
// //     // Get encoder delta counts
// //     int leftEncoderDelta = leftEncoder.getPosition();
// //     int rightEncoderDelta = rightEncoder.getPosition();
// //     leftEncoder.reset();
// //     rightEncoder.reset();

// //     // Calculate wheel distances
// //     double leftWheelDistance = (leftEncoderDelta * WHEEL_DIAMETER * M_PI) / ENCODER_COUNTS_PER_REV;
// //     double rightWheelDistance = (rightEncoderDelta * WHEEL_DIAMETER * M_PI) / ENCODER_COUNTS_PER_REV;

// //     // Calculate robot displacement and rotation
// //     double displacement = (leftWheelDistance + rightWheelDistance) / 2.0;
// //     double dTheta = (rightWheelDistance - leftWheelDistance) / WHEEL_TRACK;

// //     // Update robot position and orientation
// //     x += displacement * cos(theta);
// //     y += displacement * sin(theta);
// //     theta += dTheta;
// // }

// // void moveForward(double distance) {
// //     // Set motor speeds for forward motion
// //     leftMotor.setSpeed(100);
// //     rightMotor.setSpeed(100);
// //     leftMotor.setDirection(true);
// //     rightMotor.setDirection(true);

// //     // Move the robot the desired distance
// //     double targetDistance = distance;
// //     while (targetDistance > 0) {
// //         updateOdometry();
// //         targetDistance -= fabs(leftWheelDistance + rightWheelDistance) / 2.0;
// //     }

// //     // Stop the motors
// //     leftMotor.stop();
// //     rightMotor.stop();
// // }

// // void moveBackward(double distance) {
// //     // Set motor speeds for backward motion
// //     leftMotor.setSpeed(100);
// //     rightMotor.setSpeed(100);
// //     leftMotor.setDirection(false);
// //     rightMotor.setDirection(false);

// //     // Move the robot the desired distance
// //     double targetDistance = distance;
// //     while (targetDistance > 0) {
// //         updateOdometry();
// //         targetDistance -= fabs(leftWheelDistance + rightWheelDistance) / 2.0;
// //     }

// //     // Stop the motors
// //     leftMotor.stop();
// //     rightMotor.stop();
// // }

// // void rotate(double targetAngle) {
// //     // Calculate the angle difference and determine the direction of rotation
// //     double currentAngle = theta;
// //     double angleDiff = targetAngle - currentAngle;

// //     // Normalize the angle difference to the range [-pi, pi)
// //     if (angleDiff > M_PI) {
// //         angleDiff -= 2 * M_PI;
// //     } else if (angleDiff < -M_PI) {
// //         angleDiff += 2 * M_PI;
// //     }

// //     // Determine the direction of rotation
// //     bool turnRight = (angleDiff >= 0);

// //     // Rotate the robot to the target angle
// //     leftMotor.setSpeed(100);
// //     rightMotor.setSpeed(100);

// //     if (turnRight) {
// //         leftMotor.setDirection(true);
// //         rightMotor.setDirection(false);
// //     } else {
// //         leftMotor.setDirection(false);
// //         rightMotor.setDirection(true);
// //     }

// //     double targetAngleDiff = fabs(angleDiff);
// //     while (targetAngleDiff > 0.01) {
// //         updateOdometry();
// //         targetAngleDiff -= fabs(rightWheelDistance - leftWheelDistance) / WHEEL_TRACK;
// //     }

// //     // Stop the motors
// //     leftMotor.stop();
// //     rightMotor.stop();
// // }

// // void orientToAngle(double targetAngle) {
// //     // Calculate the angle difference
// //     double angleDiff = targetAngle - theta;

// //     // Rotate the robot to the target angle
// //     rotate(angleDiff);
// // }

// // void resetStartPosition() {
// //     startX = x;
// //     startY = y;
// //     startTheta = theta;
// // }

// // void getRelativePosition(double& relX, double& relY, double& relTheta) {
// //     relX = x - startX;
// //     relY = y - startY;
// //     relTheta = theta - startTheta;
// // }

// // int main() {
// //     // Example usage
// //     resetStartPosition(); // Set the current position as the start position
// //     moveForward(1.0); // Move the robot forward 1 meter
// //     orientToAngle(M_PI / 2); // Rotate the robot to 90 degrees
// //     moveBackward(0.5); // Move the robot backward 0.5 meters

// //     // Get the robot's position relative to the start position
// //     double relX, relY, relTheta;
// //     getRelativePosition(relX, relY, relTheta);

// //     // Print the final position and orientation
// //     printf("Robot position: (%.2f, %.2f, %.2f)\n", x, y, theta);
// //     printf("Relative position: (%.2f, %.2f, %.2f)\n", relX, relY, relTheta);

// //     return 0;
// // }

// // //

// // #ifndef MOTOR_DRIVE_H
// // #define MOTOR_DRIVE_H

// // // Wheel parameters
// // const double WHEEL_DIAMETER = 0.36; // Diameter of the wheels in meters
// // const double WHEEL_TRACK = 0.30;   // Distance between the wheels in meters NEED TO CHANGE

// // // Encoder parameters
// // const int ENCODER_COUNTS_PER_REV = 537.6; // Number of counts per wheel revolution (PPR)

// // // Functions
// // void updateOdometry();
// // void moveForward(double distance);
// // void moveBackward(double distance);
// // void rotate(double targetAngle);
// // void orientToAngle(double targetAngle);
// // void resetStartPosition();
// // void getRelativePosition(double& relX, double& relY, double& relTheta);

// // #endif