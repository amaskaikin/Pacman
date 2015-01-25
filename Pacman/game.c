#include "game.h"
#include "border.h"
#include "app_window.h"
#include "draw.h"
#include "main.h"
#include "in.h"
#include "characters.h"
#include "anim.h"
#include "physcs.h"

#define MULT_VALUE_LVL1 1000
#define MULT_VALUE_LVL5 715

static void process_player(Game_t *game);
static void process_pills(Game_t *game);
static void process_ghosts(Game_t *game);
static void process_fruit(Game_t *game);

static void gameplay(Game_t *game, unsigned dtlvl);
static void change_speed(Game_t *game);
static Face_t* check_pacghost_facing(Game_t *game);    
static GhostState_t check_ghosts_type(Ghost_t *g, GhostState_t state, int leave);
static void enter_state(Game_t *game, StateGame_t state);
static void to_frightmode(Game_t *game, Ghost_t *g, unsigned dtlarge);
static int resolve_telesquare(Body_t *body);  
static void time_mode(Ghost_t *g, TimeMode_t tmode, unsigned dtlvl, int leave, int mult, int lvl);
static int check_leave(Game_t *game, Ghost_t *g, int InkyCounter, int ClydeCounter);

static void gameplay(Game_t *game, unsigned dtlvl)
{
	int i, leave = 0;
	if (game->isfright) return;

	for (i = 0; i < 4; i++)
	{
		Ghost_t *g = &game->ghosts[i];
	
		if (game->level==1)
		{	
			leave = check_leave(game, g, game->InkyCounter, game->ClydeCounter);
			
			if (dtlvl > 0 && dtlvl <30*MULT_VALUE_LVL1) time_mode(g, Mode1, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			if (dtlvl > 30*MULT_VALUE_LVL1 && dtlvl <57*MULT_VALUE_LVL1) time_mode(g, Mode2, dtlvl, leave, MULT_VALUE_LVL1, game->level);				
			if (dtlvl > 57*MULT_VALUE_LVL1 && dtlvl <82*MULT_VALUE_LVL1) time_mode(g, Mode3, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			if (dtlvl > 82*MULT_VALUE_LVL1)	time_mode(g, Mode4, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			change_speed(game);
		}	

		if ((game->level > 1) && (game->level < 5))
		{
			leave = check_leave(game, g, game->InkyCounter, game->ClydeCounter);

			if (dtlvl > 0 && dtlvl <30*MULT_VALUE_LVL1) time_mode(g, Mode1, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			if (dtlvl > 30*MULT_VALUE_LVL1 && dtlvl <57*MULT_VALUE_LVL1) time_mode(g, Mode2, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			if (dtlvl > 57*MULT_VALUE_LVL1 && dtlvl <1033*MULT_VALUE_LVL1) time_mode(g, Mode3, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			if (dtlvl > 1035*MULT_VALUE_LVL1+1)	time_mode(g, Mode4, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			change_speed(game);
		}
		if (game->level >= 5)
		{
			if (dtlvl > 0 && dtlvl <30*MULT_VALUE_LVL5) time_mode(g, Mode1, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			if (dtlvl > 30*MULT_VALUE_LVL5 && dtlvl <57*MULT_VALUE_LVL5) time_mode(g, Mode2, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			if (dtlvl > 57*MULT_VALUE_LVL5 && dtlvl <1033*MULT_VALUE_LVL5) time_mode(g, Mode3, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			if (dtlvl > 1035*MULT_VALUE_LVL5+1)	time_mode(g, Mode4, dtlvl, leave, MULT_VALUE_LVL1, game->level);
			change_speed(game);
		}
	}
}

void g_tick(Game_t *game)
{
	int i, lives, allPillsEaten, collidedWithGhost;
	Face_t *face = &game->face;
	unsigned dt = ticks_game() - game->ticksNewMode;
	unsigned dtlvl = ticks_game() - game->lvltime;

	switch (game->stategame)
	{
		case GamePlay:
		{
			process_player(game);
			process_ghosts(game);

			process_fruit(game);
			process_pills(game, dt);

			if (game->isfright)
			{
				for (i = 0; i < 4; i++)	to_frightmode(game, &game->ghosts[i], dt);
			}

			break;
		}
	}

	allPillsEaten = game->collectPills.existPills == 0;
	face = check_pacghost_facing(game);
	lives = game->pacman.lives;

	switch (game->stategame)
	{
		case GameBegin:
			if (dt > 2200) enter_state(game, LevelBegin);
			
			break;
		case LevelBegin:
			
			if (dt > 1800) enter_state(game, GamePlay);
			
			break;
		case GamePlay:
			//printf("ticks:%d", dt);
			gameplay(game, dtlvl);

			if (allPillsEaten) enter_state(game, Win);
			else if (face->collided && !game->isfright) enter_state(game, Death);

			if (face->collided && game->isfright)
			{
				switch (face->type)
				{
					case Blinky: to_corral(&game->ghosts[0]);  break;
					case Inky:   to_corral(&game->ghosts[1]);  break;			
					case Pinky:  to_corral(&game->ghosts[2]);  break;
					case Clyde:  to_corral(&game->ghosts[3]);  break;
				}
				face->collided = 0;
			}

			break;
		case Win:
			if (dt > 4000) enter_state(game, LevelBegin);

			break;
		case Death:
			if (dt > 4000)
			{
				if (lives == 0) 
					enter_state(game, Gameover);
				else enter_state(game, LevelBegin);
			}

			break;
	}
}

void g_render(Game_t *game)
{
	int i;
	unsigned dt = ticks_game() - game->ticksNewMode;
	draw_pacman_lives(game->pacman.lives);

	draw_small_pills(&game->collectPills);
	draw_fruit_indicators(game->level);
	switch (game->stategame)
	{
		int i;
		case GameBegin:
			draw_large_pills(&game->collectPills, 0);
			draw_border(&game->border);
			break;
		case LevelBegin:
			draw_pacman_static(&game->pacman);
			for (i = 0; i < 4; i++) draw_ghost(&game->ghosts[i]);

			draw_large_pills(&game->collectPills, 0);
			draw_border(&game->border);
			break;
		case GamePlay:
			draw_large_pills(&game->collectPills, 1);
			draw_border(&game->border);

			if (game->dispFruit1.mode == Displaying) draw_fruit_game(game->level);
			if (game->dispFruit2.mode == Displaying) draw_fruit_game(game->level);

			if (game->dispFruit1.eaten && ticks_game() - game->dispFruit1.timeEaten < 2000);
			if (game->dispFruit2.eaten && ticks_game() - game->dispFruit2.timeEaten < 2000);

			draw_pacman(&game->pacman);

			for (i = 0; i < 4; i++) 
				{
					switch(game->ghosts[i].state)
					{
					case Frightened:
						{
							draw_scared_ghost(&game->ghosts[i]);
						} break;

					default: draw_ghost(&game->ghosts[i]);
					}
				}
			break;
		case Win:
			draw_pacman_static(&game->pacman);

			if (dt < 2000)
			{
				int i;
				for (i = 0; i < 4; i++) draw_ghost(&game->ghosts[i]);
				draw_border(&game->border);
			}
			else
			{
				draw_border_flash(&game->border);
			}

			break;
		case Death:
			//draw everything the same for 1ist second
			if (dt < 1000)
			{
				int i;
				draw_pacman_static(&game->pacman);

				for (i = 0; i < 4; i++) draw_ghost(&game->ghosts[i]);
			}
			else
			{
				//draw the death animation
				draw_pacman_death(&game->pacman, dt - 1000);
			}

			draw_large_pills(&game->collectPills, 1);
			draw_border(&game->border);
			break;
		case Gameover:
			draw_border(&game->border);
			break;
	}
}

void init_game(Game_t *game)
{
	init_pacman(&game->pacman);
	init_pills(&game->collectPills);
	game->level = 1;
	init_ghosts(game->ghosts);
	enter_state(game, GameBegin);
}

void new_level(Game_t *game)
{
	//reset pacmans position
	init_pacmanlvl(&game->pacman);	

	//reset pills
	init_pills(&game->collectPills);

	//reset ghosts
	init_ghosts(game->ghosts);

	//reset fruit
	reset_fruit(&game->dispFruit1);
	reset_fruit(&game->dispFruit2);
}

void death(Game_t *game)
{
	init_pacmanlvl(&game->pacman);
	init_ghosts(game->ghosts);

	reset_fruit(&game->dispFruit1);
	reset_fruit(&game->dispFruit2);
}

int game_over(Game_t *game)
{
	unsigned dt = ticks_game() - game->ticksNewMode;

	return dt > 2000 && game->stategame == Gameover;
}

static void enter_state(Game_t *game, StateGame_t state)
{
	//process leaving a state
	switch (game->stategame)
	{
		case GameBegin:	
			break;
		case Win:
			game->level++;
			game->stategame = LevelBegin;
			
			new_level(game);
			break;
		case Death:
			// Player died and is starting a new game, subtract a life
			if (state == LevelBegin)
			{
				game->pacman.lives--;
				death(game);
			}
		default: ; //do nothing
	}

	switch (state)
	{
		case GameBegin:
			break;
		case LevelBegin:
			break;
		case GamePlay:
			break;
		case Win:

			break;
		case Death:
			break;
		case Gameover:
			break;
	}

	game->ticksNewMode = ticks_game();
	game->stategame = state;
}


static void process_player(Game_t *game)
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

static void process_pills(Game_t *game, unsigned dtlarge)
{
	CollectPills_t *collect;
	int i;

	collect = &game->collectPills;

	for (i = 0; i < collect->totalPills; i++)
	{
		Pill_t *p = &collect->Pills[i];

		//skip if we've eaten this one already
		if (p->exist) continue;

		if (faces_obj(&game->pacman.body, p->x, p->y))
		{
			collect->existPills--;

			p->exist = 1;

			//eating a small pill makes pacman not move for 1 frame
			//eating a large pill makes pacman not move for 3 frames
			game->pacman.missedFrames = pill_nopframes(p);

			if (p->type == Large)
			{
				game->frighttime = dtlarge;
				game->isfright = 1;
			}

			return;
		}
	}
}

static void process_ghosts(Game_t *game)
{
	int i;
	MovRes_t result;
	for (i = 0; i < 4; i++)
	{
		if (game->ghosts[i].state == In)
		{
			int moved = move_ghost(&game->ghosts[i].body);

			if (game->ghosts[i].body.y == 13 || game->ghosts[i].body.y == 15)
			{
				game->ghosts[i].body.cur = direct_opp(game->ghosts[i].body.next);
				game->ghosts[i].body.next = game->ghosts[i].body.cur;				
			}

			continue;
		}

		if (game->ghosts[i].state == Leaving)
		{
			Direction_t up = Up, left = Left, right = Right;
			int flPinky = 0;
			int moved = move_ghost(&game->ghosts[i].body);
			switch (game->ghosts[i].type)
			{
				if (game->isfright) break;
				case Blinky: break;
				case Pinky: { game->ghosts[i].state = Scatter; flPinky = 1;} break;
				case Inky:	{ game->ghosts[i].body.next = left; } break;
				case Clyde:	{ game->ghosts[i].body.next = right;  } break;				
			}
			if (game->ghosts[i].body.x == 14)
			{
				game->ghosts[i].body.next = up;
				move_ghost(&game->ghosts[i].body);
				if (game->ghosts[i].body.y == 11 && !flPinky && !game->isfright) game->ghosts[i].state = Chase;
			}
			
			continue;
		}

		result = move_ghost(&game->ghosts[i].body);
		resolve_telesquare(&game->ghosts[i].body);

		if (result == NewSquare)
		{
			//if they are in a new tile, rerun their target update logic
			get_ghost_logic(&game->ghosts[i], game->ghosts[i].type, &game->ghosts[0], &game->pacman);

			game->ghosts[i].nextDirect = next_direction(&game->ghosts[i], &game->border);
		}
		else if (result == OverCenter)
		{
			//they've hit the center of a tile, so change their current direction to the new direction
			game->ghosts[i].body.cur = game->ghosts[i].transDirect;
			game->ghosts[i].body.next = game->ghosts[i].nextDirect;
			game->ghosts[i].transDirect = game->ghosts[i].nextDirect;
		}

		
	}
}

static void process_fruit(Game_t *game)
{
	DispFruit_t *f1, *f2;
	int curLvl, pillsEaten;
	unsigned int f1dt, f2dt;
	Pacman_t *pac;

	pillsEaten = game->collectPills.totalPills - game->collectPills.existPills;

	f1 = &game->dispFruit1;
	f2 = &game->dispFruit2;
	curLvl = game->level;

	if (pillsEaten >= 70 && f1->mode == NotDisplaying)
	{
		f1->mode = Displaying;
		show_fruit(f1, curLvl);
	}
	else if (pillsEaten == 170 && f2->mode == NotDisplaying)
	{
		f2->mode = Displaying;
		show_fruit(f2, curLvl);
	}

	f1dt = ticks_game() - f1->start;
	f2dt = ticks_game() - f2->start;

	pac = &game->pacman;

	if (f1->mode == Displaying)
	{
		if (f1dt > f1->show) f1->mode = Displayed;
	}

	if (f2->mode == Displaying)
	{
		if (f2dt > f2->show) f2->mode = Displayed;
	}

	//check for collisions

	if (f1->mode == Displaying && faces_obj(&pac->body, f1->x, f1->y))
	{
		f1->mode = Displayed;
		f1->eaten = 1;
		f1->timeEaten = ticks_game();
	}

	if (f2->mode == Displaying && faces_obj(&pac->body, f2->x, f2->y))
	{
		f2->mode = Displayed;
		f2->eaten = 1;
		f2->timeEaten = ticks_game();
	}
}

static Face_t *check_pacghost_facing(Game_t *game)
{
	int i;
	Face_t *face =  &game->face;
	for (i = 0; i < 4; i++)
	{
		Ghost_t *g = &game->ghosts[i];
		face->type = g->type;
		if (faces(&game->pacman.body, &g->body))
		{			
			face->collided = 1;
			return face;
		}
	}
	face->collided = 0;
	return face;
}


static int resolve_telesquare(Body_t *body)
{
	if (body->y != 14) return 0;

	if (body->x == -1) { body->x = 27; return 1; }
	if (body->x == 28) { body->x =  0; return 1; }

	return 0;
}

static void time_mode(Ghost_t *g, TimeMode_t tmode, unsigned dtlvl, int leave, int mult, int lvl)
{
	switch (tmode)
	{
	case Mode1:
		{
			if (dtlvl > 0 && dtlvl <10*mult)	    g->state = check_ghosts_type(g, Scatter, leave);
			if (dtlvl > 10*mult && dtlvl <30*mult)	g->state = check_ghosts_type(g, Chase, leave);
		} break;
	case Mode2:
		{
			if (dtlvl > 30*mult && dtlvl <37*mult)	g->state = check_ghosts_type(g, Scatter, leave);
			if (dtlvl > 37*mult && dtlvl <57*mult)  g->state = check_ghosts_type(g, Chase, leave);
		} break;
	case Mode3:
		{
			if (dtlvl > 57*mult && dtlvl <62*mult)  g->state = check_ghosts_type(g, Scatter, leave);
			if (dtlvl > 62*mult && dtlvl <82*mult && (lvl == 1))  g->state = check_ghosts_type(g, Chase, leave);
			else if (dtlvl > 62*mult && dtlvl <1035*mult) g->state = check_ghosts_type(g, Chase, leave);
		} break;
	case Mode4:
		{
			if (lvl ==1)
			{
				if (dtlvl > 82*mult && dtlvl <87*mult)	g->state = check_ghosts_type(g, Scatter, leave);
				if (dtlvl > 87*mult) g->state = check_ghosts_type(g, Chase, leave);
			}
			else 
			{
				if (dtlvl > 1035*mult && dtlvl <1035*mult+1)	g->state = check_ghosts_type(g, Scatter, leave);
				if (dtlvl > 1035*mult+1) g->state = check_ghosts_type(g, Chase, leave);
			}
		} break;
	}
}

static GhostState_t check_ghosts_type(Ghost_t *g, GhostState_t state, int leave)
{
	GhostState_t gstate = state;
	if (g->type != Blinky && g->type !=Pinky) 
			if (leave) 
				{
					gstate = state; 
				} else gstate = g->state;	
	return gstate;
}

static void change_speed(Game_t *game)
{
	int i;
	for (i=0; i<4;i++)
	{
		if (game->ghosts[i].state == In) game->ghosts[i].body.velocity = ghost_speed_tunnel(game->level);
		else if (game->ghosts[i].state == Frightened) 
			{
				game->pacman.body.velocity = pacman_speed_fear(game->level);
				game->ghosts[i].body.velocity = ghost_speed_fear(game->level);
			}
		else 
			{
				game->pacman.body.velocity = pacman_speed_normal(game->level);
				game->ghosts[i].body.velocity = ghost_speed_normal(game->level);
			}
	}
}

static int check_leave(Game_t *game, Ghost_t *g, int InkyCounter, int ClydeCounter)
{
	switch (g->type)
	{
	case Inky:
		{
			if (InkyCounter == 1) return 1;
			if (((game->collectPills.totalPills - game->collectPills.existPills) >= 30) && !InkyCounter)
			{
				g->state = Leaving; game->InkyCounter = 1 ; return 1;
			}
			break;
		}
	case Clyde: 
		{
			if (ClydeCounter == 1) return 1;
			if (((game->collectPills.totalPills - game->collectPills.existPills) >= 90) && !ClydeCounter) 
			{
				g->state = Leaving; game->ClydeCounter = 1; return 1;
			}
			break;
		}
	}
	return 0;	
}

static void to_frightmode(Game_t *game, Ghost_t *g, unsigned dtlarge)
{
	int i, leave = 0;
	leave = check_leave(game, g, game->InkyCounter, game->ClydeCounter);
	if ((dtlarge - game->frighttime) < MULT_VALUE_LVL1 * 5)
	{
		g->state = check_ghosts_type(g, Frightened, leave);
	}
	else game->isfright = 0;
	change_speed(game);
	
	printf("Ghost: %d , State: %d \n", g->type, g->state);
}