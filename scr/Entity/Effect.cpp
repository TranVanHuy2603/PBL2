#include "Effect.h"

Effect::Effect(sf::Texture& texture, sf::Vector2f position, int frameWidth, int frameHeight, int frameCount, float frameDuration)
    : finished(false)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);

    animation.setTexture(texture);
    for (int i = 0; i < frameCount; ++i) {
        animation.addFrame(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
    }
    animation.setFrameDuration(frameDuration);
    animation.setLoop(false); // Hiệu ứng không lặp lại
    animation.play();
}

void Effect::update(float dt)
{
    if (!finished) {
        animation.update(dt);
        animation.applyToSprite(sprite, false);
        if (animation.isFinished()) {
            finished = true;
        }
    }
}

void Effect::draw(sf::RenderWindow& window)
{
    if (!finished) {
        window.draw(sprite);
    }
}

bool Effect::isFinished() const
{
    return finished;
}