#include "Resource.h"

Resource::Resource(int x, int y, ResourceType type, const string &filename, const string &name)
    : Entity(x, y), resourcetype(type), name(name)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    status = true;
}

ResourceType Resource::get_type() const { return resourcetype; }
string Resource::get_name() const { return name; }
void Resource::set_status() { status = false; }
sf::Sprite& Resource::get_sprite() { return sprite; }
