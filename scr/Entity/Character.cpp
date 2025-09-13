#include "Character.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

Character::Character(int x, int y, double radius, bool walkable, 
          int hp, int hp_max, int damage, 
          double damage_range, double attack_speed, int gold, int exp)
          :LivingEntity(x, y, radius, walkable, hp, hp_max, damage, damage_range, attack_speed) 
          {
              this->gold = gold;
              this->exp = exp;
          }
int Character::get_gold() { return gold; }
int Character::get_exp() { return exp; }

void Character::incr_gold(int value) { this->gold += value; }
void Character::incr_exp(int value) { this->exp += value; }

void Character::decr_gold(int value) { this->gold -= value; }
void Character::decr_exp(int value) { this->exp -= value; }