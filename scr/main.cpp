#define _HAS_STD_BYTE 0
#include <SFML/Graphics.hpp>
#include <iostream>
#include "EntityManager.h"
#include "CameraController.h"
#include "MainMenu.h"
#include "Map.h"
#include "TileMap.h"
#include "UIManager.h"
#include "ASNode.h" // Cần cho việc tạo lưới A*

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RTS 2D - PBL2");
    window.setFramerateLimit(60);

    // ===== Tải tài nguyên tập trung =====
    sf::Font mainFont;
    if (!mainFont.loadFromFile("assets/font/font2.ttf")) {
        cerr << "Loi: Khong the tai font chinh!" << endl;
        return -1;
    }

    // ===== MENU =====
    MainMenu menu(window.getSize().x, window.getSize().y, mainFont); // Truyền font vào menu
    bool inMenu = true;
    bool inGame = false;

    // ===== Map setup =====
    const double CELL_SIZE = 32.0;
    Map gameMap;
    gameMap.load_File("assets/map/mapdata5xx.txt");
    TileMap tileMap;
    if (!tileMap.LoadTileset("assets/map/Tileset.png", {(unsigned int)CELL_SIZE, (unsigned int)CELL_SIZE}))
    {
        std::cerr << "Khong the load tileset!\n";
        return -1;
    }
    tileMap.buildMap(gameMap);

    // ===== TẠO LƯỚI TÌM ĐƯỜNG (A* GRID) - BƯỚC QUAN TRỌNG BỊ THIẾU =====
    Vector<Vector<ASNode>> grid;
    int mapWidth = gameMap.get_width();
    int mapHeight = gameMap.get_height();
    grid.resize(mapWidth);
    for (int i = 0; i < mapWidth; ++i)
    {
        grid[i].resize(mapHeight);
        for (int j = 0; j < mapHeight; ++j)
        {
            grid[i][j].set_position(i, j);
            // Giả định lớp Map có hàm is_obstacle để kiểm tra vật cản
            bool isWalkable = !gameMap.is_obstacle(i, j);
            grid[i][j].set_walkable(isWalkable);
        }
    }

    // ===== Camera =====
    sf::FloatRect worldBounds(0, 0, mapWidth * CELL_SIZE, mapHeight * CELL_SIZE);
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
    UIManager uiManager(mainFont); // Khởi tạo UIManager với font đã tải

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
                if (action == 1) { inMenu = false; inGame = true; }
                else if (action == 2) window.close();
            }
            else if (inGame)
            {
                uiManager.handleEvent(event, window, player, castle);
                if (event.type == sf::Event::MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.delta > 0) camera.zoom(0.9f);
                    else camera.zoom(1.1f);
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
            // ===== Update game logic - ĐÚNG THỨ TỰ =====
            // 1. Xử lý input của người chơi
            player->handleInput(dt);

            // 2. Cập nhật TẤT CẢ các thực thể (bao gồm cả player và monster)
            //    Hàm này sẽ gọi player->update và monster->update bên trong nó
            manager.update(dt, grid, CELL_SIZE);

            // 3. Cập nhật camera và UI
            camera.follow(player->get_position());
            camera.handleInput(window, dt);
            uiManager.update(player, window);

            // ===== Draw everything =====
            // Vẽ thế giới game qua camera
            window.setView(camera.getView());
            tileMap.drawVisible(window, sf::RenderStates::Default, camera.getView());
            manager.render(window); // Hàm này sẽ vẽ entities và cả effects

            // Chuyển về view mặc định để vẽ UI
            window.setView(window.getDefaultView());
            uiManager.render(window);
        }

        window.display();
    }

    return 0;
}