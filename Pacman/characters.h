#pragma once

#include "border.h"
#include "direction.h"
#include "physcs.h"

/*pacman has a location (x,y) on the board. This is the tile his center is, and it defines his actual tile
he also has x/y tile offset, which can be between (-8, 7)
this defines his exact position on each individual tile, and his position for purposes of collision*/


/*typedef for pacman when he is moving
if he moved against a wall and the player doesn't move, he is considered "stuck"
this is needed for animation purposes*/
typedef enum
{
	Stuck, 
	NoStuck
} MoveType_t;

//Define pacman with full information(FULL MTHFCK!!)
typedef struct
{
	Body_t body;
	int score;
	int missedFrames;
	int lives;
	Direction_t lastDirect;
	MoveType_t moveType;
} Pacman_t;

//Init pacman, at start game
void init_pacman(Pacman_t *pacman);

//Init pacman's location, at the start of each level
void init_pacmanlvl(Pacman_t *pacman);

//Initializes pacman's location to the starting point (as well as direction and other values).
void init_pacmanloc(Pacman_t *pacman);

//Returns pacman speed for given level
int pacman_speed_normal(int lvl);
