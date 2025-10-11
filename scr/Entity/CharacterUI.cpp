#include "CharacterUI.h"
#include <sstream>
#include <iostream>

CharacterUI::CharacterUI()
{
    // tai font chu
    if (!font.loadFromFile("assets/font/arial.ttf"))
        std::cerr << "error" << std::endl;

    // thiet lap thong tin o goc tren tren
    infoText.setFont(font);
    infoText.setCharacterSize(25);
    infoText.setFillColor(sf::Color::Red);
    infoText.setPosition(10.f, 10.f);

    // nen thanh HP
    hpBack.setSize(sf::Vector2f(400.f, 20.f));
    hpBack.setFillColor(sf::Color(50, 50, 50)); // mau nau dam
    hpBack.setOutlineThickness(2.f);
    hpBack.setOutlineColor(sf::Color::Black);

    // thanh HP con
    hpBar.setFillColor(sf::Color::Red);

    // thanh HP da mat
    hpLostBar.setFillColor(sf::Color(200, 200, 200)); // mau xam

    // chu hien thi so HP
    hpText.setFont(font);
    hpText.setCharacterSize(16);
    hpText.setFillColor(sf::Color::Black);
}

void CharacterUI::update(const Character *player, const sf::RenderTarget &target)
{
    // cap nhat thong tin o goc tren trai
    std::stringstream ss;
    ss << "    Wood: " << player->get_bag().getWood()
       << "    Stone: " << player->get_bag().getStone()
       << "    Sand: " << player->get_bag().getSand()
       << "    Coal: " << player->get_bag().getCoal()
       << "    Iron: " << player->get_bag().getIron()
       << "    Gold: " << player->get_bag().getGold()
       << "    Diamond: " << player->get_bag().getDiamond()
       << "    Emerald: " << player->get_bag().getEmerald()
       << "             "
       << "    EXP: " << player->get_exp() << " / " << player->get_exp_max()
       << "    Coin: " << player->get_gold()
       << "    Level: " << player->get_level()
       
    ;
    infoText.setString(ss.str());

    // tinh ti le HP
    float hpPercent = static_cast<float>(player->get_hp()) / player->get_hp_max();
    float barWidth = 400.f;
    float barHeight = 20.f;

    // vi tri thanh HP can giua man hinh
    sf::Vector2u winSize = target.getSize();
    hpBack.setPosition((winSize.x - barWidth) / 2.f, winSize.y - barHeight - 20.f);

    // cap nhat thanh HP con
    hpBar.setSize(sf::Vector2f(barWidth * hpPercent, barHeight));
    hpBar.setPosition(hpBack.getPosition());

    // cap nhat thanh HP da mat
    hpLostBar.setSize(sf::Vector2f(barWidth * (1.f - hpPercent), barHeight));
    hpLostBar.setPosition(hpBack.getPosition().x + hpBar.getSize().x, hpBack.getPosition().y);

    // cap nhat chu HP
    std::stringstream hpSS;
    hpSS << player->get_hp() << " / " << player->get_hp_max();
    hpText.setString(hpSS.str());

    // canh giua chu trong thanh
    sf::FloatRect textBounds = hpText.getLocalBounds();
    hpText.setOrigin(textBounds.left, textBounds.top); // reset origin
    hpText.setPosition(
        hpBack.getPosition().x + (barWidth - textBounds.width) / 2.f,
        hpBack.getPosition().y + (barHeight - textBounds.height) / 2.f - 3.f);
}

void CharacterUI::render(sf::RenderTarget &target)
{
    target.draw(infoText);
    target.draw(hpBack);
    target.draw(hpLostBar); // ve phan da mat truoc
    target.draw(hpBar);     // ve phan con len tren
    target.draw(hpText);
}
