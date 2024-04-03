#include "Arduino.h"
#include "UART.h"

UART_handler::UART_handler(int& state) : 
    state(state) {
}

void UART_handler::main() {
    // this task will handle all UART communications between ESP32s

  Serial.println("UART_handler");
}