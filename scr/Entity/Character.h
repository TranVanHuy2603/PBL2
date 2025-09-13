#include "LivingEntity.h"

class Character : public LivingEntity
{
    private:
        int gold;
        int exp;
    public:
        Character(int, int, double, bool, int, int, int, double, double, int, int);
        int get_gold();
        int get_exp();

        void incr_gold(int);
        void incr_exp(int);

        void decr_gold(int);
        void decr_exp(int);
};