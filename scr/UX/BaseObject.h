#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H
#define _HAS_STD_BYTE 0
// #define NOMINMAX

#include "CommonFunc.h"

class BaseObject {
    public:
        BaseObject();
        virtual ~BaseObject();
        void SetPosition(int x, int y);
        sf::Vector2f GetPosition() const;
        bool LoadImg(const std::string &path, sf::RenderWindow &window);
        void Draw(sf::RenderWindow &window);
    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2u size;
};

#endif
