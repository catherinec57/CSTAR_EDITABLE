#ifndef Bluetooth_h //required to ensure no cicular imports
#define Bluetooth_h

#include "Arduino.h"
#include "Queue.h"

class BluetoothController {
    public: 
    BluetoothController(IntQueue& audio_queue); // takes in audio queue to put audio data into 
     //define all methods
    void main();
    IntQueue* audio_queue;
};

#endif