#include "characters.h"

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

void init_pacman(Pacman_t *pacman)
{
	init_pacmanloc(pacman);
	pacman->score = 0;
	pacman->lives = 3;
	pacman->missedFrames = 0;
}

void init_pacmanlvl(Pacman_t *pacman)
{
	init_pacmanloc(pacman);
}

void init_pacmanloc(Pacman_t *pacman)
{
	pacman->body.x = 14;
	pacman->body.y = 23;
	pacman->body.xOffset = -8;
	pacman->body.yOffset = 0;
	pacman->body.cur = Left;
	pacman->body.next = Left;
	pacman->body.xOffsetInternal = 0;
	pacman->body.yOffsetInternal = 0;

	pacman->body.velocity = 80;
	pacman->moveType = NoStuck;
	pacman->lastDirect = Left;
}

int pacman_speed_normal(int lvl)
{
	if (lvl == 1)  return 80;
	if (lvl <= 4)  return 90;
	if (lvl <= 20) return 100;
	return 90;
}