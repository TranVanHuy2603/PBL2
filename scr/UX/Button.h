#pragma once
#include <SFML/Graphics.hpp>
#include <functional>  // để dùng callback (std::function)
#include "String.h"

class Button {
private:
    sf::RectangleShape box;   // Nền nút
    sf::Text label;           // Chữ hiển thị
    sf::Color normalColor;    // Màu mặc định
    sf::Color hoverColor;     // Màu khi hover
    sf::Color currentColor;   // Màu hiện tại (dùng cho hiệu ứng chuyển mượt)

    bool isHovered;           // Trạng thái hover
    std::function<void()> onClick;  // Callback khi click

public:
    // --- Constructor ---
    Button(const sf::Font &font, const std::string &text,
            sf::Vector2f position, sf::Vector2f size);

    // --- Cập nhật và vẽ ---
    void update(sf::RenderWindow &window, float deltaTime);
    void draw(sf::RenderWindow &window);

    // --- Sự kiện ---
    void setOnClick(std::function<void()> func);  // Gán hàm click
    bool isMouseOver(sf::Vector2i mousePos);      // Kiểm tra hover
};
