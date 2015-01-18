#include "game.h"
#include "border.h"
#include "app_window.h"
#include "draw.h"
#include "main.h"
#include "in.h"
#include "characters.h"
#include "anim.h"

void g_tick(Game_t *game)
{
	int i, lives;
	unsigned dt = ticks_game();
	//printf("dt: %d\n", dt);
	process_player(game);

	lives = game->pacman.lives;

}

void g_render(Game_t *game)
{
	unsigned dt = ticks_game();
	draw_border(&game->border);
	draw_small_pills(&game->collectPills);
	draw_large_pills(&game->collectPills);
	//draw_pacman_static(&game->pacman);	

	draw_pacman_lives(game->pacman.lives);
	draw_pacman(&game->pacman);
	
}

void init_game(Game_t *game)
{
	init_pacman(&game->pacman);
	init_pills(&game->collectPills);
	game->level = 1;
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
		pacman->lastDirect = newDir;
		
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
		//pacman is stuck, don't do anything
		return;
	}
	else
	{
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

	//if pacman is currently on a center tile and can't move in either direction, don't move him
	if (on_center(&pacman->body) && !canMoveCur && !canMoveNext)
	{
		pacman->moveType = Stuck;
		pacman->lastDirect = oldlastDirect;

		return;
	}

	move_pacman(&pacman->body, canMoveCur, canMoveNext);

	//if pacman is on the center, and he couldn't move either of  his last directions, he must be stuck now
	if (on_center(&pacman->body) && !canMoveCur && !canMoveNext)
	{
		pacman->moveType = Stuck;
		return;
	}

	resolve_telesquare(&pacman->body);
}

static int resolve_telesquare(Body_t *body)
{
	if (body->y != 14) return 0;

	if (body->x == -1) { body->x = 27; return 1; }
	if (body->x == 28) { body->x =  0; return 1; }

	return 0;
}
