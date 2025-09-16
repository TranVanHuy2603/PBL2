#include "Entity.h"
#pragma once

class StaticEntity : public Entity
{
protected:
    int gold; // luong vang ma nhan vat nhan duoc khi an
    int exp;  // luong exp ma nhan vat nhan duoc khi an
public:
    StaticEntity(int, int, double, bool, int, int);
    int get_gold();
    int get_exp();

    void set_gold(int);
    void set_exp(int);
};