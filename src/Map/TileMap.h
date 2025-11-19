#pragma once
#include <SFML/Graphics.hpp>
#include "String.h"
#include "Map.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray map_vertices;   // Mang chua cac vertex cua map
    sf::Texture map_tileSetTexture; // texture dung cho tileset
    bool map_textureLoaded;         // kiem tra da load duoc hinh anh chua
    sf::Vector2u map_tileSize;      // Kich thuoc 1 o
    int map_width, map_height;      // Kich thuoc mao (tinh theo cac o)

    // Ham draw call
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

public:
    // ======== Constructor ========
    TileMap();

    // Load texture
    bool LoadTileset(const std::string &tilesetPath, sf::Vector2u tileSize);

    // Build map tu file data nap vao
    void buildMap(const Map &map);

    // Update sau khi farm quai, khai thac tai nguyen tren 1 tile
    void updateTile(const Map &map, int x, int y);

    // Ve vung viewer hien tai len man hinh
    void drawVisible(sf::RenderTarget &target, sf::RenderStates state, const sf::View &view) const;

    // Kiemtra texture co load duoc ko
    bool is_TextureLoaded() const;

    // Cac ham phu
    int Get_min(int a, int b);
    int Get_max(int a, int b);
};