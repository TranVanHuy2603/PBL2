#include "EntityManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

EntityManager::~EntityManager()
{ // ham huy
    for (auto *e : entities)
    {
        delete e;
    }
    entities.clear();
}

void EntityManager::add(Entity *e)
{
    entities.push_back(e); // them mot vst the vao
}

void EntityManager::remove(Entity *e)
{
    entities.remove(e);
    delete e;
}

Character *EntityManager::getPlayer()
{
    for (auto *e : entities)
    {                                                     // duyet tat ca cac vat the
        Character *player = dynamic_cast<Character *>(e); // ep kieu neu la character
        if (player && player->get_type() == "Character")
        { // xem lai cho chac chan co phai la nguoic hoi khong
            return player;
        }
    }
    return nullptr; // eu khong thi tra ve con tro trong
}

Vector<Entity*>& EntityManager::getEntities()
{
    return entities; // tra ve danh sach vat the
}

void EntityManager::updateAll(float dt)
{
    for (auto *e : entities)
    {
         // update tat ca
    }
}

void EntityManager::drawAll(sf::RenderWindow &window)
{
    for (auto *e : entities)
    {
        e->draw(window); // duyet tat ca vat the va ve ra
    }
}
