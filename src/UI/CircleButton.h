#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <SFML/Graphics.hpp>
#include "String.h"

class CircleButton
{
private:
    sf::CircleShape circle;
    sf::Texture iconTexture;
    sf::Sprite icon;

public:
    CircleButton();
    CircleButton(float radius);

    bool load(float radius);

    // SET
    void setPosition(float x, float y);
    void setColor(const sf::Color& color);
    void setOutline(const sf::Color& color, float thickness);
    void setIconScale(float sx, float sy);

    // GET
    bool isHover(sf::RenderWindow& window) const;
    bool isClicked(sf::RenderWindow& window, sf::Event event) const;

    // DRAW
    void render(sf::RenderWindow& window);
    bool setTexture(const String& iconPath);
};

#endif
