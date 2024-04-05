#include "Arduino.h"
#include "UART.h"

UART_Handler::UART_Handler(int& state, IntQueue& position_queue) : 
    state(state),
    position_queue(position_queue) {
}

void UART_Handler::main() {
    // this task will handle all UART communications between ESP32s

  Serial.println("UART_handler");
}