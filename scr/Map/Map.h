#pragma once
#include <vector>
#include <string>
#include "Tile.h"

class Map {
private:
    int width, height;
    std::vector<std::vector<Tile>> grid;  // dùng Tile thay vì int

public:
    Map(int w = 0, int h = 0);

    int get_width() const;
    int get_height() const;
    const std::vector<std::vector<Tile>>& get_grid() const;

    void load_File(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    bool isWalkable(int x, int y) const;
};
