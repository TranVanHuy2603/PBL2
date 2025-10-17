#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <SFML/Graphics.hpp>
#include <windows.h>
#include "String.h"

static sf::RenderWindow* g_window = nullptr; // Cua so chinh
static sf::Event g_event; // Su kien theo thoi gian tren screen

// Phan chia man hinh
const int SCEEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

// MAU KEY
sf::Color COLOR_KEY(167, 175,180);


#endif