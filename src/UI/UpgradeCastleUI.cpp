#include "UpgradeCastleUI.h"
#include "Audio.h"
#include <iostream>

UpgradeCastleUI::UpgradeCastleUI()
{
    if (!font.loadFromFile("assets/font/font1.ttf"))
        std::cout << "Font load failed!\n";

    // --- Nút hình tròn mở UI ---
    houseButton = CircleButton(35.f);
    houseButton.setPosition(50.f, 880.f);
    houseButton.setColor(sf::Color(120, 200, 120));
    houseButton.setOutline(sf::Color::Black, 4.f);
    houseButton.setIconScale(0.2f, 0.2f);
    houseButton.setTexture("assets/icon/house.png");

    // --- Nút Upgrade ---
    const String nc = "Nang Cap", h = "Huy";
    upgradeButton = RectangleButton(0.f, 0.f, 300.f, 60.f, &font, nc,
                    sf::Color(120, 200, 120), sf::Color(150, 250, 150), sf::Color(150, 250, 150), 90);
    upgradeButton.setTextColor(sf::Color::White);
    upgradeButton.setOutline(sf::Color::Black, 3.f);

    // --- Nút Cancel ---
    cancelButton = RectangleButton(0.f, 0.f, 250.f, 60.f, &font, h,
                    sf::Color(220, 120, 120), sf::Color(250, 150, 150), sf::Color(150, 250, 150), 90);
    cancelButton.setTextColor(sf::Color::White);
    cancelButton.setOutline(sf::Color::Black, 3.f);

    // --- Text chi phí ---
    costText.setFont(font);
    costText.setCharacterSize(100);
    costText.setFillColor(sf::Color::White);
    costText.setPosition(1600.f, 250.f);
    costText.setOutlineColor(sf::Color::Black);
    costText.setOutlineThickness(3.f);
    costText.setStyle(sf::Text::Bold);

    // Notification
    notificationText.setFont(font);
    notificationText.setCharacterSize(50);
    notificationText.setPosition(1600.f, 520.f);
    notificationText.setOutlineThickness(3.f);
    notificationText.setOutlineColor(sf::Color::Black);
    notificationText.setStyle(sf::Text::Bold);

    showMenu = false;
    showNotification = false;
}

void UpgradeCastleUI::handleEvent(sf::Event &event, Character *player, Castle *castle, sf::RenderWindow &window)
{
    // Bấm nút mở menu
    if (houseButton.isClicked(window, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B))
        showMenu = !showMenu;

    if (!showMenu)
        return;

    // --- Nút Upgrade ---
    if (upgradeButton.isClicked(window, event) 
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LAlt))
    {
        int cost = castle->get_cost();

        if (castle->get_level() < 5)
        {
            if (player->get_gold() >= cost)
            {
                // Nâng cấp thành công
                static Audio upgradeSound("assets/audio/collect.ogg");
                upgradeSound.playSound();
                player->decr_gold(cost);
                castle->level_up();
                showNotificationText("Da nang cap nha thanh cong", sf::Color::Green);
            }
            else
            {
                // Không đủ vàng
                static Audio failSound("assets/audio/error.ogg");
                failSound.playSound();
                showNotificationText("Khong du vang de nang cap nha", sf::Color::Red);
            }
        }
        else
        {
            // Đã đạt level tối đa
            static Audio failSound("assets/audio/error.ogg");
            failSound.playSound();
            showNotificationText("Nha thanh da dat cap toi da", sf::Color::Yellow);
        }

        // Dù nâng cấp thành công hay thất bại, menu tắt sau click
        showMenu = false;
    }
    // --- Nút Cancel ---
    if (cancelButton.isClicked(window, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace))
        showMenu = false;
}

void UpgradeCastleUI::render(sf::RenderWindow &window, Castle *castle)
{
    // Vẽ nút mở menu
    houseButton.render(window);

    sf::Vector2u winSize = window.getSize();
    float centerX = winSize.x / 2.f;
    float centerY = winSize.y / 2.f;

    if (showNotification)
    {
        sf::FloatRect notifBounds = notificationText.getLocalBounds();
        notificationText.setOrigin(notifBounds.left + notifBounds.width / 2.f,
                                   notifBounds.top + notifBounds.height / 2.f);
        notificationText.setPosition(centerX, centerY - 200.f);
        window.draw(notificationText);

        if (notificationClock.getElapsedTime().asSeconds() > 2.f)
            showNotification = false;
    }

    if (!showMenu)
        return;

    // Nút Upgrade / Cancel
    upgradeButton.setPosition(centerX - upgradeButton.getBounds().width / 2.f, centerY - 50.f);
    cancelButton.setPosition(centerX - cancelButton.getBounds().width / 2.f, centerY + 30.f);

    upgradeButton.update(window);
    cancelButton.update(window);

    // Chi phí nâng cấp
    int cost = castle->get_cost();
    costText.setString("NANG CAP NHA\nChi Phi: " + std::to_string(cost));
    sf::FloatRect costBounds = costText.getLocalBounds();
    costText.setOrigin(costBounds.left + costBounds.width / 2.f,
                       costBounds.top + costBounds.height / 2.f);
    costText.setPosition(centerX, centerY - 200.f);

    // Vẽ các nút và text
    window.draw(costText);
    upgradeButton.render(window);
    cancelButton.render(window);
}

void UpgradeCastleUI::showNotificationText(const String &text, sf::Color color)
{
    notificationText.setString(text.c_str());
    notificationText.setFillColor(color);
    notificationText.setOutlineThickness(3.f);
    notificationText.setOutlineColor(sf::Color::Black);
    notificationText.setStyle(sf::Text::Bold);
    notificationText.setCharacterSize(80);
    showNotification = true;
    notificationClock.restart();
}
