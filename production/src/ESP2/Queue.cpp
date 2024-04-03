#include <Arduino.h>
#include "Queue.h"

// Default constructor
IntQueue::IntQueue() {
    buffer_length = 10;
    buffer = new int[buffer_length];
    head = 0;
    tail = 0;
    count = 0;
}

// Constructor with specific size
IntQueue::IntQueue(int buffer_length) {
    this->buffer_length = buffer_length;
    buffer = new int[this->buffer_length];
    head = 0;
    tail = 0;
    count = 0;
}

// Destructor
IntQueue::~IntQueue() {
    delete[] buffer;
}

// Remove and return the next value from the queue
int IntQueue::get() {
    if (count == 0) {
        Serial.println("Buffer is empty");
        return -1;
    }
    int value = buffer[head];
    head = (head + 1) % buffer_length;
    count--;
    return value;
}

// Add a value to the queue
int IntQueue::put(int value) {
    if (count >= buffer_length) {
        Serial.println("Buffer is full");
        return -1;
    }
    buffer[tail] = value;
    tail = (tail + 1) % buffer_length;
    count++;
    return 1;
}

// Peek at the next value without removing it
int IntQueue::peek() {
    if (count == 0) {
        Serial.println("Buffer is empty");
        return -1;
    }
    return buffer[head];
}

bool IntQueue::isEmpty() {
    return count == 0;
}



// all the Float Queue methods are the same as the Int Queue methods, just with float instead of int lol
FloatQueue::FloatQueue() {
    buffer_length = 10;
    buffer = new float[buffer_length];
    head = 0;
    tail = 0;
    count = 0;
}

FloatQueue::FloatQueue(int buffer_length) {
    this->buffer_length = buffer_length;
    buffer = new float[this->buffer_length];
    head = 0;
    tail = 0;
    count = 0;
}

FloatQueue::~FloatQueue() {
    delete[] buffer;
}

float FloatQueue::get() {
    if (count == 0) {
        Serial.println("Buffer is empty");
        return -1;
    }
    float value = buffer[head];
    head = (head + 1) % buffer_length;
    count--;
    return value;
}

int FloatQueue::put(float value) {
    if (count >= buffer_length) {
        Serial.println("Buffer is full");
        return -1;
    }
    buffer[tail] = value;
    tail = (tail + 1) % buffer_length;
    count++;
    return 1;
}


float FloatQueue::peek() {
    if (count == 0) {
        Serial.println("Buffer is empty");
        return -1;
    }
    return buffer[head];
}


bool FloatQueue::isEmpty() {
    return count == 0;
}

