#pragma once
#include "Quadtree.h"
#include "String.h"
#include "Audio.h"
#include <SFML/Graphics.hpp>

class Character;
class Quest;

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
    String name;
    String path;
    int damage; //sat thuong
    double damage_range; //tam danh
    double attack_speed; //toc do danh
    sf::Sprite sprite;
    sf::Texture texture;
    Audio sound;

    sf::Clock attackClock; //dung de do thoi gian giua cac cu danh
    float attackCooldown; //thoi gian giua cac lan danh

    sf::CircleShape attackCircle;   // Vòng tròn hiển thị phạm vi
    sf::Clock attackCircleClock;    // Đồng hồ để hiển thị vòng tròn trong thời gian ngắn
    bool showAttackCircle = false;  // Có đang hiển thị vòng tròn không

public:
    Weapons(WeaponType,const String, const String, int, double, double, const String&, const String&);
    int get_damage();
    double get_damage_range();
    double get_attack_speed();
    String get_name() const;
    String get_path() const;
    void attack(Quadtree&, Character*, Quest& quest); //tan cong
    void draw(sf::RenderWindow&);
    WeaponType get_type() const;
};