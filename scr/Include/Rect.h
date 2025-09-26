#include "Entity.h"
#pragma once

class Rect // mot hinh chu nhat cho quadtree quan li
{
private:
    double x, y; // toa do cua tam
    double w, h; // nua chieu rong va chieu dai
public:
    Rect(double, double, double, double);

    double get_x() const;
    double get_y() const;
    double get_w() const;
    double get_h() const;

    bool contains(const Entity *e) const;        // kiem tra xem mot vat the co nam trong vung do khong
    bool doubleersects(const Rect &range) const; // kiem tra hai vung co nam chong len nhau khong
};