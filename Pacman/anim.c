#include "anim.h"
#include "frames.h"

int anim_getFrame(Animation_t *anim)
{
	return anim->imgNum;
}

int anim_get_frame(int msBetweenFrames, int framesNum)
{
	unsigned int ticks = ticks_game();
	return (ticks / msBetweenFrames) % framesNum;
}

int anim_get_frame_dt(int currentDt, int msBetweenFrames, int framesNum)
{
	return (currentDt / msBetweenFrames) % framesNum;
}