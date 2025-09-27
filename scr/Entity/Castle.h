#pragma once
#include "Entity.h"
#include "Character.h"
#include <string>
#include <SFML/Graphics.hpp>

class Castle : public LivingEntity
{
private:
    int level;
    int cost;
    sf::Sprite spite;

public:
    Castle();
    Castle(int, int, bool, int, int, int, int);
    int get_level() const;
    int get_cost() const;
    int get_hp() const;
    void set_level(int);
    void set_cost(int);
    void set_hp(int);
    void set_texture(string);
    void level_up();
};