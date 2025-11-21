#ifndef QUEST_H
#define QUEST_H

#include <SFML/Graphics.hpp>
#include "CircleButton.h"
#include "Vector.h"
#include "RectangleButton.h"

class Character;

class Quest
{
private:
    sf::Sprite sprite, ticksprite;
    sf::Texture texture, ticktexture;

    CircleButton questButton;     // Nút mở menu
    RectangleButton exitButton;   // Nút đóng menu

    sf::Text notificationText;
    sf::Clock notificationClock;
    sf::Font font;

    Vector<int> target;
    Vector<int> progress;
    bool status[7] = { false };

    bool showMenu;
    bool showNotification;

public:
    Quest();

    void completeTask(int index);
    void addTarget(int index, Character& player);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    void showNotificationText(const std::string& text, sf::Color color);

    void draw(sf::RenderWindow& window); // Vẽ bảng nhiệm vụ (sprite)
};

#endif
