#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>

class MainMenu
{
private:
    sf::Font font;
    sf::Text title;
    sf::Text startText;
    sf::Text exitText;
    sf::RectangleShape startBox;
    sf::RectangleShape exitBox;

   
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    MainMenu(float width, float height);
    void render(sf::RenderWindow& window);
    int handleEvent(sf::Event event, sf::RenderWindow& window);
};

#endif
