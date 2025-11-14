#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation : public sf::Sprite {
private:
    const sf::Texture* texture;
    std::vector<sf::IntRect> frames;
    float frameDuration; // thoi gian giua 2 frame
    float elapsedTime; // Thoi gian tu cac khung hinh truoc den hien tai
    sf::Vector2i currentFrame; // Khung hinh hien tai
    bool isPlaying; // Animation dang hoat dong hay da dung
    bool isLoop; // Quyet dinh co lap lai animation / ko
    sf::Vector2i frameNum; // So fram theo hang va cot

    sf::Vector2i rectUV; // Toa do cua frame
    sf::Vector2i rectSize; // Kich thuoc fram

public:
    Animation();
    ~Animation();
    Animation(sf::Texture &texture, sf::Vector2i frameNum, float frameDuration);
    
    void CalculateRectSize();
    void CalculateRectUV();

    void ApplyRect();
    // ====== Get / Set =======
    sf::Vector2i getCurrentFrameIndex() const;
    void setTexture(const sf::Texture& texture);
    void addFrame(const sf::IntRect& rect);
    void setFrameDuration(float duration); // Thoi gian moi frame
    void setLoop(bool loop);

    // ====== Logic Function ========
    void play();
    void stop();
    void reset();
    void update(float dt);
    void applyToSprite(sf::Sprite& sprite, bool flipX);
    bool isFinished() const;
};
