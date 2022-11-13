#pragma once
#include<array>
#include <algorithm>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
void draw_text(bool i_center, unsigned short i_x, unsigned short i_y, const std::string& i_text, sf::RenderWindow& i_window);
