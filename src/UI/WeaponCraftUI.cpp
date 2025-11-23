#include "WeaponCraftUI.h"
#include "Weapons.h"

// du lieu vu khi (bo qua BareHand)
static const WeaponInfo weaponInfos[] = {
    {"KIEM GO", "assets/weapon/woodensword.png"},
    {"KIEM SAT", "assets/weapon/ironsword.png"},
    {"RIU", "assets/weapon/ax.png"},
    {"CUNG TEN", "assets/weapon/bow.png"},
    {"SUNG", "assets/weapon/gun.png"},
};

WeaponCraftUI::WeaponCraftUI(sf::RenderWindow &window) : showList(false)
{
    if (!font.loadFromFile("assets/font/font1.ttf"))
        std::cerr << "Loi tai font!\n";

    cartButton = CircleButton(35.f);
    cartButton.setPosition(50.f, 980.f);
    cartButton.setColor(sf::Color(220, 120, 120));
    cartButton.setOutline(sf::Color::Black, 4.f);
    cartButton.setIconScale(0.14f, 0.14f);
    cartButton.setTexture("assets/icon/cart.png");

    craftTitleText.setFont(font);
    craftTitleText.setCharacterSize(100);
    craftTitleText.setStyle(sf::Text::Bold);
    craftTitleText.setString("CHE TAO VU KHI");
    craftTitleText.setOutlineThickness(3.0f);
    craftTitleText.setOutlineColor(sf::Color::Black);
    craftTitleText.setOutlineColor(sf::Color::Black);
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
    float startX = (winSize.x - totalWidth) / 2.f + 20;
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
        btn.setTextColor(sf::Color::Yellow);

        // Căn giữa text dưới button
        sf::FloatRect b = btn.getBounds();
        btn.setTextPosition(b.left + b.width / 2.f, b.top + b.height - 15.f);
    }
}

void WeaponCraftUI::handleEvent(sf::Event &event, Character *player, sf::RenderWindow &window)
{
    int weaponCount = sizeof(weaponInfos) / sizeof(WeaponInfo);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::V)
        {
            showList = !showList;
            return;
        }

        if (showList)
        {
            for (int i = 0; i < weaponCount; ++i)
            {
                sf::Keyboard::Key keyNeeded = static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + i);
                if (event.key.code == keyNeeded)
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
                        showNotificationText("Khong du tai nguyen de che tao vu khi!", sf::Color::Red);
                        static Audio failSound("assets/audio/error.ogg");
                        failSound.setVolume(40.f);
                        failSound.playSound();
                    }

                    showList = false; // đóng menu sau khi mua
                    return;
                }
            }
        }
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        if (cartButton.isClicked(window, event))
        {
            showList = !showList;
            return;
        }

        if (showList)
        {
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
                        showNotificationText("Khong du tai nguyen de che tao vu khi!", sf::Color::Red);
                        static Audio failSound("assets/audio/error.ogg");
                        failSound.setVolume(40.f);
                        failSound.playSound();
                    }

                    showList = false; 
                    return;
                }
            }
        }
    }
}


void WeaponCraftUI::drawRecipeText(sf::RenderWindow &window, RectangleButton &btn, Recipe &r, Bag &bag)
{
    sf::Text recipeText;
    recipeText.setFont(font);
    recipeText.setCharacterSize(30); // chỉnh size lớn hơn
    recipeText.setStyle(sf::Text::Bold);
    recipeText.setOutlineThickness(2.f);
    recipeText.setOutlineColor(sf::Color::Black);

    sf::FloatRect b = btn.getBounds();
    float startX = b.left + b.width / 4 - 20.f;
    float startY = b.top - 200.f;

    // vẽ từng loại nguyên liệu với màu đỏ nếu thiếu
    recipeText.setString("GO......" + std::to_string(r.wood));
    recipeText.setFillColor(bag.getWood() >= r.wood ? sf::Color::Green : sf::Color::White);
    recipeText.setPosition(startX, startY);
    window.draw(recipeText);

    recipeText.setString("CAT....." + std::to_string(r.sand));
    recipeText.setFillColor(bag.getSand() >= r.sand ? sf::Color::Green : sf::Color::White);
    recipeText.setPosition(startX, startY + 25);
    window.draw(recipeText);

    recipeText.setString("DA......" + std::to_string(r.stone));
    recipeText.setFillColor(bag.getStone() >= r.stone ? sf::Color::Green : sf::Color::White);
    recipeText.setPosition(startX, startY + 50);
    window.draw(recipeText);

    recipeText.setString("THAN...." + std::to_string(r.coal));
    recipeText.setFillColor(bag.getCoal() >= r.coal ? sf::Color::Green : sf::Color::White);
    recipeText.setPosition(startX, startY + 75); // cách nhau 14 px
    window.draw(recipeText);

    recipeText.setString("SAT....." + std::to_string(r.iron));
    recipeText.setFillColor(bag.getIron() >= r.iron ? sf::Color::Green : sf::Color::White);
    recipeText.setPosition(startX, startY + 100);
    window.draw(recipeText);

    recipeText.setString("VANG...." + std::to_string(r.gold));
    recipeText.setFillColor(bag.getGold() >= r.gold ? sf::Color::Green : sf::Color::White);
    recipeText.setPosition(startX, startY + 125);
    window.draw(recipeText);

    recipeText.setString("KCUONG.." + std::to_string(r.diamond));
    recipeText.setFillColor(bag.getDiamond() >= r.diamond ? sf::Color::Green : sf::Color::White);
    recipeText.setPosition(startX, startY + 150);
    window.draw(recipeText);

    recipeText.setString("NGOCLB.." + std::to_string(r.emerald));
    recipeText.setFillColor(bag.getEmerald() >= r.emerald ? sf::Color::Green : sf::Color::White);
    recipeText.setPosition(startX, startY + 175);
    window.draw(recipeText);
}

void WeaponCraftUI::render(sf::RenderWindow &window, Character *player)
{
    cartButton.render(window);

    sf::Vector2u winSize = window.getSize();
    sf::FloatRect textBounds = craftTitleText.getLocalBounds();
    craftTitleText.setPosition((winSize.x - textBounds.width) / 2.f, 200.f);

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
                              bag.getSand() < r.sand ||
                              bag.getStone() < r.stone ||
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
    notificationText.setOutlineThickness(3.f);
    notificationText.setOutlineColor(sf::Color::Black);
    notificationText.setStyle(sf::Text::Bold);
    notificationText.setCharacterSize(80);
    showNotification = true;
    notificationClock.restart();
}
