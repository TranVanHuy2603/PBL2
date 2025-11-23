#pragma once
#include "LivingEntity.h"
#include "Character.h"
#include "String.h"
#include <SFML/Graphics.hpp>

class Castle : public LivingEntity
{
private:
    int level;
    int cost;
    sf::Texture texture;
    sf::Font font;
    sf::Text levelText;

    sf::RectangleShape hpBarBack; 
    sf::RectangleShape hpBar;

    float healTimer;

public:
    Castle();
    Castle(int, int, int, int);
    ~Castle();
    int get_level() const;
    int get_cost() const;
    int get_hp() const;
    void set_level(int);
    void set_cost(int);
    void set_hp(int);
    void set_texture(const String&);
    void level_up();
    void update(float);
    void render(sf::RenderWindow&);
};