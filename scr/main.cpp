#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponMenu.h"
#include "EntityManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PBL2");
    window.setFramerateLimit(60);

    Rect worldRect(0, 0, 800, 600); //khoi tao vung ban do cho quadtree
    EntityManager manager(worldRect, 10); //quan li entity

    Character* player = new Character(100, 100, false, 100, 100, 1, 0, 0, 20); //khoi tao nhan vat
    manager.set_player(player);
    manager.add(player);

    Castle* castle = new Castle(200, 200, false, 500, 500, 1, 20);
    manager.set_castle(castle);
    manager.add(castle);

    for (int i = 0; i < 15; i++)
    {
        Monster* m = new Monster(50 + i * 100, 50, false, 50, 50, 5, 60, rand()*10, 10, 20); 
        manager.add(m);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(40, 40, 40));
        window.display();
    }

    return 0;
}
