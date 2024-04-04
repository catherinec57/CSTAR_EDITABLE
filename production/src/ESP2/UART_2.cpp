#include "UART_2.h" // make sure to include header !!!
#include <Arduino.h>
#include <utility>
#include <queue>
using IntPair = std::pair<int, int>;

UART_2::UART_2(int& state, std::queue<IntPair>& DirectionsQueue) :
  state(state),
  DirectionsQueue(DirectionsQueue) { //changing initialization 
}

void UART_2::main() {
  // Implement your function here
  Serial.println("Doing Something in UART_2");
}