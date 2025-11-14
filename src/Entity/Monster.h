#pragma once
#include "LivingEntity.h"
#include "Astar.h"
#include "Castle.h"
#include "Character.h"
#include "Animation.h"
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Character;
class Castle;
class Quadtree;

class Monster : public LivingEntity
{
private:
    int gold;
    int exp;
    int damage;          // sat thuong co the gay ra
    double damage_range; // ban kinh gay sat thuong
    double attack_speed; // toc do gay sat thuong
    float attackcooldown; //thoi gian sau moi cu danh
    Vector<sf::Vector2f> path; //duong di
    int currentTarget = 0; //chi so toa do trong duong di
    sf::Texture texture;
    float pathRecalculateTimer; // Timer để tính lại đường đi

    // ANIMATION
    Animation idleAnim;
    Animation walkAnim;
    Animation attackAnim;
    Animation deathAnim;

    bool isMoving;
    bool isAttacking;

    void loadAnimations();
public:
    Monster();
    Monster(int, int, int, int, double, double, int, int);
    int get_gold() const;
    int get_exp() const;
    int get_damage() const;

    void draw(sf::RenderWindow &) override;
    void set_path(const Vector<sf::Vector2f>&);
    void movePath(float);
    void attack(LivingEntity*, float);
    void update(float, Castle*, Character*, Quadtree*, Vector<Vector<ASNode>>&, double);
};