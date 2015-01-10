#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "main.h"
#include "border.h"
#include "app_window.h"
#include "img_load.h"
#include "game.h"
#include "in.h"

//Called when a game is about to begin
static void startgame_init(void);

//Performs a loop, updating and rendering
static void main_loop(void);
//Frees all resources.
static void clean_up(void);
//Processess and deals with all SDL events.
static void process_events(void);

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
		process_events();
		startgame_init();
		process_player(&pacmanGame);
		g_render(&pacmanGame);
		
		flip_scr();
	}
}

static void startgame_init(void)
{
	init_game(&pacmanGame);
}

static void process_events(void)
{
	static SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				gameRunning = 0;

				break;
			case SDL_KEYDOWN:
				handle_keydown(event.key.keysym.sym);
				//key_down_hacks(event.key.keysym.sym);

				break;
			case SDL_KEYUP:
				handle_keyup(event.key.keysym.sym);

				break;
		}
	}

	keyevents_finished();
}

static void clean_up(void)
{
	set_window();
	set_imgs();

	SDL_Quit();
}
