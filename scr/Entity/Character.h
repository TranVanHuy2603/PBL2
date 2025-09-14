#include "LivingEntity.h"
#include <SFML/Graphics.hpp>

class Character : public LivingEntity
{
    private:
        int gold;
        int exp;
        static sf::Texture texture; //hinh anh nhan vat de ve trong cua so game
    public:
        Character(int, int, double, bool, int, int, int, double, double, int, int);
        int get_gold(); //lay so vang hien co
        int get_exp(); //lay kinh nghiem hien co

        void incr_gold(int); //tang vang len
        void incr_exp(int); //tang kinh nghiem len

        void decr_gold(int); //giam vang xuong khi xay nha
        void decr_exp(int); //giam kinh nghiem
};