#pragma once
#include <SFML/Graphics.hpp>
#include <Vector.h>

class Animation {
private:
    const sf::Texture* texture;
    Vector<sf::IntRect> frames;
    float frameDuration; // thoi gian giua 2 frame
    float elapsedTime; // Thoi gian tu cac khung hinh truoc den hien tai
    int currentFrame; // Khung hinh hien tai
    bool isPlaying; // Animation dang hoat dong hay da dung
    bool isLoop; // Quyet dinh co lap lai animation / ko

public:
    Animation();
    ~Animation();
    int getCurrentFrameIndex() const;
    void setTexture(const sf::Texture& texture);
    void addFrame(const sf::IntRect& rect);
    void setFrameDuration(float duration); // Thoi gian moi frame
    void setLoop(bool loop);
    void play();
    void stop();
    void reset();
    void update(float dt);
    void applyToSprite(sf::Sprite& sprite);
    bool isFinished() const;
};
