#include "LiDAR.h" // make sure to include header !!!
#include <Arduino.h>
#include <queue>
#include <utility>

using IntPair = std::pair<int, int>;

LiDAR::LiDAR(int& state, std::queue<IntPair>& AngleDistanceQueue) : 
  AngleDistanceQueue(AngleDistanceQueue),
  state(state) {  
  // Initialization code here
}

void LiDAR::main() {
  // Implement your function here
  int angle = 1;
  int distance = 2;
  AngleDistanceQueue.push(IntPair(angle, distance)); // add some data in the form of a pair to the queue
  Serial.println("LiDAR Task Running");
}