#include "Encoder.h" // make sure to include header !!!
#include <Arduino.h>
#include <utility>
#include <queue>
using IntPair = std::pair<int, int>;

Encoder::Encoder(int& state, std::queue<IntPair>& EncoderQueue, int& angle) : 
  state(state),
  EncoderQueue(EncoderQueue),
  angle(angle) { 
    // Initialization code here
  
}

void Encoder::main() {
  // Implement your function here
  Serial.println("Doing Something in Encoder");
}