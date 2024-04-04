#include "Motor_drive.h" // make sure to include header !!!
#include <Arduino.h>
#include <utility>
#include <queue>

using IntPair = std::pair<int, int>;

Motor::Motor(int& state, std::queue<IntPair>& DirectionsQueue, IntPair& current_position, int& angle, float& velocity) : 
  state(state),
  DirectionsQueue(DirectionsQueue),
  current_position(current_position),
  angle(angle),
  velocity(velocity) { 
    // Initialization code here
}

void Motor::main() {
  // This function should run the PID loop control of the motors based on the current position and rotation and the desired position and rotation

  Serial.println("Doing Something in Motor");
}