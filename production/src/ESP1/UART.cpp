#include "Arduino.h"
#include "UART.h"
#include <utility>
#include <queue>

using Intpair = std::pair<int, int>;


UART_Handler::UART_Handler(int& state, std::queue<IntPair>& position_queue) : 
    state(state),
    position_queue(position_queue) {
}

void UART_Handler::main() {
    // this task will handle all UART communications between ESP32s
  Serial.println("UART_handler");
}