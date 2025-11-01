#pragma once
#include <SFML/Graphics.hpp>

class CameraController {
private:
    sf::View view;               // Camera chính
    sf::FloatRect worldBounds;   // Giới hạn map (theo pixel)
    float moveSpeed;             // tốc độ di chuyển camera
    float zoomLevel;             // mức zoom hiện tại

public:
    CameraController(const sf::Vector2f& windowSize, const sf::FloatRect& bounds);

    // Cập nhật theo input (phím / chuột)
    void handleInput(const sf::RenderWindow& window, float deltaTime);

    // Đặt vị trí camera theo nhân vật
    void follow(const sf::Vector2f& target);

    // Zoom
    void zoom(float factor);

    // Getter/Setter
    const sf::View& getView() const;
    void setCenter(const sf::Vector2f& center);

private:
    void clampToBounds(); // giữ camera trong map
};
