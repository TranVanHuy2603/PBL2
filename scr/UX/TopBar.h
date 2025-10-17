#pragma once

#include "SFML/Graphics.hpp"

class TopBar {
    sf::RectangleShape background; // hình chữ nhật làm nền
    sf::Text resourcesText;        // text hiển thị tài nguyên
public:
    TopBar(const sf::Font &font, sf::Vector2u windowSize);
    void update(int gold, int wood, int Dimond); // cập nhật giá trị tài nguyên
    void draw(sf::RenderWindow &window); // vẽ lên màn hình
};
