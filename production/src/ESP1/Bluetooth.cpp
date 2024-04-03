#include "Bluetooth.h" // make sure to include header !!!
#include <Arduino.h>
#include "Queue.h"

BluetoothController::BluetoothController(int&state, IntQueue& audio_queue) : 
    state(state),  // directly assign these variables to attributes
    audio_queue(&audio_queue) { 
    //any other init goes here
}

void BluetoothController::main() {
  // Implement your function here
  // put a value in the queue
  int value;
  while (!(audio_queue->isEmpty())) {
    value = audio_queue->get();
    // do whatever you want with the value
    // Serial.println(value);
  }
  // update the state of the robot where 0 = IDLE, 1 = RUNNING, 2 = ERROR
  state = !state;
}