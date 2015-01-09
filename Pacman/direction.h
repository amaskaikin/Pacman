#pragma once

//Define four main directios
typedef enum
{
	Up,
	Down,
	Left,
	Right
} Direction_t;

//Defint for diagonal directions
typedef enum
{
	TopLeft,
	TopRight,
	BotLeft,
	BotRight
} DiagDirect_t;

//Returns opposite direction
Direction_t direct_opp(Direction_t dir);

//Copies -1, 0, 1 to the given x and y ints depending on what direction is given
void direct_xy(Direction_t dir, int *x, int *y);
