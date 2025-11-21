#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponCraftUI.h"
#include "EntityManager.h"
#include "CharacterUI.h"
#include "UpgradeCastleUI.h"
#include "WeaponSelectUI.h"
#include "Quest.h"
#include "CameraController.h"
#include "ASNode.h"
#include "Menu.h"
#include "Map.h"
#include "Audio.h"

enum class GameState
{
    Menu,
    Playing,
    GameOver,
    Win
};
// Hàm reset game
void resetGame(EntityManager &, Character *&, Castle *&, Map &, Vector<Vector<ASNode>> &, double);

void resetResourcesAndMonsters(EntityManager &, Map &, Vector<Vector<ASNode>> &, double , int , int , int damageange);

int main()
{

    sf::Font font;
    font.loadFromFile("assets/font/font2.ttf");

    Audio gameloopaudio("assets/audio/loop.mp3"),
        menuaudio("assets/audio/menu.mp3"),
        gameoveraudio("assets/audio/over.mp3"),
        winaudio("assets/audio/win.mp3");

    sf::Text levelMessage;
    levelMessage.setFont(font);
    levelMessage.setCharacterSize(40);
    levelMessage.setFillColor(sf::Color::Blue);
    levelMessage.setStyle(sf::Text::Bold);
    levelMessage.setPosition(1920 / 4.f - 300, 100); // căn giữa màn hình

    sf::Clock messageClock; // đồng hồ để đếm thời gian hiển thị thông báo
    bool showMessage = false;
    // ===== Audio =====

    gameloopaudio.setVolume(30.f);
    gameloopaudio.setLoop(true);
    menuaudio.setVolume(50.f);
    menuaudio.setLoop(true);
    gameoveraudio.setVolume(60.f);
    winaudio.setVolume(60.f);

    // ===== Window =====
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PBL2 24.NH15B");
    window.setFramerateLimit(60);

    // ===== UI =====
    Menu menu(window.getSize().x, window.getSize().y, "PBL2 GAME", "Bat dau", "Thoat"),
        over(window.getSize().x, window.getSize().y, "GAME OVER", "Choi lai", "Thoat"),
        win(window.getSize().x, window.getSize().y, "YOU WIN", "Choi lai", "Thoat");

    CharacterUI ui;
    WeaponCraftUI craftUI(window);
    UpgradeCastleUI upgradeUI;
    Quest task;

    // ===== Game objects =====
    double cellSize = 100.0;
    sf::Clock clock;
    sf::FloatRect worldBounds(0, 0, 6500.f, 3500.f);
    int width = 65, height = 35;
    Vector<ASNode> row(width);
    Vector<Vector<ASNode>> grid(height, row);
    Map map(6500.f, 3500.f);
    CameraController camera(sf::Vector2f(1920, 1080), worldBounds);
    Rect worldRect(0, 0, 6500, 3500);
    EntityManager manager(worldRect, 10);

    Character *player = new Character(3000.f, 1700.f, 200, 50, 3);
    Castle *castle = new Castle(2900.f, 1800.f, 500, 50);
    WeaponSelectUI weaponselect(window, player);

    manager.set_player(player);
    manager.add(player);
    manager.set_castle(castle);
    manager.add(castle);

    manager.create_monster(60, 50, 5, 80);
    manager.create_resource(300);
    map.setGrid(manager.getEntities(), grid, cellSize);

    // ===== Game state =====
    GameState state = GameState::Menu;
    menuaudio.playSound();

    auto playMusicForState = [&](GameState s)
    {
        gameloopaudio.stopSound();
        menuaudio.stopSound();
        gameoveraudio.stopSound();
        winaudio.stopSound();

        switch (s)
        {
        case GameState::Menu:
            menuaudio.playSound();
            break;
        case GameState::Playing:
            gameloopaudio.playSound();
            break;
        case GameState::GameOver:
            gameoveraudio.playSound();
            break;
        case GameState::Win:
            winaudio.playSound();
            break;
        }
    };

    // ===== Main Loop =====
    while (window.isOpen())
    {
        // --- Event handling ---
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (state)
            {
            case GameState::Menu:
            {
                int action = menu.handleEvent(event, window);
                if (action == 1)
                {
                    state = GameState::Playing;
                    playMusicForState(state);
                }
                else if (action == 2)
                    window.close();
                break;
            }
            case GameState::Playing:
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter ||
                    event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
                    player->attack(manager.getQuadtree(), task);

                craftUI.handleEvent(event, player, window);
                upgradeUI.handleEvent(event, player, castle, window);
                weaponselect.handleEvent(event, window);
                task.handleEvent(event, window);
                camera.handleEvent(event);
                break;
            }
            case GameState::GameOver:
            {
                int action = over.handleEvent(event, window);
                if (action == 1)
                {
                    resetGame(manager, player, castle, map, grid, cellSize);
                    state = GameState::Playing;
                    playMusicForState(state);
                }
                else if (action == 2)
                    window.close();
                break;
            }
            case GameState::Win:
            {
                int action = win.handleEvent(event, window);
                if (action == 1)
                {
                    resetGame(manager, player, castle, map, grid, cellSize);
                    state = GameState::Playing;
                    playMusicForState(state);
                }
                else if (action == 2)
                    window.close();
                break;
            }
            }
        }

        // --- Update & Render ---
        window.clear(sf::Color(40, 40, 40));
        float dt = clock.restart().asSeconds();

        switch (state)
        {
        case GameState::Menu:
            menu.render(window);
            break;

        case GameState::Playing:
        {
            player->handleInput(dt);
            manager.update(dt, grid, cellSize, map, manager);

            static int resetDone = 0;
            if (resetDone == 0 && (castle->get_level() >= 2 || player->get_level() >= 4))
            {
                levelMessage.setString("Level reached! Resources & Monsters reset!");
                messageClock.restart();
                showMessage = true;
                resetResourcesAndMonsters(manager, map, grid, cellSize, 60, 8, 85);
                resetDone++;
            }
            else if (resetDone == 1 && (castle->get_level() >= 3 || player->get_level() >= 6))
            {
                levelMessage.setString("Level reached! Resources & Monsters reset!");
                messageClock.restart();
                showMessage = true;
                resetResourcesAndMonsters(manager, map, grid, cellSize, 70, 10, 90);
                resetDone++;
            }
            else if (resetDone == 2 && (castle->get_level() >= 4 || player->get_level() >= 8))
            {
                levelMessage.setString("Level reached! Resources & Monsters reset!");
                messageClock.restart();
                showMessage = true;
                resetResourcesAndMonsters(manager, map, grid, cellSize, 80, 12, 95);
                resetDone++;
            }

            // Check game over
            if (!player->get_status() || !castle->get_status())
            {
                state = GameState::GameOver;
                playMusicForState(state);
                break;
            }

            // Check win condition
            if (castle->get_level() >= 5 || player->get_level() >= 10)
            {
                state = GameState::Win;
                playMusicForState(state);
                break;
            }

            camera.follow(player->get_position() + player->getSize() / 2.f);
            camera.handleInput(window, dt);
            ui.update(player, window);

            window.setView(camera.getView());
            map.draw(window, camera.getView());
            manager.render(window);
            auto& weapons = player->get_weapons();
            int i = player->get_indexWeapon();
            weapons[i]->draw(window);
            window.setView(window.getDefaultView());
            ui.render(window, player);
            upgradeUI.render(window, castle);
            weaponselect.update(window);
            weaponselect.render(window);
            craftUI.render(window, player);
            task.render(window);
            if (showMessage)
            {
                window.draw(levelMessage);
                if (messageClock.getElapsedTime().asSeconds() > 3.f)
                    showMessage = false;
            }
            break;
        }
        case GameState::GameOver:
            over.render(window);
            break;

        case GameState::Win:
            win.render(window);
            break;
        }

        window.display();
    }
    manager.clear();
    return 0;
}
// Hàm reset game
void resetGame(EntityManager &manager, Character *&player, Castle *&castle, Map &map,
               Vector<Vector<ASNode>> &grid, double cellSize)
{
    manager.clear();

    player = new Character(3000.f, 1700.f, 200, 50, 3);
    castle = new Castle(2900.f, 1800.f, 500, 50);

    manager.set_player(player);
    manager.add(player);
    manager.set_castle(castle);
    manager.add(castle);

    manager.create_monster(100, 50, 5, 80);
    manager.create_resource(300);

    map.setGrid(manager.getEntities(), grid, cellSize);
}

void resetResourcesAndMonsters(EntityManager &manager, Map &map,
                               Vector<Vector<ASNode>> &grid, double cellSize, int hp, int damage, int damagerange)
{
    Vector<Entity *> entities = manager.getEntities();
    for (int i = 0; i < entities.get_size(); ++i)
    {
        Entity *e = entities[i];
        if (dynamic_cast<Monster *>(e) != nullptr || dynamic_cast<Resource *>(e) != nullptr)
            manager.remove(e);
    }

    manager.create_monster(60, hp, damage, damagerange);
    manager.create_resource(300);
    map.setGrid(manager.getEntities(), grid, cellSize);
}