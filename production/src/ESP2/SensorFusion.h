#ifndef SensorFusion_h //required to ensure no cicular imports
#define SensorFusion_h

#include "Arduino.h"
#include <utility>
#include <queue>

using IntPair = std::pair<int, int>;

class SensorFusion {
  public: 
    SensorFusion(std::queue<IntPair>& AngleDistanceQueue); // change parameters based on what is required
     //define all methods
    void main();
    std::queue<IntPair>& AngleDistanceQueue;
};

#endif