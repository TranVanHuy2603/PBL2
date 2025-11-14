#pragma once
#include "Animation.h"

class Effect
{
private:
    sf::Sprite sprite;
    Animation animation;
    bool finished;

public:
    Effect(sf::Texture& texture, sf::Vector2f position, int frameWidth, int frameHeight, int frameCount, float frameDuration);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isFinished() const;
};