#include "CircleButton.h"
#include <iostream>

CircleButton::CircleButton() {}

CircleButton::CircleButton(float radius)
{
    load(radius);
}

bool CircleButton::load(float radius)
{
    // Setup circle
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setFillColor(sf::Color(150, 150, 150));
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::Black);

    return true;
}

void CircleButton::setPosition(float x, float y)
{
    circle.setPosition(x, y);
    icon.setPosition(x, y); // icon luôn nằm giữa nút
}

void CircleButton::setColor(const sf::Color& color)
{
    circle.setFillColor(color);
}

void CircleButton::setOutline(const sf::Color& color, float thickness)
{
    circle.setOutlineColor(color);
    circle.setOutlineThickness(thickness);
}

void CircleButton::setIconScale(float sx, float sy)
{
    icon.setScale(sx, sy);
}

bool CircleButton::isHover(sf::RenderWindow& window) const
{
    sf::Vector2f mouse(sf::Mouse::getPosition(window));
    sf::Vector2f center = circle.getPosition();
    float dx = mouse.x - center.x;
    float dy = mouse.y - center.y;

    return (dx * dx + dy * dy <= circle.getRadius() * circle.getRadius());
}

bool CircleButton::isClicked(sf::RenderWindow& window, sf::Event event) const
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        return isHover(window);
    }
    return false;
}

void CircleButton::render(sf::RenderWindow& window)
{
    window.draw(circle);
    window.draw(icon);
}

bool CircleButton::setTexture(const String& iconPath)
{
    if (!iconTexture.loadFromFile(iconPath.c_str()))
    {
        std::cerr << "Failed to load texture from: " << iconPath << std::endl;
        return false;
    }

    icon.setTexture(iconTexture);

    // Đặt origin icon ở giữa để dễ scale và position
    sf::FloatRect bounds = icon.getLocalBounds();
    icon.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    // Đặt icon ở giữa circle
    sf::Vector2f circlePos = circle.getPosition();
    float radius = circle.getRadius();
    icon.setPosition(circlePos.x, circlePos.y);

    return true;
}