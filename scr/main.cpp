#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponCraftUI.h"
#include "EntityManager.h"
#include "CharacterUI.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PBL2");
    window.setFramerateLimit(60);

    sf::Clock clock;
    float dt = clock.restart().asSeconds();

    Rect worldRect(0, 0, 1920, 1080);
    EntityManager manager(worldRect, 10);

    Character *player = new Character(100, 100, 200, 50);
    manager.set_player(player);
    manager.add(player);
    player->take_damage(50);

    Castle *castle = new Castle(150, 150, 500, 50);
    manager.set_castle(castle);
    manager.add(castle);

    manager.create_monster(15);
    manager.create_resource(50);

    CharacterUI ui;
    WeaponCraftUI craftUI;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            craftUI.handleEvent(event, player);

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
        ui.update(player, window);

        window.clear(sf::Color(40, 40, 40));

        manager.drawAll(window);
        ui.render(window);
        craftUI.render(window);

        window.display();
    }
    return 0;
}
