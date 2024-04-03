#ifndef IO_h //required to ensure no cicular imports
#define IO_h

#include "Arduino.h"

class IO {
  public: 
    IO(int& state);
    void main();
    int& state;
};

#endif