#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "String.h"
using namespace std;
class Entity // class dai dien cho mot vat the
{
protected:
    int x, y;          // toa do
    bool walkable;     // di qua duoc hay khong
    String type;       // loai vat the
    sf::Sprite sprite; // Hinh anh duoc hien thi tren game
    bool status = true;// trang thai

public:
    Entity();
    Entity(int, int);
    virtual ~Entity() = 0;

    int get_x() const;
    int get_y() const;
    bool get_status() const;
    sf::Sprite get_sprite() const;

    void set_position(int, int);

    bool is_walkable() const;

    virtual void draw(sf::RenderWindow &);
};
