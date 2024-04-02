#include <Arduino.h>
#include "Queue.h"

//define a default constructor
IntQueue::IntQueue() {
    this->buffer_length = 10;
    this->buffer = new int[this->buffer_length]; // by default, length is 10
    this->buffer_pointer = 0;
}

IntQueue::IntQueue(int buffer_length) { // take in the length to create the buffer void setup()
    // define a field buffer of length buffer_length
    this->buffer_length = buffer_length;
    this->buffer = new int[buffer_length];
    this->buffer_pointer = 0;
}

IntQueue::~IntQueue() { // during the destructor, delete the buffer
    delete[] this->buffer;
}

int IntQueue::get() { // get the next value in the queue
    // if the buffer is empty, return -1
    // Serial.print("Buffer Pointer in get");
    // Serial.println(this->buffer_pointer);
    if (this->buffer_pointer == 0) {
        Serial.println("Buffer is empty");
        return -1;
    }
    // return the first value of the buffer, then shift all the values to the left
    int value = this->buffer[0];
    for (int i = 0; i < this->buffer_length - 1; i++) {
        this->buffer[i] = this->buffer[i + 1];
    }
    // decrement the buffer pointer
    this->buffer_pointer--;
    return value;
}

int IntQueue::put(int value) { // put a value in the queue
    //if the buffer is not at the edge of the queue, put a value at the pointer, then increment the pointer
    if (this->buffer_pointer >= this->buffer_length) {
        Serial.print("Buffer is full");
        return -1;
    }
    this->buffer[this->buffer_pointer] = value;
    this->buffer_pointer++;
    return 1; //if successful
}
