#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include "String.h"
#include "RectangleButton.h"

class Menu
{
private:
    sf::Font font;
    sf::Text title;

    RectangleButton btn1;
    RectangleButton btn2;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    Menu(float width, float height, String titleStr,
         String btn1Str, String btn2Str);

    void render(sf::RenderWindow& window);
    int handleEvent(sf::Event event, sf::RenderWindow& window);
};

#endif
