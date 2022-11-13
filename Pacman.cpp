#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "global.h"
#include "Pacman.h"
#include "Mapcollision.h"
Pacman::Pacman() :
	animation_over(0),
	dead(0),
	direction(0),
	energizer_timer(0),
	position({ 0, 0 })
{
	//I just realized that I already explained everything in the Ghost class.
	//And I don't like to repeat myself.
}

bool Pacman::get_animation_over()
{
	return animation_over;
}

bool Pacman::get_dead()
{
	return dead;
}

unsigned char Pacman::get_direction()
{
	return direction;
}

unsigned short Pacman::get_energizer_timer()
{
	return energizer_timer;
}

void Pacman::draw(bool i_victory, sf::RenderWindow& i_window)
{
	unsigned char frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(Pacman_Animation_speed)));

	sf::Sprite sprite;

	sf::Texture texture;

	sprite.setPosition(position.x, position.y);

	if (1 == dead || 1 == i_victory)
	{
		if (animation_timer < Pacman_Death_Frames * Pacman_Animation_speed)
		{
			animation_timer++;

			texture.loadFromFile("Resources/PacmanDeath" + std::to_string(Cell_Size) + ".png");

			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(Cell_Size * frame, 0, Cell_Size, Cell_Size));

			i_window.draw(sprite);
		}
		else
		{
			//You can only die once.
			animation_over = 1;
		}
	}
	else
	{
		texture.loadFromFile("Resources/" + std::to_string(Cell_Size) + ".png");

		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(Cell_Size * frame, Cell_Size * direction, Cell_Size, Cell_Size));

		i_window.draw(sprite);

		animation_timer = (1 + animation_timer) % (Pacman_Animation_Frames * Pacman_Animation_speed);
	}
}

void Pacman::reset()
{
	animation_over = 0;
	dead = 0;

	direction = 0;

	animation_timer = 0;
	energizer_timer = 0;
}

void Pacman::set_animation_timer(unsigned short i_animation_timer)
{
	animation_timer = i_animation_timer;
}

void Pacman::set_dead(bool i_dead)
{
	dead = i_dead;

	if (1 == dead)
	{
		//Making sure that the animation starts from the beginning.
		animation_timer = 0;
	}
}

void Pacman::set_position(short i_x, short i_y)
{
	position = { i_x, i_y };
}

void Pacman::update(unsigned char i_level, std::array<std::array<Cell, Map_Height>, Map_Width>& i_map)
{
	std::array<bool, 4> walls{};
	walls[0] = map_collision(0, 0, Pacman_speed + position.x, position.y, i_map);
	walls[1] = map_collision(0, 0, position.x, position.y - Pacman_speed, i_map);
	walls[2] = map_collision(0, 0, position.x - Pacman_speed, position.y, i_map);
	walls[3] = map_collision(0, 0, position.x, Pacman_speed + position.y, i_map);

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (0 == walls[0]) //You can't turn in this direction if there's a wall there.
		{
			direction = 0;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (0 == walls[1])
		{
			direction = 1;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (0 == walls[2])
		{
			direction = 2;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (0 == walls[3])
		{
			direction = 3;
		}
	}

	if (0 == walls[direction])
	{
		switch (direction)
		{
		case 0:
		{
			position.x += Pacman_speed;

			break;
		}
		case 1:
		{
			position.y -= Pacman_speed;

			break;
		}
		case 2:
		{
			position.x -= Pacman_speed;

			break;
		}
		case 3:
		{
			position.y += Pacman_speed;
		}
		}
	}

	if (-Cell_Size >= position.x)
	{
		position.x = Cell_Size * Map_Width - Pacman_speed;
	}
	else if (Cell_Size * Map_Width <= position.x)
	{
		position.x = Pacman_speed - Cell_Size;
	}

	if (1 == map_collision(1, 0, position.x, position.y, i_map)) //When Pacman eats an energizer...
	{
		//He becomes energized!
		energizer_timer = static_cast<unsigned short>(Energizer / pow(2, i_level));
	}
	else
	{
		energizer_timer = std::max(0, energizer_timer - 1);
	}
}

Position Pacman::get_position()
{
	return position;
}
