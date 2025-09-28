#pragma once
#include "Quadtree.h"
#include "String.h"
#include <SFML/Graphics.hpp>

class Character;

enum WeaponType
{
    BareHand, //tay
    WoodenSword, //kiem go
    IronSwood, //kiem sat
    Ax, //riu
    Bow, //cung ten
    Gun //sung
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

    sf::Clock attackClock; //dung de do thoi gian giua cac cu danh
    float attackCooldown; //thoi gian giua cac lan danh

public:
    Weapons(WeaponType, int, double, double, const String&);
    int get_damage();
    double get_damage_range();
    double get_attack_speed();
    void attack(Quadtree&, Character*); //tan cong
    void draw(sf::RenderWindow&);
};