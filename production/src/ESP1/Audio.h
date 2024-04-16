#ifndef Audio_h //required to ensure no cicular imports
#define Audio_h

#include "Arduino.h"

#include <queue>
#include <utility>

class Audio {
  public: 
    Audio(int& state, std::queue<int>& audio_queue); // takes in audio queue to put audio data into 
     //define all methods
    void main();
    int& state;
    std::queue<int>& audio_queue;
    int value = 0;

};

#endif