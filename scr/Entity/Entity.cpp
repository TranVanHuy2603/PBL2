#include "Entity.h"

Entity::Entity() {}
Entity::Entity(int _x, int _y)
    : x(_x), y(_y) {};

int Entity::get_x() const { return x; }
int Entity::get_y() const { return y; }
string Entity::get_type() const { return type; }
void Entity::set_position(int newx, int newy)
{
       x = newx;
       y = newy;
}

sf::Sprite Entity::get_sprite() const { return this->sprite; }

bool Entity::is_walkable() const { return walkable; }

void Entity::draw(sf::RenderWindow &window) // tham chieu toi cua so game dang thuc thi
{
       window.draw(sprite);
}
