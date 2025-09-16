#include "Quadtree.h"
#include <vector>
#include <algorithm>

using namespace std;

Quadtree::Quadtree(Rect _area, double _capacity)
    : area(_area), capacity(_capacity), divided(false),
      NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}

Quadtree::~Quadtree()
{
    delete NW;
    delete NE;
    delete SW;
    delete SE;
}

void Quadtree::subdivide()
{
    double x = area.get_x();
    double y = area.get_y();
    double w = area.get_w() / 2;
    double h = area.get_h() / 2;

    NE = new Quadtree(Rect(x + w, y - h, w, h), capacity);
    NW = new Quadtree(Rect(x - w, y - h, w, h), capacity);
    SE = new Quadtree(Rect(x + w, y + h, w, h), capacity);
    SW = new Quadtree(Rect(x - w, y + h, x, h), capacity);

    divided = true;
}

bool Quadtree::insert(Entity *e)
{
    if (!area.contains(e))
        return false;
    else
    {
        if (entities.size() < capacity)
            entities.push_back(e);
        else
        {
            if (!divided)
                subdivide();
            if (NE->insert(e))
                return true;
            if (NW->insert(e))
                return true;
            if (SW->insert(e))
                return true;
            if (SE->insert(e))
                return true;
        }
    }
    return false;
}

void Quadtree::query(Rect r, vector<Entity*> &found) // chuc nang tim tat ca cac vat the nam trong hinh chu nhat r va luu vao found
{
    if (area.doubleersects(r))
        return;

    for (auto &e : entities) // duyet tat ca
    {
        if (r.contains(e))
            found.push_back(e); // neu nhu r chua e thi them vao found
    }
    if (divided) // neu nhu cay tree da duoc chia nho thi tim kiem trong cac cay con
    {
        NW->query(r, found);
        NE->query(r, found);
        SW->query(r, found);
        SE->query(r, found);
    }
}

bool Quadtree::remove(Entity *e)
{
    if (!area.contains(e))
        return false;
    auto it = find(entities.begin(), entities.end(), e);
    if (it != entities.end())
    {
        entities.erase(it);
        return true;
    }

    if (divided)
    {
        if (SW->remove(e))
            return true;
        if (SE->remove(e))
            return true;
        if (NW->remove(e))
            return true;
        if (NE->remove(e))
            return true;
    }
    return false;
}

bool Quadtree::update(Entity *e, double newx, double newy)
{
    remove(e);
    e->set_position(newx, newy);
    return insert(e);
}

double Quadtree::count(Rect r)
{
    vector<Entity *> res;
    query(r, res);
    return res.size();
}

void Quadtree::clear()
{
    entities.clear();
    if (divided)
    {
        NW->clear();
        delete NW;
        NW = nullptr;
        NE->clear();
        delete NE;
        NE = nullptr;
        SW->clear();
        delete SW;
        SW = nullptr;
        SE->clear();
        delete SE;
        SE = nullptr;
        divided = false;
    }
}

void Quadtree::getAllEntities(std::vector<Entity *> &all)
{
    for (auto e : entities)
        all.push_back(e);
    if (divided)
    {
        NW->getAllEntities(all);
        NE->getAllEntities(all);
        SW->getAllEntities(all);
        SE->getAllEntities(all);
    }
}
