#ifndef Motor_h //required to ensure no cicular imports
#define Motor_h

#include "Arduino.h"
#include <utility>
#include <queue>

using IntPair = std::pair<int, int>;

class Motor {
  public: 
    Motor(int& state, std::queue<IntPair>& DirectionsQueue, IntPair& current_position, int& angle, float& velocity); // change parameters based on what is required
     //define all methods
    void main();
    //define all vars
    int& state;
    std::queue<IntPair>& DirectionsQueue;
    IntPair& current_position;
    int& angle;
    float& velocity;
};

#endif