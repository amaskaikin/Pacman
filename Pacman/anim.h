#pragma once

#include "SDL.h"
#include "SDL_image.h"

typedef struct
{
	SDL_Surface *surfaces;
	int imgNum;
	int freq;
} Animation_t;

int anim_getFrame(Animation_t *anim);
int anim_get_frame(int msBetweenFrames, int framesNum);
int anim_get_frame_dt(int currentDt, int msBetweenFrames, int framesNum);