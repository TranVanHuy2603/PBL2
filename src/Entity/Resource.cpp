#include "Resource.h"

Resource::Resource(int x, int y, ResourceType type, const string &filename, int gold, int exp, float scale)
    : Entity(x, y), resourcetype(type), gold(gold), exp(exp), hp(3)
{
    if (!texture.loadFromFile(filename)) cout << "Loi khi doc tai nguyen\n";
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(x, y);
    status = true;
}

Resource::~Resource() {}

ResourceType Resource::get_type() const { return resourcetype; }
void Resource::set_status(bool value) { status = value; }
sf::Sprite& Resource::get_sprite() { return sprite; }
bool Resource::get_status() const { return status; }

void Resource::draw(sf::RenderWindow& window)
{
    if (status)
    {
        window.draw(sprite);
    }
}

int Resource::get_gold() const { return gold; }
int Resource::get_exp() const { return exp; }

void Resource::take_damage()
{
    if (status && hp > 0)
    {
        hp--;
        if (hp <= 0) 
        {
            set_status(false);
        }
    }
}