// Copyright Charles Baxter 2021

#include "StringSound.h"

StringSound::StringSound(double frequency)
    : _time(0) {
    if (frequency <= 0)
        throw std::runtime_error(
            "StringSound: frequency must be greater than 0");
    _cb = new CircularBuffer(std::ceil(SAMPLES_PER_SEC / frequency));
}

StringSound::StringSound(const std::vector<sf::Int16>& init) :
    _time(0),
    _cb(new CircularBuffer(init.size())) {
    for (uint16_t i = 0; i < init.size(); i++) {
        _cb->enqueue(init[i]);
    }
}

StringSound::StringSound(StringSound&& obj) noexcept : _time(0), _cb(obj._cb) {
    obj._cb = nullptr;
}

void StringSound::pluck() {
    unsigned s = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine eng(s);
    std::uniform_int_distribution<int16_t> int16_dist(-32768, 32767);
    _cb->clear();
    while (!_cb->isFull()) {
        _cb->enqueue(int16_dist(eng));
    }
}

void StringSound::tic() {
    if (_cb->size() < 2)
        throw std::runtime_error
            ("tic: can't operate with less than two points");

    int16_t newVal = _cb->dequeue();
    newVal = (newVal + _cb->peek()) * ENERGY_DECAY_FACTOR * 0.5;
    _cb->enqueue(newVal);

    _time++;
}

sf::Int16 StringSound::sample() {
    if (_cb->isEmpty())
        throw std::runtime_error("sample: can't sample an empty buffer");

    return _cb->peek();
}

int StringSound::time() {
    return _time;
}


StringSound::~StringSound() {
    delete _cb;
}
