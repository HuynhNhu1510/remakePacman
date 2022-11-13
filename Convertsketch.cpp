#include <array>
#include<string>
#include <SFML/Graphics.hpp>
#include "global.h"
#include "Pacman.h"
#include "Convertsketch.h"

std::array<std::array<Cell, Map_Height>, Map_Width> convert_sketch(const std::array<std::string, Map_Height>& i_map_sketch, std::array<Position, 4>& i_ghost_positions, Pacman& i_pacman)
{
	std::array<std::array<Cell, Map_Height>, Map_Width> output_map{};

	for (unsigned char a = 0; a < Map_Height; a++)
	{
		for (unsigned char b = 0; b < Map_Width; b++)
		{
			//By default, every cell is empty.
			output_map[b][a] = Cell::Empty;

			switch (i_map_sketch[a][b])
			{
				//#wall #obstacle #youcantgothroughme
			case '#':
			{
				output_map[b][a] = Cell::Wall;

				break;
			}
			case '=':
			{
				output_map[b][a] = Cell::Door;

				break;
			}
			case '.':
			{
				output_map[b][a] = Cell::Pellet;

				break;
			}
			//Red ghost
			case '0':
			{
				i_ghost_positions[0].x = Cell_Size * b;
				i_ghost_positions[0].y = Cell_Size * a;

				break;
			}
			//Pink ghost
			case '1':
			{
				i_ghost_positions[1].x = Cell_Size * b;
				i_ghost_positions[1].y = Cell_Size * a;

				break;
			}
			//Blue (cyan) ghost
			case '2':
			{
				i_ghost_positions[2].x = Cell_Size * b;
				i_ghost_positions[2].y = Cell_Size * a;

				break;
			}
			//Orange ghost
			case '3':
			{
				i_ghost_positions[3].x = Cell_Size * b;
				i_ghost_positions[3].y = Cell_Size * a;

				break;
			}
			//Pacman!
			case 'P':
			{
				i_pacman.set_position(Cell_Size * b, Cell_Size * a);

				break;
			}
			//This looks like a surprised face.
			case 'o':
			{
				output_map[b][a] = Cell::Energizer;
			}
			}
		}
	}

	return output_map;
}