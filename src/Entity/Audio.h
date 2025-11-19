#ifndef AUDIO_H
#define AUDIO_H
#include "String.h"
#include <SFML/Audio.hpp>
#include <iostream>

class Audio {
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;

public:
    Audio();
    Audio(const String&);
    bool loadSound(const std::string &filename);
    void playSound();
    void stopSound();
    void setVolume(float volume);
    void setLoop(bool loop);
};

#endif
