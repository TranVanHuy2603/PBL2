#include "WeaponMenu.h"
#include <iostream>

// global function: chuyen WeaponType sang chuoi
const char* weaponTypeToCStr(WeaponType type) {
    switch (type) {
        case WeaponType::WoodenSword: return "Wooden Sword:\n3 Wood - 1 Coal";
        case WeaponType::IronSwood:   return "Iron Sword:\n4 Iron - 2 Coal - 1 Wood";
        case WeaponType::Ax:          return "Ax:\n3 Iron - 1 Coal - 3 Wood";
        case WeaponType::Bow:         return "Bow:\n2 Iron - 1 Coal - 2 Wood\n2 Gold";
        case WeaponType::Gun:         return "Gun:\n3 Iron - 1 Coal - 1 Wood\n4 Gold - 3 Diamond - 1 Emerald";
        default: return "Unknown Weapon";
    }
}

// khoi tao menu
WeaponMenu::WeaponMenu() {
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "ERROR: Khong load duoc font arial.ttf\n";
    }
    visible = false;
}

// tao cac button trong menu
void WeaponMenu::create(int startX, int startY, Vector<String>& icons, Vector<WeaponType>& types) {
    const int size = 60;   // kich thuoc button
    const int space = 30;  // khoang cach giua cac button

    std::cout << "icons size = " << icons.get_size() << "\n";

    for (int i = 0; i < icons.get_size(); i++) {
        WeaponButton btn;
        btn.rect.setSize(sf::Vector2f(size, size));
        btn.rect.setFillColor(sf::Color::Red); // màu nổi bật để test
        btn.rect.setPosition(startX, startY + i * (size + space));

        std::cout << "Load icon " << icons[i] << "...\n";
        if (!btn.texture.loadFromFile(icons[i].c_str())) {
            std::cerr << "Khong load duoc icon " << icons[i] << "\n";
        } else {
            std::cout << "Loaded " << icons[i] << "\n";
        }

        btn.icon.setTexture(btn.texture);
        btn.icon.setPosition(startX, startY + i * (size + space));

        btn.type = types[i];

        btn.label.setFont(font);
        btn.label.setCharacterSize(12);
        btn.rect.setFillColor(sf::Color::Red);
        btn.label.setString(weaponTypeToCStr(types[i]));
        btn.label.setPosition(startX + size + 5, startY + i * (size + space) + 20);

        buttons.push_back(btn);
    }

    std::cout << "Da tao " << buttons.get_size() << " buttons\n";
}

// ve menu
void WeaponMenu::draw(sf::RenderWindow& window) {
    std::cout << "Goi draw() - visible = " << (visible ? "true" : "false") 
              << ", buttons = " << buttons.get_size() << "\n";

    if (!visible) {
        std::cout << "⚠️ Menu khong hien thi do visible = false\n";
        return;
    }

    for (int i = 0; i < buttons.get_size(); i++) {
        window.draw(buttons[i].rect);
        window.draw(buttons[i].icon);
        window.draw(buttons[i].label);
    }
}


// xu li click chuot
void WeaponMenu::handleClick(int mouseX, int mouseY, Character* player) {
    if (!visible) return;

    for (int i = 0; i < buttons.get_size(); i++) {
        if (buttons[i].rect.getGlobalBounds().contains(mouseX, mouseY)) {
            bool crafted = player->craft_weapon(buttons[i].type);
            if (crafted) {
                std::cout << "Che tao " << weaponTypeToCStr(buttons[i].type) << " thanh cong\n";
            } else {
                std::cout << "Khong du tai nguyen de che tao " << weaponTypeToCStr(buttons[i].type) << "\n";
            }
            return;
        }
    }
}

// bat/tat menu
void WeaponMenu::toggle() {
    visible = !visible;
}

// kiem tra menu co hien thi hay khong
bool WeaponMenu::isVisible() const {
    return visible;
}
