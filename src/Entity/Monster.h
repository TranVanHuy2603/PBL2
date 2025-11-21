#pragma once
#include "LivingEntity.h"
#include "GBFS.h"
#include "Castle.h"
#include "Audio.h"
#include "Character.h"
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
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
    int damage;           // sat thuong co the gay ra
    double damage_range;  // ban kinh gay sat thuong
    double attack_speed;  // toc do gay sat thuong
    float attackcooldown; // thoi gian sau moi cu danh
    sf::Texture texture;

    Vector<sf::Vector2f> pathPositions; // đường đi thực tế
    int currentTarget = 0;

    sf::RectangleShape hpBack; // Nền
    sf::RectangleShape hpBar;  // HP còn
    sf::Vector2f hpBarSize;    // Kích thước đầy đủ của thanh HP

    int randomDir = 0;
    float randomMoveDuration = 0.f;
    bool isMoving = true;
    sf::Vector2f moveDir;            // hướng di chuyển hiện tại
    float minX = 0.f, maxX = 6500.f; // biên map theo X
    float minY = 0.f, maxY = 3500.f;

public:
    Monster();
    Monster(int, int, int, int, double, double, int, int);
    int get_gold() const;
    int get_exp() const;

    void draw(sf::RenderWindow &) override;
    void movePath(const Vector<sf::Vector2f> &, float);
    void attack(LivingEntity *, float);
    void update(float, Castle *, Character *, Quadtree *, Vector<Vector<ASNode>> &, double);
    void updateRandomMovement(float deltaTime);
};