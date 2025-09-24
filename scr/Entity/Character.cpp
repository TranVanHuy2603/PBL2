#include "Character.h"
#include "Entity.h"
#include "Quadtree.h"
#include "Rect.h"
#include <SFML/Graphics.hpp>
#include <cmath>

sf::Texture Character::texture;

Character::Character() {}

Character::Character(int x, int y, bool walkable,
                     int hp, int hp_max, int level, int gold, int exp, int exp_max)
    : LivingEntity(x, y, walkable, hp, hp_max)
{
    this->level = level;
    this->gold = gold;
    this->exp = exp;
    this->exp_max = exp_max;
    this->type = "Character";
    this->sprite.setTexture(texture);           // gan hinh anh nha vat cho sprite de ive ra cua so game
    this->sprite.setPosition(this->x, this->y); // set vi tri cua hinh anh la toa  do cua nhan vat
}
int Character::get_gold() { return gold; }
int Character::get_exp() { return exp; }
int Character::get_exp_max() { return exp_max; }

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
    }
}

void Character::setPath(const Vector<sf::Vector2f> &newPath) // cap nhat duong di cho nhan vat tu A*
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
    if (currentTarget < static_cast<int>(path.get_size()))
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

void Character::attack(Quadtree & qt)
{
    weapons->attack(qt, this);
}

string Character::serialize() const {
    std::ostringstream ss;
    ss  << x << "," 
        << y << "," 
        << walkable << ","
        << hp << ","
        << hp_max << "," 
        << level << "," 
        << gold << ","
        << exp << "," 
        << exp_max;
    return ss.str();
    }

void Character::deserialize(std::istream& in) {
        char comma;
        in  >> x >> comma
            >> y >> comma
            >> walkable >> comma
            >> hp >> comma
            >> hp_max >> comma
            >> level >> comma
            >> gold >> comma
            >> exp >> comma
            >> exp_max;
    }

