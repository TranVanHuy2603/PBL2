#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponCraftUI.h"
#include "EntityManager.h"
#include "CharacterUI.h"
#include "UpgradeCastleUI.h"
#include "CameraController.h"
#include "ASNode.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PBL2");
    window.setFramerateLimit(60);
    double cellSize = 100.0;


    // ===== Khởi tạo đồng hồ thời gian =====
    sf::Clock clock;

    // ===== Giới hạn thế giới (bản đồ) =====
    sf::FloatRect worldBounds(0, 0, 8000.f, 4000.f);

    // ===== Camera =====
    CameraController camera(sf::Vector2f(1920, 1080), worldBounds);

    // ===== Quản lý thực thể =====
    Rect worldRect(0, 0, 8000, 4000);
    EntityManager manager(worldRect, 10);

    // ===== Nhân vật =====
    Character *player = new Character(3500.f, 1700.f, 200, 50);
    manager.set_player(player);
    manager.add(player);
    player->take_damage(80);

    // ===== Lâu đài =====
    Castle *castle = new Castle(4000.f, 2000.f, 500, 50);
    manager.set_castle(castle);
    manager.add(castle);
    castle->take_damage(20);

    // ===== Quái và tài nguyên =====
    manager.create_monster(50);
    manager.create_resource(150);

    // ===== Giao diện =====
    CharacterUI ui;
    WeaponCraftUI craftUI;
    UpgradeCastleUI upgradeUI;

    // ===== Vòng lặp chính =====
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Sự kiện thoát
            if (event.type == sf::Event::Closed)
                window.close();

            // Sự kiện tấn công
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                player->attack(manager.getQuadtree());

            // Xử lý UI
            craftUI.handleEvent(event, player);
            upgradeUI.handleEvent(event, player, castle);
        }

        // ===== Cập nhật thời gian khung hình =====
        float dt = clock.restart().asSeconds();



        // ===== Cập nhật logic =====
        player->handleInput(dt);
        ui.update(player, window);

        // ===== Camera =====
        camera.handleInput(window, dt);        // WASD để di chuyển camera
        camera.follow(player->get_position()); // hoặc có thể bỏ dòng này nếu muốn tự do

        // ===== Vẽ khung hình =====
        window.clear(sf::Color(40, 40, 40));

        // Áp dụng camera trước khi vẽ thế giới
        window.setView(camera.getView());

        manager.render(window);

        // Đặt lại view mặc định cho UI (UI luôn cố định trên màn hình)
        window.setView(window.getDefaultView());

        ui.render(window);
        upgradeUI.render(window);
        craftUI.render(window);

        window.display();
    }

    return 0;
}
