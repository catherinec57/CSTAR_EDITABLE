#ifndef Motor_h //required to ensure no cicular imports
#define Motor_h

#include "Arduino.h"

class Motor {
  public: 
    Motor(int pin); // change parameters based on what is required
     //define all methods
    void doSomething();
    //define all vars
    int var;
  private:
    int _pin; // define all private fields, _ designates private
};

#endif