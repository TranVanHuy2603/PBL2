#include "BaseObject.h"
using u = unsigned int;
BaseObject::BaseObject() {}

BaseObject::~BaseObject() {}

void BaseObject::SetPosition(int x, int y) {
    this->sprite.setPosition(static_cast<float>(x), static_cast<float>(y)); 
}

sf::Vector2f BaseObject::GetPosition() const{ 
    return this->sprite.getPosition(); 
}
bool BaseObject::LoadImg(const std::string &path, sf::RenderWindow &window)
{
    sf::Texture new_texture;
    if (!new_texture.loadFromFile(path)) {
        return false;
    }

    this->sprite.setTexture(new_texture);
    sf::Image image;
    if(image.loadFromFile(path)) {
        for(int y = 0; y < image.getSize().y; y++) {
            for(int x = 0; x < image.getSize().x; x++) {
                if(image.getPixel(x, y) == COLOR_KEY) 
                    image.setPixel(x, y, sf::Color(0,0,0,0));
            }
        }
        new_texture.loadFromImage(image);
        sprite.setTexture(new_texture);
    }

    texture = new_texture;
    size = texture.getSize();
    return true;
}

void BaseObject::Draw(sf::RenderWindow &window) {
    window.draw(this->sprite); // Ve nhan vat ra/ vat the
}