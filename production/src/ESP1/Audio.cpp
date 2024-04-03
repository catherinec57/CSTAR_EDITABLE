#include "Audio.h" // make sure to include header !!!
#include <Arduino.h>
#include "Queue.h"

Audio::Audio(int& state, IntQueue& audio_queue) : 
    state(state),
    audio_queue(&audio_queue) { //changing initialization 
  // this->audio_queue = audio_queue;
}

void Audio::main() {
  // Implement your function here
  // put a value in the queue
  audio_queue->put(value);
  value++;
}