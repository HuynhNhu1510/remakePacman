#pragma once
#include<array>
#include <algorithm>
#include "global.h"
bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, std::array<std::array<Cell, Map_Height>, Map_Width>& i_map);