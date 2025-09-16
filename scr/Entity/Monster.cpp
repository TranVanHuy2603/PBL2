#include "Monster.h"

Monster::Monster(int x, int y, double radius, bool walkable,
                 int hp, int hp_max, int damage,
                 double damage_range, double attack_speed, int gold, int exp)
    : LivingEntity(x, y, radius, walkable, hp, hp_max,
                   damage, damage_range, attack_speed)
{
    this->gold = gold;
    this->exp = exp;
}

int Monster::get_gold() const { return gold; }
int Monster::get_exp() const { return exp; }

void Monster::update(float deltaTime) 
{
}

void Monster::draw(sf::RenderWindow &)
{
}
