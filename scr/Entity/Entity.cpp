#include "Entity.h"

Entity::Entity(int _x, int _y, double _radius)
       :x(_x), y(_y), radius(_radius) {};

int Entity::get_x() const { return x; }
int Entity::get_y() const { return y; }
int Entity::get_radius() const { return radius; }
void Entity::set_position(int newx, int newy) 
{
       x = newx;
       y = newy;
} 
bool Entity::is_walkable() const { return walkable; } 