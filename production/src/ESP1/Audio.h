#ifndef Audio_h //required to ensure no cicular imports
#define Audio_h

#include "cppQueue.h"
#include "Arduino.h"
#include "Queue.h"

class Audio {
  public: 
    Audio(int& state, IntQueue& audio_queue); // takes in audio queue to put audio data into 
     //define all methods
    void main();
    int& state;
    IntQueue* audio_queue;
    int value = 0;

};

#endif