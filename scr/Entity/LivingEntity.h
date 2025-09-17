#pragma once
#include "Entity.h"

class LivingEntity : public Entity
{
protected:
    int hp;              // luong mau con lai
    int hp_max;          // luong mau toi da
    int damage;          // sat thuong co the gay ra
    double damage_range; // ban kinh gay sat thuong
    double attack_speed; // toc do gay sat thuong
    bool status;
public:
    LivingEntity();
    LivingEntity(int, int, double, bool, int, int, int, double, double);
    int get_hp();
    int get_hp_max();
    int get_damage();
    double get_damage_range();
    double get_attack_speed();
    bool get_status();

    void set_hp(int);
    void set_hp_max(int);
    void set_damage(int);
    void set_damage_range(double);
    void set_attack_speed(double);

    void take_damage(int);
};