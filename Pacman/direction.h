#ifndef _DIRECTION
#define _DIRECTION

//Define four main directios
typedef enum
{
	Up,
	Down,
	Left,
	Right
} Direction_t;

//Defint for diagonal directions
typedef enum
{
	TopLeft,
	TopRight,
	BotLeft,
	BotRight
} DiagDirect_t;

//Returns opposite direction
Direction_t direct_opp(Direction_t dir);

//Copies -1, 0, 1 to the given x and y ints depending on what direction is given
void direct_xy(Direction_t dir, int *x, int *y);

/*Same behaviour as dir_xy() except this emulates the bug for ghosts where
AI based on up direction is both Up *and* Left.*/
void direct_xy_bug(Direction_t dir, int *x, int *y);

#endif