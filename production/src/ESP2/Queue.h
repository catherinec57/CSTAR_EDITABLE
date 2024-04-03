#ifndef Queue_h //required to ensure no cicular imports
#define Queue_h

#include "Arduino.h"

class IntQueue {
    private:
        int* buffer;
        int buffer_length;
        int head;
        int tail;
        int count;

    public:
        IntQueue();
        IntQueue(int buffer_length);
        ~IntQueue();
        int get();
        int put(int value);
        int peek();
        bool isEmpty();
};


// basically duplicate for the Float Queue
class FloatQueue {
    private:
        float* buffer;
        int buffer_length;
        int head;
        int tail;
        int count;

    public:
        FloatQueue();
        FloatQueue(int buffer_length);
        ~FloatQueue();
        float get();
        int put(float value);
        float peek();
        bool isEmpty();
};

#endif