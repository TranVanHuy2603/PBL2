#include "Collision.h"
#include <iostream>
using namespace std;
bool Collision::CheckCollision(const sf::Sprite& a, const sf::Sprite& b) {
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

// -----------------------------------------------------------
// Ngăn nhân vật đi xuyên tường
void Collision::CharacterWall(Character* player, const vector<sf::FloatRect>& walls) {
    sf::FloatRect playerBounds = player->get_sprite().getGlobalBounds();

    for (const auto& wall : walls) {
        if (playerBounds.intersects(wall)) {
            sf::Vector2f pos = player->get_sprite().getPosition();

            // Dời nhân vật ra khỏi tường
            if (playerBounds.left < wall.left) pos.x = wall.left - playerBounds.width;
            else if (playerBounds.left + playerBounds.width > wall.left + wall.width)
                pos.x = wall.left + wall.width;
            if (playerBounds.top < wall.top) pos.y = wall.top - playerBounds.height;
            else if (playerBounds.top + playerBounds.height > wall.top + wall.height)
                pos.y = wall.top + wall.height;

            player->get_sprite();
            player->set_position(pos);
        }
    }
}

// -----------------------------------------------------------
// Nhân vật chạm quái → nhận damage
void Collision::CharacterMonster(Character* player, vector<Monster*>& monsters) {
    for (auto* monster : monsters) {
        if (!monster->get_status()) continue;

        if (CheckCollision(player->get_sprite(), monster->get_sprite())) {
            player->take_damage(monster->get_damage());
            std::cout << "Player bi quai tan cong!\n";
        }
    }
}

// -----------------------------------------------------------
// Quái chạm vào Castle → gây damage
void Collision::MonsterCastle(vector<Monster*>& monsters, Castle* castle) {
    for (auto* monster : monsters) {
        if (!monster->get_status()) continue;

        if (CheckCollision(monster->get_sprite(), castle->get_sprite())) {
            castle->take_damage(monster->get_damage());
            std::cout << "Castle bi quai tan cong!\n";
        }
    }
}
