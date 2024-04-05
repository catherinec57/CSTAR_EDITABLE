#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor {
  public: 
    Motor(int PWM_SIGNAL_1, int PWM_SIGNAL_2);
    ~Motor();
    void setSpeed(int speed);
    void setDirection(bool clockwise);
    void stop();

  private:
    int _PWM_SIGNAL_1;
    int _PWM_SIGNAL_2;
};

#endif