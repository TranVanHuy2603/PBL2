#include "Map.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Map::Map(int w, int h) : width(w), height(h) {
    grid.resize(height, std::vector<Tile>(width, Tile(TileType::Grass)));
}

int Map::get_width() const { return width; }
int Map::get_height() const { return height; }
const vector<vector<Tile>>& Map::get_grid() const { return grid; }

void Map::load_File(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERROR opening " << filename << endl;
        return;
    }

    grid.clear();
    string line;
    while (getline(file, line)) {
        vector<Tile> row;
        stringstream ss(line);
        int value;
        while (ss >> value) {
            row.emplace_back(Tile(static_cast<TileType>(value)));  // thay vì int, giờ tạo Tile
        }
        if (!row.empty()) {
            grid.push_back(row);
        }
    }

    height = grid.size();
    width = (height > 0) ? grid[0].size() : 0;

    file.close();
}

bool Map::isWalkable(int x, int y) const {
    if (y < 0 || y >= height || x < 0 || x >= width)
        return false;
    return grid[y][x].isWalkable();
}