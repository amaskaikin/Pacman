#include "direction.h"

void direct_xy(Direction_t dir, int *x, int *y)
{
	switch (dir)
	{
		case Up:    { *x =  0; *y = -1; break; }
		case Down:  { *x =  0; *y =  1; break; }
		case Left:  { *x = -1; *y =  0; break; }
		case Right: { *x =  1; *y =  0; break; }
	}
}

void direct_xy_bug(Direction_t dir, int *x, int *y)
{
	switch (dir)
	{
		case Up:    { *x = -1; *y = -1; break; }
		case Down:  { *x =  0; *y =  1; break; }
		case Left:  { *x = -1; *y =  0; break; }
		case Right: { *x =  1; *y =  0; break; }
	}
}

Direction_t direct_opp(Direction_t dir)
{
	if      (dir == Left)  { return Right; }
	else if (dir == Right) { return Left;  }
	else if (dir == Up)    { return Down;  }
	else                   { return Up;    }
}
