#include "EntityManager.h"
#include "Monster.h"
#include "Castle.h"
#include "Character.h"
#include <iostream>

using namespace std;

struct ResourceInfo
{
    ResourceType type;
    float xs; // ti te ra
    std::string filename;
    int gold;
    int exp;
};

ResourceInfo resourceInfos[] = {
    {ResourceType::Wood, 0.2f, "assets/wood.png", 5, 2},
    {ResourceType::Stone, 0.15f, "assets/stone.png", 5, 2},
    {ResourceType::Sand, 0.13f, "assets/sand.png", 4, 2},
    {ResourceType::Coal, 0.13f, "assets/coal.png", 7, 10},
    {ResourceType::Iron, 0.12f, "assets/iron.png", 8, 15},
    {ResourceType::Gold, 0.09f, "assets/gold.png", 8, 20},
    {ResourceType::Diamond, 0.09f, "assets/diamond.png", 20, 30},
    {ResourceType::Emerald, 0.09f, "assets/emerald.png", 25, 35}};

EntityManager::EntityManager(const Rect &area, double cap)
    : qt(area, cap)
{
}

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
    qt.insert(e);
}

void EntityManager::remove(Entity *e)
{
    entities.remove(e);
    delete e;
}

Character *EntityManager::getPlayer() { return player; }

Castle *EntityManager::getCastle() { return castle; }

Vector<Entity *> &EntityManager::getEntities()
{
    return entities;
}

void EntityManager::set_player(Character *value) { player = value; }
void EntityManager::set_castle(Castle *value) { castle = value; }

void EntityManager::updateAll(float dt, Vector<Vector<ASNode>> &grid, double cellSize)
{
    Castle *castle = getCastle();
    Character *player = getPlayer();

    for (auto *e : entities) // duyet tat ca vat the
    {
        if (Monster *m = dynamic_cast<Monster *>(e))
        {
            // quai tim duong tan cong bang A*
            m->update(dt, castle, player, &qt, grid, cellSize);
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

Quadtree &EntityManager::getQuadtree()
{
    cout << "Tra ve quadtree de thuc hien query tan cong\n";
    return qt;
}

bool isOverlapping(const sf::Sprite &s1, const sf::Sprite &s2)
{
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

void EntityManager::create_monster(int n)
{
    sf::Sprite tempSprite; // sprite tam

    for (int i = 0; i < n; i++)
    {
        bool check = false; // false la khong duoc tao, true la duoc tao
        while (!check)
        {
            // random mot vi tri cho linh
            float x = rand() % 750 + 25;
            float y = rand() % 550 + 25;
            tempSprite.setPosition(x, y);
            check = true;

            // kiem tra vi tri moi co chong len nhung vat the hien co trong game khong
            for (auto *e : entities)
            {
                if (isOverlapping(tempSprite, e->get_sprite()))
                {
                    check = false; // neu nhu chong len thi khog duoc
                    break;
                }
            }
        }

        Monster *m = new Monster(tempSprite.getPosition().x, tempSprite.getPosition().y, 50, 10, 5, rand() % 10, 10, 20);
        add(m);
    }
}

ResourceInfo choose() // ap dung thay Tu day lien:))))
{
    float r = static_cast<float>(rand()) / RAND_MAX; // 0~1
    float sum = 0.f;
    for (auto &info : resourceInfos)
    {
        sum += info.xs;
        if (r <= sum)
            return info;
    }
    return resourceInfos[0];
}

void EntityManager::create_resource(int n)
{
    sf::Sprite tempSprite;

    for (int i = 0; i < n; i++)
    {
        bool check = false;
        ResourceInfo info = choose();

        while (!check)
        {
            float x = rand() % 750 + 25;
            float y = rand() % 550 + 25;
            tempSprite.setPosition(x, y);
            check = true;

            for (auto *e : entities)
            {
                if (isOverlapping(tempSprite, e->get_sprite()))
                {
                    check = false;
                    break;
                }
            }
        }

        Resource *r = new Resource(tempSprite.getPosition().x, tempSprite.getPosition().y, info.type, info.filename, info.gold, info.exp);
        add(r);
    }
}
