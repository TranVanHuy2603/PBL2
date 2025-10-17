#pragma once
#include "Vector.h"
#include <memory>
#include "MapLayer.h"
#include "CameraController.h"
#include <SFML/Window.hpp>


class MapManager {
public:
MapManager(const sf::Vector2f& windowSize, const sf::FloatRect& worldBounds);


void addLayer(std::unique_ptr<MapLayer> layer);
void handleInput(const sf::RenderWindow& window, float dt);
void update(float dt);
void draw(sf::RenderWindow& window);


CameraController& getCamera() { return camera; }
private:
Vector <std::unique_ptr<MapLayer>> layers;
CameraController camera;
};