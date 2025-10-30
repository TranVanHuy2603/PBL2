#pragma once
#define _HAS_STD_BYTE 0
#include "SFML/Graphics.hpp"
#include "String.h"

class UnitPanel
{
    sf::RectangleShape backgound;
    sf::Text unitInfo; // Username, HP, EP, Vu_Khi, Power (suc tan cong)
public:
    UnitPanel(const sf::Font &font);
    void update(const String &info);
    void draw(sf::RenderWindow &window);
};

