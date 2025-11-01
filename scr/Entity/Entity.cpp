#include "Entity.h"
#include <iostream>

// ===== Constructor =====
Entity::Entity()
    : x(0), y(0), walkable(true)
{
    sprite.setPosition(0.f, 0.f);
    sprite.setScale(1.f, 1.f);
    sprite.setOrigin(0.f, 0.f);
}

Entity::Entity(int _x, int _y)
    : x(_x), y(_y), walkable(true)
{
    sprite.setPosition((float)x, (float)y);
    sprite.setScale(1.f, 1.f);
    sprite.setOrigin(0.f, 0.f);
}

// ===== Getter =====
int Entity::get_x() const { return x; }
int Entity::get_y() const { return y; }
std::string Entity::get_type() const { return type; }
bool Entity::is_walkable() const { return walkable; }
const sf::Sprite& Entity::get_sprite() const { return sprite; }

// ===== Setter =====
void Entity::set_position(int newx, int newy)
{
    x = newx;
    y = newy;
    sprite.setPosition((float)x, (float)y);
}

void Entity::set_texture(const std::string& path)
{
    if (!texture.loadFromFile(path))
        std::cout << "Error loading texture from: " << path << "\n";
    sprite.setTexture(texture);
}

void Entity::set_texture(const sf::Texture& tex)
{
    texture = tex;
    sprite.setTexture(texture);
}

void Entity::set_origin_center()
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Entity::set_scale(float sx, float sy)
{
    sprite.setScale(sx, sy);
}

void Entity::set_texture_rect(const sf::IntRect& rect)
{
    sprite.setTextureRect(rect);
}

// ===== Draw =====
void Entity::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
