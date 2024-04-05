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