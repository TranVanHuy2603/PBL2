#pragma once
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Character.h"
#include "Castle.h"
#include "Quadtree.h"

class EntityManager {
private:
    Vector<Entity*> entities; //tat ca cac vat the
    Quadtree quadtree; //cay quadtree

    Character* player = nullptr;
    Castle* castle = nullptr;

public:
    EntityManager(const Rect&);
    ~EntityManager();

    void add(Entity*);
    void remove(Entity*);

    Character* getPlayer();
    Castle* getCastle();
    Vector<Entity*>& getEntities();
    
    void set_player(Character*);
    void set_castle(Castle*);

    void updateAll(float, Quadtree*, Vector<Vector<ASNode>>&, double);
    void drawAll(sf::RenderWindow&);

    Vector<Entity*> queryRange(const Rect&);
};
