#include "features.h"
#include "frames.h"
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

void init_pills(CollectPills_t *collectPills)
{
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

