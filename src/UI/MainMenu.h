#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>

enum class MenuAction {
    NONE,
    START_GAME,
    EXIT_GAME
};

class MainMenu
{
private:
    sf::Text title;
    sf::Text startText;
    sf::Text exitText;
    sf::RectangleShape startBox;
    sf::RectangleShape exitBox;

   
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    MainMenu(float width, float height, const sf::Font &font);
    void render(sf::RenderWindow& window);
    MenuAction handleEvent(sf::Event event, sf::RenderWindow& window);
};

#endif
