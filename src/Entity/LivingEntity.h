#pragma once
#include "Entity.h"

class LivingEntity : public Entity
{
protected:
    int hp;              // luong mau con lai
    int hp_max;          // luong mau toi da
public:
    LivingEntity();
    LivingEntity(int, int, int);
    virtual ~LivingEntity();

    int get_hp() const;
    int get_hp_max() const;

    void set_hp(int);
    void set_hp_max(int);

    virtual void take_damage(int);
};