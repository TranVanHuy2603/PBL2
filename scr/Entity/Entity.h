#include <string>
#include <SFML/Graphics.hpp>
#pragma once

class Entity //class dai dien cho mot vat the
{
    protected:
        int x, y; //toa do
        double radius; //ban kinh tac dong
        bool walkable; //di qua duoc hay khong
        sf::Sprite sprite; //Hinh anh duoc hien thi tren game
    public:
        Entity(int, int, double);
        int get_x() const;
        int get_y() const;
        int get_radius() const;

        void set_position(int, int);
        bool is_walkable() const;
        virtual void draw(sf::RenderWindow&); //ve hinh anh ra cua so game
};
