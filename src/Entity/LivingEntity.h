#pragma once
#include "Entity.h"

class LivingEntity : public Entity
{
protected:
    int hp;              // luong mau con lai
    int hp_max;          // luong mau toi da
    bool status;
public:
    LivingEntity();
    LivingEntity(int, int, int);
    int get_hp() const;
    int get_hp_max() const;

    bool get_status() const;

    void set_hp(int);
    void set_hp_max(int);
    void set_damage(int);

    virtual void take_damage(int);
};