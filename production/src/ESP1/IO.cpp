#include "IO.h" // make sure to include header !!!
#include <Arduino.h>

IO::IO(int& state) : 
    state(state) { 

  // Initialization code here
}

void IO::main() {
  // Implement your function 
  // render on the RGB the state of the robot where 0 = IDLE, 1 = RUNNING, 2 = ERROR
  //print the state
  Serial.println(state);
}