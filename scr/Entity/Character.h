#include "LivingEntity.h"
#include <SFML/Graphics.hpp>

enum class ControlMode { Manual, Auto };

class Character : public LivingEntity
{
    private:
        int level;
        int gold;
        int exp; //hinh anh nhan vat de ve trong cua so game
        ControlMode mode = ControlMode::Manual; //che do di chuyen bang A* hay la bang ban phim
    public:
        static sf::Texture texture;
        Character(int, int, double, bool, int, int, int, double, double, int, int, int);
        int get_gold(); //lay so vang hien co
        int get_exp(); //lay kinh nghiem hien co

        void incr_gold(int); //tang vang len
        void incr_exp(int); //tang kinh nghiem len

        void decr_gold(int); //giam vang xuong khi xay nha
        void decr_exp(int); //giam kinh nghiem
        void setScale(float, float);

        ControlMode get_Mode();
        void set_Mode(ControlMode mode);

        int get_level();
        void levelUp();


        void setPath(const std::vector<sf::Vector2f>&);
        void handleInput(double);
        void moveAlongPath(float);

        void update(float) override;
};