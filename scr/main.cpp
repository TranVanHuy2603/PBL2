#define _HAS_STD_BYTE 0
#include <SFML/Graphics.hpp>
#include <iostream>
#include "EntityManager.h"
#include "CameraController.h"
#include "MainMenu.h"
#include "Map.h"
#include "TileMap.h"
#include "UIManager.h" // Bao gồm file quản lý UI mới

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RTS 2D - PBL2");
    window.setFramerateLimit(60);

    // ===== MENU =====
    MainMenu menu(window.getSize().x, window.getSize().y);
    bool inMenu = true;
    bool inGame = false;

    // ===== Map setup =====
    Map gameMap;
    gameMap.load_File("assets/map/mapdata5xx.txt");
    TileMap tileMap;
    if (!tileMap.LoadTileset("assets/map/Tileset.png", {32, 32}))
    {
        std::cerr << "Khong the load tileset!\n";
        return -1;
    }
    tileMap.buildMap(gameMap);

    // ===== Camera =====
    sf::FloatRect worldBounds(0, 0, gameMap.get_width() * 32, gameMap.get_height() * 32);
    CameraController camera(sf::Vector2f(1920, 1080), worldBounds);

    // ===== Entities =====
    Rect worldRect(0, 0, worldBounds.width, worldBounds.height);
    EntityManager manager(worldRect, 10);

    Character* player = new Character(3500.f, 1700.f, 200, 50);
    manager.set_player(player);
    manager.add(player);

    Castle* castle = new Castle(4000.f, 2000.f, 500, 50);
    manager.set_castle(castle);
    manager.add(castle);

    manager.create_monster(50);
    manager.create_resource(150);

    // ===== UI Manager =====
    // Chỉ cần tạo một đối tượng UIManager để quản lý tất cả UI
    UIManager uiManager;

    // ===== Clock =====
    sf::Clock clock;

    // ===== GAME LOOP =====
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
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
                    window.close();
            }
            else if (inGame)
            {
                // UIManager xử lý tất cả các sự kiện liên quan đến UI
                uiManager.handleEvent(event, window, player, castle);

                // Zoom bằng lăn chuột
                if (event.type == sf::Event::MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.delta > 0)
                        camera.zoom(0.9f);
                    else
                        camera.zoom(1.1f);
                }
            }
        }

        window.clear(sf::Color(40, 40, 40));

        if (inMenu)
        {
            menu.render(window);
        }
        else if (inGame)
        {
            // ===== Update game logic =====

            // 1. Xử lý input của người chơi (di chuyển, nhấn nút tấn công)
            player->handleInput(dt);

            // 2. Cập nhật trạng thái của người chơi (animation, logic tấn công)
            //    Truyền vào Quadtree để hàm attack bên trong có thể tìm mục tiêu
            player->update(dt, manager.getQuadtree());

            // 3. Cập nhật tất cả các thực thể khác (quái vật, tài nguyên,...)
            manager.update(dt);

            // 4. Cập nhật camera và UI
            camera.follow(player->get_position() + player->getSize() / 2.f);
            camera.handleInput(window, dt);
            uiManager.update(player, window);

            // ===== Draw everything =====
            // Vẽ thế giới game qua camera
            window.setView(camera.getView());
            tileMap.drawVisible(window, sf::RenderStates::Default, camera.getView());
            manager.render(window);

            // Chuyển về view mặc định để vẽ UI
            window.setView(window.getDefaultView());
            uiManager.render(window);
        }

        window.display();
    }

    return 0;
}