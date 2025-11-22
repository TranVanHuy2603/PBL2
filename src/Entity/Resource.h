#pragma once
#include "Entity.h"
#include "Audio.h"
#include <string>

using namespace std;

enum class ResourceType
{
    Wood,    // Go
    Stone,   // Đa
    Sand,    // Cat
    Coal,    // Than
    Iron,    // Sat
    Gold,    // Vang
    Diamond, // Kim cuong
    Emerald, // Ngoc luc bao
    Count
};

class Resource : public Entity
{
private:
    ResourceType resourcetype; // loai tai nguyen
    sf::Texture texture;
    bool status;
    int gold;
    int exp;
    int hp;

public:
    Resource(int, int, ResourceType, const string &, int, int, float);
    ResourceType get_type() const;
    int get_quantity() const;
    sf::Sprite &get_sprite();
    int get_gold() const;
    int get_exp() const;
    bool get_status() const;

    void set_status(bool);
    void draw(sf::RenderWindow&) override;

    void take_damage();
};
