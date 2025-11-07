#include <iostream>
#include "MainMenu.h"


MainMenu::MainMenu(float width, float height, const sf::Font &font)
{
    // === ẢNH NỀN ===
    if (!backgroundTexture.loadFromFile("assets/background/backgroundmenu.png"))
        std::cerr << "Error loading background image\n";
    backgroundSprite.setTexture(backgroundTexture);

    // Scale cho vừa cửa sổ (1920x1080)
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        width / static_cast<float>(textureSize.x),
        height / static_cast<float>(textureSize.y)
    );

    // === FONT VÀ CHỮ ===
    title.setFont(font);
    title.setString("PBL2 GAME RTS");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::Yellow);
    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2, tb.height / 2);
    title.setPosition(width / 2, height / 3);

    startBox.setSize({300, 70});
    startBox.setOrigin(150, 35);
    startBox.setPosition(width / 2, height / 2);
    startBox.setFillColor(sf::Color(100, 200, 100));

    startText.setFont(font);
    startText.setString("Bat dau");
    startText.setCharacterSize(40);
    sf::FloatRect sb = startText.getLocalBounds();
    startText.setOrigin(sb.width / 2, sb.height / 2);
    startText.setPosition(width / 2, height / 2 - 5);
    startText.setFillColor(sf::Color::Black);

    exitBox.setSize({300, 70});
    exitBox.setOrigin(150, 35);
    exitBox.setPosition(width / 2, height / 2 + 120);
    exitBox.setFillColor(sf::Color(200, 100, 100));

    exitText.setFont(font);
    exitText.setString("Thoat");
    exitText.setCharacterSize(40);
    sf::FloatRect eb = exitText.getLocalBounds();
    exitText.setOrigin(eb.width / 2, eb.height / 2);
    exitText.setPosition(width / 2, height / 2 + 115);
    exitText.setFillColor(sf::Color::Black);
}

void MainMenu::render(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);

    window.draw(title);
    window.draw(startBox);
    window.draw(exitBox);
    window.draw(startText);
    window.draw(exitText);
}

MenuAction MainMenu::handleEvent(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));
        if (startBox.getGlobalBounds().contains(mouse))
            return MenuAction::START_GAME; // Trả về giá trị enum
        if (exitBox.getGlobalBounds().contains(mouse))
            return MenuAction::EXIT_GAME; // Trả về giá trị enum
    }
    return MenuAction::NONE;
}
