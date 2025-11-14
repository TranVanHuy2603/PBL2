#pragma once
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <SFML/Graphics.hpp>
#include "String.h"

// Cửa sổ chính
static sf::RenderWindow* g_window = nullptr;
static sf::Event g_event;

// Kích thước màn hình
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

// Màu key
inline const sf::Color COLOR_KEY(167, 175, 180);

#endif
