#pragma once 

#include "SDL.h"

#define PILLS_NUMBER 244

//Define pills type
typedef enum
{
	Small,
	Large	
} PillType_t;

//Define a pill with type, location etc.
typedef struct
{
	PillType_t type;
	int x;
	int y;
	SDL_Surface *img;
} Pill_t;

//All pills (counts existing pills0)
typedef struct
{
	int totalPills;
	Pill_t Pills[PILLS_NUMBER];
} CollectPills_t;

//Init pills, reset all counters
void init_pills(CollectPills_t *collectPills);


