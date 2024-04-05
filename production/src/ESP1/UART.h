#ifndef UART_h //required to ensure no cicular imports
#define UART_h

#include "Arduino.h"
#include "Queue.h"

class UART_Handler {
  public: 
    UART_Handler(int& state, IntQueue& position_queue);
    void main();
    int& state;
    IntQueue& position_queue;
};

#endif