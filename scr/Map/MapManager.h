#pragma once

#include <memory>
#include "MapLayer.h"
#include <vector>
#include "CameraController.h"
#include <SFML/Window.hpp>
using namespace std;
class MapManager
{
public:
    MapManager(const sf::Vector2f &windowSize, const sf::FloatRect &worldBounds);

    void addLayer(std::unique_ptr<MapLayer> layer);
    void handleInput(const sf::RenderWindow &window, float dt);
    void update(float dt);
    void draw(sf::RenderWindow &window);

    CameraController &getCamera() { return camera; }

private:
    vector<std::unique_ptr<MapLayer>> layers;
    CameraController camera;
};