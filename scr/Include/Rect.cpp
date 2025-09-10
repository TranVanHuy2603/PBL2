#include "Rect.h"

Rect::Rect(int _x, int _y, int _w, int _h)
    : x(_x), y(_y), w(_w), h(_h) {};

int Rect::get_x() const { return x; }
int Rect::get_y() const { return y; }
int Rect::get_w() const { return w; }
int Rect::get_h() const { return h; }

bool Rect::contains(const Entity* e) const
{
    return e->get_x() - x <= w && e->get_x() - x >= -w 
        && e->get_y() - y <= h && e->get_y() - y >= -h; 
}

bool Rect::intersects(const Rect& r) const
{
    return !(r.get_x() - r.get_w() > x + w ||
             r.get_x() + r.get_w() < x - w ||
             r.get_y() - r.get_h() > y + h ||
             r.get_y() + r.get_h() < y - h  );
}