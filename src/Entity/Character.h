#pragma once
#include "LivingEntity.h"
#include "Monster.h"
#include "Quadtree.h"
#include "Weapons.h"
#include "Bag.h"
#include "Castle.h"
#include "String.h"
#include "Quest.h"
#include <sstream>
// dung trong ham craft_weapon()
struct Recipe // cong thuc che che tao vu khi
{
    int wood;
    int stone;
    int sand;
    int coal;
    int iron;
    int gold;
    int diamond;
    int emerald;
};

extern Recipe recipes[];

class Castle;

class Character : public LivingEntity
{
private:
    int level;
    int gold;
    int exp;
    int exp_max;
    Bag bag;
    int lives;
    Vector<Weapons *> weapons;
    int indexWeapon; // chi so cua vu khi trong vecto

    sf::Texture up;
    sf::Texture right_cung, right_kiemgo, right_kiemsat, right_riu, right_sung, right_hand;
    sf::Texture down_cung, down_kiemgo, down_kiemsat, down_riu, down_sung, down_hand;
    sf::Texture left_cung, left_kiemgo, left_kiemsat, left_riu, left_sung, left_hand;

    bool isDying = false;
    float dyingTimer = 0.f;

public:
    Character();
    Character(int, int, int, int, int);
    ~Character();

    int get_gold() const; // lay so vang hien co
    int get_exp() const;  // lay kinh nghiem hien co
    int get_exp_max() const;
    Bag get_bag() const;
    Bag &get_bag();
    int get_indexWeapon() const;
    int get_level() const; // lay ra level
    Vector<Weapons *> &get_weapons();
    int get_resource_amount(ResourceType type) const;
    sf::Vector2f get_position() const;
    sf::Vector2f getSize() const;
    bool get_status() const;
    int get_lives() const;

    void set_indexWeapon(int);
    void setScale(float, float); // doi kich co cua anh

    void incr_gold(int); // tang vang len
    void incr_exp(int);  // tang kinh nghiem len
    void decr_gold(int); // giam vang xuong khi xay nha
    void decr_exp(int);  // giam kinh nghiem

    void levelUp(); // tang level
    void level_up_castle(Castle *);

    void handleInput(double); // di chuyen bang tay

    void update(float); // di chuyen

    void attack(Quadtree &, Quest &task); // tan cong.....tham so dau vao la mot vecto cac Monster

    void add_weapon(Weapons *);
    void switch_weapon(int index);
    bool craft_weapon(WeaponType);
    void take_damage(int value) override;
};