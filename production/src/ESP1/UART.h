#ifndef UART_h //required to ensure no cicular imports
#define UART_h

#include "Arduino.h"

class UART_Hander {
  public: 
    UART_handler(int& state);
    void main();
    int& state;
};

#endif