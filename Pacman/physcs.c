#include "physcs.h"
#include <stdlib.h>

int faces_obj(Body_t *body, int otherX, int otherY)
{
	return body->x == otherX && body->y == otherY;
}

int move_pacman(Body_t *body, int canMoveCur, int canMoveNext)
{
	int divide, remain, offX, offY, xNow, yNow, overCenter, overOffset;
	//default movement to not changing position
	MovRes_t result = SameSquare;

	int xBefore = body->xOffset;
	int yBefore = body->yOffset;

	int xDir = 0;
	int yDir = 0;
	//check if we've gone onto a new square
	//int low = -8;
	//int high = 7;
	int low = -8;
	int high = 7;
	int offset = 15;
	
	//we have double pixels so multiply by 2
	int BASE_VALUE = 75 * 2;
	int MULT_VALUE = 60;

	//our pixel value for the velocity
	//range between 1800 for v==40, to 4725 for v==105
	int velPixValue = (body->velocity / 100.0f) * BASE_VALUE;
	direct_xy(body->cur, &xDir, &yDir);

	divide = velPixValue / MULT_VALUE;
	remain = velPixValue % MULT_VALUE;

	//add any new speed to current pixel position (only useful for velocity >= 80)
	body->xOffset += divide * xDir;
	body->yOffset += divide * yDir;

	//add any new carry to current carry (always useful except for velocity == 80)
	body->xOffsetInternal += remain * xDir;
	body->yOffsetInternal += remain * yDir;

	//add any new pixels we've introduced with our carry
	//this value will be non-zero if we have introduced enough carry
	offX = body->xOffsetInternal / MULT_VALUE;
	offY = body->yOffsetInternal / MULT_VALUE;

	//add to our pixel offset any new carry pixels
	body->xOffset += offX;
	body->yOffset += offY;

	//and subtract that carrys pixel from our offsetinternal
	body->xOffsetInternal -= offX * MULT_VALUE;
	body->yOffsetInternal -= offY * MULT_VALUE;

	// we should now have resolved all the values we need to

	xNow = body->xOffset;
	yNow = body->yOffset;
	//Now handle if we've moved over center, or into a new square

	overCenter = 0;
	overOffset = 0;

	//move over center square
	if ((xBefore < 0 && xNow >= 0) || (xBefore > 0 && xNow <= 0))
	{
		overCenter = 1;

		result = OverCenter;

		//transitioned over
		overOffset = abs(body->xOffset) * MULT_VALUE + abs(body->xOffsetInternal);
	}
	else if ((yBefore < 0 && yNow >= 0) || (yBefore > 0 && yNow <= 0))
	{
		overCenter = 1;

		result = OverCenter;

		//transitioned over
		overOffset = abs(body->xOffset) * MULT_VALUE + abs(body->xOffsetInternal);
	}

	if (overCenter)
	{
		Direction_t newDir;

		if (canMoveNext)
		{
			newDir = body->next;
		}
		else if (canMoveCur)
		{
			newDir = body->cur;
		}
		else
		{
			//they are stuck, so set everything to 0 then return
			body->xOffset = 0;
			body->yOffset = 0;

			body->xOffsetInternal = 0;
			body->yOffsetInternal = 0;

			return result;
		}

		body->cur = newDir;

		direct_xy(newDir, &xDir, &yDir);

		body->xOffset = overOffset / MULT_VALUE * xDir;
		body->yOffset = overOffset / MULT_VALUE * yDir;

		body->xOffsetInternal = (overOffset % MULT_VALUE) * xDir;
		body->yOffsetInternal = (overOffset % MULT_VALUE) * yDir;

		return result;
	}

	if (body->xOffset < low)
	{
		body->xOffset += offset;
		body->x--;

		result = NewSquare;
	}
	else if (body->xOffset > high)
	{
		body->xOffset -= offset;
		body->x++;

		result = NewSquare;
	}
	else if (body->yOffset < low)
	{
		body->yOffset += offset;
		body->y--;

		result = NewSquare;
	}
	else if (body->yOffset > high)
	{
		body->yOffset -= offset;
		body->y++;

		result = NewSquare;
	}

	return result;
}

// Note on center/ horo/ vert functions:
// This pacman game uses 2 pixels for every pixel in the original game.
// This means being in the "center" of a specific axis actually means either of 2 pixel locations
// These functions deal with that

int on_center(Body_t *body)
{
	return on_horo(body) && on_vert(body);
}

int on_horo(Body_t *body)
{
	return body->yOffset == 0;// || body->yOffset == 1;
}

int on_vert(Body_t *body)
{
	return body->xOffset == 0;// || body->xOffset == 1;
}
