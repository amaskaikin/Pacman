#pragma once

#include "border.h"
#include "characters.h"
#include "frames.h"
#include "features.h"

typedef enum
{
	GameBegin,
	LevelBegin,
	GamePlay,
	Win,
	Death,
	Gameover
} StateGame_t;

typedef enum
{
	Mode1,
	Mode2,
	Mode3,
	Mode4,
} TimeMode_t;

typedef struct
{
	Border_t border;
	Pacman_t pacman;
	Ghost_t ghosts[4];
	CollectPills_t collectPills;
	StateGame_t stategame;
	TimeMode_t timemode;
	unsigned int ticksNewMode;
	unsigned int lvltime;
	DispFruit_t dispFruit1, dispFruit2;
	int level;
	int InkyCounter, ClydeCounter;
} Game_t;

//Ticks(game 1 tick - 1/60th of a second)
void g_tick(Game_t *game);

//Renders the game
void g_render(Game_t *game);

//Init first level
void init_game(Game_t *game);

//Init next level
void new_level(Game_t *game);

void death(Game_t *game);