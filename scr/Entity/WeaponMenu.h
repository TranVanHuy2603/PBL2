#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Character.h"

// button hien thi tung vu khi
struct WeaponButton {
    sf::RectangleShape rect; // nen button
    sf::Text label;          // thong tin vu khi
    sf::Sprite icon;         // anh icon
    sf::Texture texture;     // texture rieng cua button
    WeaponType type;         // loai vu khi
};

// khai bao truoc Character
class Character;

class WeaponMenu {
private:
    Vector<WeaponButton> buttons; // danh sach cac button
    sf::Font font;                // font chu
    bool visible = false;         // menu co hien thi hay khong

public:
    WeaponMenu(); // khoi tao

    // tao menu: startX/startY la toa do bat dau, icons la danh sach anh, types la danh sach vu khi
    void create(int startX, int startY, Vector<String>& icons, Vector<WeaponType>& types);

    void draw(sf::RenderWindow& window); // ve menu len cua so
    void handleClick(int mouseX, int mouseY, Character* player); // xu li click chuot
    void toggle();                        // bat/tat menu
    bool isVisible() const;               // kiem tra menu co hien thi hay khong
};
