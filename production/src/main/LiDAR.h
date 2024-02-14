#ifndef LiDAR_h //required to ensure no cicular imports
#define LiDAR_h

#include "Arduino.h"

class LiDAR {
  public: 
    LiDAR(int pin); // change parameters based on what is required
     //define all methods
    void doSomething();
    //define all vars
    int var;
  private:
    int _pin; // define all private fields, _ designates private
};

#endif