#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
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
};

class Resource : public Entity
{
private:
    ResourceType resourcetype; // loai tai nguyen
    sf::Sprite sprite;
    sf::Texture texture;
    std::string name; // ten hien thi khi che tao
    bool status;

public:
    Resource(int, int, ResourceType, const string &, const string &);
    ResourceType get_type() const;
    int get_quantity() const;
    string get_name() const;
    void set_status();
    sf::Sprite &get_sprite();
    void draw(sf::RenderWindow&) override;
};
