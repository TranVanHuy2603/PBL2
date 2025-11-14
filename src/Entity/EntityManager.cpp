#include "EntityManager.h"
#include "Monster.h"
#include "Castle.h"
#include "Character.h"
#include <iostream>

using namespace std;

// ======== Cau truc thong tin resource ========
struct ResourceInfo
{
    ResourceType type;
    float xs;               // ti le xuat hien
    std::string filename;   // duong dan hinh anh
    int gold;               // vang thu duoc
    int exp;                // kinh nghiem nhan duoc
    float scale;            // ti le phong to/thu nho
};

// Bang thong tin cac loai tai nguyen
ResourceInfo resourceInfos[] = {
    {ResourceType::Wood, 0.2f, "assets/resource/wood.png", 5, 2, 0.5f},
    {ResourceType::Stone, 0.15f, "assets/resource/stone.png", 5, 2, 0.4f},
    {ResourceType::Sand, 0.13f, "assets/resource/sand.png", 4, 2, 0.2f},
    {ResourceType::Coal, 0.13f, "assets/resource/coal.png", 7, 10, 0.2f},
    {ResourceType::Iron, 0.12f, "assets/resource/iron.png", 8, 15, 0.21f},
    {ResourceType::Gold, 0.09f, "assets/resource/gold.png", 8, 20, 0.6f},
    {ResourceType::Diamond, 0.09f, "assets/resource/diamond.png", 20, 30, 0.4f},
    {ResourceType::Emerald, 0.09f, "assets/resource/emerald.png", 25, 35, 0.2f}
};

// ======== Ham ho tro ========
bool isOverlapping(const sf::Sprite &s1, const sf::Sprite &s2)
{
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

// ======== Khoi tao va huy ========
EntityManager::EntityManager(const Rect &area, double cap)
    : qt(area, cap)
{
}

EntityManager::~EntityManager()
{
    for (auto *e : entities)
        delete e;
    entities.clear();
}

// ======== Them / xoa Entity co dinh ========
void EntityManager::add(Entity *e)
{
    // Dung cho cac vat the tinh (Resource, Castle, v.v.)
    entities.push_back(e);
    qt.insert(e);
}

void EntityManager::remove(Entity *e)
{
    qt.remove(e);
    entities.remove(e);
    delete e;
}

// ======== Getter ========
Character *EntityManager::getPlayer() { return player; }
Castle *EntityManager::getCastle() { return castle; }

Vector<Entity *> &EntityManager::getEntities() { return entities; }

const Vector<Entity*>& EntityManager::getEntities() const {return this->entities; }

Quadtree &EntityManager::getQuadtree()
{
    cout << "Tra ve quadtree de thuc hien query tan cong\n";
    return qt;
}

void EntityManager::set_player(Character *value) { player = value; }
void EntityManager::set_castle(Castle *value) { castle = value; }

// ======== Tao quai ========

// Tao 1 quai tai vi tri chi dinh
void EntityManager::create_monster_at(float x, float y)
{
    Monster *m = new Monster(x, y, 50, 10, 5, rand() % 10, 10, 20);

    // Monster la vat the dong → them truc tiep, khong dung add()
    entities.push_back(m);
    qt.insert(m);

    cout << "Tao MONSTER tai (" << x << ", " << y << ")\n";
}

// Tao nhieu quai ngau nhien
void EntityManager::create_monster(int n)
{
    sf::Sprite tempSprite;

    for (int i = 0; i < n; i++)
    {
        bool valid = false;
        while (!valid)
        {
            float x = rand() % 8000;
            float y = rand() % 4000;
            tempSprite.setPosition(x, y);
            valid = true;

            for (auto *e : entities)
            {
                if (isOverlapping(tempSprite, e->get_sprite()))
                {
                    valid = false;
                    break;
                }
            }
        }

        Monster *m = new Monster(tempSprite.getPosition().x,
                                 tempSprite.getPosition().y,
                                 50, 10, 5, rand() % 10, 10, 20);

        entities.push_back(m);
        qt.insert(m);
    }

    cout << "Da tao " << n << " quai vat\n";
}

// ======== Tao tai nguyen ========

ResourceInfo choose_random_resource()
{
    float r = static_cast<float>(rand()) / RAND_MAX;
    float sum = 0.f;

    for (auto &info : resourceInfos)
    {
        sum += info.xs;
        if (r <= sum)
            return info;
    }

    return resourceInfos[0];
}

void EntityManager::create_resource_at(int x, int y)
{
    ResourceInfo info = choose_random_resource();
    Resource *res = new Resource(x, y, info.type, info.filename, info.gold, info.exp, info.scale);

    entities.push_back(res);
    qt.insert(res);

    cout << "Tao RESOURCE tai (" << x << ", " << y << ")\n";
}

void EntityManager::create_resource(int n)
{
    sf::Sprite tempSprite;

    for (int i = 0; i < n; i++)
    {
        bool valid = false;
        ResourceInfo info = choose_random_resource();

        while (!valid)
        {
            float x = rand() % 8000;
            float y = rand() % 4000;
            tempSprite.setPosition(x, y);
            valid = true;

            for (auto *e : entities)
            {
                if (isOverlapping(tempSprite, e->get_sprite()))
                {
                    valid = false;
                    break;
                }
            }
        }

        Resource *r = new Resource(tempSprite.getPosition().x, tempSprite.getPosition().y,
                                   info.type, info.filename, info.gold, info.exp, info.scale);

        entities.push_back(r);
        qt.insert(r);
    }

    cout << "Da tao " << n << " tai nguyen\n";
}

void EntityManager::rebuildQuadtree(const Rect& newArea) {
    qt.clear();
    qt = Quadtree(newArea, qt.get_capacity()); // Giả sử có hàm get_capacity
    for (auto* e : entities) {
        qt.insert(e);
    }
}

// ======== Vong cap nhat ========
void EntityManager::update(float dt, Vector<Vector<ASNode>> &grid, double cellSize)
{
      Castle* castle = getCastle();
    Character* player = getPlayer();

    // Cập nhật và xóa các thực thể (quái, tài nguyên)
    for (int i = entities.get_size() - 1; i >= 0; --i)
    {
        Entity* e = entities[i];
        if (Monster* m = dynamic_cast<Monster*>(e))
        {
            if (!m->get_status())
            {
                qt.remove(m);
                entities.erase(entities.begin() + i);
                delete m;
            }
            else
            {
                m->update(dt, castle, player, &qt, grid, cellSize);
            }
        }
        // Thêm logic cho Resource nếu cần
    }

    if (castle)
        castle->update(dt);

    if (player)
    {
        // SỬA LỖI TẠI ĐÂY: Truyền Quadtree vào hàm update của player
        player->update(dt, qt, *this);
    }

    // Cập nhật và xóa các hiệu ứng đã kết thúc
   for (int i = effects.get_size() - 1; i >= 0; --i)
    {
        effects[i]->update(dt);
        if (effects[i]->isFinished())
        {
            delete effects[i];
            effects.erase(effects.begin() + i);
        }
    }
}

// ======== Ve toan bo vat the ========
void EntityManager::render(sf::RenderWindow &window)
{
    for (auto *e : entities)
        e->draw(window);

    if (player)
        player->draw(window);
    if (castle)
        castle->render(window);
}

void EntityManager::createWeaponEffect(Weapons* weapon, sf::Vector2f position)
{
    sf::Texture& tex = weapon->getEffectTexture();
    if (tex.getSize().x == 0) return; // Không có texture thì không tạo

    // Giả định thông số animation, bạn có thể lưu chúng trong WeaponInfo
    int frameWidth = 128;
    int frameHeight = 128;
    int frameCount = 5;
    float frameDuration = 0.05f;

    effects.push_back(new Effect(tex, position, frameWidth, frameHeight, frameCount, frameDuration));
}
