#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Castle.h"
#include "Character.h"
#include "CircleButton.h"
#include "RectangleButton.h"

class UpgradeCastleUI
{
private:
    sf::Font font;

    // Nút mở menu nâng cấp (hình tròn có icon)
    CircleButton houseButton;

    // Hai nút nâng cấp & hủy
    RectangleButton upgradeButton;
    RectangleButton cancelButton;

    // Hiển thị chi phí nâng cấp
    sf::Text costText;

    bool showMenu = false;

    // Thông báo kết quả nâng cấp
    sf::Text notificationText;
    bool showNotification = false;
    sf::Clock notificationClock;

public:
    UpgradeCastleUI();

    void handleEvent(sf::Event& event, Character* player, Castle* castle, sf::RenderWindow& window);
    void render(sf::RenderWindow& window, Castle*);

private:
    void showNotificationText(const String& text, sf::Color color);
};
