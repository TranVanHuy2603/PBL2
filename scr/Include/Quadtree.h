#include "Rect.h"
#include "Entity.h"
#include "Vector.h"
#pragma once

class Quadtree
{
private:
    Rect area;                      // vung chu nhat ma quadtree quan li
    double capacity;                // so luong vat the toi da chua trong mot o
    Vector<Entity *> entities; // danh sach cac vat the
    bool divided;
    // cac o con
    Quadtree *NW; // tay bac
    Quadtree *NE; // dong bac
    Quadtree *SW; // tay nam
    Quadtree *SE; // dong nam
public:
    Quadtree(Rect, double);
    ~Quadtree();

    void subdivide();                          // chia nho o
    bool insert(Entity *);                     // them vat the
    void query(Rect, Vector<Entity *> &); // truy van
    bool remove(Entity *);
    bool update(Entity *, double, double);
    double count(Rect r);
    void clear();
    void getAllEntities(Vector<Entity *> &);
};
