#pragma once
#include "Entity.h"

class ASNode
{
private:
    int x, y;           // chi so tren grid
    bool walkable;      // co the di qua hay khong
    ASNode* parent;     // node cha de truy nguoc duong di
    int g;           // chi phi tu start den node hien tai
    int h;           // uoc luong chi phi tu node den goal

public:
    ASNode(int _x, int _y);
    int f() const; // tong chi phi

    int get_x() const;
    int get_y() const;

    void set_walkable(bool w);
    bool get_walkable() const;

    ASNode* get_parent() const;
    void set_parent(ASNode* p);

    int get_g() const;
    int get_h() const;
    void set_g(int val);
    void set_h(int val);
};
