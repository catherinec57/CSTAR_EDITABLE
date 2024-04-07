#ifndef ENCODER_H
#define ENCODER_H

class Encoder {
public:
    Encoder(int CHA, int CHB);
    int getPosition();
    void reset();

private:
    int _CHA;
    int _CHB;
    volatile int _position;
    void handleInterrupt();
    static void handleInterrupt0();
    static void handleInterrupt1();
};

#endif



// 

#include "Encoder.h"
#include <Arduino.h>

Encoder::Encoder(int CHA, int CHB) {
    _CHA = CHA;
    _CHB = CHB;
    _position = 0;

    // Attach interrupts to the encoder pins
    attachInterrupt(digitalPinToInterrupt(_CHA), handleInterrupt0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(_CHB), handleInterrupt1, CHANGE);
}

int Encoder::getPosition() {
    return _position;
}

void Encoder::reset() {
    _position = 0;
}

void Encoder::handleInterrupt() {
    if (digitalRead(_CHA) == digitalRead(_CHB)) {
        _position++;
    } else {
        _position--;
    }
}

void Encoder::handleInterrupt0() {
    Encoder::getInstance()->handleInterrupt();
}

void Encoder::handleInterrupt1() {
    Encoder::getInstance()->handleInterrupt();
}

//

#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor {
  public: 
    Motor(int PWM_SIGNAL_1, int PWM_SIGNAL_2);
    ~Motor();
    void setSpeed(int speed);
    void setDirection(bool clockwise);
    void stop();

  private:
    int _PWM_SIGNAL_1;
    int _PWM_SIGNAL_2;
};

#endif

//

#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int PWM_SIGNAL_1, int PWM_SIGNAL_2) {
    _PWM_SIGNAL_1 = PWM_SIGNAL_1;
    _PWM_SIGNAL_2 = PWM_SIGNAL_2;
    pinMode(_PWM_SIGNAL_1, OUTPUT);
    pinMode(_PWM_SIGNAL_2, OUTPUT);
}

void Motor::setSpeed(int speed) {
    analogWrite(_PWM_SIGNAL_1, speed);
    analogWrite(_PWM_SIGNAL_2, speed);
}

void Motor::setDirection(bool clockwise) {
    if (clockwise) {
        digitalWrite(_PWM_SIGNAL_1, HIGH);
        digitalWrite(_PWM_SIGNAL_2, LOW);
    } else {
        digitalWrite(_PWM_SIGNAL_1, LOW);
        digitalWrite(_PWM_SIGNAL_2, HIGH);
    }
}

void Motor::stop() {
    setSpeed(0);
}

//

#include "Motor_Drive.h"
#include "Encoder.h"
#include "Motor.h"
#include <math.h>
#include <Arduino.h>

// Encoder and motor objects
    Encoder leftEncoder(2, 3);
    Encoder rightEncoder(4, 5);
    Motor leftMotor(6, 7);
    Motor rightMotor(8, 9);

double x = 0.0, y = 0.0, theta = 0.0;
double startX = 0.0, startY = 0.0, startTheta = 0.0;

void updateOdometry() {
    // Get encoder delta counts
    int leftEncoderDelta = leftEncoder.getPosition();
    int rightEncoderDelta = rightEncoder.getPosition();
    leftEncoder.reset();
    rightEncoder.reset();

    // Calculate wheel distances
    double leftWheelDistance = (leftEncoderDelta * WHEEL_DIAMETER * M_PI) / ENCODER_COUNTS_PER_REV;
    double rightWheelDistance = (rightEncoderDelta * WHEEL_DIAMETER * M_PI) / ENCODER_COUNTS_PER_REV;

    // Calculate robot displacement and rotation
    double displacement = (leftWheelDistance + rightWheelDistance) / 2.0;
    double dTheta = (rightWheelDistance - leftWheelDistance) / WHEEL_TRACK;

    // Update robot position and orientation
    x += displacement * cos(theta);
    y += displacement * sin(theta);
    theta += dTheta;
}

void moveForward(double distance) {
    // Set motor speeds for forward motion
    leftMotor.setSpeed(100);
    rightMotor.setSpeed(100);
    leftMotor.setDirection(true);
    rightMotor.setDirection(true);

    // Move the robot the desired distance
    double targetDistance = distance;
    while (targetDistance > 0) {
        updateOdometry();
        targetDistance -= fabs(leftWheelDistance + rightWheelDistance) / 2.0;
    }

    // Stop the motors
    leftMotor.stop();
    rightMotor.stop();
}

void moveBackward(double distance) {
    // Set motor speeds for backward motion
    leftMotor.setSpeed(100);
    rightMotor.setSpeed(100);
    leftMotor.setDirection(false);
    rightMotor.setDirection(false);

    // Move the robot the desired distance
    double targetDistance = distance;
    while (targetDistance > 0) {
        updateOdometry();
        targetDistance -= fabs(leftWheelDistance + rightWheelDistance) / 2.0;
    }

    // Stop the motors
    leftMotor.stop();
    rightMotor.stop();
}

void rotate(double targetAngle) {
    // Calculate the angle difference and determine the direction of rotation
    double currentAngle = theta;
    double angleDiff = targetAngle - currentAngle;

    // Normalize the angle difference to the range [-pi, pi)
    if (angleDiff > M_PI) {
        angleDiff -= 2 * M_PI;
    } else if (angleDiff < -M_PI) {
        angleDiff += 2 * M_PI;
    }

    // Determine the direction of rotation
    bool turnRight = (angleDiff >= 0);

    // Rotate the robot to the target angle
    leftMotor.setSpeed(100);
    rightMotor.setSpeed(100);

    if (turnRight) {
        leftMotor.setDirection(true);
        rightMotor.setDirection(false);
    } else {
        leftMotor.setDirection(false);
        rightMotor.setDirection(true);
    }

    double targetAngleDiff = fabs(angleDiff);
    while (targetAngleDiff > 0.01) {
        updateOdometry();
        targetAngleDiff -= fabs(rightWheelDistance - leftWheelDistance) / WHEEL_TRACK;
    }

    // Stop the motors
    leftMotor.stop();
    rightMotor.stop();
}

void orientToAngle(double targetAngle) {
    // Calculate the angle difference
    double angleDiff = targetAngle - theta;

    // Rotate the robot to the target angle
    rotate(angleDiff);
}

void resetStartPosition() {
    startX = x;
    startY = y;
    startTheta = theta;
}

void getRelativePosition(double& relX, double& relY, double& relTheta) {
    relX = x - startX;
    relY = y - startY;
    relTheta = theta - startTheta;
}

int main() {
    // Example usage
    resetStartPosition(); // Set the current position as the start position
    moveForward(1.0); // Move the robot forward 1 meter
    orientToAngle(M_PI / 2); // Rotate the robot to 90 degrees
    moveBackward(0.5); // Move the robot backward 0.5 meters

    // Get the robot's position relative to the start position
    double relX, relY, relTheta;
    getRelativePosition(relX, relY, relTheta);

    // Print the final position and orientation
    printf("Robot position: (%.2f, %.2f, %.2f)\n", x, y, theta);
    printf("Relative position: (%.2f, %.2f, %.2f)\n", relX, relY, relTheta);

    return 0;
}

//

#ifndef MOTOR_DRIVE_H
#define MOTOR_DRIVE_H

// Wheel parameters
const double WHEEL_DIAMETER = 0.36; // Diameter of the wheels in meters
const double WHEEL_TRACK = 0.30;   // Distance between the wheels in meters NEED TO CHANGE

// Encoder parameters
const int ENCODER_COUNTS_PER_REV = 537.6; // Number of counts per wheel revolution (PPR)

// Functions
void updateOdometry();
void moveForward(double distance);
void moveBackward(double distance);
void rotate(double targetAngle);
void orientToAngle(double targetAngle);
void resetStartPosition();
void getRelativePosition(double& relX, double& relY, double& relTheta);

#endif