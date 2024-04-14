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
  int xValue;
  int yValue;
  String finalString;
  while (!(audio_queue.isEmpty()) && !(position_queue.isEmpty())) {
    //while loop that adds value from audio queue into a string till queue is empty
    String audioStr;
    while(!(audio_queue.isEmpty())) {
      audioStr.concat(String(audio_queue.get()));
      audioStr.concat(", ");
    }
    //adding audio and position to one long string
    //NEED TO FIX GETTING POSITION DATA
    finalString.concat(audioStr);
    finalString.concat(String(position_queue.get()));
    finalString.concat(", ");
    finalString.concat(String(position_queue.get()));

    SerialBT.print(finalString);

    finalString = "";
    audioStr = "";
  }
  // update the state of the robot where 0 = IDLE, 1 = RUNNING, 2 = ERROR
  state = !state;
}