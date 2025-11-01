#pragma once
#include <SFML/Graphics.hpp>


// Lớp trừu tượng cho mọi layer của bản đồ.
// Kế thừa sf::Drawable + sf::Transformable để có thể dùng window.draw(*layer)
class MapLayer : public sf::Drawable, public sf::Transformable {
public:
// update trạng thái nội bộ (ví dụ animation, sinh entities...)
virtual void update(float deltaTime) = 0;


// draw() là override của sf::Drawable -> vẫn để pure virtual để lớp con implement
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;


virtual ~MapLayer() = default;
};