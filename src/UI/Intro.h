#pragma once
#include <SFML/Graphics.hpp>
#include "Audio.h"
#include "Vector.h" // Vector tự định nghĩa

class Intro
{
private:
    Vector<String> lines;   // danh sách các câu
    int index;              // câu hiện tại
    sf::Text text;          // text hiển thị
    sf::Font font;          // font chữ
    float alpha;            // alpha để fade-in
    bool finished;          // kết thúc
    sf::Sprite background; // background
    sf::Texture bgTexture;
    Audio nextSound;        // âm thanh xuất hiện câu

public:
    Intro();
    void update(float dt);  // cập nhật alpha
    void draw(sf::RenderWindow& window); // vẽ background + text
    void next();            // chuyển câu tiếp
    bool isFinished() const { return finished; }
};
