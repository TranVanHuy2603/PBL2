#include "WeaponSelectUI.h"
#include <iostream>

WeaponSelectUI::WeaponSelectUI(sf::RenderWindow &window, Character *player)
{
    if (!font.loadFromFile("assets/font/font2.ttf"))
        std::cerr << "Failed to load font!\n";

    this->player = player;
    showNotification = false;

    initButtons(window);
}

// Khởi tạo nút dựa trên số lượng vũ khí hiện tại
void WeaponSelectUI::initButtons(sf::RenderWindow &window)
{
    buttons.clear();
    if (!player) return;

    auto &weapons = player->get_weapons();
    float x = window.getSize().x - buttonWidth - margin;
    float yStart = window.getSize().y - buttonHeight - margin - 60;

    for (int i = 0; i < weapons.get_size(); ++i)
    {
        float y = yStart - i * (buttonHeight + spacing);

        RectangleButton btn(
            x, y,
            buttonWidth, buttonHeight,
            &font,
            weapons[i]->get_name(),
            sf::Color(100,100,100),
            sf::Color(150,150,150),
            sf::Color(160,160,160),
            12
        );
        cout << "Tao button moi cho sung\n";
        // ==== CĂN GIỮA ICON TRONG NÚT ====
        sf::FloatRect btnBounds  = btn.getBounds();

        // Set text dưới icon
        btn.setTextPosition(
            btnBounds.left + btnBounds.width / 2.f,
            btnBounds.top  + btnBounds.height - 15.f
        );

        buttons.push_back(btn);
    }
}


void WeaponSelectUI::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
    if (!player)
        return;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        for (size_t i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i].isClicked(window, event))
            {
                player->switch_weapon((int)i); // đổi vũ khí
                showNotificationText("Da chon vu khi", sf::Color::Green);

                // đổi màu nút ngay lập tức
                for (size_t j = 0; j < buttons.size(); ++j)
                    buttons[j].setFillColor(j == i ? sf::Color(200, 200, 0) : sf::Color(100, 100, 100));

                static Audio selectSound("assets/audio/select.ogg");
                selectSound.setVolume(40.f);
                selectSound.playSound();
            }
        }
    }
}

// Cập nhật nút nếu số lượng vũ khí thay đổi
void WeaponSelectUI::update(sf::RenderWindow &window)
{
    if (!player)
        return;

    auto &weapons = player->get_weapons();

    // Nếu số lượng vũ khí thay đổi, tạo lại nút
    if (weapons.get_size() != buttons.size())
        initButtons(window);
}

// Render
void WeaponSelectUI::render(sf::RenderWindow &window)
{
    auto &weapons = player->get_weapons();
    int index = player->get_indexWeapon();
    for (int i = 0; i < weapons.get_size(); ++i)
    {
        if (i == index) buttons[i].setFillColor(sf::Color::Green);
        buttons[i].setIcon(weapons[i]->get_path());
        buttons[i].setIconScale(0.25f, 0.25f);
    }
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        buttons[i].update(window);
        buttons[i].render(window);
    }

    // Hiển thị thông báo
    if (showNotification)
    {
        float elapsed = notificationClock.getElapsedTime().asSeconds();
        if (elapsed < 2.f)
        {
            sf::Vector2u size = window.getSize();
            sf::FloatRect bounds = notificationText.getLocalBounds();
            notificationText.setFont(font);
            notificationText.setCharacterSize(24);
            notificationText.setStyle(sf::Text::Bold);
            notificationText.setPosition(
                (size.x - bounds.width) / 2.f,
                (size.y - bounds.height) / 2.f);
            window.draw(notificationText);
        }
        else
        {
            showNotification = false;
        }
    }
}

void WeaponSelectUI::showNotificationText(const std::string &text, sf::Color color)
{
    notificationText.setString(text);
    notificationText.setFillColor(color);
    showNotification = true;
    notificationClock.restart();
}
