#ifndef MOTOR_H //required to ensure no cicular imports
#define MOTOR_H

#include "Arduino.h"

class Motor {
  public: 
    Motor(int PWM_SIGNAL_1, int PWM_SIGNAL_2);
    ~Motor();
    void setSpeed(int speed);
    void setDirection(bool direction);
    void stop();

  private:
    int PWM_SIGNAL_1;
    int PWM_SIGNAL_2;
};

#endif