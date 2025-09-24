#include "LivingEntity.h"
#include "Entity.h"

LivingEntity::LivingEntity() {}

LivingEntity::LivingEntity(int x, int y, bool walkable,
                           int hp, int hp_max)
    : Entity(x, y)
{
    this->hp = hp;
    this->hp_max = hp_max;
    this->walkable = walkable;
    this->status = true;
}

int LivingEntity::get_hp() { return hp; }
int LivingEntity::get_hp_max() { return hp_max; }
bool LivingEntity::get_status() { return status; }

void LivingEntity::set_hp(int value) { hp = value; }
void LivingEntity::set_hp_max(int value) { hp_max = value; }

void LivingEntity::take_damage(int value) 
{ 
    hp -= value;
    if (hp <= 0) this->status = false;
}