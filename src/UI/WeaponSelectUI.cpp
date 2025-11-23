#include "WeaponSelectUI.h"
#include <iostream>

WeaponSelectUI::WeaponSelectUI(sf::RenderWindow &window, Character *player)
{
    if (!font.loadFromFile("assets/font/font1.ttf"))
        std::cerr << "Failed to load font!\n";

    this->player = player;
    showNotification = false;

    // Chọn vũ khí đầu tiên mặc định
    if(player && player->get_weapons().get_size() > 0 && player->get_indexWeapon() < 0)
        player->switch_weapon(0);

    initButtons(window);
}

// Khởi tạo nút dựa trên số lượng vũ khí hiện tại
void WeaponSelectUI::initButtons(sf::RenderWindow &window)
{
    buttons.clear();
    if (!player) return;

    auto &weapons = player->get_weapons();
    float x = window.getSize().x - buttonWidth - margin - 20.f;
    float yStart = window.getSize().y - buttonHeight - margin - 60;

    for (int i = 0; i < weapons.get_size(); ++i)
    {
        float y = yStart - i * (buttonHeight + spacing);

        RectangleButton btn(
            x, y,
            buttonWidth, buttonHeight,
            &font,
            weapons[i]->get_name(),
            sf::Color(100, 100, 100),  // normal
            sf::Color(150, 150, 150),  // hover
            sf::Color::Yellow,          // selected
            30
        );

        // Text dưới icon
        sf::FloatRect btnBounds = btn.getBounds();
        btn.setTextPosition(
            btnBounds.left + btnBounds.width / 2.f,
            btnBounds.top + btnBounds.height - 15.f
        );
        btn.setTextColor(sf::Color::Green);
        btn.setOutline(sf::Color::Black, 2.f);

        buttons.push_back(btn);
    }
}

void WeaponSelectUI::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
    if (!player) return;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        for (size_t i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i].isClicked(window, event))
            {
                player->switch_weapon((int)i); // đổi vũ khí
                showNotificationText("Da chon vu khi", sf::Color::Green);

                static Audio selectSound("assets/audio/select.ogg");
                selectSound.setVolume(40.f);
                selectSound.playSound();
            }
        }
    }

    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::C)
    {
        auto &weapons = player->get_weapons();
        int index = player->get_indexWeapon();
        index++;
        if (index >= weapons.get_size()) index = 0;
        player->switch_weapon(index);

        char msg[128];
        sprintf(msg, "Da doi vu khi thanh %s", weapons[index]->get_name().c_str());
        showNotificationText(msg, sf::Color::Green);

        static Audio selectSound("assets/audio/select.ogg");
        selectSound.setVolume(40.f);
        selectSound.playSound();
    }
}

// Cập nhật nếu số lượng vũ khí thay đổi
void WeaponSelectUI::update(sf::RenderWindow &window)
{
    if (!player) return;

    auto &weapons = player->get_weapons();
    if (weapons.get_size() != buttons.size())
        initButtons(window);

    // Cập nhật hover màu nút (nhưng không ghi đè nút được chọn)
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        // Chỉ hover nếu không phải nút được chọn
        if ((int)i != player->get_indexWeapon())
            buttons[i].update(window);
    }
}

void WeaponSelectUI::render(sf::RenderWindow &window)
{
    int index = player->get_indexWeapon();
    auto &weapons = player->get_weapons();

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        // Đặt màu nút: vàng nếu chọn, bình thường nếu không
        if ((int)i == index)
            buttons[i].setFillColor(sf::Color::Yellow);
        else
            buttons[i].setFillColor(sf::Color(100, 100, 100));

        // Icon
        buttons[i].setIcon(weapons[i]->get_path());
        buttons[i].setIconScale(0.25f, 0.25f);

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
            notificationText.setStyle(sf::Text::Bold);
            notificationText.setPosition(
                (size.x - bounds.width) / 2.f,
                (size.y - bounds.height) / 2.f - 200.f
            );
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
    notificationText.setOutlineThickness(3.f);
    notificationText.setOutlineColor(sf::Color::Black);
    notificationText.setStyle(sf::Text::Bold);
    notificationText.setCharacterSize(80);
    showNotification = true;
    notificationClock.restart();
}
