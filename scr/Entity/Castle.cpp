#include "Castle.h"

Castle::Castle() {}
Castle::Castle(int x, int y, bool status,  int hp, int hp_max, int lv, int cost)
       :LivingEntity(x, y, status, hp, hp_max), level(lv), cost(cost) 
{
    this->walkable = false;
};
int Castle::get_level() const { return level; }
int Castle::get_cost() const { return cost; }
void Castle::set_level(int value) { level = value;  }
void Castle::set_cost(int value) { cost = value; }
void Castle::set_texture(string filetexture) 
{
    sf::Texture tt;
    tt.loadFromFile(filetexture);
    spite.setTexture(tt);
}
void Castle::level_up()
{
    if (level <= 10)
    {
        level++;
        cost += 50;
    }
}

void Castle::update(float deltatime) { }