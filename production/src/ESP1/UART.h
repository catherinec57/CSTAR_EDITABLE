#ifndef UART_h //required to ensure no cicular imports
#define UART_h
#include <utility>
#include <queue>
#include "Arduino.h"
#include <SoftwareSerial.h>
using IntPair = std::pair<int, int>;

class UART_Handler {
  public: 
    UART_Handler(int& state, std::queue<IntPair>& command_queue, IntPair &current_position, SoftwareSerial &SwSerial);
    void main();
    int& state;
    std::queue<IntPair>& command_queue;
    SoftwareSerial &SwSerial;
    IntPair &current_position;
};

#endif