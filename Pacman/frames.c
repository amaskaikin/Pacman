#include "frames.h"
#include "SDL_framerate.h"

static FPSmanager fpsManager;
static int numTicks;

void init_fps(int hz)
{
	SDL_initFramerate(&fpsManager);
	senthz_fps(hz);
}

void senthz_fps(int hz)
{
	SDL_setFramerate(&fpsManager, hz);
}

void sleep_fps(void)
{
	numTicks++;
	SDL_framerateDelay(&fpsManager);
}

unsigned int ticks_game(void)
{
	return SDL_GetTicks();
}

unsigned int ticks_startup()
{
	return SDL_GetTicks();
}

unsigned int frames_game(void)
{
	return numTicks;
}

unsigned int frames_startup(void)
{
	return numTicks;
}