#include "WeaponMenu.h"

void WeaponMenu::create(int startX, int startY, Vector<std::string>& icon)
{
    buttons.clear();
    int w = 100;
    int h = 100;
    int dir = 20;

    for (int i = 0; i < icon.get_size(); i++)
    {
        WeaponButton wb;

        wb.rect.setPosition(startX, startY + i * (h + dir));
        wb.rect.setSize(sf::Vector2f(w, h));
        wb.rect.setFillColor(sf::Color(50,50,50));
        wb.rect.setOutlineColor(sf::Color::White);
        wb.rect.setOutlineThickness(2);

        wb.texture.loadFromFile(icon[i]);
        wb.icon.setTexture(wb.texture);
        wb.icon.setPosition(startX + 10, startY + i * (h + dir) + 10);
        wb.icon.setScale(0.8f, 0.8f);

        buttons.push_back(wb);
        
    };
}


void WeaponMenu::draw(sf::RenderWindow& window)
{
    if (!visible) return;

    for (auto& wb : buttons)
    {
        window.draw(wb.rect);
        window.draw(wb.label);
    }
}

void WeaponMenu::handleClick(int mouseX, int mouseY, Character* player)
{
    if (!visible) return;

    for (auto& wb : buttons)
    {
        if (wb.rect.getGlobalBounds().contains(mouseX, mouseY))
        {
            player.
        }
    }
}
