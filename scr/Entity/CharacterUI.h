#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class CharacterUI
{
private:
    sf::Font font;           // font chu
    sf::Text infoText;       // text hien thi level, exp, gold

    sf::RectangleShape hpBack;     // nen thanh HP
    sf::RectangleShape hpBar;      // phan HP con
    sf::RectangleShape hpLostBar;  // phan HP da mat
    sf::Text hpText;               // chu hien thi so HP

public:
    CharacterUI();

    // cap nhat UI theo player
    void update(const Character* player, const sf::RenderTarget& target);

    // ve UI len man hinh
    void render(sf::RenderTarget& target);
};
