#pragma once
#include "LivingEntity.h"
#include "Monster.h"
#include "Quadtree.h"
#include "Weapons.h"
#include "Bag.h"
#include "Castle.h"
#include "String.h"
#include <SFML/Graphics.hpp>
#include <sstream>

class Castle;

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
    int exp_max;
    Bag bag;
    Vector<Weapons*> weapons;
    int indexWeapon; //chi so cua vu khi trong vector
    ControlMode mode = ControlMode::Manual; // che do di chuyen bang A* hay la bang ban phim
public:
    static sf::Texture texture;
    Character();
    Character(int, int, bool, int, int, int, int, int, int);
    int get_gold(); // lay so vang hien co
    int get_exp();  // lay kinh nghiem hien co
    int get_exp_max();
    Bag& get_bag();
    int get_indexWeapon() const;
    Vector<Weapons*>& get_weapons();
    void set_indexWeapon(int);

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
    void handleInput(double);                   // di chuyen bang tay
    void movePath(float);                       // di chuyen theo a*

    void update(float); // di chuyen

    bool isColliding(const sf::Sprite &); // dung de xu li va cham voi cac vat the khac
    void attack(Quadtree &);              // tan cong.....tham so dau vao la mot vecto cac Monster

    void add_weapon(Weapons*);
    void switch_weapon(int index);
    bool craft_weapon(WeaponType);
    void level_up_castle(Castle*);
};