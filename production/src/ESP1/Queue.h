#ifndef Queue_h //required to ensure no cicular imports
#define Queue_h

#include "Arduino.h"

class IntQueue {
    public: 
        IntQueue();
        IntQueue(int buffer_length); // take in the length to create the buffer void setup()
        ~IntQueue();
        int get(); // get the next value in the queue
        int put(int value); // put a value in the queue
        //define buffer based on input buffer length
        int* buffer;
        int buffer_pointer;
        int buffer_length;
};


class StringQueue {
    public:
        StringQueue(int buffer_length);
        String get();
        int put(String value);
};

class FloatQueue {
    public:
        FloatQueue(int buffer_length);
        float get();
        int put(float value);
};

#endif