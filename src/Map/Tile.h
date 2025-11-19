#pragma once
enum class TileType
{
    Grass,
    Forest,
    Hill,
    Mountain,
    Water,
    Tree,    // Go
    Stone,   // Đa
    Sand,    // Cat
    Coal,    // Than
    Iron,    // Sat
    Gold,    // Vang
    Diamond, // Kim cuong
    Emerald, // Ngoc luc bao

};

class Tile
{
private:
    // ====== CAc thuoc tinh logic cua tile ======
    TileType type;
    bool walkable; // Co di qua duoc khong
    int cost;      // Chi phi di chuyen (Dung ho A*)

    // ====== Thuoc tinh Render ======
    int tileSetIndex; // vi tri cua tile nay trong anh tileset lon
    // Ham thay doi trang thai cua Tile
    void setupTile(TileType);

public:
    Tile(TileType);

    // Các hàm để lấy thông tin (getter)
    bool isWalkable() const; 
    int getCost() const;
    TileType getType() const;
    int getTilesetIndex() const; 

    // Ham thay doi trang thai cua dia hinh
    void setType(TileType);
};
