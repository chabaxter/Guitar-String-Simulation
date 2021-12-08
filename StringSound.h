// Copyright Charles Baxter 2021

#pragma once  //NOLINT

#include <vector>
#include <cmath>
#include <random>
#include <chrono>  //NOLINT

#include <SFML/System.hpp>

#include "CircularBuffer.h"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100
#define ENERGY_DECAY_FACTOR 0.993

class StringSound {
 public:
    explicit StringSound(double frequency);
    explicit StringSound(const std::vector<sf::Int16>& init);
    StringSound(const StringSound& obj) = delete;

    StringSound(StringSound&& obj) noexcept;

    void pluck();
    void tic();
    sf::Int16 sample();
    int time();

    ~StringSound();
 private:
    int _time;
    CircularBuffer* _cb;
};
