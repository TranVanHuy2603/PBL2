#pragma once
#define _HAS_STD_BYTE 0

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Entity.h"
#include "Character.h"
#include "Castle.h"
#include "Quadtree.h"
#include "Resource.h"
#include "ASNode.h"
#include "Rect.h"

// Lop quan ly tat ca vat the trong game (Player, Castle, Monster, Resource, ...)
class EntityManager
{
private:
    Vector<Entity*> entities; // Danh sach tat ca vat the trong game
    Quadtree qt;              // Cay quadtree dung cho viec truy van nhanh (vd: tim doi tuong gan nhat)

    Character* player = nullptr; // Nhan vat nguoi choi
    Castle* castle = nullptr;    // Thanh chinh cua nguoi choi

public:
    // ======== Khoi tao / huy ========
    EntityManager(const Rect& area, double capacity);
    ~EntityManager();

    // ======== Cac ham quan ly co ban ========

    // Them 1 vat the tĩnh (resource, nha, cay, castle, ...)
    void add(Entity* e);

    // Xoa 1 vat the ra khoi game
    void remove(Entity* e);

    // ======== Truy cap doi tuong dac biet ========
    Character* getPlayer();
    Castle* getCastle();

    // Lay danh sach tat ca vat the
    Vector<Entity*>& getEntities();
    const Vector<Entity*>& getEntities() const;

    // Lay quadtree hien tai (phuc vu cho A*, tan cong, ... )
    Quadtree& getQuadtree();

    // Gan nhan vat va thanh
    void set_player(Character* value);
    void set_castle(Castle* value);

    // ======== Tao doi tuong ========

    // --- Monster ---
    void create_monster(int n);             // Tao n quai vat ngau nhien
    void create_monster_at(float x, float y); // Tao 1 quai vat tai vi tri chi dinh

    // --- Resource ---
    void create_resource(int n);            // Tao n tai nguyen ngau nhien
    void create_resource_at(int x, int y);  // Tao tai nguyen tai vi tri chi dinh

    // ======== Cap nhat & ve ========

    // Cap nhat toan bo doi tuong (goi update() cua tung entity)
    void update(float dt, Vector<Vector<ASNode>>& grid, double cellSize);

    // Ve tat ca doi tuong ra man hinh
    void render(sf::RenderWindow& window);
};
