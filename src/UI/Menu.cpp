#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height, String text0, String text1, String text2)
{
    if (!backgroundTexture.loadFromFile("assets/background/backgroundmenu.png"))
        std::cerr << "Error loading background image\n";
    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u texSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        width / (float)texSize.x,
        height / (float)texSize.y
    );

    if (!font.loadFromFile("assets/font/font2.ttf"))
        std::cerr << "Error loading font\n";

    title.setFont(font);
    title.setString(text0.c_str());
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::Yellow);

    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2, tb.height / 2);
    title.setPosition(width / 2, height / 3);

    btn1 = RectangleButton(
        width / 2 - 150, height / 2 - 35,
        350, 90,
        &font, text1,
        sf::Color(100, 200, 100),   
        sf::Color(130, 230, 130),  sf::Color(80, 180, 80),
        50      // click
    );
    btn1.setTextColor(sf::Color::Black);

    btn2 = RectangleButton(
        width / 2 - 150, height / 2 + 85,
        350, 90,
        &font, text2,
        sf::Color(200, 100, 100),
        sf::Color(230, 130, 130),
        sf::Color(180, 80, 80),
        50
    );
    btn2.setTextColor(sf::Color::Black);
}

void Menu::render(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);

    btn1.update(window);
    btn2.update(window);

    window.draw(title);
    btn1.render(window);
    btn2.render(window);
}

int Menu::handleEvent(sf::Event event, sf::RenderWindow &window)
{
    if (btn1.isClicked(window, event)) return 1;
    if (btn2.isClicked(window, event)) return 2;

    return 0;
}
