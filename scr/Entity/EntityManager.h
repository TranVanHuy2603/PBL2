#pragma once
#include <Vector.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Character.h"
#include "Monster.h"

class EntityManager {
private:
    Vector<Entity*> entities; //danh sach cac vat the  (con tro)

public:
    EntityManager() = default;
    ~EntityManager();

    void add(Entity*); //them vat the
    void remove(Entity*); //xoa vat the

    Character* getPlayer(); //tra ve nguoi choi
    Vector<Entity*>& getEntities(); //tra ve vat the

    void updateAll(float); //cap nhat tat ca
    void drawAll(sf::RenderWindow&); //ve

    void save(const std::string&); //luu
    void load(const std::string&); //doc du lieu tu file
};
