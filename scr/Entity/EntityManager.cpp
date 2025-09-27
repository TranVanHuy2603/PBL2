#include "EntityManager.h"
#include "Monster.h"
#include "Castle.h"
#include "Character.h"
#include <iostream>

using namespace std;

EntityManager::~EntityManager()
{
    for (auto *e : entities)
    {
        delete e;
    }
    entities.clear();
}

void EntityManager::add(Entity *e)
{
    entities.push_back(e);
}

void EntityManager::remove(Entity *e)
{
    entities.remove(e);
    delete e;
}

Character* EntityManager::getPlayer() { return player; }

Castle* EntityManager::getCastle() { return castle; }

Vector<Entity*>& EntityManager::getEntities()
{
    return entities;
}

void EntityManager::set_player(Character* value) { player = value; }
void EntityManager::set_castle(Castle* value) { castle = value; }

void EntityManager::updateAll(float dt, Quadtree* qt, Vector<Vector<ASNode>>& grid, double cellSize)
{
    Castle* castle   = getCastle();
    Character* player = getPlayer();

    for (auto *e : entities)//duyet tat ca vat the
    {
        if (Monster* m = dynamic_cast<Monster*>(e))
        {
            //quai tim duong tan cong bang A*
            m->update(dt, castle, player, qt, grid, cellSize);
        }

    }
    castle->update(dt);
    player->update(dt);
}

void EntityManager::drawAll(sf::RenderWindow &window)
{
    for (auto *e : entities)
        e->draw(window);
}
