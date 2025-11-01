#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "String.h"

class Entity // đại diện cho mọi vật thể trong game
{
protected:
    sf::Sprite sprite;   // sprite chính của entity (sẽ dùng cho animation)
    sf::Texture texture; // texture riêng, để tránh mất dữ liệu khi animation thay frame
    int x, y;            // toạ độ trong thế giới game
    bool walkable;       // có thể đi xuyên qua hay không
    std::string type;    // loại đối tượng (Character, Monster, Castle, ...)

public:
    Entity();
    Entity(int x, int y);

    // ===== Getter =====
    int get_x() const;
    int get_y() const;
    std::string get_type() const;
    bool is_walkable() const;
    const sf::Sprite& get_sprite() const;

    // ===== Setter =====
    void set_position(int newx, int newy);
    void set_texture(const std::string& path);
    void set_texture(const sf::Texture& tex);
    void set_origin_center();
    void set_scale(float sx, float sy);
    void set_texture_rect(const sf::IntRect& rect);

    // ===== Draw =====
    virtual void draw(sf::RenderWindow& window);
};
