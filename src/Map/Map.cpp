#include "Map.h"
#include <iostream>
#include "String.h"
#include "Vector.h"
#include "Monster.h"
using namespace std;

Map::Map(float worldWidth, float worldHeight)
{
    if (!loadFromFile(worldWidth, worldHeight))
    {
        cout << "Failed to load map texture!" << endl;
    }
}

bool Map::loadFromFile(float worldWidth, float worldHeight)
{
    if (!backgroundTexture.loadFromFile("assets/background/map.png"))
    {
        return false;
    }

    background.setTexture(backgroundTexture);

    // Lấy kích thước gốc texture
    sf::Vector2u texSize = backgroundTexture.getSize();

    // Scale sprite để phủ toàn bộ world
    float scaleX = worldWidth / texSize.x;
    float scaleY = worldHeight / texSize.y;
    background.setScale(scaleX, scaleY);

    // Đặt vị trí giữa world
    background.setPosition(0.f, 0.f); // nếu muốn bắt đầu từ (0,0)
    // hoặc đặt center nếu muốn dùng center:
    // background.setOrigin(texSize.x/2.f, texSize.y/2.f);
    // background.setPosition(worldWidth/2.f, worldHeight/2.f);

    return true;
}

void Map::draw(sf::RenderWindow &window, const sf::View &view)
{
    sf::View oldView = window.getView();

    // Dùng view camera để vẽ background
    window.setView(view);
    window.draw(background);

    // Khôi phục view mặc định để vẽ các object khác
    window.setView(oldView);
}

// void Map::setGrid(Vector<Entity *> &entity, Vector<Vector<ASNode>> &grid, double cellSize)
// {

//     for (auto *ent : entity)
//     {
//         Monster *monster = dynamic_cast<Monster *>(ent);
//         if (monster)
//         { // chỉ những đối tượng Monster
//             int mx = static_cast<int>(monster->get_x() / cellSize);
//             int my = static_cast<int>(monster->get_y() / cellSize);
//             if (mx >= 0 && mx < grid[0].get_size() &&
//                 my >= 0 && my < grid.get_size())
//             {
//                 grid[my][mx].set_walkable(false);
//             }
//         }
//     }
// }

// void Map::updateGrid(Vector<Entity*>& entities, Vector<Vector<ASNode>>& grid, double cellSize)
// {
//     int rows = grid.get_size();
//     if (rows == 0) return;
//     int cols = grid[0].get_size();

//     // 1️⃣ Reset grid (tất cả walkable = true)
//     for (int y = 0; y < rows; ++y)
//         for (int x = 0; x < cols; ++x)
//             grid[y][x].set_walkable(true); // hoặc giữ vật cản cố định nếu cần

//     // 2️⃣ Đặt lại các ô có quái
//     for (auto* ent : entities) {
//         Monster* monster = dynamic_cast<Monster*>(ent);
//         if (!monster) continue;

//         int mx = static_cast<int>(monster->get_x() / cellSize);
//         int my = static_cast<int>(monster->get_y() / cellSize);

//         // Kiểm tra ranh giới grid
//         if (mx >= 0 && mx < cols && my >= 0 && my < rows)
//             grid[my][mx].set_walkable(false);
//     }
// }
