#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Character.h"

struct WeaponButton {
    sf::RectangleShape rect;        // hình chữ nhật làm nền ô
    sf::Texture texture;            // anh icon
    sf::Text label;                 // tên hoặc thông tin vũ khí
    sf::Sprite icon;                //anh
    WeaponType type;                //loai vu khi
};

class Character;

class WeaponMenu {
private:
    Vector<WeaponButton> buttons; //danh sach cac button
    bool visible = false; //co duoc hien thi khong
    sf::Font font; //font chu

public:
    WeaponMenu();
    void create(int, int, Vector<String>&, Vector<WeaponType>&); //tao menu
    void draw(sf::RenderWindow&); //ve
    void handleClick(int, int, Character*); //xu li chon bang click chuot
    void toggle(); //bat tat menu 
    bool isVisible() const; //kiem tra menu co duoc hien thi khong
};
