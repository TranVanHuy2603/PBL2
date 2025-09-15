#include <SFML/Graphics.hpp>
#include "Character.h"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Character Test");
    sf::Clock clock;

    // Load texture cho nhân vật
    sf::Texture tex;
    tex.loadFromFile("assets/f34637b89c0617584e17.jpg"); // đường dẫn tới hình nhân vật
    Character::texture = tex;

    // Tạo nhân vật
    Character player(100, 100, 16, true, 100, 100, 10, 32, 1.0, 1, 0, 0);

    // --- Test Auto mode ---
    std::vector<sf::Vector2f> path = { {100,100}, {300,100}, {300,300}, {500,300} };
    player.setPath(path);
    player.set_Mode(ControlMode::Auto);
    player.setScale(0.2f, 0.2f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Chuyển qua Manual mode nếu nhấn M
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                player.set_Mode(ControlMode::Manual);
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Update nhân vật
        player.update(deltaTime);

        // Vẽ
        window.clear(sf::Color::Black);
        player.draw(window);
        window.display();
    }

    return 0;
}
