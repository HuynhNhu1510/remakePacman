#pragma once
#include"Pacman.h"
#include"global.h"

std::array<std::array<Cell, Map_Height>, Map_Width> Convert_sketch(const std::array<std::string, Map_Height>& i_map_sketch, std::array<Position, 4>& i_ghost_positions, Pacman& i_pacman);
