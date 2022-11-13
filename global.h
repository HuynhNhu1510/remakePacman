#pragma once
constexpr unsigned char Cell_Size = 16;
constexpr unsigned char Font_Size = 16;
constexpr unsigned char Ghost_Speed = 1;
constexpr unsigned char Ghost_1_Chase = 2;
constexpr unsigned char Ghost_2_Chase = 1;
constexpr unsigned char Ghost_3_Chase = 4;
constexpr unsigned char Ghost_Animation_Speed = 4;
constexpr unsigned char Ghost_Escape_Speed = 4;
constexpr unsigned char Ghost_Animation_Frames = 6;
constexpr unsigned char Ghost_Frightened_Speed = 3;
constexpr unsigned char Map_Height = 21;
constexpr unsigned char Map_Width = 21;
constexpr unsigned char Screen_Resize = 2;
constexpr unsigned char Pacman_Animation_Frames = 6;
constexpr unsigned char Pacman_Animation_speed = 4;
constexpr unsigned char Pacman_Death_Frames = 12;
constexpr unsigned char Pacman_speed = 2;
constexpr unsigned short Chase_Duration = 1024;
constexpr unsigned short Energizer_Duration = 512;
constexpr unsigned short Frame_Duration = 16667;
constexpr unsigned short Ghost_Flash_Start = 64;
constexpr unsigned short Long_Scatter_Duration = 512;
constexpr unsigned short short_Scatter_Duration = 256;
enum Cell
{
	Door,
	Empty,
	Energizer,
	Pellet,
	Wall
};
class Position
{
public:
	short x;
	short y;

	bool operator==(const Position& i_position)
	{
		return this->x == i_position.x && this->y == i_position.y;
	}
};