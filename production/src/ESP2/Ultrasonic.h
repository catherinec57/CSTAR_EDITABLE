#ifndef Ultrasonic_h //required to ensure no cicular imports
#define Ultrasonic_h

#include "Arduino.h"

class Ultrasonic {
  public: 
    Ultrasonic(int& state); // change parameters based on what is required
     //define all methods
    void main();
    int& state;
};

#endif