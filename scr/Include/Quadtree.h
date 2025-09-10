#include "Rect.h"
#include "Entity.h"
#include <vector>
#pragma once

class Quadtree
{
    private:
        Rect area; //vung chu nhat ma quadtree quan li
        int capacity; //so luong vat the toi da chua trong mot o 
        std::vector<Entity*> entities; //danh sach cac vat the
        bool divided;
        //cac o con
        Quadtree *NW; //tay bac
        Quadtree *NE; //dong bac
        Quadtree *SW; //tay nam
        Quadtree *SE; //dong nam
    public:
        Quadtree(Rect, int);
        ~Quadtree();

        void subdivide(); //chia nho o
        bool insert(Entity*); //them vat the
        void query(Rect, std::vector<Entity*>&); //truy van 
        bool remove(Entity*);
        bool update(Entity*, int, int);
        int count(Rect r);
        void clear();
        void getAllEntities(std::vector<Entity*>&);
};

