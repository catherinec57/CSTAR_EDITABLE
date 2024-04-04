#ifndef LiDAR_h //required to ensure no cicular imports
#define LiDAR_h

#include "Arduino.h"
#include <utility>
#include <queue>

using IntPair = std::pair<int, int>;

class LiDAR {
  public: 
    LiDAR(int& state, std::queue<IntPair>& AngleDistanceQueue); // change parameters based on what is required
     //define all methods

    void main();
    std::queue<IntPair>& AngleDistanceQueue;
    int& state;
};

#endif