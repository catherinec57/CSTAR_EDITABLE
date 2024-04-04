#include "SensorFusion.h" // make sure to include header !!!
#include <Arduino.h>
#include <queue>
#include <utility>

using IntPair = std::pair<int, int>;

SensorFusion::SensorFusion(std::queue<IntPair>& AngleDistanceQueue) :
  AngleDistanceQueue(AngleDistanceQueue)  { //changing initialization 
}

void SensorFusion::main() {
  // if not empty
  if (!(AngleDistanceQueue.empty())) {
    IntPair AngleDistancePair = AngleDistanceQueue.front(); // Get the front item
    AngleDistanceQueue.pop(); // Remove the front item
    // Implement your function here
    int angle = AngleDistancePair.first;
    int distance = AngleDistancePair.second;
    Serial.print(angle);
    Serial .print(distance);
  }
}