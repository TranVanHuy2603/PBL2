#include "TopBar.h"
#include "String.h"

TopBar::TopBar(const sf::Font &font, sf::Vector2u windowSize)
{
    // Tao backgound cho thanh
    this->background.setSize(sf::Vector2f(static_cast <float> (windowSize.x), 50.f));
    this->background.setFillColor(sf::Color(50, 50, 50, 200)); // Mau xam mo
    this->background.setPosition(0, 0);

    // Tao icon hien thi tai nguyen
    resourcesText.setFont(font);
    resourcesText.setCharacterSize(20);
    resourcesText.setPosition(10.f, 10.f);
    resourcesText.setFillColor(sf::Color::White);

    // Init first data
    resourcesText.setString("Gold: 0    Wood: 0     Dimond: 0 ");

}
void TopBar::update(int gold, int wood, int Dimond)     // cập nhật giá trị tài nguyên
{
    this->resourcesText.setString((String("Gold: ") + String::to_string(gold) + "\t\t" + 
    String("Wood: ") + String::to_string(wood) + "\t\t" + String("Dimond: ") + 
    String::to_string(Dimond)).String::c_str());
} 

void TopBar::draw(sf::RenderWindow &window) // vẽ lên màn hình
{
    window.draw(this->background);
    window.draw(this->resourcesText);
}