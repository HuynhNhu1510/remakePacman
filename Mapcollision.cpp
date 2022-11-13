#include<array>
#include<cmath>
#include"global.h"
#include"Mapcollision.h"

bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, std::array<std::array<Cell, Map_Height>, Map_Width>& i_map) {
	bool output = 0;
	/*vi tri chinh xac cua pacman hien tai de tinh toan va cham*/
	float cell_x = i_x / static_cast<float>(Cell_Size);
	float cell_y = i_y / static_cast<float>(Cell_Size);

	for (unsigned char a = 0; a < 4; a++) {
		short x = 0;
		short y = 0;

		switch (a) {
		case 0: {//top left
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 1: {//top right
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(floor(cell_y));
			break;
		}
		case 2: {//bottom left
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(ceil(cell_y));
			break;
		}
		case 3: {//bottom right
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(ceil(cell_x));

		}

	}
		if (0 <= x && 0 <= y && Map_Height > y && Map_Width > x) {
			//check position is still in the map
			if (0 == i_collect_pellets) {
				if (Cell::Wall == i_map[x][y]) {
					output = 1;
				}
				else if (0 == i_use_door && Cell::Door == i_map[x][y]) {//wall check
					output = 1;
				}
			}
			else {
				if (Cell::Energizer == i_map[x][y]) {//collecteble thing
					output = 1;

					i_map[x][y] = Cell::Empty;
				}
				else if (Cell::Pellet == i_map[x][y]) {
					i_map[x][y] = Cell::Empty;
				}
			}
		}
		return output;
	}
}
