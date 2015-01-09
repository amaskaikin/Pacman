#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "main.h"
#include "border.h"
#include "app_window.h"
#include "img_load.h"
#include "game.h"

//Performs a loop, updating and rendering
static void main_loop(void);
//Frees all resources.
static void clean_up(void);

static Game_t pacmanGame;
static int gameRunning = 1;

int main(int argc, char** argv) {
   
	init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	load_imgs();
	load_border(&pacmanGame.border, "maps/encodedboard");
	
	main_loop();
	clean_up();

	return 0;
}

static void main_loop(void)
{
	while (gameRunning)
	{
		g_render(&pacmanGame);
		flip_scr();
	}
}

static void clean_up(void)
{
	set_window();
	set_imgs();

	SDL_Quit();
}
