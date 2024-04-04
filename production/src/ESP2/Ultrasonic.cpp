#include "Ultrasonic.h" // make sure to include header !!!
#include <Arduino.h>

Ultrasonic::Ultrasonic(int& state) : state(state) { //changing initialization 
}

void Ultrasonic::main() {
  // Implement your function here
  Serial.println("Doing Something in Ultrasonic");
}