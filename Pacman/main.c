#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "main.h"
#include "border.h"
#include "app_window.h"
#include "img_load.h"
#include "game.h"
#include "in.h"
#include "frames.h"

//Initializes all resources.
static void resource_init(void);

//Initialize all the internal entities needed for the game at startup
static void game_init(void);

//Called when a game is about to begin
static void startgame_init(void);

//Performs a loop, updating and rendering
static void main_loop(void);

//Defers to appropriate tick, based on current state.
static void internal_tick(void);

//Frees all resources.
static void clean_up(void);

//Processess and deals with all SDL events.
static void process_events(void);

static Game_t pacmanGame; 
static ProgramState_t state = Start;
static int gameRunning = 1;

int main(int argc, char** argv) 
{
	resource_init();
	game_init();

	main_loop();
	clean_up();

	return 0;
}

static void main_loop(void)
{
	while (gameRunning)
	{
		process_events();
		internal_tick();
		clear_scr(0, 0, 0, 0);
		g_render(&pacmanGame);
		
		flip_scr();
		sleep_fps();
	}
}

static void internal_tick(void)
{
	switch (state)
	{
		case Start:
			{
				state = Game;
				startgame_init();
			}
			break;
		case Game:
			g_tick(&pacmanGame);
	}
}

static void startgame_init(void)
{
	init_game(&pacmanGame);
}

static void game_init(void)
{
	//Load the board here. We only need to do it once
	load_border(&pacmanGame.border, &pacmanGame.collectPills, "maps/encodedboard");

	//set to be Start
	state = Start;

	//init the framerate manager
	init_fps(60);

}

static void resource_init(void)
{
	init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	load_imgs();
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
