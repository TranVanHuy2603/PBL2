#define _HAS_STD_BYTE 0
#include <SFML/Graphics.hpp>
#include <iostream>

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
    //================================================================================
    // 1. KHỞI TẠO CỬA SỔ VÀ CÁC TÀI NGUYÊN TRUNG TÂM
    //================================================================================
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PBL2 - Game RTS 2D");
    window.setFramerateLimit(60);

    sf::Font mainFont;
    if (!mainFont.loadFromFile("assets/font/font2.ttf")) {
        cerr << "Loi nghiem trong: Khong the tai file font chinh!" << endl;
        return -1;
    }

    //================================================================================
    // 2. THIẾT LẬP CÁC TRẠNG THÁI VÀ HỆ THỐNG CỦA GAME
    //================================================================================

    bool inMenu = true;
    bool inGame = false;

    MainMenu menu(window.getSize().x, window.getSize().y, mainFont);

    // --- Entities (Player, Castle, Monsters, Resources) ---
    // EntityManager phải được tạo TRƯỚC khi load map
    sf::FloatRect worldBoundsPlaceholder(0, 0, 1, 1);
    EntityManager manager(Rect(0, 0, 1, 1), 10);

    // --- Map & A* Grid ---
    const double CELL_SIZE = 32.0;
    Map gameMap;
    
    // THAY ĐỔI 1: CHỈ LOAD DỮ LIỆU TILE TỪ FILE MAP
    // Bằng cách truyền `nullptr`, chúng ta yêu cầu hàm load_File bỏ qua phần entities.
    gameMap.load_File("assets/map/mapdata5xx.txt", nullptr);

    // Cập nhật lại worldBounds và Quadtree sau khi đã biết kích thước map
    int mapWidth = gameMap.get_width();
    int mapHeight = gameMap.get_height();
    sf::FloatRect worldBounds(0, 0, mapWidth * CELL_SIZE, mapHeight * CELL_SIZE);
    manager.rebuildQuadtree(Rect(0, 0, worldBounds.width, worldBounds.height));

    // THAY ĐỔI 2: TẠO PLAYER VÀ CASTLE Ở VỊ TRÍ CỐ ĐỊNH
    Character* player = new Character(3500.f, 1700.f, 200, 50);
    manager.add(player);
    manager.set_player(player);

    Castle* castle = new Castle(4000.f, 2000.f, 500, 50);
    manager.add(castle);
    manager.set_castle(castle);

    // THAY ĐỔI 3: BỎ ĐI VIỆC KIỂM TRA NULL POINTER VÌ CHÚNG TA CHẮC CHẮN ĐÃ TẠO CHÚNG
    // if (!player || !castle) { ... }

    // Tạo thêm quái và tài nguyên ngẫu nhiên
    manager.create_monster(50);
    manager.create_resource(150);

    // --- TileMap (để vẽ map) ---
    TileMap tileMap;
    if (!tileMap.LoadTileset("assets/map/Tileset.png", {(unsigned int)CELL_SIZE, (unsigned int)CELL_SIZE}))
    {
        std::cerr << "Loi: Khong the load tileset!" << endl;
        return -1;
    }
    tileMap.buildMap(gameMap);

    // --- Tạo lưới A* cho quái vật tìm đường ---
    Vector<Vector<ASNode>> astarGrid;
    astarGrid.resize(mapWidth);
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

    // --- Camera ---
    CameraController camera(sf::Vector2f(1920, 1080), worldBounds);

    // --- UI In-Game ---
    UIManager uiManager(mainFont);

    // --- Timing ---
    sf::Clock clock;

    //================================================================================
    // 3. GAME LOOP CHÍNH (Giữ nguyên)
    //================================================================================
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

        if (inGame)
        {
            player->handleInput(dt);
            manager.update(dt, astarGrid, CELL_SIZE);
            camera.follow(player->get_position());
            camera.handleInput(window, dt);
            uiManager.update(player, window);
        }

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

    return 0;
}