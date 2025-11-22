#include "WeaponCraftUI.h"
#include "Weapons.h"

// du lieu vu khi (bo qua BareHand)
static const WeaponInfo weaponInfos[] = {
    {"Wooden Sword", "assets/weapon/woodensword.png"},
    {"Iron Sword", "assets/weapon/ironsword.png"},
    {"Axe", "assets/weapon/ax.png"},
    {"Bow", "assets/weapon/bow.png"},
    {"Gun", "assets/weapon/gun.png"},
};

WeaponCraftUI::WeaponCraftUI(sf::RenderWindow &window) : showList(false)
{
    if (!font.loadFromFile("assets/font/font1.ttf"))
        std::cerr << "Loi tai font!\n";

    cartButton = CircleButton(35.f);
    cartButton.setPosition(50.f, 980.f);
    cartButton.setColor(sf::Color(220, 120, 120));
    cartButton.setOutline(sf::Color::Black, 3.f);
    cartButton.setIconScale(0.14f, 0.14f);
    cartButton.setTexture("assets/icon/cart.png");

    craftTitleText.setFont(font);
    craftTitleText.setCharacterSize(100);
    craftTitleText.setStyle(sf::Text::Bold);
    craftTitleText.setString("CHE TAO VU KHI");
    craftTitleText.setFillColor(sf::Color::White);

    initWeaponButtons(window);
}

void WeaponCraftUI::initWeaponButtons(sf::RenderWindow &window)
{
    int weaponCount = sizeof(weaponInfos) / sizeof(WeaponInfo);
    float buttonWidth = 180.f;
    float buttonHeight = 180.f;
    float spacing = 80.f;

    // Tính tổng chiều rộng của dãy button
    float totalWidth = weaponCount * buttonWidth + (weaponCount - 1) * (spacing);
    sf::Vector2u winSize = window.getSize();

    // Lấy vị trí startX để căn giữa theo chiều ngang
    float startX = (winSize.x - totalWidth) / 2.f;
    float startY = 700.f; // giữ vị trí y ở dưới, có thể tinh chỉnh

    for (int i = 0; i < weaponCount; ++i)
    {
        RectangleButton &btn = weaponButtons[i];

        // Khởi tạo RectangleButton
        float x = startX + i * (buttonWidth + spacing);
        btn = RectangleButton(
            x, startY,
            buttonWidth, buttonHeight,
            &font,
            weaponInfos[i].name.c_str(),
            sf::Color(100, 100, 100),
            sf::Color(150, 150, 150),
            sf::Color(160, 160, 160),
            30);

        // Icon
        btn.setIcon(weaponInfos[i].iconPath.c_str());
        btn.setIconScale(0.5f, 0.5f);

        // Text dưới button
        // btn.setString(weaponInfos[i].name.c_str());
        btn.setTextColor(sf::Color::Black);

        // Căn giữa text dưới button
        sf::FloatRect b = btn.getBounds();
        btn.setTextPosition(b.left + b.width / 2.f, b.top + b.height - 15.f);
    }
}

void WeaponCraftUI::handleEvent(sf::Event &event, Character *player, sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (cartButton.isClicked(window, event))
        {
            showList = !showList;
            return;
        }

        if (showList)
        {
            int weaponCount = sizeof(weaponInfos) / sizeof(WeaponInfo);
            for (int i = 0; i < weaponCount; ++i)
            {
                RectangleButton &wb = weaponButtons[i];
                if (wb.isClicked(window, event))
                {
                    if (player->craft_weapon(static_cast<WeaponType>(i + 1)))
                    {
                        showNotificationText("Da che tao vu khi thanh cong!", sf::Color::Green);
                        static Audio craftSound("assets/audio/collect.ogg");
                        craftSound.setVolume(40.f);
                        craftSound.playSound();
                    }

                    else
                    {
                        static Audio notenoughmoney("assets/audio/error.ogg");
                        notenoughmoney.setVolume(40.f);
                        notenoughmoney.playSound();
                        showNotificationText("Khong du tai nguyen de che tao vu khi!", sf::Color::Red);
                    }
                }
                showList = !showList;
            }
        }
    }
}

void WeaponCraftUI::drawRecipeText(sf::RenderWindow &window, RectangleButton &btn, Recipe &r, Bag &bag)
{
    sf::Text recipeText;
    recipeText.setFont(font);
    recipeText.setCharacterSize(35); // chỉnh size lớn hơn
    recipeText.setStyle(sf::Text::Bold);

    sf::FloatRect b = btn.getBounds();
    float startX = b.left + b.width / 4 - 20.f;
    float startY = b.top - 150.f;

    // vẽ từng loại nguyên liệu với màu đỏ nếu thiếu
    recipeText.setString("Go: " + std::to_string(r.wood));
    recipeText.setFillColor(bag.getWood() >= r.wood ? sf::Color::Green : sf::Color::Red);
    recipeText.setPosition(startX, startY);
    window.draw(recipeText);

    recipeText.setString("Than: " + std::to_string(r.coal));
    recipeText.setFillColor(bag.getCoal() >= r.coal ? sf::Color::Green : sf::Color::Red);
    recipeText.setPosition(startX, startY + 20); // cách nhau 14 px
    window.draw(recipeText);

    recipeText.setString("Sat: " + std::to_string(r.iron));
    recipeText.setFillColor(bag.getIron() >= r.iron ? sf::Color::Green : sf::Color::Red);
    recipeText.setPosition(startX, startY + 40);
    window.draw(recipeText);

    recipeText.setString("Vang: " + std::to_string(r.gold));
    recipeText.setFillColor(bag.getGold() >= r.gold ? sf::Color::Green : sf::Color::Red);
    recipeText.setPosition(startX, startY + 60);
    window.draw(recipeText);

    recipeText.setString("KCuong: " + std::to_string(r.diamond));
    recipeText.setFillColor(bag.getDiamond() >= r.diamond ? sf::Color::Green : sf::Color::Red);
    recipeText.setPosition(startX, startY + 80);
    window.draw(recipeText);

    recipeText.setString("NgocLB: " + std::to_string(r.emerald));
    recipeText.setFillColor(bag.getEmerald() >= r.emerald ? sf::Color::Green : sf::Color::Red);
    recipeText.setPosition(startX, startY + 100);
    window.draw(recipeText);
}

void WeaponCraftUI::render(sf::RenderWindow &window, Character *player)
{
    cartButton.render(window);

    sf::Vector2u winSize = window.getSize();
    sf::FloatRect textBounds = craftTitleText.getLocalBounds();
    craftTitleText.setPosition((winSize.x - textBounds.width) / 2.f - textBounds.top, 200.f);

    if (showList)
    {
        int weaponCount = sizeof(weaponInfos) / sizeof(WeaponInfo);
        Bag bag = player->get_bag();

        for (int i = 0; i < weaponCount; ++i)
        {
            RectangleButton &wb = weaponButtons[i];
            wb.update(window);
            // Lấy recipe của vũ khí i
            Recipe r = recipes[i + 1]; // bỏ qua BareHand, WeaponType bắt đầu từ 1

            bool canCraft = !(bag.getWood() < r.wood ||
                              bag.getCoal() < r.coal ||
                              bag.getIron() < r.iron ||
                              bag.getGold() < r.gold ||
                              bag.getDiamond() < r.diamond ||
                              bag.getEmerald() < r.emerald);

            // Đổi màu theo khả năng chế tạo
            if (canCraft)
                wb.setFillColor(sf::Color(100, 200, 100)); // xanh
            else
                wb.setFillColor(sf::Color(200, 150, 150)); // đỏ nhạt

            wb.render(window);
            drawRecipeText(window, wb, r, bag);
        }
        window.draw(craftTitleText);
    }

    if (showNotification)
    {
        float elapsed = notificationClock.getElapsedTime().asSeconds();
        if (elapsed < 3.f)
        {
            sf::Vector2u size = window.getSize();
            sf::FloatRect textBounds = notificationText.getLocalBounds();
            notificationText.setFont(font);
            notificationText.setCharacterSize(80);
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
    notificationText.setString(text);
    notificationText.setFillColor(color);
    showNotification = true;
    notificationClock.restart();
}
