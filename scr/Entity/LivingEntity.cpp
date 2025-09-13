#include "LivingEntity.h"
#include "Entity.h"

LivingEntity::LivingEntity(int x, int y, double radius, bool walkable, 
                           int hp, int hp_max, int damage, 
                           double damage_range, double attack_speed)
    :Entity(x, y, radius)
    {
        this->hp = hp;
        this->hp_max = hp_max;
        this->damage = damage;
        this->damage_range = damage_range;
        this->attack_speed = attack_speed;
        this->walkable = walkable;
    }

int LivingEntity::get_hp() { return hp; }
int LivingEntity::get_hp_max() { return hp_max; }
int LivingEntity::get_damage() { return damage; }
double LivingEntity::get_damage_range() { return damage_range; }
double LivingEntity::get_attack_speed() { return attack_speed; }

void LivingEntity::set_hp(int value) { hp = value; }
void LivingEntity::set_hp_max(int value) { hp_max = value; }
void LivingEntity::set_damage(int value) { damage = value; }
void LivingEntity::set_damage_range(double value) { damage_range = value; }
void LivingEntity::set_attack_speed(double value) { attack_speed = value; }