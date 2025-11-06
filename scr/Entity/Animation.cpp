#include "Animation.h"
#include <iostream>

// ==========================
// === HÀM KHỞI TẠO / HỦY ===
// ==========================

Animation::Animation()
    : texture(nullptr), frameDuration(0.1f), elapsedTime(0.f),
      currentFrame(sf::Vector2i(0, 0)), isPlaying(false), isLoop(true),
      frameNum(1, 1)
{
}

Animation::~Animation() {}

Animation::Animation(sf::Texture &texture, sf::Vector2i frameNum, float frameDuration)
{
    this->texture = &texture;
    this->frameNum = frameNum;
    this->frameDuration = frameDuration;
    this->elapsedTime = 0.f;
    this->currentFrame = sf::Vector2i(0, 0);
    this->isPlaying = false;
    this->isLoop = true;

    CalculateRectSize();
    CalculateRectUV();
    ApplyRect();
}

// ============================
// === HÀM TÍNH TOÁN FRAME ===
// ============================

void Animation::CalculateRectSize()
{
    if (!texture) return;
    rectSize.x = texture->getSize().x / frameNum.x;
    rectSize.y = texture->getSize().y / frameNum.y;
}

void Animation::CalculateRectUV()
{
    rectUV.x = currentFrame.x * rectSize.x;
    rectUV.y = currentFrame.y * rectSize.y;
}

void Animation::ApplyRect()
{
    if (!texture) return;
    setTexture(*texture);
    setTextureRect(sf::IntRect(rectUV.x, rectUV.y, rectSize.x, rectSize.y));
}

// ==========================
// === GETTER / SETTER ===
// ==========================

sf::Vector2i Animation::getCurrentFrameIndex() const
{
    return currentFrame;
}

void Animation::setTexture(const sf::Texture &texture)
{
    this->texture = &texture;
}

void Animation::addFrame(const sf::IntRect &rect)
{
    frames.push_back(rect);
}

void Animation::setFrameDuration(float duration)
{
    frameDuration = duration;
}

void Animation::setLoop(bool loop)
{
    isLoop = loop;
}

// ==========================
// === LOGIC CHÍNH ANIMATION ===
// ==========================

void Animation::play()
{
    isPlaying = true;
    currentFrame = sf::Vector2i(0, 0);
    elapsedTime = 0.f;
}

void Animation::stop()
{
    isPlaying = false;
}

void Animation::reset()
{
    currentFrame = sf::Vector2i(0, 0);
    elapsedTime = 0.f;
}

void Animation::update(float dt)
{
    if (!isPlaying || !texture) return;

    elapsedTime += dt;
    if (elapsedTime >= frameDuration)
    {
        elapsedTime -= frameDuration;
        currentFrame.x++;

        if (currentFrame.x >= frameNum.x)
        {
            currentFrame.x = 0;
            currentFrame.y++;

            if (currentFrame.y >= frameNum.y)
            {
                if (isLoop)
                {
                    currentFrame = sf::Vector2i(0, 0);
                }
                else
                {
                    currentFrame = sf::Vector2i(frameNum.x - 1, frameNum.y - 1);
                    isPlaying = false;
                }
            }
        }

        CalculateRectUV();
        ApplyRect();
    }
}

// ==========================
// === ÁP DỤNG VÀO SPRITE ===
// ==========================

// Giờ đây có thêm flipX để đảo chiều khi nhân vật quay trái
void Animation::applyToSprite(sf::Sprite &sprite, bool flipX)
{
    if (!texture) return;

    // Lưu lại các trạng thái cũ
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f scale = sprite.getScale();
    sf::Vector2f origin = sprite.getOrigin();
    sf::Color color = sprite.getColor();

    // Cập nhật texture và frame hiện tại
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(rectUV.x, rectUV.y, rectSize.x, rectSize.y));

    // === Flip X nếu cần ===
    if (flipX)
    {
        // Đảo chiều theo trục X bằng cách nhân scale.x với -1
        sprite.setScale(-std::abs(scale.x), scale.y);

        // Cập nhật origin để giữ vị trí đúng (đảo quanh tâm frame)
        sprite.setOrigin(rectSize.x, 0);
    }
    else
    {
        sprite.setScale(std::abs(scale.x), scale.y);
        sprite.setOrigin(0, 0);
    }

    // Khôi phục các thuộc tính còn lại
    sprite.setPosition(pos);
    sprite.setColor(color);
}

// ==========================
// === KIỂM TRA TRẠNG THÁI ===
// ==========================

bool Animation::isFinished() const
{
    return !isPlaying;
}
