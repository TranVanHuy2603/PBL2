#include <SFML/Graphics.hpp>
#include "Map.h"
#include "TileMap.h"
#include "CameraController.h"
#include "UI/TopBar.h"
#include "UI/UnitPanel.h"
#include "UI/Button.h"

int main()
{
    // --- 1. Cửa sổ game ---
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RTS 2D Game");
    window.setFramerateLimit(60);

    // --- 2. Load font ---
    sf::Font font;
    font.loadFromFile("assets/arial.ttf");

    // --- 3. Load map ---
    Map gameMap;
    gameMap.load_File("assets/mapdata.txt");

    TileMap tileMap;
    tileMap.LoadTileset("assets/tileset.png", sf::Vector2u(64, 64));
    tileMap.buildMap(gameMap);

    // --- 4. Khởi tạo camera ---
    CameraController camera(
        sf::Vector2f(window.getSize()),
        sf::FloatRect(0, 0, gameMap.get_width() * 64, gameMap.get_height() * 64)
    );

    // --- 5. UI ---
    TopBar topBar(font, window.getSize());
    UnitPanel unitPanel(font);

    Button buildButton(font, "Build", {1080, 10}, {100, 40});
    buildButton.setOnClick([]() {
        std::cout << "Build button clicked!\n";
    });

    // --- 6. Clock để tính deltaTime ---
    sf::Clock clock;

    // --- 7. Vòng lặp chính ---
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // --- 8. Xử lý input camera ---
        camera.handleInput(window, deltaTime);

        // --- 9. Cập nhật UI ---
        buildButton.update(window, deltaTime);
        topBar.update(1000, 500); // ví dụ hiển thị tài nguyên giả
        unitPanel.update("Unit: Soldier\nHP: 100/100\nAttack: 10");

        // --- 10. Vẽ mọi thứ ---
        window.clear();

        // Vẽ map với camera
        window.setView(camera.getView());
        tileMap.drawVisible(window, sf::RenderStates::Default, camera.getView());

        // Vẽ UI overlay (dùng default view)
        window.setView(window.getDefaultView());
        topBar.draw(window);
        unitPanel.draw(window);
        buildButton.draw(window);

        window.display();
    }

    return 0;
}
