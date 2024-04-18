#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int PWM_SIGNAL_1, int PWM_SIGNAL_2) {
    _PWM_SIGNAL_1 = PWM_SIGNAL_1;
    _PWM_SIGNAL_2 = PWM_SIGNAL_2;
    pinMode(_PWM_SIGNAL_1, OUTPUT);
    pinMode(_PWM_SIGNAL_2, OUTPUT);
}

// void Motor::setSpeed(int speed) {
//     analogWrite(_PWM_SIGNAL_1, speed);
//     analogWrite(_PWM_SIGNAL_2, speed);
// }

void Motor::setDirection(bool clockwise) {
    if (clockwise) {
        digitalWrite(_PWM_SIGNAL_1, HIGH);
        digitalWrite(_PWM_SIGNAL_2, LOW);
    } else {
        digitalWrite(_PWM_SIGNAL_1, LOW);
        digitalWrite(_PWM_SIGNAL_2, HIGH);
    }
}

void Motor::stop() {
    setSpeed(0);
}