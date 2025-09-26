#include <SFML/Graphics.hpp>
#include "WeaponMenu.h"
#include "Character.h"
#include "Bag.h"

int main() {
    // tao cua so
    sf::RenderWindow window(sf::VideoMode(800, 600), "Weapon Crafting Menu Test");

    // khoi tao nhan vat test
    Character player(100, 100, true, 100, 100, 1, 10, 0, 10);

    // them mot vai tai nguyen
    player.get_bag().add(ResourceType::Wood);
    player.get_bag().add(ResourceType::Wood);
    player.get_bag().add(ResourceType::Wood);
    player.get_bag().add(ResourceType::Coal);

    // tao menu
    WeaponMenu menu;
    menu.toggle(); // bat menu de test

    Vector<String> icons;
    Vector<WeaponType> types;

    // danh sach icon va loai vu khi
    icons.push_back("assets/Woodensword.png"); types.push_back(WeaponType::WoodenSword);
    icons.push_back("assets/Ironsword.png");   types.push_back(WeaponType::IronSwood);
    icons.push_back("assets/Ax.png");          types.push_back(WeaponType::Ax);
    icons.push_back("assets/Bow.png");         types.push_back(WeaponType::Bow);
    icons.push_back("assets/Gun.png");         types.push_back(WeaponType::Gun);

    // tao cac button trong menu
    menu.create(100, 100, icons, types);

    // khoi tao font va text thong bao
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Khong load duoc font\n";
    }
    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(18);
    message.setFillColor(sf::Color::Red);
    message.setPosition(250, 50);

    std::string msgText = "";

    // vong lap game
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // bam M de bat/tat menu
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                menu.toggle();
            }

            // click chuot trai
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {

                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                int before = player.get_weapons().get_size();
                menu.handleClick(mouseX, mouseY, &player);
                int after = player.get_weapons().get_size();

                if (after > before) {
                    msgText = "Crafted weapon successfully!";
                } else {
                    msgText = "Not enough resources!";
                }
                message.setString(msgText);
            }
        }

        // xoa man hinh
        window.clear(sf::Color::White);

        // ve menu
        menu.draw(window);

        // ve thong bao
        if (!msgText.empty()) window.draw(message);

        // hien thi len cua so
        window.display();
    }

    return 0;
}
