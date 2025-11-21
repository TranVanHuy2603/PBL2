#pragma once
#include <SFML/Graphics.hpp>
#include "Weapons.h"   // de dung WeaponType
#include "Character.h"
#include "String.h"
#include "CircleButton.h"
#include "RectangleButton.h"
#include <iostream>

struct WeaponInfo
{
    String name;
    String iconPath;
};

// luu thong tin ve nut hien thi tung vu khi
struct WeaponButton
{
    WeaponType type;
    sf::RectangleShape button;
    sf::Sprite icon;
    sf::Text nameText;
};

class WeaponCraftUI
{
private:
    sf::Font font;
    sf::Text craftTitleText;

    RectangleButton weaponButtons[(int)WeaponType::Count];
    CircleButton cartButton;

    bool showList; // hien thi danh sach vu khi

    sf::Text notificationText;
    sf::Clock notificationClock;
    bool showNotification = false;

public:
    WeaponCraftUI(sf::RenderWindow&);

    void initWeaponButtons(sf::RenderWindow&);  // khoi tao cac nut vu khi
    void handleEvent(sf::Event& event, Character* player, sf::RenderWindow& window);
    void drawRecipeText(sf::RenderWindow& window, RectangleButton &btn, Recipe &r, Bag &bag);
    void render(sf::RenderWindow& window, Character*);

    void showNotificationText(const std::string& text, sf::Color color);
};
