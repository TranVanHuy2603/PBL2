#pragma once
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Character.h"
#include "Map.h"

class EntityManager {
private:
    Vector<Entity*> entities; //tat ca cac vat the
    Quadtree qt; //cay quadtree

    Character* player = nullptr;
    Castle* castle = nullptr;

public:
    EntityManager(const Rect&, double);
    ~EntityManager();

    void add(Entity*);
    void remove(Entity*);

    Character* getPlayer();
    Castle* getCastle();
    Vector<Entity*>& getEntities();
    Quadtree& getQuadtree();
    
    void set_player(Character*);
    void set_castle(Castle*);

    void update(float, /*Vector<Vector<ASNode>>&, double,*/ Map&, EntityManager&);
    void render(sf::RenderWindow&);

    Vector<Entity*> queryRange(const Rect&);

    void create_monster(int, int, int, int);
    void create_resource(int);

    void clear();
    
    void updateQuadtree();
};
