#include <string>
#include <SFML/Graphics.hpp>
#pragma once
using namespace std;

class Entity // class dai dien cho mot vat the
{
protected:
    int x, y;          // toa do
    double radius;     // ban kinh tac dong
    bool walkable;     // di qua duoc hay khong
    string type;
    sf::Sprite sprite; // Hinh anh duoc hien thi tren game
    vector<sf::Vector2f> path;
    int currentTarget = 0;

public:
    Entity();
    Entity(int, int, double);
    int get_x() const;
    int get_y() const;
    int get_radius() const;
    string get_type() const;

    void set_position(int, int);
    bool is_walkable() const;
    sf::Sprite get_sprite() const;
    virtual void draw(sf::RenderWindow &); // ve hinh anh ra cua so game
    virtual void update(float) = 0;
    virtual string serialize() const = 0;
    virtual void deserialize(std::istream&) = 0;
};
