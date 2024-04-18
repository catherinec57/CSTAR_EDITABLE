#include "IO.h" // IO header file
#include <Arduino.h>

// Pin values from MCU Schematic
#define red_pin 21
#define green_pin 23
#define blue_pin 33

// Set colors for the RGB LED
void setYellow() {         // Idle = Yellow
    digitalWrite(red_pin, HIGH);
    digitalWrite(green_pin, HIGH);
    digitalWrite(blue_pin, LOW);
}
void setGreen() {         // Running = Green
    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, HIGH);
    digitalWrite(blue_pin, LOW);
}
void setRed() {          // Error = Red
    digitalWrite(red_pin, HIGH);
    digitalWrite(green_pin, LOW);
    digitalWrite(blue_pin, LOW);
}
void setBlue() {
  digitalWrite(blue_pin, HIGH);
  digitalWrite(green_pin, LOW);
  digitalWrite(red_pin, LOW);
}


// Enumerate states
enum State{
    IDLE = 0,     // When robot is idle/paused/not moving
    RUNNING = 1,  // When robot is running/moving
    ERROR = 2     // When robot runs into an error/is stopped
};


IO::IO(int& state) : 
    state(state) {
  // Initialization code - setup LED pins
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
}


void IO::main() {
  Serial.print(state);
  // Implement function
  // Render on the RGB the state of the robot where 0 = IDLE, 1 = RUNNING, 2 = ERROR

      switch(state){
          case IDLE:
              setBlue(); // When idle = set LED to Yellow
              break;

          case RUNNING:
              setGreen();  // When running -> set LED to Green
              break;

          case ERROR:
              setRed();    // When error -> set LED to Red
              break;
      }
}
