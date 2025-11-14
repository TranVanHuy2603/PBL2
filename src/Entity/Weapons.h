#pragma once
#include "Quadtree.h"
#include "String.h"
#include "Audio.h"
#include <SFML/Graphics.hpp>

class Character;

enum WeaponType
{
    BareHand, //tay
    WoodenSword, //kiem go
    IronSwood, //kiem sat
    Ax, //riu
    Bow, //cung ten
    Gun, //sung
    Count
};

class Weapons //vu khi
{
protected:
    WeaponType type; //loai vu khi
    int damage; //sat thuong
    double damage_range; //tam danh
    double attack_speed; //toc do danh
    sf::Sprite sprite;
    sf::Texture texture;
    Audio sound;

    sf::Clock attackClock; //dung de do thoi gian giua cac cu danh
    float attackCooldown; //thoi gian giua cac lan danh
    bool isAnimating;
    float animationProgress; // Từ 0.0 đến 1.0
    
    sf::Texture effectTexture;

public:
    Weapons(WeaponType, int, double, double, const String&, const String&);
    int get_damage();
    double get_damage_range();
    double get_attack_speed();
    sf::Texture& getEffectTexture(); 
    void attack(Quadtree&, Character*); //tan cong
    void startAttackAnimation();
    void updateAnimation(float dt, const sf::Vector2f& ownerPos, bool ownerIsFacingLeft);
    void draw(sf::RenderWindow&);
};