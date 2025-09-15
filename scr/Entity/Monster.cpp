#include "Monster.h"

Monster::Monster(int x, int y, double radius, bool walkable, 
                    int hp, int hp_max, int damage, 
                    double damage_range, double attack_speed)
: LivingEntity(x, y, radius, walkable, hp, hp_max, 
                damage, damage_range, attack_speed) {}
