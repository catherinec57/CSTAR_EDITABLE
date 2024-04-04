#ifndef UART_2_h //required to ensure no cicular imports
#define UART_2_h
#include <utility>
#include <queue>
using IntPair = std::pair<int, int>;

#include "Arduino.h"


class UART_2 {
  public: 
    UART_2(int& state, std::queue<IntPair>& DirectionsQueue); // change parameters based on what is required
     //define all methods
    void main();
    int& state;
    std::queue<IntPair>& DirectionsQueue;
};

#endif