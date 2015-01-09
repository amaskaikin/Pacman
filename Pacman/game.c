#include "game.h"
#include "border.h"
#include "app_window.h"
#include "draw.h"
#include "main.h"

void g_render(Game_t *game)
{
	draw_border(&game->border);
}