#include "CharacterUI.h"
#include <sstream>
#include <iostream>

CharacterUI::CharacterUI()
{
    // Tải font chữ
    if (!font.loadFromFile("assets/font/font2.ttf"))
        std::cerr << "Error loading font" << std::endl;

    // Tải icon nguyên liệu
    String resourceFiles[8] = {
        "assets/resource/wood.png",
        "assets/resource/stone.png",
        "assets/resource/sand.png",
        "assets/resource/coal.png",
        "assets/resource/iron.png",
        "assets/resource/gold.png",
        "assets/resource/diamond.png",
        "assets/resource/emerald.png"
    };

    for (int i = 0; i < 8; i++)
    {
        if (!resourceTextures[i].loadFromFile(resourceFiles[i].c_str()))
            std::cerr << "Error loading " << resourceFiles[i] << std::endl;
        resourceIcons[i].setTexture(resourceTextures[i]);
        resourceIcons[i].setScale(30.f / resourceTextures[i].getSize().x, 30.f / resourceTextures[i].getSize().y);
    }

    // Level + Coin + EXP
    topRightText.setFont(font);
    topRightText.setCharacterSize(18);
    topRightText.setFillColor(sf::Color::White);
    topRightText.setOutlineColor(sf::Color::Black);
    topRightText.setOutlineThickness(2.f);
    topRightText.setStyle(sf::Text::Bold);

    // Thanh HP
    hpBack.setSize(sf::Vector2f(400.f, 20.f));
    hpBack.setFillColor(sf::Color(50, 50, 50));
    hpBack.setOutlineThickness(2.f);
    hpBack.setOutlineColor(sf::Color::Black);

    hpBar.setFillColor(sf::Color::Green);
    hpLostBar.setFillColor(sf::Color(200, 200, 200));

    hpText.setFont(font);
    hpText.setCharacterSize(18);
    hpText.setFillColor(sf::Color::White);

    hp.setFont(font);
    hp.setString("HP");
    hp.setCharacterSize(18);
    hp.setFillColor(sf::Color::White);
    hp.setOutlineColor(sf::Color::Black);
    hp.setOutlineThickness(2.f);
    hp.setStyle(sf::Text::Bold);

    // Lives
    if (!livesTexture.loadFromFile("assets/icon/lives.png"))
        std::cerr << "Error loading lives icon" << std::endl;
    livesIcon.setTexture(livesTexture);
    livesIcon.setScale(0.065f, 0.065f);
}

void CharacterUI::update(const Character* player, const sf::RenderTarget& target)
{
    sf::Vector2u winSize = target.getSize();

    // ==== Thanh nguyên liệu (xám) ở góc trên trái ====
    float startX = 0.f, startY = 0.f;
    float barHeight = 45.f;
    float barWidth = winSize.x - 2 * startX;

    resourceBar.setSize(sf::Vector2f(barWidth, barHeight));
    resourceBar.setFillColor(sf::Color(80, 80, 80, 220));
    resourceBar.setPosition(startX, startY);

    // Cập nhật số lượng nguyên liệu
    resourceAmounts[0] = player->get_bag().getWood();
    resourceAmounts[1] = player->get_bag().getStone();
    resourceAmounts[2] = player->get_bag().getSand();
    resourceAmounts[3] = player->get_bag().getCoal();
    resourceAmounts[4] = player->get_bag().getIron();
    resourceAmounts[5] = player->get_bag().getGold();
    resourceAmounts[6] = player->get_bag().getDiamond();
    resourceAmounts[7] = player->get_bag().getEmerald();

    // Icon và số lượng sát cạnh trên thanh
    float iconSize = 30.f;
    float spacing = 50.f; // sát nhau
    for (int i = 0; i < 8; i++)
    {
        resourceIcons[i].setScale(iconSize / resourceTextures[i].getSize().x,
                                  iconSize / resourceTextures[i].getSize().y);
        resourceIcons[i].setPosition(startX + 5.f + i * (iconSize + spacing), startY + 5.f);
    }

    // ==== Level / Coin / EXP (trên cùng bên phải) ====
    std::stringstream ss;
    ss << "Level: " << player->get_level()
       << "    Coin: " << player->get_gold()
       << "    EXP: " << player->get_exp() << " / " << player->get_exp_max();
    topRightText.setString(ss.str());
    topRightText.setCharacterSize(17);
    sf::FloatRect textBounds = topRightText.getLocalBounds();
    topRightText.setPosition(winSize.x - textBounds.width - 15.f, 15.f); // căn góc trên phải

    // ==== Thanh HP ở giữa phía dưới ====
    float hpPercent = static_cast<float>(player->get_hp()) / player->get_hp_max();
    float hpBarWidth = 400.f, hpBarHeight = 25.f;
    hpBack.setSize(sf::Vector2f(hpBarWidth, hpBarHeight));
    hpBack.setPosition((winSize.x - hpBarWidth) / 2.f, winSize.y - hpBarHeight - 80.f);

    hpBar.setSize(sf::Vector2f(hpBarWidth * hpPercent, hpBarHeight));
    hpBar.setPosition(hpBack.getPosition());

    hpLostBar.setSize(sf::Vector2f(hpBarWidth * (1.f - hpPercent), hpBarHeight));
    hpLostBar.setPosition(hpBack.getPosition().x + hpBar.getSize().x, hpBack.getPosition().y);

    if (hpPercent > 0.5f) hpBar.setFillColor(sf::Color::Green);
    else if (hpPercent > 0.25f) hpBar.setFillColor(sf::Color::Yellow);
    else hpBar.setFillColor(sf::Color::Red);

    // HP text
    std::stringstream hpSS;
    hpSS << player->get_hp() << " / " << player->get_hp_max();
    hpText.setString(hpSS.str());
    hpText.setOutlineColor(sf::Color::Black);
    hpText.setStyle(sf::Text::Bold);
    hpText.setOutlineThickness(2.f);
    textBounds = hpText.getLocalBounds();
    hpText.setOrigin(textBounds.left + textBounds.width / 2.f,
                     textBounds.top + textBounds.height / 2.f);
    hpText.setPosition(hpBack.getPosition().x + hpBarWidth / 2.f,
                       hpBack.getPosition().y + hpBarHeight / 2.f);

    hp.setPosition(hpBack.getPosition().x - 50.f, hpBack.getPosition().y + 5.f);
}



void CharacterUI::render(sf::RenderTarget& target, Character* player)
{
    // ==== Thanh nguyên liệu + icon + số lượng ====
    target.draw(resourceBar);
    for (int i = 0; i < 8; i++)
    {
        target.draw(resourceIcons[i]);
        sf::Text amountText;
        amountText.setFont(font);
        amountText.setCharacterSize(16);
        amountText.setStyle(sf::Text::Bold);
        amountText.setOutlineThickness(2.f);
        amountText.setOutlineColor(sf::Color::Black);
        amountText.setFillColor(sf::Color::White);
        amountText.setString(std::to_string(resourceAmounts[i]));
        amountText.setPosition(resourceIcons[i].getPosition().x + 20.f, resourceIcons[i].getPosition().y + 20.f);
        target.draw(amountText);
    }

    // ==== Level + Coin + EXP ====
    target.draw(topRightText);

    // ==== Thanh HP ====
    target.draw(hpBack);
    target.draw(hpLostBar);
    target.draw(hpBar);
    target.draw(hpText);
    target.draw(hp);

    // ==== Lives ====
    sf::Vector2f hpPos = hpBack.getPosition();
    float barWidth = hpBack.getSize().x;
    float iconSpacing = 30.f;

    for (int i = 0; i < player->get_lives(); i++)
    {
        livesIcon.setPosition(hpPos.x + barWidth + 30.f + i * (livesIcon.getGlobalBounds().width * 0.065 + iconSpacing),
                              hpPos.y + (hpBack.getSize().y - 30) / 2.f);
        target.draw(livesIcon);
    }
}
