#include "RectangleButton.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

RectangleButton::RectangleButton(float x, float y, float width, float height,
                                 sf::Font* font, const String& str,
                                 sf::Color normal, sf::Color hover, sf::Color click,
                                 int size)
{
    this->font = font;

    // Hình chữ nhật
    shape.setPosition(x, y);
    shape.setSize({ width, height });
    normalColor = normal;
    hoverColor = hover;
    clickColor = click;
    shape.setFillColor(normalColor);

    // Text
    text.setFont(*font);
    text.setString(str.c_str());
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2.f);

    // Căn giữa text
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    text.setPosition(x + width / 2.f, y + height / 2.f);
}

bool RectangleButton::isMouseOver(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    return mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
           mousePos.y >= pos.y && mousePos.y <= pos.y + size.y;
}

bool RectangleButton::isClicked(sf::RenderWindow& window, sf::Event& event)
{
    return isMouseOver(window) &&
           event.type == sf::Event::MouseButtonPressed &&
           event.mouseButton.button == sf::Mouse::Left;
}

void RectangleButton::update(sf::RenderWindow& window)
{
    if (isMouseOver(window))
        shape.setFillColor(hoverColor);
    else
        shape.setFillColor(normalColor);
}

void RectangleButton::render(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(icon);
    window.draw(text);
}

// ===== SETTER =====
void RectangleButton::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    // Cập nhật text theo vị trí mới
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    text.setPosition(x + shape.getSize().x / 2.f, y + shape.getSize().y / 2.f);
}

void RectangleButton::setTextPosition(float x, float y)
{
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    text.setPosition(x, y);
}

void RectangleButton::setSize(float w, float h)
{
    shape.setSize({ w, h });
    // Cập nhật text theo size mới
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    text.setPosition(shape.getPosition().x + w / 2.f, shape.getPosition().y + h / 2.f);
}

void RectangleButton::setString(const String& str)
{
    text.setString(str.c_str());
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    text.setPosition(shape.getPosition().x + shape.getSize().x / 2.f,
                     shape.getPosition().y + shape.getSize().y / 2.f);
}

void RectangleButton::setFillColor(const sf::Color& col)
{
    shape.setFillColor(col);
}

void RectangleButton::setOutline(const sf::Color& col, float thickness)
{
    shape.setOutlineColor(col);
    shape.setOutlineThickness(thickness);
}

void RectangleButton::setTextColor(const sf::Color& color)
{
    text.setFillColor(color);
}

void RectangleButton::setFont(sf::Font* f)
{
    font = f;
    text.setFont(*f);
}

bool RectangleButton::setIcon(const String& path)
{
    if (!iconTexture.loadFromFile(path.c_str()))
        return false; // load thất bại

    icon.setTexture(iconTexture);
    // đặt icon mặc định ở góc trái của button
    icon.setPosition(shape.getPosition().x + 5.f, shape.getPosition().y + 5.f);
    return true;
}

void RectangleButton::setIconScale(float scaleX, float scaleY)
{
    icon.setScale(scaleX, scaleY);

    // Cập nhật lại vị trí icon nếu cần căn vào giữa button
    sf::FloatRect iconBounds = icon.getLocalBounds();
    icon.setOrigin(iconBounds.width / 2.f, iconBounds.height / 2.f);
    icon.setPosition(
        shape.getPosition().x + shape.getSize().x / 2.f,
        shape.getPosition().y + shape.getSize().y / 2.f
    );
}
