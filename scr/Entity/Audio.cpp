#include "Audio.h"

Audio::Audio(){}

Audio::Audio(const String &filename) {
    if (!buffer.loadFromFile(filename.c_str())) {
        std::cerr << "Không thể tải âm thanh từ file: " << filename << std::endl;
    }
    sound.setBuffer(buffer);
}

bool Audio::loadSound(const std::string &filename) {
    if (!buffer.loadFromFile(filename)) {
        return false;
    }
    sound.setBuffer(buffer);
    return true;
}

void Audio::playSound() {
    sound.play();
}

void Audio::stopSound() {
    sound.stop();
}

void Audio::setVolume(float volume) {
    sound.setVolume(volume); 
}

void Audio::setLoop(bool loop) {
    sound.setLoop(loop);
}
