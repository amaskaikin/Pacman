#ifndef _CHARACTERS
#define _CHARACTERS

#include "border.h"
#include "direction.h"
#include "physcs.h"

/*pacman has a location (x,y) on the board. This is the tile his center is, and it defines his actual tile
he also has x/y tile offset, which can be between (-8, 7)
this defines his exact position on each individual tile, and his position for purposes of collision*/


/*typedef for pacman when he is moving
if he moved against a wall and the player doesn't move, he is considered "stuck"
this is needed for animation purposes*/
typedef enum
{
	Stuck, 
	NoStuck
} MoveType_t;

//Define pacman with full information(FULL MTHFCK!!)
typedef struct
{
	Body_t body;
	int score;
	int missedFrames;
	int lives;
	Direction_t lastDirect;
	MoveType_t moveType;
} Pacman_t;

//Init pacman, at start game
void init_pacman(Pacman_t *pacman);

//Init pacman's location, at the start of each level
void init_pacmanlvl(Pacman_t *pacman);

//Initializes pacman's location to the starting point (as well as direction and other values).
void init_pacmanloc(Pacman_t *pacman);

//Returns pacman speed for given level
int pacman_speed_normal(int lvl);

//Returns pacman speed for given level in fright mode.
int pacman_speed_fear(int lvl);

typedef enum
{
	In,      
	Leaving, 
	Chase,      
	Scatter,    
	Frightened, 
	Eaten       
} GhostState_t;

//Define ghosts type
typedef enum
{
	Blinky,  // red ghost
	Inky,	 // cyan
	Pinky,	 // pink
	Clyde	 // orange
} GhostType_t;

//Ghost, yeah
typedef struct
{
	Body_t body;
	int targetX;
	int targetY;
	int eaten;
	Direction_t transDirect; //direction ghost should face for middle of current square to middle of next square
	Direction_t nextDirect;  ////direction ghost should face when reaching the center of the next square
	GhostType_t type;
	GhostState_t state;
} Ghost_t;

void init_ghosts(Ghost_t ghosts[4]);

void reset_ghosts(Ghost_t *ghost, GhostType_t type);

void get_ghost_logic(Ghost_t *targetGhost, GhostType_t type, Ghost_t *redGhost, Pacman_t *pacman);

void to_corral(Ghost_t *ghost);

//gets the next direction the ghost will travel in based on their target square
Direction_t next_direction(Ghost_t *ghost, Border_t *border);

void get_red_logic(Ghost_t *red, Pacman_t *pacman);
void get_blue_logic(Ghost_t *blue, Ghost_t *redGhost, Pacman_t *pacman);
void get_pink_logic(Ghost_t *pink, Pacman_t *pacman);
void get_orange_logic(Ghost_t *orange, Pacman_t *pacman);

int ghost_speed_normal(int lvl);
int ghost_speed_fear(int lvl);
int ghost_speed_tunnel(int lvl);

#endif