#include "Resource.h"

Resource::Resource(int x, int y, ResourceType type, const string &filename, int gold, int exp)
    : Entity(x, y), resourcetype(type), gold(gold), exp(exp)
{
    if (!texture.loadFromFile(filename)) cout << "Loi khi doc tai nguyen\n";
    sprite.setTexture(texture);
    status = true;
}

ResourceType Resource::get_type() const { return resourcetype; }
void Resource::set_status() { status = false; }
sf::Sprite& Resource::get_sprite() { return sprite; }

void Resource::draw(sf::RenderWindow& window)
{
    if (status)
    {
        window.draw(sprite);
    }
}

int Resource::get_gold() const { return gold; }
int Resource::get_exp() const { return exp; }
