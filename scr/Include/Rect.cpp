#include "Rect.h"

Rect::Rect(double _x, double _y, double _w, double _h)
    : x(_x), y(_y), w(_w), h(_h) {};

double Rect::get_x() const { return x; }
double Rect::get_y() const { return y; }
double Rect::get_w() const { return w; }
double Rect::get_h() const { return h; }

bool Rect::contains(const Entity* e) const
{
    return e->get_x() - x <= w && e->get_x() - x >= -w 
        && e->get_y() - y <= h && e->get_y() - y >= -h; 
}

bool Rect::doubleersects(const Rect& r) const
{
    return !(r.get_x() - r.get_w() > x + w ||
             r.get_x() + r.get_w() < x - w ||
             r.get_y() - r.get_h() > y + h ||
             r.get_y() + r.get_h() < y - h  );
}