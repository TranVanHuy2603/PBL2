#pragma once
#include "GBFS.h"
#include "Castle.h"
#include "Audio.h"
#include "Character.h"
#include <sstream>
#include <iostream>
#include <random>

using namespace std;

class Character;
class Castle;
class Quadtree;

class Monster : public LivingEntity
{
private:
    int gold;
    int exp;
    int damage;
    double damage_range;
    double attack_speed;
    float attackcooldown;
    sf::Texture texture;

    Vector<sf::Vector2f> pathPositions;
    int currentTarget = 0;

    sf::RectangleShape hpBack;
    sf::RectangleShape hpBar;
    sf::Vector2f hpBarSize;

    // --- biến di chuyển random / zig-zag ---
    sf::Vector2f moveDir; // hướng di chuyển hiện tại
    float moveTimer;      // thời gian còn lại đi theo hướng hiện tại
    float speed;          // tốc độ quái

    int randomDir = 0;
    float randomMoveDuration = 0.f;
    bool isMoving = true;

    float minX = 0.f, maxX = 6500.f; // biên map theo X
    float minY = 0.f, maxY = 3500.f; // biên map theo Y

public:
    Monster();
    Monster(int, int, int, int, double, double, int, int);
    ~Monster();
    int get_gold() const;
    int get_exp() const;

    void draw(sf::RenderWindow &) override;
    void movePath(const Vector<sf::Vector2f> &, float);
    void attack(LivingEntity *, float);
    void update(float, Castle *, Character *, Quadtree *, Vector<Vector<ASNode>> &, double);
    void updateRandomMovement(float deltaTime);
};
