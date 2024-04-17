#include "Arduino.h"
#include "UART.h"
#include <utility>
#include <queue>
#include <SoftwareSerial.h>

using Intpair = std::pair<int, int>;


UART_Handler::UART_Handler(int& state, std::queue<IntPair>& command_queue, IntPair &current_position, SoftwareSerial &SwSerial) : 
    state(state),
    command_queue(command_queue),
    current_position(current_position),
    SwSerial(SwSerial){
  // Initialization code - setup UART pins
  //definitions
    
    SwSerial.begin(9600);
}

void UART_Handler::main() {
  // check to see if there is any data available on the command queue
  if (!command_queue.empty()) {
    // get the next command from the queue
    IntPair command = command_queue.front();
    command_queue.pop();
    // send the command to the robot
    switch(command.first) {
      case 0:
        // send a UART message over SWSerial
        Serial.println("sending F");
        SwSerial.write('F');
        break;
      case 1:
        Serial.println("sending R");
        SwSerial.write('R');
        break;
    }
  }
}