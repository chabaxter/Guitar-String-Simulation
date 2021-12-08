// Copyright Charles Baxter 2021

#pragma once  //NOLINT

#include <stdint.h>
#include <stdexcept>

class CircularBuffer {
 public:
    explicit CircularBuffer(int capacity);

    int size() const;
    bool isEmpty() const;
    bool isFull() const;
    void enqueue(int16_t x);
    int16_t dequeue();
    int16_t peek() const;
    void clear();

    ~CircularBuffer();
 private:
    int16_t* buffer;
    int cap;
    int head{ 0 };
    int tail{ 0 };
    int numItems{ 0 };
};

