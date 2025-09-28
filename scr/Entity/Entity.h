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
    string type;
    sf::Sprite sprite; // Hinh anh duoc hien thi tren game
    Vector<sf::Vector2f> path;

public:
    Entity();
    Entity(int, int);
    int get_x() const;
    int get_y() const;
    string get_type() const;

    void set_position(int, int);
    bool is_walkable() const;
    sf::Sprite get_sprite() const;
    virtual void draw(sf::RenderWindow &); // ve hinh anh ra cua so game
};
