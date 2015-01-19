#include "features.h"
#include "frames.h"
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

void init_pills(CollectPills_t *collectPills)
{
	int i;
	for (i=0; i<PILLS_NUMBER; i++)
	{
		collectPills->Pills[i].exist = 0;
	}

	collectPills->existPills = PILLS_NUMBER;
	collectPills->totalPills = PILLS_NUMBER;
}

int pill_nopframes(Pill_t *pill)
{
	switch (pill->type)
	{
		case Small: return 1;
		case Large: return 3;
	}
}

Fruit_t fruit_nextlvl(int lvl)
{
	if (lvl < 1)
	{
		printf("invalid level: %d\n", lvl);
		exit(1);
	}

	switch (lvl)
	{
		case 1:           return Cherry;
		case 2:           return Strawberry;
		case 3:  case 4:  return Peach;
		case 5:  case 6:  return Apple;
		case 7:  case 8:  return Grapes;
		case 9:  case 10: return Galaxian;
		case 11: case 12: return Bell;
		default:          return Key;
	}
}

void reset_fruit(DispFruit_t *dispfruit)
{
	dispfruit->fruit = Cherry;
	dispfruit->mode = NotDisplaying;
	dispfruit->start = 0;
	dispfruit->show = 0;
	dispfruit->eaten = 0;
	dispfruit->timeEaten = 0;
	dispfruit->x = 13;
	dispfruit->y = 17;
}
