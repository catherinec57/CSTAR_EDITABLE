#include "Bluetooth.h" // make sure to include header !!!
#include <Arduino.h>
#include "Queue.h"



BluetoothController::BluetoothController(int&state, IntQueue& audio_queue, IntQueue& position_queue) : 
    state(state),  // directly assign these variables to attributes
    audio_queue(audio_queue),
    position_queue(position_queue) { 
      #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
      #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
      #endif
      BluetoothSerial SerialBT;
    //any other init goes here
}

void BluetoothController::main() {
  // Implement your function here
  // put a value in the queue
  int audioValue;
  int posValue;
  while (!(audio_queue.isEmpty())) {
    audioValue = audio_queue.get();
    SerialBT.print(audioValue);
  }
  while (!(position_queue.isEmpty())) {
    posValue = position_queue.get();
    SerialBT.print(posValue);
  }
  // update the state of the robot where 0 = IDLE, 1 = RUNNING, 2 = ERROR
  state = !state;
}