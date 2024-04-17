#include "Bluetooth.h" // make sure to include header !!!
#include <Arduino.h>
#include "BluetoothSerial.h"

#include <utility>
#include <queue>

using IntPair = std::pair<int, int>;


BluetoothController::BluetoothController(int&state, std::queue<int>& audio_queue, std::queue<IntPair>& command_queue, BluetoothSerial& btSerial, IntPair &current_position) : 
    state(state),  // directly assign these variables to attributes
    audio_queue(audio_queue),
    command_queue(command_queue),
    SerialBT(btSerial),
    current_position(current_position){ 
        Serial.print("Bluetooth 1");
      #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
      #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
      #endif
      
    //any other init goes here
}

void BluetoothController::main() {
  Serial.println("Bluetooth working");

  // if there is data available over Bluetooth
  // read the data and add it to the command queue
  if (SerialBT.available()) { // this should be changed to adding actual commands into the queue
    char command = SerialBT.read();
    Serial.println(command);
    switch(command) {
      case 'F':
        // add the command to the queue
        command_queue.push(std::make_pair(0, 0));
        Serial.println("Pushing F");
        break;
      case 'R':
        command_queue.push(std::make_pair(1, 0));
        Serial.println("Pushing R");
        break;
    }
  }

  // stream current position over bluetooth
  SerialBT.print("Current Position: ");
  SerialBT.print(current_position.first);
  SerialBT.print(", ");
  SerialBT.print(current_position.second);
  SerialBT.print("\n");
  

  // int audioValue;
  // int xValue;
  // int yValue;
  // String finalString;
  // String audioStr;
  // while (!(audio_queue.empty()) && !(position_queue.empty())) {
  //   //while loop that adds value from audio queue into a string till queue is empty
  //   while(!(audio_queue.empty())) {
  //     audioStr.concat(String(audio_queue.front()));
  //     audio_queue.pop();
  //     audioStr.concat(", ");
  //   }
  //   //adding audio and position to one long string
  //   //NEED TO FIX GETTING POSITION DATA
  //   finalString.concat(audioStr);
  //   finalString.concat(String(position_queue.front().first));
  //   position_queue.pop();
  //   finalString.concat(", ");
  //   finalString.concat(String(position_queue.front().second));
  //   position_queue.pop();

  //   SerialBT.print(finalString);

  //   finalString = "";
  //   audioStr = "";
  //}
  //update the state of the robot where 0 = IDLE, 1 = RUNNING, 2 = ERROR
  state = 1;
}