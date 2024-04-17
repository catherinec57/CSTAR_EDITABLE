#ifndef Bluetooth_h //required to ensure no cicular imports
#define Bluetooth_h

#include "Arduino.h"

#include "BluetoothSerial.h"
#include <utility>
#include <queue>

using IntPair = std::pair<int, int>;

class BluetoothController {
    public: 
    BluetoothController(int& state, std::queue<int>& audio_queue, std::queue<IntPair>& position_queue, BluetoothSerial& btSerial); // takes in audio queue to put audio data into 
     //define all methods
    void main();
    int& state;
    std::queue<int>& audio_queue;
    std::queue<IntPair>& position_queue;
    BluetoothSerial& SerialBT;
};

#endif