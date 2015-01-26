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

int pacman_speed_fear(int lvl)
{
	if (lvl == 1)  return 90;
	if (lvl <= 4)  return 95;
	if (lvl <= 20) return 100;
	return 100;
}

void init_ghosts(Ghost_t ghosts[4])
{
	int i;
	ghosts[0].type = Blinky;
	ghosts[1].type = Inky;
	ghosts[2].type = Pinky;
	ghosts[3].type = Clyde;

	for (i = 0; i < 4; i++)
	{
		reset_ghosts(&ghosts[i], ghosts[i].type);
	}
}

void reset_ghosts(Ghost_t *ghost, GhostType_t type)
{
	int x, y;
	int ox, oy;
	Direction_t dir;
	Direction_t next;
	GhostState_t state;

	switch (type)
	{
		case Blinky: { x = 14; y = 11; ox = -8; oy =  0; state = Scatter; dir = Left; next = Left; break; }
		case Inky: { x = 16; y = 14; ox = -8; oy =  0; state = In; dir = Up;   next = Down; break; }
		case Clyde: { x = 12; y = 14; ox = -8; oy =  0; state = In; dir = Up;   next = Down; break; }
		case Pinky: { x = 14; y = 14; ox = -8; oy =  0; state = Leaving; dir = Down; next = Up; break; }
	}

	ghost->body.x = x;
	ghost->body.y = y;
	ghost->body.xOffset = ox;
	ghost->body.yOffset = oy;
	ghost->body.cur = dir;
	ghost->body.next = next;
	ghost->body.xOffsetInternal = 0;
	ghost->body.yOffsetInternal = 0;

	ghost->state = state;
	ghost->transDirect = Left;
	ghost->nextDirect = Left;

	ghost->eaten = 0;
}

void to_corral(Ghost_t *ghost)
{
	int x, y;
	int ox, oy;

	switch (ghost->type)
	{
		case Blinky: { x = 14; y = 14; ox = -8; oy =  0;  break; }
		case Inky: { x = 14; y = 14; ox = -8; oy =  0;  break; }
		case Clyde: { x = 14; y = 14; ox = -8; oy =  0;  break; }
		case Pinky: { x = 14; y = 14; ox = -8; oy =  0;  break; }		
	}
	ghost->state = Leaving;
	ghost->body.x = x;
	ghost->body.y = y;
	ghost->body.xOffsetInternal = 0;
	ghost->body.yOffsetInternal = 0;

}

void go_home(Ghost_t *ghost, GhostType_t type)
{
	int targetX;
	int targetY;

	switch (type)
	{
		case Blinky: { targetX = 25; targetY =  -2; break; }
		case Inky:   { targetX = 27; targetY =  31; break; }
		case Clyde:  { targetX =  0; targetY =  31; break; }
		case Pinky:  { targetX =  2; targetY =  -2; break; }
		default:
			printf("error ghost\naborting\n");
			exit(1);
	}

	ghost->targetX = targetX;
	ghost->targetY = targetY;
}

typedef struct
{
	Direction_t dir;
	int distance;
} Targetcalc_t;

typedef struct
{
	int x;
	int y;
} Borderoffset_t;

Direction_t next_direction(Ghost_t *ghost, Border_t *border)
{
	/*ghost has just entered a new tile
	we look ahead to their next tile
	we get the distance from each of those to the ghosts target tile
	we then select the one with the smallest distance
	if there is a tie, we break it in order Up, Left, Down, Right*/
	int x, y, i, dx, dy;
	Direction_t reverse;
	Targetcalc_t shortest;
	Targetcalc_t targets[4] =  { {Up, INT_MAX}, {Left, INT_MAX}, {Down, INT_MAX}, {Right, INT_MAX}};
	Borderoffset_t offsets[4] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

	direct_xy(ghost->nextDirect, &x, &y);

	//calculate the distances between the squares (or if it is even valid)
	for (i = 0; i < 4; i++)
	{
		int testX = ghost->body.x + x + offsets[i].x;
		int testY = ghost->body.y + y + offsets[i].y;

		//allow for when ghost is going through teleporter
		if (testX == 0) testX = 26;
		if (testX == 27) testX = 1;

		//make sure the square is a valid walkable square
		if (!(isvalid_sq(border, testX, testY) || isteleport_sq(testX, testY))) continue;

		//a further condition is that ghosts cannot enter certain squares moving upwards
		if (targets[i].dir == Up && isghostnoup_squ(testX, testY)) continue;

		dx = testX - ghost->targetX;
		dy = testY - ghost->targetY;

		//really the square root, but don't take to keep precision
		targets[i].distance = (dx * dx + dy * dy);
	}

	//a ghost can never turn around, so exclude the opposite direction to what they are facing
	reverse = direct_opp(ghost->nextDirect);
	shortest.dir = Right;
	shortest.distance = INT_MAX;

	//iterate backwards so that we get the tie-breaking logic for free
	for (i = 3; i >= 0; i--)
	{
		if (targets[i].dir == reverse) continue;

		if (targets[i].distance <= shortest.distance)
		{
			shortest.distance = targets[i].distance;
			shortest.dir = targets[i].dir;
		}
	}

	return shortest.dir;
}

void get_ghost_logic(Ghost_t *targetGhost, GhostType_t type, Ghost_t *redGhost, Pacman_t *pacman)
{
	if (targetGhost->state == Scatter)
	{
		go_home(targetGhost, type);
		return;
	}

	switch (type)
	{
		case Blinky: get_red_logic(targetGhost, pacman);            break;
		case Inky:   get_blue_logic(targetGhost, redGhost, pacman);	break;
		case Clyde:  get_orange_logic(targetGhost, pacman);         break;
		case Pinky:  get_pink_logic(targetGhost, pacman);           break;
	}
}

void get_red_logic(Ghost_t *redGhost, Pacman_t *pacman)
{
	// Red's AI is to set his target position to pacmans
	redGhost->targetX = pacman->body.x;
	redGhost->targetY = pacman->body.y;
}

void get_orange_logic(Ghost_t *orangeGhost, Pacman_t *pacman)
{
	// Orange's logic is in two parts:
	// If Pacmans distance is 8 or more squares away, his target is pacman
	// If Pacman is less than 8 squares, his target is his home
	int dx, dy, distance;
	dx = orangeGhost->body.x - pacman->body.x;
	dy = orangeGhost->body.y - pacman->body.y;

	//really the square root, but can compare with square of other number
	distance = dx * dx + dy * dy;

	if (distance >= (8 * 8))
	{
		get_red_logic(orangeGhost, pacman);
	}
}

void get_blue_logic(Ghost_t *blueGhost, Ghost_t *redGhost, Pacman_t *pacman)
{
	int tx, ty, rx, ry, targetX, targetY;
	int offsetX = 0;
	int offsetY = 0;

	//use dir_xy_buggy to get 2 up AND 2 left, as per bug in original game
	direct_xy_bug(pacman->body.cur, &offsetX, &offsetY);

	offsetX *= 2;
	offsetY *= 2;

	tx = pacman->body.x + offsetX;
	ty = pacman->body.y + offsetY;

	rx = redGhost->body.x;
	ry = redGhost->body.y;

	targetX = 2 * tx - rx;
	targetY = 2 * ty - ry;

	blueGhost->targetX = targetX;
	blueGhost->targetY = targetY;
}

void get_pink_logic(Ghost_t *pinkGhost, Pacman_t *pacman)
{
	// Pinks's AI is to set his target position to pacmans, plus a few more in the distance
	int targetOffsetX = 0;
	int targetOffsetY = 0;

	//use dir_xy_buggy to get 4 up AND 4 left, as per bug in original game
	direct_xy_bug(pacman->body.cur, &targetOffsetX, &targetOffsetY);

	targetOffsetX *= 4;
	targetOffsetY *= 4;

	pinkGhost->targetX = pacman->body.x + targetOffsetX;
	pinkGhost->targetY = pacman->body.y + targetOffsetY;
}


int ghost_speed_normal(int lvl)
{
	if (lvl == 1)  return 75;
	if (lvl <= 4)  return 85;
	if (lvl <= 20) return 95;
	return 95;
}
int ghost_speed_fear(int lvl)
{
	if (lvl == 1)  return 50;
	if (lvl <= 4)  return 55;
	if (lvl <= 20) return 60;
	return 100; //ghosts don't get into frightened mode past this
}
int ghost_speed_tunnel(int lvl)
{
	if (lvl == 1)  return 40;
	if (lvl <= 4)  return 45;
	if (lvl <= 20) return 50;
	return 50;
}