#include "Character.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <cmath>

sf::Texture Character::texture; 

Character::Character(int x, int y, double radius, bool walkable, 
          int hp, int hp_max, int damage, 
          double damage_range, double attack_speed, int level, int gold, int exp)
          :LivingEntity(x, y, radius, walkable, hp, hp_max, damage, damage_range, attack_speed) 
        {
            this->level = level;
            this->gold = gold;
            this->exp = exp;
            this->sprite.setTexture(texture); //gan hinh anh nha vat cho sprite de ive ra cua so game
            this->sprite.setPosition(this->x, this->y); //set vi tri cua hinh anh la toa  do cua nhan vat
        }
int Character::get_gold() { return gold; }
int Character::get_exp() { return exp; }

void Character::incr_gold(int value) { this->gold += value; }
void Character::incr_exp(int value) { this->exp += value; }

void Character::decr_gold(int value) { this->gold -= value; }
void Character::decr_exp(int value) { this->exp -= value; }
void Character::setScale(float x, float y) { sprite.setScale(x, y); }

ControlMode Character::get_Mode() { return mode; }
void Character::set_Mode(ControlMode mode) {this->mode = mode; }

int Character::get_level() { return level; }

void Character::levelUp()
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

void Character::setPath(const std::vector<sf::Vector2f>& newPath) 
{
    path = newPath;
    currentTarget = 0;
}

void Character::handleInput(double deltaTime) 
{
    sf::Vector2f move(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move.y -= 100.f * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move.y += 100.f * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move.x -= 100.f * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move.x += 100.f * deltaTime;

    sprite.move(move);
}

void Character::moveAlongPath(float deltaTime) 
{
    if (currentTarget < path.size()) {
        sf::Vector2f target = path[currentTarget];//lay toa do tiep theo
        sf::Vector2f pos = sprite.getPosition();//vi tri cua vat

        sf::Vector2f dir = target - pos;//duong di
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (length > 1.f) {
            dir /= length;
            pos += dir  * deltaTime * 100.f;
            sprite.setPosition(pos);
        } else {
            currentTarget++;
        }
    }
}

void Character::update(float deltaTime) 
{
    if (mode == ControlMode::Manual) {
        handleInput(deltaTime);
    } else if (mode == ControlMode::Auto) {
        moveAlongPath(deltaTime);
    }
}
