#pragma once
#include "Quadtree.h"
#include <SFML/Graphics.hpp>

class Character;

enum WeaponType
{
    BareHand,
    Sword,
    Ax,
    Bow
};

class Weapons //vu khi
{
protected:
    WeaponType type;
    int damage;
    double damage_range;
    double attack_speed;
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Weapons(WeaponType, int, double, double, string&);
    int get_damage();
    double get_damage_range();
    double get_attack_speed();
    void attack(Quadtree&, Character*); //tan cong
    void draw(sf::RenderWindow&);
};