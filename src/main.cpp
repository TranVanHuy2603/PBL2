#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponCraftUI.h"
#include "EntityManager.h"
#include "CharacterUI.h"
#include "UpgradeCastleUI.h"
#include "CameraController.h"
#include "ASNode.h"
#include "MainMenu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PBL2");
    window.setFramerateLimit(60);

    // ===== MENU =====
    MainMenu menu(window.getSize().x, window.getSize().y);
    bool inMenu = true;  // trạng thái: đang ở menu
    bool inGame = false; // trạng thái: đang chơi

    // ===== Game objects =====
    double cellSize = 100.0;
    sf::Clock clock;
    sf::FloatRect worldBounds(0, 0, 8000.f, 4000.f);
    CameraController camera(sf::Vector2f(1920, 1080), worldBounds);
    Rect worldRect(0, 0, 8000, 4000);
    EntityManager manager(worldRect, 10);
    Character *player = new Character(3500.f, 1700.f, 200, 50);
    manager.set_player(player);
    manager.add(player);
    player->take_damage(150);

    Castle *castle = new Castle(4000.f, 2000.f, 500, 50);
    manager.set_castle(castle);
    manager.add(castle);
    castle->take_damage(100);

    manager.create_monster(50);
    manager.create_resource(150);

    CharacterUI ui;
    WeaponCraftUI craftUI;
    UpgradeCastleUI upgradeUI;

    // ===== LOOP =====
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (inMenu)
            {
                int action = menu.handleEvent(event, window);
                if (action == 1)
                {
                    inMenu = false;
                    inGame = true;
                }
                else if (action == 2)
                {
                    window.close();
                }
            }
            else if (inGame)
            {
                // Xử lý game
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                    player->attack(manager.getQuadtree());
                craftUI.handleEvent(event, player);
                upgradeUI.handleEvent(event, player, castle);
            }
        }

        window.clear(sf::Color(40, 40, 40));

        if (inMenu)
        {
            menu.render(window);
        }
        else if (inGame)
        {
            float dt = clock.restart().asSeconds();
            
            player->handleInput(dt);               // nhân vật di chuyển trước
            camera.follow(player->get_position() + player->getSize() / 2.f);  // camera theo sau NGAY LẬP TỨC
            camera.handleInput(window, dt);        // xử lý phím WASD cho camera tự do (nếu có)
            ui.update(player, window);             // sau cùng mới cập nhật UI

            window.setView(camera.getView());
            manager.render(window);
            window.setView(window.getDefaultView());
            ui.render(window);
            upgradeUI.render(window);
            craftUI.render(window);
        }

        window.display();
    }

    return 0;
}
