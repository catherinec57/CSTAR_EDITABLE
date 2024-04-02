#include "Audio.h" // make sure to include header !!!
#include <Arduino.h>
#include "Queue.h"

Audio::Audio(IntQueue& audio_queue) : audio_queue(&audio_queue) { //changing initialization 
  // this->audio_queue = audio_queue;
}

void Audio::main() {
  // Implement your function here
  Serial.println("Doing Something in Audio");
  // put a value in the queue
  this->audio_queue->put(1);
}