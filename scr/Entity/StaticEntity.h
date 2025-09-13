#include "Entity.h"

class StaticEntity : public Entity 
{
    protected:
        int gold;
        int exp;
    public:
        StaticEntity(int, int, double, bool, int, int);
        int get_gold();
        int get_exp();

        void set_gold(int);
        void set_exp(int);
};