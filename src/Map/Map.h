#pragma once
#include "Vector.h"
#include "ASNode.h"
#include "Entity.h"
#include <string>
#include "SFML/Graphics.hpp"

class Map {
private:
    sf::Sprite background;
    sf::Texture backgroundTexture;

public:
    Map(float, float);
    bool loadFromFile(float, float);
    void draw(sf::RenderWindow &window, const sf::View &view);
    // void setGrid(Vector<Entity*>& entity, Vector<Vector<ASNode>>&, double);
    // void updateGrid(Vector<Entity*>& entities, Vector<Vector<ASNode>>& grid, double);
};
