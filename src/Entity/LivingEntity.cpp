#include "LivingEntity.h"

LivingEntity::LivingEntity() {}

LivingEntity::LivingEntity(int x, int y, int hp_max)
    : Entity(x, y), hp(hp_max), hp_max(hp_max)
{
    this->status = true;
    this->walkable = false;
}

LivingEntity::~LivingEntity() {}

int LivingEntity::get_hp() const { return hp; }
int LivingEntity::get_hp_max() const { return hp_max; }

void LivingEntity::set_hp(int value) { hp = value; }
void LivingEntity::set_hp_max(int value) { hp_max = value; }

void LivingEntity::take_damage(int value) 
{ 
    hp -= value;
    if (hp <= 0) this->status = false;
}