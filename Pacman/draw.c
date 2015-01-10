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

//draws an image at a board coordinate
void draw_image_coord(SDL_Surface *surface, int x, int y);
void draw_image_coord_offset(SDL_Surface *surface, int x, int y, int xOffset, int yOffset);

void draw_image_coord(SDL_Surface *surface, int x, int y)
{
	draw_image_coord_offset(surface, x, y, 0, 0);
}

void draw_image_coord_offset(SDL_Surface *surface, int x, int y, int xOffset, int yOffset)
{
	int pixPerTile = 16;
	set_surface(pixPerTile * x + xOffset, pixPerTile * y + yOffset, surface);
}

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

//
//
// Pacman renderering
//
//

void draw_pacman_static(Pacman_t *pacman)
{
	int xOffset = pacman->body.xOffset - 4;
	int yOffset = offset + pacman->body.yOffset - 6;

	draw_image_coord_offset(pacman_img(), pacman->body.x, pacman->body.y, xOffset, yOffset);
}