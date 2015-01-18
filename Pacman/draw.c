#include "SDL.h"
#include "SDL_image.h"

#include "border.h"
#include "draw.h"
#include "img_load.h"
#include "game.h"
#include "app_window.h"
#include "anim.h"

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
void draw_pacman(Pacman_t *pacman)
{
	int frame;
	int xOffset, yOffset;
	Direction_t aniDir;

	if (pacman->moveType == Stuck)
	{
		//if left/ down, he needs full open frame
		//if up/ right, he uses semi-open frame
		aniDir = pacman->lastDirect;
		if (aniDir == Left || aniDir == Down)
		{
			frame = 2;
		}
		else
		{
			frame = 1;
		}
	}
	else
	{
		aniDir = pacman->body.cur;
		frame = anim_get_frame(50, 4);
	}

	xOffset = pacman->body.xOffset - 4;
	yOffset = offset + pacman->body.yOffset - 4;

	draw_image_coord_offset(pacman_ani_img(aniDir, frame), pacman->body.x, pacman->body.y, xOffset, yOffset);
}

void draw_pacman_static(Pacman_t *pacman)
{
	int xOffset = pacman->body.xOffset - 4;
	int yOffset = offset + pacman->body.yOffset - 6;

	draw_image_coord_offset(pacman_img(), pacman->body.x, pacman->body.y, xOffset, yOffset);
}

void draw_pacman_lives(int numLives)
{
	int i;
	int x = 2 * 16;
	int y = 34 * 16;

	for (i = 0; i < numLives; i++)
	{
		set_surface(x, y, pacman_life_img());

		x += 16 * 2;
	}
}

//
//
// PIll renderering
//
//

void draw_pill_small(Pill_t *p)
{
	draw_image_coord(p->img, p->x, p->y);
}

void draw_small_pills(CollectPills_t *cp)
{
	int i;
	for (i = 0; i < PILLS_NUMBER; i++)
	{
		Pill_t p = cp->Pills[i];

		if (p.type != Small) continue;

		set_surface(p.x * 16, offset + p.y * 16, p.img);
	}
}

void draw_large_pills(CollectPills_t *cp)
{
	int i;

	for (i = 0; i < PILLS_NUMBER; i++)
	{
		Pill_t p = cp->Pills[i];

		if (p.type != Large) continue;

		set_surface(p.x * 16, offset + p.y * 16, p.img);
	}
}
