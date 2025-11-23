#include "Quest.h"
#include "Character.h"
#include <iostream>

Quest::Quest()
{
    // Load background bảng nhiệm vụ
    if (!texture.loadFromFile("assets/quest/quest.png"))
        std::cout << "Failed to load quest background\n";
    sprite.setTexture(texture);
    sprite.setScale(0.6f, 0.6f);

    if (!ticktexture.loadFromFile("assets/icon/tick.png"))
        std::cout << "Failed to load tick texture\n";
    ticksprite.setTexture(ticktexture);
    ticksprite.setScale(0.1f, 0.1f); // tùy chỉnh kích thước tick

    // Nút mở menu
    questButton = CircleButton(35.f);
    questButton.setPosition(50.f, 780.f);
    questButton.setColor(sf::Color(100, 149, 237));
    questButton.setOutline(sf::Color::Black, 4.f);
    questButton.setIconScale(0.3f, 0.3f);
    questButton.setTexture("assets/icon/quest.png");

    // Nút đóng menu
    const String exit = "Thoat";
    exitButton = RectangleButton(0.f, 0.f, 75.f, 25.f, &font, exit,
                                 sf::Color(220, 120, 120), sf::Color(250, 150, 150), sf::Color(250, 150, 150), 12);
    exitButton.setTextColor(sf::Color::White);
    

    // Font cho notification
    if (!font.loadFromFile("assets/font/font2.ttf"))
        std::cout << "Font load failed!\n";

    notificationText.setFont(font);
    notificationText.setCharacterSize(32);
    notificationText.setPosition(1600.f, 520.f);

    // Target & progress
    target.push_back(2);
    target.push_back(4);
    target.push_back(5);
    target.push_back(10);
    target.push_back(10);
    target.push_back(30);
    target.push_back(1);
    for (int i = 0; i < 7; i++)
        progress.push_back(0);

    showMenu = false;
    showNotification = false;
}

void Quest::completeTask(int index)
{
    if (index >= 0 && index < 7)
        status[index] = true;
}

void Quest::addTarget(int index, Character& player)
{
    if (index < 0 || index >= 7)
        return;

    if (progress[index] < target[index] - 1)
    {
        progress[index]++;
        cout << "Thu thap nhiem vu\n";
    }
    else if (!status[index])
    {
        status[index] = true;
        showNotificationText("Nhiem vu " + std::to_string(index + 1) + " hoan thanh", sf::Color::Green);
        switch(index)
        {
            case 0:
            {
                player.incr_exp(30);
                break;
            }
            case 1:
            {
                player.incr_gold(50);
                break;
            }
            case 2:
            {
                player.set_hp(player.get_hp_max());
                break;
            }
            case 3:
            {
                if (player.get_hp() + 300 < player.get_hp_max())
                    player.set_hp(player.get_hp() + 300);
                player.set_hp(player.get_hp_max());
                break;
            }
            case 4:
            {
                player.incr_gold(400);
                break;
            }
            case 5:
            {
                player.levelUp();
                break;
            }
            case 6:
            {
                player.incr_exp(100);
            }
        }
    }
}

void Quest::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
    // Mở / đóng bảng nhiệm vụ
    if (questButton.isClicked(window, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N))
        showMenu = !showMenu;

    // Đóng menu nếu nút exit được click
    if (showMenu && exitButton.isClicked(window, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace))
        showMenu = false;
}

void Quest::render(sf::RenderWindow &window)
{
    // Vẽ nút mở menu
    questButton.render(window);

    // Vẽ notification nếu có
    if (showNotification)
    {
        sf::Vector2u winSize = window.getSize();
        float centerX = winSize.x / 2.f;
        float centerY = winSize.y / 2.f;

        sf::FloatRect notifBounds = notificationText.getLocalBounds();
        notificationText.setOrigin(notifBounds.left + notifBounds.width / 2.f,
                                   notifBounds.top + notifBounds.height / 2.f);
        notificationText.setPosition(centerX, centerY - 200.f);
        window.draw(notificationText);

        if (notificationClock.getElapsedTime().asSeconds() > 2.f)
            showNotification = false;
    }

    // Vẽ bảng nhiệm vụ nếu menu mở
    if (showMenu)
    {
        draw(window);
        exitButton.setPosition(200.f, 255.f);
        exitButton.render(window);
    }
}

void Quest::showNotificationText(const std::string &text, sf::Color color)
{
    notificationText.setString(text);
    notificationText.setFillColor(color);
    notificationText.setOutlineThickness(2.f);
    notificationText.setOutlineColor(sf::Color::Black);
    notificationText.setStyle(sf::Text::Bold);
    showNotification = true;
    notificationClock.restart();
}

void Quest::draw(sf::RenderWindow &window)
{
    // Chỉ vẽ sprite background vì các task đã có trong texture
    sf::Vector2u winSize = window.getSize();
    sf::FloatRect bounds = sprite.getLocalBounds();
    float marginLeft = 200.f;
    sprite.setPosition(marginLeft, (winSize.y - bounds.height * sprite.getScale().y) / 2.f);
    window.draw(sprite);

    float startX = 720.f;              // khoảng cách từ lề trái background
    float startY = 373.f; // lề trên
    float spacingY = 60.f;                         // khoảng cách giữa các nhiệm vụ theo chiều dọc

    for (int i = 0; i < 7; i++)
    {
        if (status[i]) // nếu nhiệm vụ đã hoàn thành
        {
            ticksprite.setPosition(startX, startY + i * spacingY);
            window.draw(ticksprite);
        }
    }
}
