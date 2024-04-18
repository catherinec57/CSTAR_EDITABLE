#include "Motor_Drive.h"
#include "Encoder.h"
#include "Motor.h"
#include <math.h>
#include <Arduino.h>
#include <iostream>
#include <stdbool.h>

using namespace std;

// Encoder and motor objects
    Encoder leftEncoder(2, 3);
    Encoder rightEncoder(4, 5);
    Motor leftMotor(6, 7);
    Motor rightMotor(8, 9);

double x = 0.0, y = 0.0, theta = 0.0;
double startX = 0.0, startY = 0.0, startTheta = 0.0;

void setSpeed(int velocity) {
  if (velocity < 0) {
    analogWrite(_PWM_SIGNAL_1, 0); // PWM???
    analogWrite(_PWM_SIGNAL_2, velocity);
  }
  else {
    analogWrite(_PWM_SIGNAL_1, velocity);
    analogWrite(_PWM_SIGNAL_2, 0);
  }
}

// void updateOdometry() {
//     // Get encoder delta counts
//     int leftEncoderDelta = leftEncoder.getPosition();
//     int rightEncoderDelta = rightEncoder.getPosition();
//     leftEncoder.reset();
//     rightEncoder.reset();

//     // Calculate wheel distances
//     double leftWheelDistance = (leftEncoderDelta * WHEEL_DIAMETER * M_PI) / ENCODER_COUNTS_PER_REV;
//     double rightWheelDistance = (rightEncoderDelta * WHEEL_DIAMETER * M_PI) / ENCODER_COUNTS_PER_REV;

//     // Calculate robot displacement and rotation
//     double displacement = (leftWheelDistance + rightWheelDistance) / 2.0;
//     double dTheta = (rightWheelDistance - leftWheelDistance) / WHEEL_TRACK;

//     // Update robot position and orientation
//     x += displacement * cos(theta);
//     y += displacement * sin(theta);
//     theta += dTheta;
// }

void move(int velocity) {
    // Set motor speeds for forward motion
    leftMotor.setSpeed(velocity);
    rightMotor.setSpeed(-velocity);
}

// void moveBackward(double distance) {
//     // Set motor speeds for backward motion
//     leftMotor.setSpeed(100);
//     rightMotor.setSpeed(100);
//     leftMotor.setDirection(false);
//     rightMotor.setDirection(false);

    // Move the robot the desired distance
//     double targetDistance = distance;
//     while (targetDistance > 0) {
//         updateOdometry();
//         targetDistance -= fabs(leftWheelDistance + rightWheelDistance) / 2.0;
//     }

//     // Stop the motors
//     leftMotor.stop();
//     rightMotor.stop();
// }

void rotate(double targetAngle) {
    leftMotor.setSpeed(velocity);
    rightMotor.setSpeed(velocity);
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


// PID LOOP - NEHA

// Initialize static variables (constants)
double setpoint = 0;           // Desired value (end location - static value)
double current_pos = 0;        // Actual value (as the robot is moving, NOT the start point - dynamic value)
double error = 0;
double inv_error = 0;
double velocity = 0;         // PID output speed
double velocity = 0;                // Robot's actual speed
long double e = 2.71828182846;      // e for exponential curve

// Initialize dynamic variables
int max_speed = 255;     // Maximum speed the robot is at before slowing down
int slowing_dist = 2;    // Robot will start to slow down when it reaches this distance from the setpoint
                         // (In the future, will want to make this a function of our current velocity)


// Initialization code can go here, pin descriptions, ect.
void setupPID() {
    setpoint = 10;      // Desired position
    current_pos = 0;    // Position that the robot is currently at
}


// Compute output
void updatePID() {
    // Error = distance the robot is away from the desired position
    error = setpoint - current_pos;
    inv_error = current_pos - setpoint;

    // Calculate the derivative of the error (goal is to stop at setpoint)
    if (error <= slowing_dist) {
        // Slow to a stop
        //velocity = (error * max_speed) / slowing_dist;      // Linearly
        velocity = max_speed - max_speed * pow(e, (error * inv_error));    // Exponentially (better)
    }
    else {
        // Maintain constant speed
        velocity = max_speed;
    }
}


// Define states as an enumeration
typedef enum {
    STOPPED = 0,
    DRIVING = 1,  // Rotating
    SPINNING = 2  // Going forward
} RobotState;

// Current state of the robot
RobotState state;

// Apply output - only when robot is RUNNING
void applyPID() {
    switch (state) {
        case SPINNING:
            update_rotation_PID();
            break;
        case DRIVING:
            update_driving_PID();
            break;
        case STOPPED:
            do_nothing();
            break;
    }
}

void update_rotation_PID() {
    // Update rotation based on PID control
    rotate(theta);  // theta = target angle from the PID
}

void update_driving_PID() {
    // Update driving based on PID control
    move(current_pos);  // Move forward to 'current_pos' as updated by PID
}

void do_nothing() {
    // No operation (used in STOPPED state)
}
