#include "game.h"
#include "border.h"
#include "app_window.h"
#include "draw.h"
#include "main.h"
#include "in.h"
#include "characters.h"

void g_render(Game_t *game)
{
	draw_border(&game->border);
	draw_pacman_static(&game->pacman);
}

void init_game(Game_t *game)
{
	init_pacman(&game->pacman);
	game->level = 1;

}

//checks if it's valid that pacman could move in this direction at this point in time
int can_move(Pacman_t *pacman, Border_t *border, Direction_t dir)
{
	int x, y, newX, newY;
	//easy edge cases, tile has to be parallal with a direction to move it
	if ((dir == Up   || dir == Down ) && !on_vert(&pacman->body)) return 0;
	if ((dir == Left || dir == Right) && !on_horo(&pacman->body)) return 0;

	//if pacman wants to move on an axis and he is already partially on that axis (not 0)
	//it is always a valid move
	if ((dir == Left || dir == Right) && !on_vert(&pacman->body)) return 1;
	if ((dir == Up   || dir == Down ) && !on_horo(&pacman->body)) return 1;

	//pacman is at 0/0 and moving in the requested direction depends on if there is a valid tile there
	x = 0;
	y = 0;

	direct_xy(dir, &x, &y);

	newX = pacman->body.x + x;
	newY = pacman->body.y + y;

	return isvalid_sq(border, newX, newY) || isteleport_sq(newX, newY);
}

void process_player(Game_t *game)
{
	Direction_t newDir, oldlastDirect;
	int newCurX, newCurY, newNextX, newNextY, canMoveCur, canMoveNext;
	int curDirX = 0;
	int curDirY = 0;
	int nextDirX = 0;
	int nextDirY = 0;
	int dirPressed = dir_pressed_now(&newDir);
	Pacman_t *pacman = &game->pacman;
	Border_t *border = &game->border;

	if (pacman->missedFrames != 0)
	{
		pacman->missedFrames--;
		return;
	}

	oldlastDirect = pacman->lastDirect;

	if (dirPressed)
	{
		//user wants to move in a direction
		pacman->lastDirect = newDir;

		//if player holds opposite direction to current walking dir
		//we can always just switch current walking direction
		//since we're on parallel line
		if (newDir == direct_opp(pacman->body.cur))
		{
			pacman->body.cur = newDir;
			pacman->body.next = newDir;
		}

		//if pacman was stuck before just set his current direction as pressed
		if (pacman->moveType == Stuck)
		{
			pacman->body.cur = newDir;
		}

		pacman->body.next = newDir;
	}
	else if (pacman->moveType == Stuck)
	{
		//pacman is stuck and player didn't move - player should still be stuck.
		//don't do anything
		return;
	}
	else
	{
		//user doesn't want to change direction and pacman isn't stuck
		//pacman can move like normal

		//just set the next dir to current dir
		pacman->body.next = pacman->body.cur;
	}

	pacman->moveType = NoStuck;
	
	direct_xy(pacman->body.cur, &curDirX, &curDirY);
	direct_xy(pacman->body.next, &nextDirX, &nextDirY);

	newCurX = pacman->body.x + curDirX;
	newCurY = pacman->body.y + curDirY;
	newNextX = pacman->body.x + nextDirX;
	newNextY = pacman->body.y + nextDirY;

	canMoveCur =  isvalid_sq(border, newCurX, newCurY) || isteleport_sq(newCurX, newCurY);
	canMoveNext = isvalid_sq(border, newNextX, newNextY) || isteleport_sq(newNextX, newNextY);

	//if pacman is currently on a center tile and can't move in either direction
	//don't move him
	if (on_center(&pacman->body) && !canMoveCur && !canMoveNext)
	{
		pacman->moveType = Stuck;
		pacman->lastDirect = oldlastDirect;

		return;
	}

	move_pacman(&pacman->body, canMoveCur, canMoveNext);

	//if pacman is on the center, and he couldn't move either of  his last directions
	//he must be stuck now
	if (on_center(&pacman->body) && !canMoveCur && !canMoveNext)
	{
		pacman->moveType = Stuck;
		return;
	}

	resolve_telesquare(&pacman->body);
}

static int resolve_telesquare(Body_t *body)
{
	//TODO: chuck this back in the board class somehow

	if (body->y != 14) return 0;

	if (body->x == -1) { body->x = 27; return 1; }
	if (body->x == 28) { body->x =  0; return 1; }

	return 0;
}
