#pragma once

#include "border.h"

typedef struct
{
	Border_t border;
} Game_t;

//Renders the game
void g_render(Game_t *game);
