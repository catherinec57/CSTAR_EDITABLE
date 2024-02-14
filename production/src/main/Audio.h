#ifndef Audio_h //required to ensure no cicular imports
#define Audio_h

#include "Arduino.h"

class Audio {
  public: 
    Audio(int pin); // change parameters based on what is required
     //define all methods
    void doSomething();
    //define all vars
    int var;
  private:
    int _pin; // define all private fields, _ designates private
};

#endif