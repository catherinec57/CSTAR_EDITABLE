#include "SensorFusion.h" // make sure to include header !!!
#include <Arduino.h>
#include <queue>
#include <utility>

using IntPair = std::pair<int, int>;

SensorFusion::SensorFusion(int& state, std::queue<IntPair>& AngleDistanceQueue, std::queue<IntPair>& EncoderQueue, IntPair& current_position, int& angle, float& velocity) :
  AngleDistanceQueue(AngleDistanceQueue),
  state(state),
  EncoderQueue(EncoderQueue),
  current_position(current_position),
  angle(angle),
  velocity(velocity) { //changing initialization 
}

void SensorFusion::main() {
  // IMPLEMENT LOOP HERE (will be called by wrapper in a loop)

  // if not empty
  if (!(AngleDistanceQueue.empty())) {
    // read from the angle distance queue
    IntPair AngleDistancePair = AngleDistanceQueue.front(); // Get the front item
    AngleDistanceQueue.pop(); // Remove the front item
    int angle = AngleDistancePair.first;
    int distance = AngleDistancePair.second;
    Serial.print(angle);
    Serial .print(distance);
  }
}