#include "UnitPanel.h"

UnitPanel::UnitPanel(const sf::Font &font)
{
    // Nen Panel
    this->backgound.setSize(sf::Vector2f(250.f, 150.f));
    this->backgound.setFillColor(sf::Color(70, 70, 70, 200));
    this->backgound.setPosition(10.f, 60.f);

    // Text hien thi info unit
    this->unitInfo.setFont(font);
    this->unitInfo.setCharacterSize(18);
    this->unitInfo.setFillColor(sf::Color::White);

    // Thong so suc manh cua nhan vat luc dau
    this->unitInfo.setString("UserName: None\n HP: 0/0\n EP: 0/0\nVu_khi: None\t\tPower: 0");
}

void UnitPanel::update(const String &info)
{
    this->unitInfo.setString(info.String::c_str());
}

void UnitPanel::draw(sf::RenderWindow &window){
    window.draw(this->backgound);
    window.draw(this->unitInfo);
}
