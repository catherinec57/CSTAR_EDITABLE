#ifndef Audio_h //required to ensure no cicular imports
#define Audio_h

#include "Arduino.h"
#include "Queue.h"

class Audio {
  public: 
    Audio(IntQueue& audio_queue); // takes in audio queue to put audio data into 
     //define all methods
    void main();
    IntQueue* audio_queue;
};

#endif