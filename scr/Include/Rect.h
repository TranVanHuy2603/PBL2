#include "Entity.h"
#pragma once

class Rect //mot hinh chu nhat cho quadtree quan li
{
    private:
        int x, y; //toa do cua tam
        int w, h; //nua chieu rong va chieu dai
    public:
        Rect(int, int, int, int);
        
        int get_x() const;
        int get_y() const;
        int get_w() const;
        int get_h() const;

        bool contains(const Entity* e) const; //kiem tra xem mot vat the co nam trong vung do khong
        bool intersects(const Rect& range) const; //kiem tra hai vung co nam chong len nhau khong
};