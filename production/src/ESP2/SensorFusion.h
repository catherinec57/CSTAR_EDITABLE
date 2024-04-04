#ifndef SensorFusion_h //required to ensure no cicular imports
#define SensorFusion_h

#include "Arduino.h"
#include <utility>
#include <queue>

using IntPair = std::pair<int, int>;

class SensorFusion {
  public: 
    SensorFusion(int& state, std::queue<IntPair>& AngleDistanceQueue, std::queue<IntPair>& EncoderQueue, IntPair& current_position, int& angle, float& velocity); // change parameters based on what is required
     //define all methods
    void main();
    std::queue<IntPair>& AngleDistanceQueue;
    std::queue<IntPair>& EncoderQueue;
    int& state;
    IntPair& current_position;
    int& angle;
    float& velocity;
    
};

#endif