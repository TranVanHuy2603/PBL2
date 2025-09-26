#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Character.h"

struct WeaponButton {
    sf::RectangleShape rect;        // hình chữ nhật làm nền ô
    sf::Texture texture;
    sf::Text label;                 // tên hoặc thông tin vũ khí
    sf::Sprite icon;
};

class Character;

class WeaponMenu {
private:
    Vector<WeaponButton> buttons;
    bool visible = false;

public:
    void create(int startX, int startY, Vector<std::string>& icon);
    void draw(sf::RenderWindow& window);
    void handleClick(int mouseX, int mouseY, Character* player);
    void toggle() { visible = !visible; }
    bool isVisible() const { return visible; }
};
