#include "Bluetooth.h" // make sure to include header !!!
#include <Arduino.h>
#include "Queue.h"

BluetoothController::BluetoothController(IntQueue& audio_queue) : audio_queue(&audio_queue) { //changing initialization 
//   this->audio_queue = audio_queue;
  // Initialization code here
}

void BluetoothController::main() {
  // Implement your function here
  Serial.println("Doing Something in Bluetooth Controller");
  // put a value in the queue
  int value = this->audio_queue->get();
  Serial.print("Got this value fromt the Q:");
  Serial.println(value);
}