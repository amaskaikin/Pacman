#ifndef _BORDER
#define _BORDER

#include "SDL.h"
#include "SDL_image.h"
#include "features.h"

#define BORDER_LENGTH 28
#define BORDER_HEIGHT 31

//Define squaretype(the field of game consists of squares)
typedef enum
{
	DoubleCorner,
	SingleCorner,
	Middle,
	Hall,
	TLeft,
	TRight,
	CorralCorner,
	CorralSide
} SquareType_t;

//Define border of square
typedef struct
{
	SDL_Surface *img;
	int x;
	int y;
	int walkable;
} BorderSquare_t;

//Define border, exactly
typedef struct
{
	BorderSquare_t borderSquares[BORDER_LENGTH][BORDER_HEIGHT];
} Border_t;

int isvalid_sq(Border_t *border, int x, int y);
int isteleport_sq(int x, int y); //Return 1 if the square is teleport

void load_border(Border_t *border, CollectPills_t *collectPills, const char* file);

#endif