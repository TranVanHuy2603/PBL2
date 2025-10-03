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

class Character : public LivingEntity
{
private:
    int level;
    int gold;
    int exp;
    int exp_max;
    Bag bag;
    sf::Texture texture;
    Vector<Weapons*> weapons;
    int indexWeapon; //chi so cua vu khi trong vector
public:

    Character();
    Character(int, int, int, int);
    ~Character();

    int get_gold(); // lay so vang hien co
    int get_exp();  // lay kinh nghiem hien co
    int get_exp_max();
    Bag& get_bag();
    int get_indexWeapon() const;
    Vector<Weapons*>& get_weapons();
    sf::Texture get_texture() const;

    void set_indexWeapon(int);
    void setScale(float, float); // doi kich co cua anh
    void set_texture(String texture);

    void incr_gold(int); // tang vang len
    void incr_exp(int);  // tang kinh nghiem len
    void decr_gold(int); // giam vang xuong khi xay nha
    void decr_exp(int);  // giam kinh nghiem

    int get_level(); // lay ra level
    void levelUp();  // tang level

    void handleInput(double);                   // di chuyen bang tay
    // void movePath(float);                       // di chuyen theo a*

    void update(float); // di chuyen

    bool isColliding(const sf::Sprite &); // dung de xu li va cham voi cac vat the khac
    void attack(Quadtree &);              // tan cong.....tham so dau vao la mot vecto cac Monster

    void add_weapon(Weapons*);
    void switch_weapon(int index);
    bool craft_weapon(WeaponType);
    void level_up_castle(Castle*);
};