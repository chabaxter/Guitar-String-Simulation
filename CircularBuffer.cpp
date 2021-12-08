// Copyright Charles Baxter 2021

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int capacity) : cap(capacity) {
    if (capacity < 1)
        throw std::invalid_argument(
            "CircularBuffer constructor: "
                "capacity must be greater than zero.\n");

    buffer = new int16_t[capacity];
}

int CircularBuffer::size() const {
    return numItems;
}

bool CircularBuffer::isEmpty() const {
    return numItems == 0;
}

bool CircularBuffer::isFull() const {
    return numItems == cap;
}

void CircularBuffer::enqueue(int16_t x) {
    if (isFull())
        throw std::runtime_error(
            "enqueue: can't enqueue to a full ring.\n");

    buffer[tail] = x;
    tail = ((tail + 1) == cap) ? 0 : tail + 1;
    numItems++;
}

int16_t CircularBuffer::dequeue() {
    if (isEmpty())
        throw std::runtime_error(
            "dequeue: can't dequeue from an empty ring.\n");

    int16_t retVal = buffer[head];
    head = ((head + 1) == cap) ? 0 : head + 1;
    numItems--;
    return retVal;
}

int16_t CircularBuffer::peek() const {
    if (isEmpty())
        throw std::runtime_error("peek: can't peek into an empty ring.\n");

    return buffer[head];
}

void CircularBuffer::clear() {
    head = tail = numItems = 0;
}

CircularBuffer::~CircularBuffer() {
    delete[] buffer;
}
