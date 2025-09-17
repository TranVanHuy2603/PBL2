#include <SFML/Graphics.hpp>
#include <iostream>
#include "EntityManager.h"
#include "Character.h"
#include "Map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 1200), "Game Test");
    window.setFramerateLimit(60);

    // ==== LOAD TEXTURE NHÂN VẬT ====
    if (!Character::texture.loadFromFile("assets/nv.jpg"))
    {
        std::cerr << "Error: Không thể load ảnh nhân vật!\n";
        return -1;
    }

    // ==== MAP ====
    Map map(20, 15); // 20 cột, 15 hàng
    map.load_File("assets/map.txt");

    // ==== ENTITY MANAGER ====
    EntityManager manager;

    // ==== CHARACTER (PLAYER) ====
    Character *player = new Character(100, 100, 16, true,
                                      100, 100, 10, 50, 1.0,
                                      1, 0, 0, 100);
    player->setScale(0.2f, 0.2f);
    player->set_Mode(ControlMode::Manual); // điều khiển bằng tay
    manager.add(player);

    sf::Clock clock;
    string filename = "save.txt";

    // ==== GAME LOOP ====
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.key.code == sf::Keyboard::M)
            {
                if (player->get_Mode() == ControlMode::Manual)
                {
                    player->set_Mode(ControlMode::Auto); // chế độ tự động
                    std::cout << "Switched to Auto Mode (A*)\n";
                }
                else
                {
                    player->set_Mode(ControlMode::Manual); // quay lại tay
                    std::cout << "Switched to Manual Mode\n";
                }
            }
            // Save game (F5)
        }

        float deltaTime = clock.restart().asSeconds();

        // ==== UPDATE ENTITIES ====
        for (auto *e : manager.getEntities())
        {
            if (Character *c = dynamic_cast<Character *>(e))
            {
                c->update(deltaTime);
            }
        }

        // ==== DRAW ====
        window.clear();
        map.draw(window);

        for (auto *e : manager.getEntities())
        {
            window.draw(e->get_sprite());
        }

        window.display();
    }

    return 0;
}
