#pragma once
#include "Entity.h"

class ASNode
{
private:
    double x, y;    // chi so tren grid
    bool walkable;  // co the di qua hay khong
    ASNode *parent; // node cha de truy nguoc duong di
    double g;       // chi phi tu start den node hien tai
    double h;       // uoc luong chi phi tu node den goal

public:
    ASNode(); 
    ASNode(double _x, double _y);
    double f() const; // tong chi phi

    double get_x() const;
    double get_y() const;

    void set_walkable(bool w);
    bool get_walkable() const;

    ASNode *get_parent() const;
    void set_parent(ASNode *p);

    double get_g() const;
    double get_h() const;
    void set_g(double val);
    void set_h(double val);
};
