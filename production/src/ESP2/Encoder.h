#ifndef Encoder_h //required to ensure no cicular imports
#define Encoder_h

#include "Arduino.h"
#include <queue>
#include <utility>

using IntPair = std::pair<int, int>;

class Encoder {
  public: 
    Encoder(int& state, std::queue<IntPair>& EncoderQueue, int& angle); // change parameters based on what is required
     //define all methods
    void main();
    //define all vars
    int& state;
    std::queue<IntPair>& EncoderQueue;
    int& angle;

};

#endif