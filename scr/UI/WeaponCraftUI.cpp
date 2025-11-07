#include "WeaponCraftUI.h"

// du lieu vu khi (bo qua BareHand)
static const WeaponInfo weaponInfos[] = {
    {"Wooden Sword", "assets/weapon/woodensword.png"},
    {"Iron Sword", "assets/weapon/ironsword.png"},
    {"Axe", "assets/weapon/axe.png"},
    {"Bow", "assets/weapon/bow.png"},
    {"Gun", "assets/weapon/gun.png"},
};

WeaponCraftUI::WeaponCraftUI(const sf::Font& font)
        : font(font), showList(false)
{
    init();
    initWeaponButtons();
}

void WeaponCraftUI::init()
{
    // nut hinh tron
    cartButton.setRadius(40.f);
    cartButton.setFillColor(sf::Color(150, 75, 0)); // mau nau
    cartButton.setPosition(20.f, 900.f);

    if (!cartTexture.loadFromFile("assets/icon/cart.png"))
        std::cerr << "Loi tai anh cart.png\n";

    cartIcon.setTexture(cartTexture);
    cartIcon.setScale(0.11f, 0.11f);
    cartIcon.setPosition(cartButton.getPosition().x + 10.f,
                         cartButton.getPosition().y + 10.f);
}

void WeaponCraftUI::initWeaponButtons()
{
    float startX = 150.f;
    float startY = 850.f;
    float spacing = 160.f;

    int weaponCount = sizeof(weaponInfos) / sizeof(WeaponInfo);
    for (int i = 0; i < weaponCount; ++i)
    {
        WeaponButton &wb = weaponButtons[i];
        wb.type = static_cast<WeaponType>(i + 1); // +1 de bo BareHand

        wb.font = &font; 
        wb.nameText.setFont(*wb.font);
        // o vu khi
        wb.button.setSize(sf::Vector2f(150.f, 150.f));
        wb.button.setFillColor(sf::Color(100, 100, 100));
        wb.button.setPosition(startX + i * spacing, startY);

        if (!weaponTextures[i].loadFromFile(weaponInfos[i].iconPath.c_str()))
            std::cerr << "Loi tai anh: " << weaponInfos[i].iconPath.c_str() << "\n";

        wb.icon.setTexture(weaponTextures[i]);
        wb.icon.setPosition(wb.button.getPosition().x + 25.f,
                            wb.button.getPosition().y + 25.f);
        wb.icon.setScale(0.4f, 0.4f);

        wb.nameText.setFont(font);
        wb.nameText.setString(weaponInfos[i].name.c_str());
        wb.nameText.setCharacterSize(12);
        wb.nameText.setFillColor(sf::Color::White);
        wb.nameText.setPosition(wb.button.getPosition().x + 10.f,
                                wb.button.getPosition().y + 120.f);
    }
}

void WeaponCraftUI::handleEvent(sf::Event &event, Character *player)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (cartButton.getGlobalBounds().contains(mousePos))
        {
            showList = !showList;
            return;
        }

        if (showList)
        {
            int weaponCount = sizeof(weaponInfos) / sizeof(WeaponInfo);
            for (int i = 0; i < weaponCount; ++i)
            {
                WeaponButton &wb = weaponButtons[i];
                if (wb.button.getGlobalBounds().contains(mousePos))
                {
                    if (player->craft_weapon(wb.type))
                        showNotificationText("Da che tao vu khi thanh cong!", sf::Color::Green);
                    else
                        showNotificationText("Khong du tai nguyen de che tao vu khi!", sf::Color::Red);
                }
            }
        }
    }
}

void WeaponCraftUI::render(sf::RenderWindow &window)
{
    window.draw(cartButton);
    window.draw(cartIcon);

    if (showList)
    {
        int weaponCount = sizeof(weaponInfos) / sizeof(WeaponInfo);
        for (int i = 0; i < weaponCount; ++i)
        {
            window.draw(weaponButtons[i].button);
            window.draw(weaponButtons[i].icon);
            window.draw(weaponButtons[i].nameText);
        }
    }

    if (showNotification)
    {
        float elapsed = notificationClock.getElapsedTime().asSeconds();
        if (elapsed < 3.f)
        {
            sf::Vector2u size = window.getSize();
            sf::FloatRect textBounds = notificationText.getLocalBounds();
            notificationText.setFont(font);
            notificationText.setCharacterSize(35);
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

void WeaponCraftUI::showNotificationText(const std::string &text, sf::Color color)
{
    notificationText.setFont(font); 
    notificationText.setString(text);
    notificationText.setFillColor(color);
    showNotification = true;
    notificationClock.restart();
}
