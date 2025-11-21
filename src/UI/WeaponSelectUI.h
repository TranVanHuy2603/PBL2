#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "RectangleButton.h"
#include "Character.h"
#include "Audio.h"

class WeaponSelectUI
{
private:
    Character* player;
    std::vector<RectangleButton> buttons;
    sf::Font font;
    sf::Text notificationText;
    sf::Clock notificationClock;
    bool showNotification;

    const float buttonWidth = 90.f;
    const float buttonHeight = 90.f;
    const float spacing = 10.f;
    const float margin = 10.f;

    void initButtons(sf::RenderWindow &window);

public:
    WeaponSelectUI(sf::RenderWindow &window, Character* player);

    void handleEvent(sf::Event &event, sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);

    void showNotificationText(const std::string &text, sf::Color color);
};
