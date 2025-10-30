#include "Animation.h"

Animation::Animation()
    : texture(nullptr), frameDuration(0.1f), elapsedTime(0.f),
    currentFrame(0), isPlaying(false), isLoop(true)
{

}
Animation::~Animation()
{

}

int Animation::getCurrentFrameIndex() const 
{
    return this->currentFrame;
}

void Animation::setTexture(const sf::Texture &texture)
{
    this->texture = &texture;
}

void Animation::addFrame(const sf::IntRect &rect) // Them frame
{
    frames.push_back(rect);
}

void Animation::setFrameDuration(float duration) // Thoi gian moi frame
{
    frameDuration = duration;
}

void Animation::setLoop(bool loop)
{
    isLoop = loop;
}

void Animation::play() // Xac nhan choi
{
    isPlaying = true;
    currentFrame = 0;
    elapsedTime = 0.0;
}

void Animation::stop()
{
    isPlaying = false;
}

void Animation::reset()
{
    currentFrame = 0;
    elapsedTime = 0.0;
}

void Animation::update(float dt)
{
    if(!isPlaying || frames.empty()) return;

    elapsedTime += dt;
    if(elapsedTime >= frameDuration) {
        elapsedTime -= frameDuration;
        currentFrame++;

        if(currentFrame >= static_cast<int>(frames.get_size())) {
            if(isLoop) currentFrame = 0;
            else {
                currentFrame = frames.get_size() - 1;
                isPlaying = false;
            }
        }
    }
}

void Animation::applyToSprite(sf::Sprite &sprite)
{
    if(!texture || frames.empty()) return;
    sprite.setTexture(*texture);
    sprite.setTextureRect(frames[currentFrame]);
}

bool Animation::isFinished() const
{
    return !isPlaying;
}