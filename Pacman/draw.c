#include "SDL.h"
#include "SDL_image.h"

#include "border.h"
#include "draw.h"
#include "img_load.h"
#include "game.h"
#include "app_window.h"

//Offset the board is off from the top of the screen
//Needed because some items are stored in board (x,y) coords and need to be rendered at an offset
#define Y_OFFSET 3
static int offset = 3 * 16;

//
//
// Board rendering
//
//

void draw_border(Border_t *border)
{
	int x,y;
	for (y = 0; y < BORDER_HEIGHT; y++)
	{
		for (x = 0; x < BORDER_LENGTH; x++)
		{
			set_surface(x * 16, offset + y * 16, (border->borderSquares[x][y]).img);
		}
	}
}

