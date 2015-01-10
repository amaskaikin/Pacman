#pragma once

#include "border.h"
#include "characters.h"

typedef struct
{
	Border_t border;
	Pacman_t pacman;
	int level;
} Game_t;

//Renders the game
void g_render(Game_t *game);

//Init first level
void init_game(Game_t *game);

void process_player(Game_t *game);
