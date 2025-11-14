#include "TileMap.h"
#include <iostream>
#include <cmath>

// ======== Constructor ========
TileMap::TileMap()
    : map_vertices(sf::Quads), map_textureLoaded(false),
      map_width(0), map_height(0)
{
}

// Load texture
bool TileMap::LoadTileset(const std::string &tilesetPath, sf::Vector2u tileSize)
{
    if (!map_tileSetTexture.loadFromFile(tilesetPath))
    {
        cout << "Khong the tai hinh anh" << tilesetPath << endl;
        map_textureLoaded = false;
        return false;
    }
    map_tileSetTexture.setRepeated(false);
    map_textureLoaded = true;
    map_tileSize = tileSize;

    return true;
}

// Build map tu file data nap vao
void TileMap::buildMap(const Map &Map)
{
    map_width = Map.get_width();
    map_height = Map.get_height();
    if (map_width == 0 || map_height == 0)
    {
        cout << "Khong doc duoc ban do" << endl;
        return;
    }

    // Khoi tao mang Vertex cua 4 dinh trong 1 tile
    map_vertices.setPrimitiveType(sf::Quads);
    map_vertices.resize(map_width * map_height * 4);
    if (map_vertices.getVertexCount() != static_cast<std::size_t>(map_width) * map_height * 4) {
    std::cerr << "Vertex array size mismatch: " << map_vertices.getVertexCount()
              << " vs " << (map_width * map_height * 4) << std::endl;
    }

    // Lay luoi tu map
    const auto &grid = Map.get_grid();
    int tilePerRow = map_tileSetTexture.getSize().x / map_tileSize.x; // Tinh so tile moi hang load duoc tu anh

    for (int y = 0; y < map_height; y++)
    {
        for (int x = 0; x < map_width; x++)
        {
            const Tile &tile = grid[y][x];          // Lay loai Tile hien tai
            int tileIndex = tile.getTilesetIndex(); // Lay index cua Tile trong anh TileSet

            int tx = tileIndex % tilePerRow; // Chi so cot trong texture
            int ty = tileIndex / tilePerRow; // Chi so hang trong texture

            sf::Vertex *quad = &map_vertices[(x + y * map_width) * 4]; // Xac dinh vi tri 4 vertex trong arr map_vertice
            // Chuyen tu mang 2D --> 1D

            // Cap nhat toa do that tren man hinh
            quad[0].position = sf::Vector2f(x * map_tileSize.x, y * map_tileSize.y);
            quad[1].position = sf::Vector2f((x + 1) * map_tileSize.x, y * map_tileSize.y);
            quad[2].position = sf::Vector2f(x * map_tileSize.x, (y + 1) * map_tileSize.y);
            quad[3].position = sf::Vector2f((x + 1) * map_tileSize.x, (y + 1) * map_tileSize.y);

            // Cap nhat toa do trong texture
            quad[0].texCoords = sf::Vector2f(tx * map_tileSize.x, ty * map_tileSize.y);
            quad[1].texCoords = sf::Vector2f((tx + 1) * map_tileSize.x, ty * map_tileSize.y);
            quad[2].texCoords = sf::Vector2f(tx * map_tileSize.x, (ty + 1) * map_tileSize.y);
            quad[3].texCoords = sf::Vector2f((tx + 1) * map_tileSize.x, (ty + 1) * map_tileSize.y);
        }
    }
}

// Update sau khi farm quai, khai thac tai nguyen tren 1 tile
void TileMap::updateTile(const Map &map, int x, int y)
{
    if (x < 0 || y < 0 || x >= map_width || y >= map_height)
    {
        cout << "Vi tri khong hop le\n";
        return;
    }

    const Tile &tile = map.get_grid()[y][x];
    int tilePerRow = map_tileSetTexture.getSize().x / map_tileSize.x;
    int tileIndex = tile.getTilesetIndex();
    int tx = tileIndex % tilePerRow;
    int ty = tileIndex / tilePerRow;

    sf::Vertex *quad = &map_vertices[(x + y * map_width) * 4];

    quad[0].position = sf::Vector2f(tx * map_tileSize.x, ty * map_tileSize.y);
    quad[1].position = sf::Vector2f((tx + 1) * map_tileSize.x, ty * map_tileSize.y);
    quad[2].position = sf::Vector2f(tx * map_tileSize.x, (ty + 1) * map_tileSize.y);
    quad[3].position = sf::Vector2f((tx + 1) * map_tileSize.x, (ty + 1) * map_tileSize.y);
}

// Ve vung viewer hien tai len man hinh
void TileMap::drawVisible(sf::RenderTarget &target, sf::RenderStates state, const sf::View &view) const
{
    if (!map_textureLoaded)
    {
        cout << "Khong doc duoc file map\n";
        return;
    }
    state.transform *= getTransform();
    state.texture = &map_tileSetTexture;

    // Lay vung nhin thay cua camera
    sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());

    // Xac dinh phan vung cho map
    int StartX = TileMap::Get_max(0, static_cast<int>(viewRect.left / map_tileSize.x));
    int StartY = TileMap::Get_max(0, static_cast<int>(viewRect.top / map_tileSize.y));
    int endX = TileMap::Get_min(map_width, static_cast<int>((viewRect.left + viewRect.width) / map_tileSize.x) + 1);
    int endY = TileMap::Get_min(map_height, static_cast<int>((viewRect.top + viewRect.height) / map_tileSize.y) + 1);

    // 3. Tạo một vertex array tạm cho vùng visible
   int w = TileMap::Get_max(0, endX - StartX);
    int h = TileMap::Get_max(0, endY - StartY);
    sf::VertexArray visible(sf::Quads);
    if (w == 0 || h == 0) {
        // nothing to draw
        return;
    }
    visible.resize(static_cast<std::size_t>(w) * static_cast<std::size_t>(h) * 4);

    // 4. Copy các tile trong vùng nhìn sang visible
    for (int y = StartY; y < endY; ++y)
    {
        for (int x = StartX; x < endX; ++x)
        {
            const sf::Vertex *src = &map_vertices[(x + y * map_width) * 4];
            sf::Vertex *dst = &visible[((x - StartX) + (y - StartY) * (endX - StartX)) * 4];
            for (int i = 0; i < 4; i++)
                dst[i] = src[i];
        }
    }

    // 5. Vẽ vùng visible
    target.draw(visible, state);
}

void TileMap::update(float deltaTime)
{
    // Nếu bạn có animated tiles: update frame index ở đây.
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (!map_textureLoaded)
    {
        cout << "Khong doc duoc file map\n";
        return;
    }
    state.transform *= getTransform();
    state.texture = &map_tileSetTexture;
    target.draw(map_vertices, state);
}

// Kiemtra texture co load duoc ko
bool TileMap::is_TextureLoaded() const
{
    return map_textureLoaded;
}

// Cac ham phu
int TileMap::Get_min(int a, int b)
{
    return (a < b) ? a : b;
}

int TileMap::Get_max(int a, int b)
{
    return (a > b) ? a : b;
}
