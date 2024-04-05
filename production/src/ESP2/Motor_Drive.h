#ifndef MOTOR_DRIVE_H
#define MOTOR_DRIVE_H

// Wheel parameters
const double WHEEL_DIAMETER = 0.10; // Diameter of the wheels in meters
const double WHEEL_TRACK = 0.30;   // Distance between the wheels in meters

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