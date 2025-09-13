#include <string>
#pragma once

class Entity //class dai dien cho mot vat the
{
    protected:
        int x, y; //toa do
        double radius; //ban kinh tac dong
        bool walkable; //di qua duoc hay khong
    public:
        Entity(int, int, double);
        int get_x() const;
        int get_y() const;
        int get_radius() const;

        void set_position(int, int);
        bool is_walkable() const;
};
