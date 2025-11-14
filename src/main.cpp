#define _HAS_STD_BYTE 0
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

// Bao gồm tất cả các file header cần thiết cho hệ thống
#include "MainMenu.h"
#include "UIManager.h"
#include "EntityManager.h"
#include "CameraController.h"
#include "Map.h"
#include "TileMap.h"
#include "ASNode.h"

using namespace std;

int main()
{
    try
    {
        //================================================================================
        // 1. KHỞI TẠO CỬA SỔ VÀ KIỂM TRA MÔI TRƯỜNG
        //================================================================================
        cout << "=== PBL2 - Game RTS 2D ===" << endl;
        cout << "Working directory: " << filesystem::current_path().string() << endl;

        sf::RenderWindow window(sf::VideoMode(1920, 1080), "PBL2 - Game RTS 2D");
        window.setFramerateLimit(60);

        //================================================================================
        // 2. TẢI FONT CHÍNH
        //================================================================================
        sf::Font mainFont;
        if (!mainFont.loadFromFile("assets/font/font2.ttf"))
        {
            cerr << "[Loi nghiem trong] Khong the tai font: assets/font/font2.ttf" << endl;
            return EXIT_FAILURE;
        }

        //================================================================================
        // 3. THIẾT LẬP TRẠNG THÁI GAME
        //================================================================================
        bool inMenu = true;
        bool inGame = false;

        MainMenu menu(window.getSize().x, window.getSize().y, mainFont);

        //================================================================================
        // 4. ENTITY & MAP KHỞI TẠO
        //================================================================================
        const double CELL_SIZE = 32.0;

        sf::FloatRect worldBoundsPlaceholder(0, 0, 1, 1);
        EntityManager manager(Rect(0, 0, 1, 1), 10);

        Map gameMap;
        if (!gameMap.load_File("assets/map/mapdata5xx.txt", nullptr))
        {
            cerr << "[Canh bao] Khong the load file map: assets/map/mapdata5xx.txt" << endl;
            return EXIT_FAILURE;
        }

        int mapWidth = gameMap.get_width();
        int mapHeight = gameMap.get_height();

        sf::FloatRect worldBounds(0, 0, mapWidth * CELL_SIZE, mapHeight * CELL_SIZE);
        manager.rebuildQuadtree(Rect(0, 0, worldBounds.width, worldBounds.height));

        //================================================================================
        // 5. TẠO NHÂN VẬT CHÍNH & CASTLE
        //================================================================================
        Character* player = new Character(350.f, 170.f, 200, 50);
        manager.add(player);
        manager.set_player(player);

        Castle* castle = new Castle(400.f, 200.f, 500, 50);
        manager.add(castle);
        manager.set_castle(castle);

        //================================================================================
        // 6. SINH QUÁI VÀ TÀI NGUYÊN
        //================================================================================
        manager.create_monster(50);
        manager.create_resource(150);

        //================================================================================
        // 7. LOAD TILESET & XÂY MAP HIỂN THỊ
        //================================================================================
        TileMap tileMap;
        if (!tileMap.LoadTileset("assets/map/Tileset.png", {(unsigned int)CELL_SIZE, (unsigned int)CELL_SIZE}))
        {
            cerr << "[Loi] Khong the load tileset: assets/map/Tileset.png" << endl;
            return EXIT_FAILURE;
        }
        tileMap.buildMap(gameMap);

        //================================================================================
        // 8. KHỞI TẠO LƯỚI A* PATHFINDING
        //================================================================================
        Vector<Vector<ASNode>> astarGrid;
        astarGrid.resize(mapWidth);
        std::cout << "Map size: " << mapWidth << " x " << mapHeight << std::endl;

        for (int i = 0; i < mapWidth; ++i)
        {
            astarGrid[i].resize(mapHeight);
            for (int j = 0; j < mapHeight; ++j)
            {
                astarGrid[i][j].set_position(i, j);
                bool isWalkable = gameMap.isWalkable(i, j);
                astarGrid[i][j].set_walkable(isWalkable);
            }
        }

        //================================================================================
        // 9. CAMERA & UI
        //================================================================================
        CameraController camera(sf::Vector2f(1920, 1080), worldBounds);
        UIManager uiManager(mainFont);

        sf::Clock clock;

        //================================================================================
        // 10. GAME LOOP CHÍNH
        //================================================================================
        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Xử lý menu
                if (inMenu)
                {
                    MenuAction action = menu.handleEvent(event, window);
                    if (action == MenuAction::START_GAME)
                    {
                        inMenu = false;
                        inGame = true;
                    }
                    else if (action == MenuAction::EXIT_GAME)
                    {
                        window.close();
                    }
                }
                // Xử lý trong game
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

            //=============================
            // Update logic
            //=============================
            if (inGame)
            {
                player->handleInput(dt);
                manager.update(dt, astarGrid, CELL_SIZE);
                camera.follow(player->get_position());
                camera.handleInput(window, dt);
                uiManager.update(player, window);
            }

            //=============================
            // Render
            //=============================
            window.clear(sf::Color(40, 40, 40));

            if (inMenu)
            {
                menu.render(window);
            }
            else if (inGame)
            {
                window.setView(camera.getView());
                tileMap.drawVisible(window, sf::RenderStates::Default, camera.getView());
                manager.render(window);

                window.setView(window.getDefaultView());
                uiManager.render(window);
            }

            window.display();
        }

        // Giải phóng thủ công nếu cần (dù destructor của manager thường xử lý rồi)
        delete player;
        delete castle;

        return EXIT_SUCCESS;
    }
    catch (const std::exception &ex)
    {
        cerr << "[Exception] Chuong trinh bi loi: " << ex.what() << endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        cerr << "[Exception] Loi khong xac dinh trong main()" << endl;
        return EXIT_FAILURE;
    }
}
