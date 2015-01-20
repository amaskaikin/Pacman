#pragma once

#include "border.h"
#include "characters.h"
#include "frames.h"
#include "features.h"

typedef struct
{
	Border_t border;
	Pacman_t pacman;
	Ghost_t ghosts[4];
	CollectPills_t collectPills;
	int level;
} Game_t;

//Ticks(game 1 tick - 1/60th of a second)
void g_tick(Game_t *game);

//Renders the game
void g_render(Game_t *game);

//Init first level
void init_game(Game_t *game);

void process_player(Game_t *game);
