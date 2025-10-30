#pragma once
#include "LivingEntity.h"
#include "Monster.h"
#include "Quadtree.h"
#include "Weapons.h"
#include "Bag.h"
#include "Castle.h"
#include "String.h"
#include "Animation.h"
#include "BaseObject.h"
#include <SFML/Graphics.hpp>
#include <sstream>

class Castle;
enum class Direction {
    Left,
    Right
};

class Character : public LivingEntity, public BaseObject
{
private:
    int level; // Cap bac
    int gold;
    int exp; // Kinh nghiem hien co
    int exp_max;
    float hp; // Mau
    Bag bag;
    sf::Texture texture, hurtTexture;
    Vector<Weapons *> weapons;
    int indexWeapon; // chi so cua vu khi trong vector
    void takeDamage(float);

    // ==== Animation ======
    Animation idleAnim; // Trang thai dung yen ua
    Animation walkAnim;
    Animation attackAnim;
    Animation deathAnim;
    Animation hurtAnim;
    bool isDead;
    bool isHurt;
    float hurtTimer;
    sf::Vector2f velocity;
    float deceleration;
    Direction facing;
    bool isMoving;
    bool isAttacking;
    bool hitTriggered;
    int hitFrameIndex;

public:
    Character();
    Character(int, int, int, int);
    ~Character();

    int get_gold() const; // lay so vang hien co
    int get_exp() const;  // lay kinh nghiem hien co
    int get_exp_max() const;
    Bag get_bag() const;
    Bag &get_bag();
    int get_indexWeapon() const;
    int get_level() const; // lay ra level
    Vector<Weapons *> &get_weapons();
    sf::Texture get_texture() const;
    int get_resource_amount(ResourceType type) const;
    sf::Vector2f get_position() const;
    sf::Vector2f getSize() const;

    void set_position(const sf::Vector2f& pos);
    void set_indexWeapon(int);
    void setScale(float, float); // doi kich co cua anh
    void set_texture(String texture);

    void incr_gold(int); // tang vang len
    void incr_exp(int);  // tang kinh nghiem len
    void decr_gold(int); // giam vang xuong khi xay nha
    void decr_exp(int);  // giam kinh nghiem

    void levelUp(); // tang level
    void level_up_castle(Castle *);

    // void handleInput(double); // di chuyen bang tay

    // void update(float); // di chuyen

    void attack(Quadtree &); // tan cong.....tham so dau vao la mot vecto cac Monster

    void add_weapon(Weapons *);
    void switch_weapon(int index);
    bool craft_weapon(WeaponType);

    // ====== Animation ========
    void loadAnimations();
    void handleInput(float dt);
    void update(float dt);
};