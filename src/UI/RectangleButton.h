#pragma once
#include <SFML/Graphics.hpp>
#include "String.h"

class RectangleButton
{
private:
    sf::RectangleShape shape;
    sf::Text text;

    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color clickColor;

    sf::Font* font;

    sf::Texture iconTexture;
    sf::Sprite icon;

public:
    RectangleButton() = default;

    RectangleButton(float x, float y, float width, float height,
                    sf::Font* font, const String& str,
                    sf::Color normal = sf::Color(80, 80, 80),
                    sf::Color hover  = sf::Color(120, 120, 120),
                    sf::Color click  = sf::Color(160, 160, 160),
                    int size = 32);

    bool isMouseOver(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window, sf::Event& event);

    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    // ======= SETTER =======
    void setPosition(float x, float y);
    void setTextPosition(float x, float y);
    void setSize(float w, float h);
    void setString(const String& str);
    void setFillColor(const sf::Color& col);
    void setOutline(const sf::Color& col, float thickness);
    void setTextColor(const sf::Color& color);
    void setFont(sf::Font* f);
    bool setIcon(const String& path); // load từ file
    void setIconScale(float scaleX, float scaleY);

    // ======= GETTER =======
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};
