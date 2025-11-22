#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class CharacterUI
{
private:
    sf::Font font;

    // Thanh nguyên liệu
    sf::RectangleShape resourceBar;           
    sf::Sprite resourceIcons[8];              
    sf::Texture resourceTextures[8];          
    int resourceAmounts[8];                   

    // Level + Coin + EXP
    sf::Text topRightText;

    // Thanh HP
    sf::RectangleShape hpBack;
    sf::RectangleShape hpBar;
    sf::RectangleShape hpLostBar;
    sf::Text hpText;
    sf::Text hp;
    
    // Lives
    sf::Texture livesTexture;
    sf::Sprite livesIcon;

public:
    CharacterUI();

    void update(const Character* player, const sf::RenderTarget& target);
    void render(sf::RenderTarget& target, Character* player);
};
