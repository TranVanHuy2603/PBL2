#include "Button.h"

// --- Constructor ---
Button::Button(const sf::Font &font, const std::string &text,
       sf::Vector2f position, sf::Vector2f size)
{
    // Dat mau mac dinh
    normalColor = sf::Color(70, 130, 180); // xanh duong nhat
    hoverColor = sf::Color(100, 180, 250); // xanh sang
    currentColor = normalColor;
    isHovered = false;

    // Tao nen cho nut
    box.setSize(size);
    box.setFillColor(this->currentColor);
    box.setPosition(position);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::White);

    // Set text
    this->label.setFont(font);
    this->label.setCharacterSize(18);
    this->label.setFillColor(sf::Color::White);
    this->label.setString(text);

    // Can giua
    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
    label.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);

}

// --- Cập nhật và vẽ ---
void Button::update(sf::RenderWindow &window, float deltaTime)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool hoverNow = isMouseOver(mousePos);

    // Nếu chuột hover -> chuyển màu dần
    if (hoverNow)
    {
        if (!isHovered) {
            isHovered = true; // vừa hover vào
        }
        // Chuyển màu mượt dần bằng nội suy tuyến tính
        currentColor.r += static_cast<int>((hoverColor.r - currentColor.r) * 5 * deltaTime);
        currentColor.g += static_cast<int>((hoverColor.g - currentColor.g) * 5 * deltaTime);
        currentColor.b += static_cast<int>((hoverColor.b - currentColor.b) * 5 * deltaTime);

        // Nếu click trái chuột
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (onClick) {
                onClick(); // Gọi callback
            }
        }
    }
    else
    {
        if (isHovered) {
            isHovered = false; // vừa rời khỏi nút
        }
        // Chuyển màu mượt trở lại
        currentColor.r += static_cast<int>((normalColor.r - currentColor.r) * 5 * deltaTime);
        currentColor.g += static_cast<int>((normalColor.g - currentColor.g) * 5 * deltaTime);
        currentColor.b += static_cast<int>((normalColor.b - currentColor.b) * 5 * deltaTime);
    }

    box.setFillColor(currentColor);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(this->box);
    window.draw(this->label);
}

// --- Sự kiện ---
void Button::setOnClick(std::function<void()> func) // Gán hàm click
{
    onClick = func;
}

// ===== Kiem tra hover =========
bool Button::isMouseOver(sf::Vector2i mousePos)
{
    return this->box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
