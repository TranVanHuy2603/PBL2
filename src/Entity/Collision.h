#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Monster.h"
#include "Castle.h"
#include "Quadtree.h"

class Collision {
public:
    // Kiểm tra va chạm giữa 2 sprite
    static bool CheckCollision(const sf::Sprite& a, const sf::Sprite& b);

    // Xử lý va chạm nhân vật với quái
    static void CharacterMonster(Character* player, Vector<Monster*>& monsters);

    // Xử lý nhân vật không đi xuyên tường (có thể dùng bounding box map)
    static void CharacterWall(Character* player, const Vector<sf::FloatRect>& walls);

    // Xử lý quái va chạm với castle
    static void MonsterCastle(Vector<Monster*>& monsters, Castle* castle);
};

#endif
