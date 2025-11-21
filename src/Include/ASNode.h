#pragma once

class ASNode
{
private:
    int x, y;       // CHỈ SỐ GRID → phải là int
    bool walkable;
    ASNode* parent;
    double g, h;

public:
    ASNode();
    ASNode(int _x, int _y);

    double f() const;

    int get_x() const;
    int get_y() const;

    void set_walkable(bool w);
    bool get_walkable() const;

    void set_parent(ASNode* p);
    ASNode* get_parent() const;

    void set_g(double val);
    void set_h(double val);

    double get_g() const;
    double get_h() const;
};
