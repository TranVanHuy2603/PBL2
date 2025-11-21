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
    infoText.setCharacterSize(40);
    infoText.setFillColor(sf::Color::Red);
    infoText.setOutlineColor(sf::Color::Black);
    infoText.setOutlineThickness(1.f);
    infoText.setPosition(10.f, 10.f);

    // Góc phải: Coin, EXP, Level
    topRightText.setFont(font);
    topRightText.setCharacterSize(40);
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

    hp.setFont(font);
    hp.setString("HP");
    hp.setCharacterSize(40);
    hp.setFillColor(sf::Color::Black);

    livesTexture.loadFromFile("assets/icon/lives.png");
    livesIcon.setTexture(livesTexture);
    livesIcon.setScale(0.065, 0.065);
}

void CharacterUI::update(const Character *player, const sf::RenderTarget &target)
{
    // ==== Góc trái: tài nguyên ====
    std::stringstream ss;
    ss << "Go: " << player->get_bag().getWood()
       << "    Da: " << player->get_bag().getStone()
       << "    Cat: " << player->get_bag().getSand()
       << "    Than: " << player->get_bag().getCoal()
       << "    Sat: " << player->get_bag().getIron()
       << "    Vang: " << player->get_bag().getGold()
       << "    KCuong: " << player->get_bag().getDiamond()
       << "    NgocLB: " << player->get_bag().getEmerald();
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
    hpBack.setPosition((winSize.x - barWidth) / 2.f, winSize.y - barHeight - 80.f);

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

    sf::Vector2f hpPos = hpBack.getPosition();
    // Căn giữa theo chiều cao thanh
    hp.setPosition(hpPos.x - 40.f, hpPos.y - barHeight);
}

void CharacterUI::render(sf::RenderTarget &target, Character *player)
{
    target.draw(infoText);     // Góc trái
    target.draw(topRightText); // Góc phải
    target.draw(hpBack);
    target.draw(hpLostBar);
    target.draw(hpBar);
    target.draw(hpText);
    target.draw(hp);

    sf::Vector2f hpPos = hpBack.getPosition(); // Góc trái thanh HP
    float barWidth = hpBack.getSize().x;
    float barHeight = hpBack.getSize().y;

    float iconSpacing = 30.f; 
    float iconSize = 0.05f;  

    float startX = hpPos.x + barWidth + 30.f;
    float startY = hpBack.getPosition().y + (hpBack.getSize().y - 30) / 2.f;

    for (int i = 0; i < player->get_lives(); i++)
    {
        livesIcon.setPosition(startX + i * (livesIcon.getGlobalBounds().width * iconSize + iconSpacing), startY);
        target.draw(livesIcon);
    }
}
