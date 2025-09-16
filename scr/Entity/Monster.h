#include "LivingEntity.h"
#pragma once

class Monster : public LivingEntity
{
private:
    int gold;
    int exp;
public:
    Monster(int, int, double, bool, int, int, int, double, double, int, int);
    int get_gold() const;
    int get_exp() const;
    void update(float) override;
    void draw(sf::RenderWindow &) override;
};