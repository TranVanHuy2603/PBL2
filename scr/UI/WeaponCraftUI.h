#define _HAS_STD_BYTE 0
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Weapons.h"   // de dung WeaponType
#include "Character.h"
#include "String.h"


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
    sf::Texture weaponTextures[(int)WeaponType::Count];
    WeaponButton weaponButtons[(int)WeaponType::Count];

    sf::CircleShape cartButton; // nut hinh tron (xe day)
    sf::Texture cartTexture;
    sf::Sprite cartIcon;

    bool showList; // hien thi danh sach vu khi

    sf::Text notificationText;
    sf::Clock notificationClock;
    bool showNotification = false;

public:
    WeaponCraftUI();

    void init();               // khoi tao nut xe day
    void initWeaponButtons();  // khoi tao cac nut vu khi
    void handleEvent(sf::Event& event, Character* player);
    void render(sf::RenderWindow& window);

    void showNotificationText(const std::string& text, sf::Color color);
};
