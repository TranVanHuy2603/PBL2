#include "Tile.h"

Tile::Tile(TileType type)
{
    setupTile(type);
}

// Các hàm để lấy thông tin (getter)
bool Tile::isWalkable() const
{
    return this->walkable;
}
int Tile::getCost() const
{
    return this->cost;
}
TileType Tile::getType() const
{
    return this->type;
}
int Tile::getTilesetIndex() const
{
    return this->tileSetIndex;
}

// Ham thay doi trang thai cua dia hinh
void Tile::setType(TileType newType)
{
    setupTile(newType);
}

void Tile::setupTile(TileType newType)
{
    this->type = newType;
    switch (newType)
    {
        case TileType::Grass:
            this->walkable = true;
            this->cost = 1;
            this->tileSetIndex = 0;
            break;
        case TileType::Forest:
            this->walkable = true;
            this->cost = 4;
            this->tileSetIndex = 1;
            break;
        case TileType::Hill:
            this->walkable = true;
            this->cost = 9;
            this->tileSetIndex = 2;
            break;
        case TileType::Mountain:
            this->walkable = false;
            this->cost = 9999;
            this->tileSetIndex = 3;
            break;
        case TileType::Water:
            this->walkable = false;
            this->cost = 9999;
            this->tileSetIndex = 4;
            break;
        case TileType::Tree:
            this->walkable = false;
            this->cost = 9999;
            this->tileSetIndex = 5;
            break;
        case TileType::Stone:
            this->walkable = true;
            this->cost = 3;
            this->tileSetIndex = 6;
            break;
        case TileType::Sand:
            this->walkable = true;
            this->cost = 2;
            this->tileSetIndex = 7;
            break;
        case TileType::Coal:
            this->walkable = true;
            this->cost = 2;
            this->tileSetIndex = 8;
            break;
        case TileType::Iron:
            this->walkable = true;
            this->cost = 3;
            this->tileSetIndex = 9;
            break;
        case TileType::Gold:
            this->walkable = true;
            this->cost = 3;
            this->tileSetIndex = 10;
            break;
        case TileType::Diamond:
            this->walkable = true;
            this->cost = 3;
            this->tileSetIndex = 11;
            break;
        case TileType::Emerald:
            this->walkable = true;
            this->cost = 3;
            this->tileSetIndex = 12;
            break;
        default:
            this->walkable = true;
            this->cost = 1;
            this->tileSetIndex = 13;
    }
}