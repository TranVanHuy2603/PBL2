#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

struct Weapon {
    std::string name;
    int price;
    std::string imagePath;
};

struct WeaponButton {
    bool hasWeapon = false;
    Weapon weapon;
    sf::RectangleShape rect;
    sf::Text label;
};

int main()
{
    // Tạo cửa sổ
    sf::RenderWindow window(sf::VideoMode(1024, 768), "RTS Weapon Shop Menu");

    // Font chữ
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Cannot load font!\n";
        return -1;
    }

    // Tạo menu 3 ô trống
    std::vector<WeaponButton> menuButtons;
    int startX = 800;
    int startY = 50;
    int buttonWidth = 150;
    int buttonHeight = 100;
    int gap = 20;

    for (int i = 0; i < 3; i++) {
        WeaponButton wb;
        wb.rect.setPosition(startX, startY + i * (buttonHeight + gap));
        wb.rect.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        wb.rect.setFillColor(sf::Color(50, 50, 50));      // màu nền ô
        wb.rect.setOutlineColor(sf::Color::White);         // viền trắng
        wb.rect.setOutlineThickness(3);

        wb.label.setFont(font);
        wb.label.setString("Empty");
        wb.label.setCharacterSize(20);
        wb.label.setFillColor(sf::Color::White);
        wb.label.setPosition(startX + 20, startY + i * (buttonHeight + gap) + buttonHeight / 2 - 10);

        menuButtons.push_back(wb);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Click chuột
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                for (auto& wb : menuButtons) {
                    if (wb.rect.getGlobalBounds().contains(mouseX, mouseY)) {
                        if (wb.hasWeapon)
                            std::cout << "Buy weapon: " << wb.weapon.name << "\n";
                        else
                            std::cout << "This slot is empty!\n";
                    }
                }
            }
        }

        window.clear(sf::Color(20, 20, 20)); // nền tổng thể
        for (auto& wb : menuButtons) {
            window.draw(wb.rect);
            window.draw(wb.label);
        }
        window.display();
    }

    return 0;
}
