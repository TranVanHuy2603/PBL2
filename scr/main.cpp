#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponMenu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Weapon Menu (DEBUG)");
    window.setFramerateLimit(60);

    WeaponMenu menu;

    // Danh sách icon (hãy chắc chắn các file này tồn tại)
    Vector<String> icons;
    icons.push_back("assets/Woodensword.png");
    icons.push_back("assets/Ironsword.png");
    icons.push_back("assets/Ax.png");
    icons.push_back("assets/Bow.png");
    icons.push_back("assets/Gun.png");

    // Danh sách loại vũ khí tương ứng
    Vector<WeaponType> types;
    types.push_back(WeaponType::WoodenSword);
    types.push_back(WeaponType::IronSwood);
    types.push_back(WeaponType::Ax);
    types.push_back(WeaponType::Bow);
    types.push_back(WeaponType::Gun);

    std::cout << "Tao menu\n";
    menu.create(50, 50, icons, types);
    menu.toggle(); // bật menu luôn

    std::cout << "Menu da tao xong\n";

    // Vòng lặp chính
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(40, 40, 40)); // nền tối cho dễ nhìn
        menu.draw(window);
        window.display();
    }

    return 0;
}
