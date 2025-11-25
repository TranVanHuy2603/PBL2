#include "Intro.h"
#include <iostream>

Intro::Intro() : index(0), alpha(0.f), finished(false), nextSound("assets/audio/intro.ogg")
{
    bgTexture.loadFromFile("assets/background/backgroundmenu.png");
    background.setTexture(bgTexture);
    sf::Vector2u textureSize = bgTexture.getSize();
    float scaleX = 1920.f / textureSize.x;
    float scaleY = 1080.f / textureSize.y;
    background.setScale(scaleX, scaleY);
    // Thêm các câu intro
    lines.push_back("The gioi da bi diet vong\nsau mot cuoc xam chiem cua nguoi ngoai hanh tinh");
    lines.push_back("Tat ca nha cua deu bi pha huy");
    lines.push_back("Chi con minh ban song sot");
    lines.push_back("Hay sinh ton");
    lines.push_back("Xay dung phao dai va che tao vu khi\nde chong lai nguoi ngoai hanh tinh xam chiem");
    lines.push_back("Chien dau va giai cuu trai dat");
    lines.push_back("BAT DAU!");

    // Load font
    if (!font.loadFromFile("assets/font/font1.ttf"))
        std::cerr << "Failed to load font!\n";

    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color(255, 255, 0, 0)); // màu trắng (trong suốt)
    text.setString(lines[index].c_str());
    text.setOutlineThickness(2.f);
    text.setOutlineColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    // Center text
    text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);

    // Background

    nextSound.setVolume(100.f);

    // Đặt text giữa màn hình
    text.setPosition(1920.f / 2.f, 1080.f / 2.f);
}

void Intro::update(float dt)
{
    if (alpha < 255.f)
    {
        alpha += 200.f * dt; // tốc độ fade-in
        if (alpha > 255.f)
            alpha = 255.f;
        text.setFillColor(sf::Color(255, 255, 0, static_cast<sf::Uint8>(alpha)));
    }
}

void Intro::draw(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(text);
}

void Intro::next()
{
    if (index < lines.get_size() - 1)
    {
        index++;
        text.setString(lines[index].c_str());
        // center lại
        text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
        alpha = 0.f;           // reset fade-in
        nextSound.playSound(); // phát 1 lần
    }
    else
    {
        finished = true;
    }
}
