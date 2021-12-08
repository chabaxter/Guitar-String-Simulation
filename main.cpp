// Copyright Charles Baxter 2021

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "CircularBuffer.h"
#include "StringSound.h"

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(300, 200), "SFML Guitar Sim");
    sf::Event event;

    size_t notePos;
    std::string keys{ "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' " };

    std::vector<sf::Int16> vec_samples;
    std::vector<sf::Sound> sounds(keys.length());
    std::vector<sf::SoundBuffer> soundBuffers(keys.length());

    auto makeSamples = [&vec_samples](StringSound& sound) ->void {
        vec_samples.clear();
        sound.pluck();
        int duration = 8;  // seconds
        int i;
        for (i = 0; i < SAMPLES_PER_SEC * duration; i++) {
            sound.tic();
            vec_samples.push_back(sound.sample());
        }
    };

    for (uint16_t i = 0; i < keys.length(); i++) {
        StringSound ss(CONCERT_A * pow(2, (i - 24) / 12.0));
        makeSamples(ss);
        if (!soundBuffers[i].loadFromSamples(
            &vec_samples[0], vec_samples.size(), 2, SAMPLES_PER_SEC))
            throw std::runtime_error(
                "sf::SoundBuffer: failed to load from samples.");
        sounds[i].setBuffer(soundBuffers[i]);
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::TextEntered:
                notePos = keys.find(event.text.unicode);
                if (notePos != std::string::npos) {
                    sounds[notePos].play();
                }
                break;

            default:
                break;
            }

            window.clear();
            window.display();
        }
    }
    return 0;
}
