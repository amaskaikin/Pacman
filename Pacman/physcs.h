#ifndef _PHYSCS
#define _PHYSCS

#include "direction.h"

typedef struct
{
	int x;
	int y;
	int xOffset;
	int yOffset;
	Direction_t cur;    //current direction we are moving
	Direction_t next;   //direction to move once we reach the center of the next tile
	int velocity;
	int xOffsetInternal; //accurate offset used for internal calculation
	int yOffsetInternal; //accurate offset used for internal calculation
} Body_t;

//Results of a movement
typedef enum
{
	NewSquare,  //Object moved into a new square
	OverCenter, //Object has moved over the center of its current tile
	SameSquare  //Object has moved within square without moving over the center
} MovRes_t;

//Determines if the bodies face based on their square only
int faces(Body_t *body1, Body_t *body2);

int faces_obj(Body_t *body, int otherX, int otherY);

MovRes_t move_ghost(Body_t *body);

int move_pacman(Body_t *body, int canMoveCur, int canMoveNext);

//Returns 1 if the body is in the center of a tile
int on_center(Body_t *body);

//Returns 1 if the body is in the center of a tile on the vertical axis
int on_vert(Body_t *body);

//Returns 1 if the body is in the center of a tile on the horozontal axis
int on_horo(Body_t *body);

#endif