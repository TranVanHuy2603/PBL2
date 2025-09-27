#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponMenu.h"
#include "EntityManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PBL2");
    window.setFramerateLimit(60);

    EntityManager manager;

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
