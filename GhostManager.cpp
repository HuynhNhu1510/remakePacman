#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "global.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostManager.h"

Ghostmanager::Ghostmanager() :
	current_wave(0),
	wave_timer(Long_Scatter_Duration),
	ghosts({ Ghost(0), Ghost(1), Ghost(2), Ghost(3) })
{

}

void Ghostmanager::draw(bool i_flash, sf::RenderWindow& i_window)
{
	for (Ghost& ghost : ghosts)
	{
		ghost.draw(i_flash, i_window);
	}
}

void Ghostmanager::reset(unsigned char i_level, const std::array<Position, 4>& i_ghost_positions)
{
	current_wave = 0;

	//increase level
	wave_timer = static_cast<unsigned short>(short_Scatter_Duration / pow(2, i_level));

	for (unsigned char a = 0; a < 4; a++)
	{
		ghosts[a].set_position(i_ghost_positions[a].x, i_ghost_positions[a].y);
	}

	for (Ghost& ghost : ghosts)
	{
		//We use the blue ghost to get the location of the house and the red ghost to get the location of the exit.
		ghost.reset(ghosts[2].get_position(), ghosts[0].get_position());
	}
}

void Ghostmanager::update(unsigned char i_level, std::array<std::array<Cell, Map_Height>, Map_Width>& i_map, Pacman& i_pacman)
{
	if (0 == i_pacman.get_energizer_timer()) //We won't update the wave timer when Pacman is energized.
	{
		if (0 == wave_timer)
		{
			if (7 > current_wave)
			{
				current_wave++;

				for (Ghost& ghost : ghosts)
				{
					ghost.switch_mode();
				}
			}
			if (1 == current_wave % 2)
			{
				wave_timer = Chase_Duration;
			}
			else if (2 == current_wave)
			{
				wave_timer = static_cast<unsigned short>(Long_Scatter_Duration / pow(2, i_level));
			}
			else
			{
				wave_timer = static_cast<unsigned short>(short_Scatter_Duration / pow(2, i_level));
			}
		}
		else
		{
			wave_timer--;
		}
	}

	for (Ghost& ghost : ghosts)
	{
		ghost.update(i_level, i_map, ghosts[0], i_pacman);
	}
}