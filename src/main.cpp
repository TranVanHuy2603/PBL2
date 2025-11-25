#include <SFML/Graphics.hpp>
#include <iostream>
#include "WeaponCraftUI.h"
#include "EntityManager.h"
#include "CharacterUI.h"
#include "UpgradeCastleUI.h"
#include "WeaponSelectUI.h"
#include "Quest.h"
#include "CameraController.h"
#include "Menu.h"
#include "Map.h"
#include "Audio.h"
#include "Intro.h"

enum class GameState
{
    Menu,
    Intro,
    Playing,
    GameOver,
    Win
};

// --- Reset functions ---
void resetGame(EntityManager &manager, Character *&player, Castle *&castle)
{
    manager.clear();
    player = new Character(3000.f, 1700.f, 200, 50, 3);
    castle = new Castle(2900.f, 1800.f, 500, 50);
    manager.set_player(player);
    manager.add(player);
    manager.set_castle(castle);
    manager.add(castle);
    manager.create_monster(100, 50, 10, 80);
    manager.create_resource(300);
}

void resetResourcesAndMonsters(EntityManager &manager, double cellSize, int hp, int damage, int damageRange)
{
    Vector<Entity *> entities = manager.getEntities();
    for (int i = 0; i < entities.get_size(); i++)
    {
        Entity *e = entities[i];
        if (dynamic_cast<Monster *>(e) || dynamic_cast<Resource *>(e))
            manager.remove(e);
    }
    manager.create_monster(60, hp, damage, damageRange);
    manager.create_resource(150);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "FORTRESS OF SURVIVAL");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("assets/font/font1.ttf");

    Audio gameloopaudio("assets/audio/loop.ogg"),
        menuaudio("assets/audio/menu.ogg"),
        gameoveraudio("assets/audio/over.ogg"),
        winaudio("assets/audio/win.ogg");

    // --- Intro ---
    Intro intro;

    // --- UI ---
    Menu menu(1920, 1080, "FORTRESS OF SURVIVAL", "PLAY GAME", "EXIT"),
        over(1920, 1080, "GAME OVER", "PLAY AGAIN", "EXIT"),
        win(1920, 1080, "YOU WIN", "PLAY AGAIN", "EXIT");

    CharacterUI ui;
    WeaponCraftUI craftUI(window);
    UpgradeCastleUI upgradeUI;
    Quest task;

    // --- Game objects ---
    double cellSize = 100.0;
    sf::Clock clock;
    sf::FloatRect worldBounds(0, 0, 6500.f, 3500.f);
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

    manager.create_monster(60, 50, 10, 120);
    manager.create_resource(200);

    // --- Game state ---
    GameState state = GameState::Menu;
    menuaudio.setLoop(true);
    menuaudio.playSound();
    gameloopaudio.setLoop(true);

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
        default:
            break;
        }
    };

    // --- Message for level reset ---
    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(80);
    message.setFillColor(sf::Color::Green);
    message.setStyle(sf::Text::Bold);
    message.setPosition(1920 / 4.f - 300, 100);

    sf::Clock messageClock;
    bool showMessage = false;

    int resetDone = 0;

    // --- Main loop ---
    while (window.isOpen())
    {
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
                    state = GameState::Intro;
                    playMusicForState(state);
                }
                else if (action == 2)
                    window.close();
                break;
            }

            case GameState::Intro:
            {
                menuaudio.stopSound();
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                {
                    intro.next();
                    if (intro.isFinished())
                    {
                        state = GameState::Playing;
                        playMusicForState(state);
                    }
                }
                break;
            }

            case GameState::Playing:
            {
                if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) ||
                    (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right))
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
                    resetGame(manager, player, castle);
                    resetDone = 0;
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
                    resetGame(manager, player, castle);
                    resetDone = 0;
                    state = GameState::Playing;
                    playMusicForState(state);
                }
                else if (action == 2)
                    window.close();
                break;
            }
            }
        }

        // --- Update ---
        float dt = clock.restart().asSeconds();
        window.clear(sf::Color(40, 40, 40));

        switch (state)
        {
        case GameState::Menu:
            menu.render(window);
            break;
        case GameState::Intro:
            intro.update(dt);
            intro.draw(window);
            break;

        case GameState::Playing:
        {
            player->handleInput(dt);
            manager.update(dt, map, manager);

            // --- Level reset logic ---
            if (resetDone == 0 && player->get_level() >= 3)
            {
                message.setString("Level moi! Tai nguyen & Quai vat da reset!");
                messageClock.restart();
                showMessage = true;
                resetResourcesAndMonsters(manager, cellSize, 70, 20, 150);
                resetDone++;
            }
            else if (resetDone == 1 && player->get_level() >= 5)
            {
                message.setString("Level moi! Tai nguyen & Quai vat da reset!");
                messageClock.restart();
                showMessage = true;
                resetResourcesAndMonsters(manager, cellSize, 70, 25, 170);
                resetDone++;
            }
            else if (resetDone == 2 && player->get_level() >= 7)
            {
                message.setString("Level moi! Tai nguyen & Quai vat da reset!");
                messageClock.restart();
                showMessage = true;
                resetResourcesAndMonsters(manager, cellSize, 80, 30, 250);
                resetDone++;
            }
            else if (resetDone == 3 && player->get_level() >= 9)
            {
                message.setString("Level moi! Tai nguyen & Quai vat da reset!");
                messageClock.restart();
                showMessage = true;
                resetResourcesAndMonsters(manager, cellSize, 80, 35, 350);
                resetDone++;
            }

            // --- Check game over ---
            if (!player->get_status() || !castle->get_status())
            {   
                state = GameState::GameOver;
                playMusicForState(state);
                break;
            }

            // --- Check win ---
            if (castle->get_level() >= 5 && player->get_level() >= 10 && player->get_weapons().get_size() == 6)
            {
                state = GameState::Win;
                playMusicForState(state);
                break;
            }

            camera.follow(player->get_position() + player->getSize() / 2.f);
            camera.handleInput(window, dt);

            window.setView(camera.getView());
            map.draw(window, camera.getView());
            manager.render(window);
            auto &weapons = player->get_weapons();
            weapons[player->get_indexWeapon()]->draw(window);
            window.setView(window.getDefaultView());

            ui.update(player, window);
            ui.render(window, player);
            upgradeUI.render(window, castle);
            weaponselect.update(window);
            weaponselect.render(window);
            craftUI.render(window, player);
            task.render(window);

            if (showMessage)
            {
                window.draw(message);
                if (messageClock.getElapsedTime().asSeconds() > 5.f)
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
