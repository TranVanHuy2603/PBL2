#include "Map.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Map::Map(int w, int h) : width(w), height(h)
{
    grid.resize(height, vector<int>(width, 0));
}
int Map::get_height() { return height; }
int Map::get_width() { return width; }
vector<vector<int>> Map::get_grid() { return grid; }

void Map::load_File(const std::string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "ERROR" << filename << endl;
        return;
    }

    grid.clear();
    string line;
    while (getline(file, line)) //doc tung fong tronng file
    {
        vector<int> row; //hang
        stringstream ss(line);
        int value;
        while (ss >> value) //doc lan luot tung so
        {
            row.push_back(value); //them so vao hang
        }
        if (!row.empty()) 
        {
            grid.push_back(row); //them hang vao do thi
        }
        height = grid.size();
        width = (height > 0) ? grid[0].size() : 0;
    }
    file.close();
}

void Map::draw(sf::RenderWindow& window) {
    const int tileSize = 32; //kich thuoc cua mot o

    sf::RectangleShape tile(sf::Vector2f((float)tileSize, (float)tileSize));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == 0) {//neu di duoc
                tile.setFillColor(sf::Color::Green); // walkable
            } else { //neu khong di duoc
                tile.setFillColor(sf::Color::Black); // blocked
            }
            tile.setPosition((float)x * tileSize, (float)y * tileSize);
            window.draw(tile);
        }
    }
}

bool Map::isWalkable(int x, int y) const {
    if (y < 0 || y >= height || x < 0 || x >= width)
        return false; // ra ngoài map coi như blocked
    return grid[y][x] == 0;
}