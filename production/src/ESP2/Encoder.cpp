#include "Encoder.h"
#include <Arduino.h>

Encoder::Encoder(int CHA, int CHB) {
    _CHA = CHA;
    _CHB = CHB;
    _position = 0;

    // Attach interrupts to the encoder pins
    attachInterrupt(digitalPinToInterrupt(_CHA), handleInterrupt0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(_CHB), handleInterrupt1, CHANGE);
}

int Encoder::getPosition() {
    return _position;
}

void Encoder::reset() {
    _position = 0;
}

void Encoder::handleInterrupt() {
    if (digitalRead(_CHA) == digitalRead(_CHB)) {
        _position++;
    } else {
        _position--;
    }
}

void Encoder::handleInterrupt0() {
    QuadratureEncoder::getInstance()->handleInterrupt();
}

void Encoder::handleInterrupt1() {
    QuadratureEncoder::getInstance()->handleInterrupt();
}