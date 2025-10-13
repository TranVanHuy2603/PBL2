#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Castle.h"
#include "Character.h"

class UpgradeCastleUI
{
private:
    sf::Font font;
    sf::CircleShape houseButton; // nut hinh tron
    sf::Texture houseTexture;
    sf::Sprite houseIcon;

    sf::RectangleShape upgradeButton;
    sf::RectangleShape cancelButton;
    sf::Text upgradeText;
    sf::Text cancelText;

    // hien thi chi phi nang cap
    sf::Text costText;

    bool showMenu;

    // Thong bao
    sf::Text notificationText;
    bool showNotification = false;
    sf::Clock notificationClock;

public:
    UpgradeCastleUI();

    void handleEvent(sf::Event &event, Character *player, Castle *castle);
    void render(sf::RenderWindow &window);
    void showNotificationText(const std::string &text, sf::Color color);
};
