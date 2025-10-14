#include "UpgradeCastleUI.h"

UpgradeCastleUI::UpgradeCastleUI() : showMenu(false)
{
    if (!font.loadFromFile("assets/font/arial.ttf"))
        std::cerr << "Loi tai font!\n";

    // Nut icon ngoi nha
    houseButton.setRadius(40.f);
    houseButton.setFillColor(sf::Color(100, 100, 255));
    houseButton.setPosition(20.f, 800.f);

    if (!houseTexture.loadFromFile("assets/icon/house.png"))
        std::cerr << "Loi tai anh house.png\n";

    houseIcon.setTexture(houseTexture);
    houseIcon.setScale(0.17f, 0.17f);
    houseIcon.setPosition(houseButton.getPosition().x + 10.f,
                          houseButton.getPosition().y + 10.f);

    // Nut nang cap
    upgradeButton.setSize(sf::Vector2f(200.f, 60.f));
    upgradeButton.setFillColor(sf::Color(0, 180, 0));
    upgradeButton.setPosition(100.f, 700.f);

    upgradeText.setFont(font);
    upgradeText.setString("Nang cap nha");
    upgradeText.setCharacterSize(22);
    upgradeText.setFillColor(sf::Color::White);
    upgradeText.setPosition(120.f, 715.f);

    // Nut huy
    cancelButton.setSize(sf::Vector2f(200.f, 60.f));
    cancelButton.setFillColor(sf::Color(180, 0, 0));
    cancelButton.setPosition(100.f, 770.f);

    cancelText.setFont(font);
    cancelText.setString("Huy");
    cancelText.setCharacterSize(22);
    cancelText.setFillColor(sf::Color::White);
    cancelText.setPosition(190.f, 785.f);

    // Chu hien thi chi phi
    costText.setFont(font);
    costText.setCharacterSize(20);
    costText.setFillColor(sf::Color::Yellow);
    costText.setPosition(110.f, 660.f);
}

void UpgradeCastleUI::handleEvent(sf::Event &event, Character *player, Castle *castle)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        // Bam vao nut nha
        if (houseButton.getGlobalBounds().contains(mousePos))
        {
            showMenu = !showMenu;

            // Cap nhat thong tin chi phi moi nhat
            if (castle->get_level() >= 5)
                costText.setString("Nha da cap toi da!");
            else
            {
                std::string costStr = "Chi phi nang cap: " + std::to_string(castle->get_cost()) + " Coin";
                costText.setString(costStr);
            }

            return;
        }

        if (showMenu)
        {
            // Nut nang cap
            if (upgradeButton.getGlobalBounds().contains(mousePos))
            {
                if (castle->get_level() >= 5)
                {
                    showNotificationText("Nha da dat cap toi da!", sf::Color::Red);
                }
                else
                {
                    int cost = castle->get_cost();
                    int gold = player->get_gold();

                    if (gold >= cost)
                    {
                        player->decr_gold(cost);
                        castle->level_up();
                        showNotificationText("Nang cap nha thanh cong!", sf::Color::Green);
                    }
                    else
                    {
                        showNotificationText("Khong du tien de nang cap!", sf::Color::Red);
                    }
                }
                showMenu = false;
            }

            // Nut huy
            else if (cancelButton.getGlobalBounds().contains(mousePos))
            {
                showMenu = false;
            }
        }
    }
}

void UpgradeCastleUI::render(sf::RenderWindow &window)
{
    // Ve nut nha
    window.draw(houseButton);
    window.draw(houseIcon);

    // Ve menu
    if (showMenu)
    {
        window.draw(costText);

        // Neu nha chua dat cap toi da moi ve nut nang cap
        if (costText.getString() != "Nha da cap toi da!")
        {
            window.draw(upgradeButton);
            window.draw(upgradeText);
        }

        window.draw(cancelButton);
        window.draw(cancelText);
    }

    // Ve thong bao
    if (showNotification)
    {
        float elapsed = notificationClock.getElapsedTime().asSeconds();
        if (elapsed < 2.5f)
        {
            sf::Vector2u size = window.getSize();
            sf::FloatRect textBounds = notificationText.getLocalBounds();
            notificationText.setFont(font);
            notificationText.setCharacterSize(26);
            notificationText.setStyle(sf::Text::Bold);
            notificationText.setPosition(
                (size.x - textBounds.width) / 2.f,
                (size.y - textBounds.height) / 2.f - 200.f);
            window.draw(notificationText);
        }
        else
        {
            showNotification = false;
        }
    }
}

void UpgradeCastleUI::showNotificationText(const std::string &text, sf::Color color)
{
    notificationText.setString(text);
    notificationText.setFillColor(color);
    showNotification = true;
    notificationClock.restart();
}
