#include "Character.h"
#include "Entity.h"
#include "Quadtree.h"
#include "Rect.h"
#include <SFML/Graphics.hpp>
#include <cmath>

sf::Texture Character::texture;

Character::Character(int x, int y, double radius, bool walkable,
                     int hp, int hp_max, int damage, double damage_range, 
                     double attack_speed, int level, int gold, int exp, int exp_max)
    : LivingEntity(x, y, radius, walkable, hp, hp_max, damage, damage_range, attack_speed)
{
    this->level = level;
    this->gold = gold;
    this->exp = exp;
    this->exp_max = exp_max;
    this->sprite.setTexture(texture);           // gan hinh anh nha vat cho sprite de ive ra cua so game
    this->sprite.setPosition(this->x, this->y); // set vi tri cua hinh anh la toa  do cua nhan vat
}
int Character::get_gold() { return gold; }
int Character::get_exp() { return exp; }

void Character::incr_gold(int value) { this->gold += value; }
void Character::incr_exp(int value) { this->exp += value; }

void Character::decr_gold(int value) { this->gold -= value; }
void Character::decr_exp(int value) { this->exp -= value; }
void Character::setScale(float x, float y) { sprite.setScale(x, y); }

ControlMode Character::get_Mode() { return mode; }
void Character::set_Mode(ControlMode mode) { this->mode = mode; }

int Character::get_level() { return level; }

void Character::levelUp() // tang level
{
    if (level < 5)
    {
        level++;
        exp = 0;
        hp_max += 50;
        hp = hp_max;
        damage += 5;
    }
}

void Character::setPath(const std::vector<sf::Vector2f> &newPath) // cap nhat duong di cho nhan vat tu A*
{
    path = newPath;
    currentTarget = 0;
}

void Character::handleInput(double deltaTime) // di chuyen bang tay
{
    sf::Vector2f move(0.f, 0.f); // toa do di chuyen

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move.y -= 100.f * deltaTime; // di len

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move.y += 100.f * deltaTime; // di xuong

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move.x -= 100.f * deltaTime; // qua trai

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move.x += 100.f * deltaTime; // qua phai

    sprite.move(move);
}

void Character::movePath(float deltaTime)
{
    if (currentTarget < static_cast<int>(path.size()))
    {
        sf::Vector2f target = path[currentTarget]; // lay toa do tiep theo
        sf::Vector2f pos = sprite.getPosition();   // vi tri cua vat

        sf::Vector2f dir = target - pos; // duong di
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (length > 1.f)
        {
            dir /= length;
            pos += dir * deltaTime * 100.f;
            sprite.setPosition(pos);
        }
        else
        {
            currentTarget++;
        }
    }
}

void Character::update(float deltaTime)
{
    if (mode == ControlMode::Manual)// di chuyen bang tay
        handleInput(deltaTime);
        
    else if (mode == ControlMode::Auto)
        movePath(deltaTime); // di chuyen tu dong bang A*
}

bool Character::isColliding(const sf::Sprite &other)
{
    return sprite.getGlobalBounds().intersects(other.getGlobalBounds());//neu vung chu nhat chua nhan vat chong ven vung chu nhat cua vat the thi la va cham
}

void Character::attack(Quadtree& qt)
{
    sf::FloatRect bound = sprite.getGlobalBounds(); //lay ra hinh chu nhat chua nhan vat
    sf::Vector2f center(bound.left + bound.width / 2.f, bound.top + bound.height / 2);//lay ra tam
    //dung quadtree de lay ra nhung vat the xung quanh nhan vat
    Rect range(center.x, center.y, damage_range, damage_range); //tao mot hinh chu nhat bao quanh vung gay sat thuong
    std::vector<Entity*> found;//vecto luu cac vat the xung quanh nhan vat
    qt.query(range, found);

    for (auto e : found)
    {
        sf::FloatRect eBound = e->get_sprite().getGlobalBounds();
        sf::Vector2f eCenter(eBound.left + eBound.width / 2.f, eBound.top + eBound.height / 2);//lay ra tam cua tung vat the

        float dx = center.x - eCenter.x;//lay khoang cach truc x
        float dy = center.y - eCenter.y;//lay khoang cach truc y
        float d = std::sqrt(dx*dx + dy*dy);//khoang cach thuc te

        if (d > damage_range) continue;

        if (Monster* m = dynamic_cast<Monster*>(e))
        {
            m->take_damage(damage);
            if (!m->get_status()) //neu nhu quai chet
            {
                incr_gold(m->get_gold()); //tang vang
                incr_exp(m->get_exp()); //tang exp
                if (exp >= exp_max) 
                {
                    levelUp();//tang level
                }
            }
        }
        else 
        {
            //Them xu li neu la cac vat the khac
        }
    }
}
