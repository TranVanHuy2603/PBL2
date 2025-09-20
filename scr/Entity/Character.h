
#include "LivingEntity.h"
#include "Monster.h"
#include "Quadtree.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#pragma once

enum class ControlMode
{
    Manual,
    Auto
};

class Character : public LivingEntity
{
private:
    int level;
    int gold;
    int exp;      
    int exp_max;                          // hinh anh nhan vat de ve trong cua so game
    ControlMode mode = ControlMode::Manual; // che do di chuyen bang A* hay la bang ban phim
public:
    static sf::Texture texture;
    Character();
    Character(int, int, double, bool, int, int, int, double, double, int, int, int, int);
    int get_gold(); // lay so vang hien co
    int get_exp();  // lay kinh nghiem hien co

    void incr_gold(int); // tang vang len
    void incr_exp(int);  // tang kinh nghiem len

    void decr_gold(int); // giam vang xuong khi xay nha
    void decr_exp(int);  // giam kinh nghiem

    void setScale(float, float); // doi kich co cua anh

    ControlMode get_Mode();          // lay ra che do hien tai
    void set_Mode(ControlMode mode); // set che do bang tay hay a*

    int get_level(); // lay ra level
    void levelUp();  // tang level

    void setPath(const Vector<sf::Vector2f> &); // gan duong di cho nhan vat
    void handleInput(double);                        // di chuyen bang tay
    void movePath(float);                            // di chuyen theo a*

    void update(float) override; // di chuyen

    bool isColliding(const sf::Sprite &); // dung de xu li va cham voi cac vat the khac
    void attack(Quadtree&); //tan cong.....tham so dau vao la mot vecto cac Monster

    std::string serialize() const override;
    void deserialize(std::istream&) override;
};