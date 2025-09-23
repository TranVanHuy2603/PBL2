#include "LivingEntity.h"
#include <sstream>
#include <iostream>
#pragma once

class Monster : public LivingEntity
{
private:
    int gold;
    int exp;
public:
    Monster();
    Monster(int, int, double, bool, int, int, int, double, double, int, int);
    int get_gold() const;
    int get_exp() const;
    void update(float) override;
    void draw(sf::RenderWindow &) override;
    std::string serialize() const override;
    void deserialize(std::istream&) override;
};