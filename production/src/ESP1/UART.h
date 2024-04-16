#ifndef UART_h //required to ensure no cicular imports
#define UART_h
#include <utility>
#include <queue>
#include "Arduino.h"
using IntPair = std::pair<int, int>;

class UART_Handler {
  public: 
    UART_Handler(int& state, std::queue<IntPair>& position_queue);
    void main();
    int& state;
    std::queue<IntPair>& position_queue;
};

#endif