#pragma once
#include "LivingEntity.h"
#include <sstream>
#include <iostream>

using namespace std;

class Monster : public LivingEntity
{
private:
    int gold;
    int exp;
    int damage;          // sat thuong co the gay ra
    double damage_range; // ban kinh gay sat thuong
    double attack_speed; // toc do gay sat thuong
public:
    Monster();
    Monster(int, int, double, bool, int, int, int, double, double, int, int);
    int get_gold() const;
    int get_exp() const;
    void update(float);
    void draw(sf::RenderWindow &) override;
};