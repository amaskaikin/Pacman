#include "app_window.h"

static SDL_Surface *scr;

void set_window(void)
{
	SDL_FreeSurface(scr);
}

void set_surface(int x, int y, SDL_Surface* source)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, scr, &offset);
}

void flip_scr(void)
{
	SDL_Flip(scr);
}

int init_window(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 1;
	}

	/*Set up a video mode with the specified width, height and bits-per-pixel.*/
	scr = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

	if (scr == NULL)
	{
		return 1;
	}

	SDL_WM_SetCaption(title, NULL);

	return 0;
}

SDL_Surface *get_scr(void)
{
	return scr;
}

void clear_scr(int r, int g, int b, int a)
{
	Uint32 col = SDL_MapRGBA(scr->format, r, g, b, a);
	SDL_FillRect(scr, NULL, col);
}