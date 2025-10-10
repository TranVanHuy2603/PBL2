#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponMenu.h"
#include "EntityManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PBL2");
    window.setFramerateLimit(60);

    sf::Clock clock;           // tạo đồng hồ
    float dt = clock.restart().asSeconds();

    Rect worldRect(0, 0, 1920, 1080); //khoi tao vung ban do cho quadtree
    EntityManager manager(worldRect, 10); //quan li entity

    Character* player = new Character(100, 100, 200, 50); //khoi tao nhan vat
    manager.set_player(player);
    manager.add(player);

    Castle* castle = new Castle(150, 150, 500, 50);
    manager.set_castle(castle);
    manager.add(castle);

    manager.create_monster(15);
    manager.create_resource(20);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                player->attack(manager.getQuadtree());
            }
        }
        }

        float dt = clock.restart().asSeconds();
        player->handleInput(dt);
        window.clear(sf::Color(40, 40, 40));
        manager.drawAll(window);
        window.display();
    }
    return 0;
}
