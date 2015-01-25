#ifndef _APP_WINDOW
#define _APP_WINDOW

#include "SDL.h"

//Sets the rendering window
void set_window(void);

//Sets a surface to the screen at the given coordinates.
void set_surface(int x, int y, SDL_Surface* source);

//Used for double buffering. Flips the buffers.
void flip_scr(void);

//Initializes the window with title, height and width
int init_window(const char* title, int width, int height);

//Gets the SDL_Surface which represents the entire screen.
SDL_Surface *get_scr(void);

//Cleans the screen to the given color.
void clear_scr(int r, int g, int b, int a);

#endif
