#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class CharacterUI
{
private:
    const sf::Font &font;           // font chữ

    sf::Text infoText;       // góc trái: tài nguyên
    sf::Text topRightText;   // góc phải: coin, exp, level

    sf::RectangleShape hpBack;     // nền thanh HP
    sf::RectangleShape hpBar;      // phần HP còn
    sf::RectangleShape hpLostBar;  // phần HP đã mất
    sf::Text hpText;               // chữ hiển thị số HP

public:
    CharacterUI(const sf::Font& font);

    // cập nhật UI theo player
    void update(const Character* player, const sf::RenderTarget& target);

    // vẽ UI lên màn hình
    void render(sf::RenderTarget& target);
};
