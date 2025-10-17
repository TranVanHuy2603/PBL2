#include "CharacterUI.h"
#include <sstream>
#include <iostream>

CharacterUI::CharacterUI()
{
    // Tải font chữ
    if (!font.loadFromFile("assets/font/font1.ttf"))
        std::cerr << "Error loading font" << std::endl;

    // Góc trái: thông tin tài nguyên
    infoText.setFont(font);
    infoText.setCharacterSize(30);
    infoText.setFillColor(sf::Color::Red);
    infoText.setOutlineColor(sf::Color::Black);
    infoText.setOutlineThickness(1.f);
    infoText.setPosition(10.f, 10.f);

    // Góc phải: Coin, EXP, Level
    topRightText.setFont(font);
    topRightText.setCharacterSize(35);
    topRightText.setFillColor(sf::Color::Red);
    topRightText.setOutlineColor(sf::Color::Black);
    topRightText.setOutlineThickness(1.f);

    // Nền thanh HP
    hpBack.setSize(sf::Vector2f(400.f, 20.f));
    hpBack.setFillColor(sf::Color(50, 50, 50));
    hpBack.setOutlineThickness(2.f);
    hpBack.setOutlineColor(sf::Color::Black);

    // Thanh HP còn
    hpBar.setFillColor(sf::Color::Green);

    // Thanh HP đã mất
    hpLostBar.setFillColor(sf::Color(200, 200, 200));

    // Chữ HP
    hpText.setFont(font);
    hpText.setCharacterSize(25);
    hpText.setFillColor(sf::Color::Black);
}

void CharacterUI::update(const Character *player, const sf::RenderTarget &target)
{
    // ==== Góc trái: tài nguyên ====
    std::stringstream ss;
    ss << "Wood  " << player->get_bag().getWood()
       << "\nStone " << player->get_bag().getStone()
       << "\nSand  " << player->get_bag().getSand()
       << "\nCoal  " << player->get_bag().getCoal()
       << "\nIron  " << player->get_bag().getIron()
       << "\nGold  " << player->get_bag().getGold()
       << "\nDiamond " << player->get_bag().getDiamond()
       << "\nEmerald " << player->get_bag().getEmerald();
    infoText.setString(ss.str());

    // ==== Góc phải: Coin + EXP + Level ====
    std::stringstream topSS;
    topSS << "Level " << player->get_level()
          << "\nCoin  " << player->get_gold()
          << "\nEXP   " << player->get_exp() << " / " << player->get_exp_max();
    topRightText.setString(topSS.str());

    // Căn phải
    sf::Vector2u winSize = target.getSize();
    sf::FloatRect bounds = topRightText.getLocalBounds();
    topRightText.setPosition(winSize.x - bounds.width - 20.f, 10.f);

    // === Thanh HP ===
    float hpPercent = static_cast<float>(player->get_hp()) / player->get_hp_max();
    float barWidth = 400.f, barHeight = 20.f;

    // Căn giữa dưới
    hpBack.setPosition((winSize.x - barWidth) / 2.f, winSize.y - barHeight - 20.f);

    // HP còn
    hpBar.setSize(sf::Vector2f(barWidth * hpPercent, barHeight));
    hpBar.setPosition(hpBack.getPosition());

    // Đổi màu theo HP
    if (hpPercent > 0.5f)
        hpBar.setFillColor(sf::Color::Green);
    else if (hpPercent > 0.25f)
        hpBar.setFillColor(sf::Color::Yellow);
    else
        hpBar.setFillColor(sf::Color::Red);

    // HP đã mất
    hpLostBar.setSize(sf::Vector2f(barWidth * (1.f - hpPercent), barHeight));
    hpLostBar.setPosition(hpBack.getPosition().x + hpBar.getSize().x, hpBack.getPosition().y);

    // Chữ HP
    std::stringstream hpSS;
    hpSS << player->get_hp() << " / " << player->get_hp_max();
    hpText.setString(hpSS.str());
    sf::FloatRect textBounds = hpText.getLocalBounds();
    hpText.setOrigin(textBounds.left + textBounds.width / 2.f,
                     textBounds.top + textBounds.height / 2.f);
    hpText.setPosition(
        hpBack.getPosition().x + barWidth / 2.f,
        hpBack.getPosition().y + barHeight / 2.f - 1.f);
}

void CharacterUI::render(sf::RenderTarget &target)
{
    target.draw(infoText);     // Góc trái
    target.draw(topRightText); // Góc phải
    target.draw(hpBack);
    target.draw(hpLostBar);
    target.draw(hpBar);
    target.draw(hpText);
}
