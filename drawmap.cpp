#include <array>
#include <SFML/Graphics.hpp>
#include "global.h"
void draw_map(const std::array<std::array<Cell, Map_Height>, Map_Width>& i_map, sf::RenderWindow& i_window)
{
	sf::Sprite sprite;

	sf::Texture texture;
	texture.loadFromFile("Resources/Images/Map" + std::to_string(Cell_Size) + ".png");

	sprite.setTexture(texture);

	for (unsigned char a = 0; a < Map_Height; a++)
	{
		for (unsigned char b = 0; b < Map_Height; b++)
		{
			sprite.setPosition(static_cast<float>(Cell_Size * a), static_cast<float>(Cell_Size * b));

			//We just crop out what we need from the texture.
			switch (i_map[a][b])
			{
			case Cell::Door:
			{
				sprite.setTextureRect(sf::IntRect(2 * Cell_Size, Cell_Size, Cell_Size, Cell_Size));

				i_window.draw(sprite);

				break;
			}
			case Cell::Energizer:
			{
				sprite.setTextureRect(sf::IntRect(Cell_Size, Cell_Size, Cell_Size, Cell_Size));

				i_window.draw(sprite);

				break;
			}
			case Cell::Pellet:
			{
				sprite.setTextureRect(sf::IntRect(0, Cell_Size, Cell_Size, Cell_Size));

				i_window.draw(sprite);

				break;
			}
			case Cell::Wall:
			{
				bool down = 0;
				bool left = 0;
				bool right = 0;
				bool up = 0;

				if (b < Map_Height - 1)
				{
					if (Cell::Wall == i_map[a][1 + b])
					{
						down = 1;
					}
				}
				if (0 < a)
				{
					if (Cell::Wall == i_map[a - 1][b])
					{
						left = 1;
					}
				}
				else
				{
					left = 1;
				}

				if (a < Map_Width - 1)
				{
					if (Cell::Wall == i_map[1 + a][b])
					{
						right = 1;
					}
				}
				else
				{
					right = 1;
				}

				if (0 < b)
				{
					if (Cell::Wall == i_map[a][b - 1])
					{
						up = 1;
					}
				}
			sprite.setTextureRect(sf::IntRect(Cell_Size * (down + 2 * (left + 2 * (right + 2 * up))), 0, Cell_Size, Cell_Size));

				i_window.draw(sprite);
			}
			}
		}
	}
}