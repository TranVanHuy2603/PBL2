#pragma once
#include <SFML/System.hpp>
#include "Tile.h"
#include "EntityManager.h"

class Map {
private:
    int width;
    int height;
    Tile** grid; // mảng 2D động lưu tile

public:
    Map();
    ~Map();

    int get_width() const;
    int get_height() const;
    Tile* get_tile(int x, int y) const;

    void load_File(const char* filename, EntityManager* entityManager = nullptr);
    void saveToFile(const char* filename, const EntityManager* entityManager = nullptr) const;

    bool isWalkable(int x, int y) const;
};
