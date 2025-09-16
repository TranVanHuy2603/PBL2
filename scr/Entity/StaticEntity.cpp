#include "StaticEntity.h"
#include "Entity.h"

StaticEntity::StaticEntity(int x, int y, double radius, bool walkable, int gold, int exp)
    : Entity(x, y, radius)
{
    this->walkable = walkable;
    this->gold = gold;
    this->exp = exp;
}
int StaticEntity::get_gold() { return gold; }
int StaticEntity::get_exp() { return exp; }

void StaticEntity::set_gold(int value) { gold = value; }
void StaticEntity::set_exp(int value) { exp = value; }
