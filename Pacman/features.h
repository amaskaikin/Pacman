#ifndef _FEATURES
#define _FEATURES

#include "SDL.h"

#define PILLS_NUMBER 244

//Define pills type
typedef enum
{
	Small,
	Large	
} PillType_t;

//Define a pill with type, location etc.
typedef struct
{
	PillType_t type;
	int x;
	int y;
	int exist;
	SDL_Surface *img;
} Pill_t;

//All pills (counts existing pills0)
typedef struct
{
	int totalPills;
	int existPills;
	Pill_t Pills[PILLS_NUMBER];
} CollectPills_t;

//Init pills, reset all counters
void init_pills(CollectPills_t *collectPills);

//Return the number of movement frames this pill makes pacman miss when eaten
int pill_nopframes(Pill_t *pill);

//Define fruits type
typedef enum
{
	Cherry,
	Strawberry,
	Peach,
	Apple,
	Grapes,
	Galaxian,
	Bell,
	Key
} Fruit_t;

/*Fruit's conditions:
Not-displayed (not enough pills yet);
Displaying;
Displayed (timed-out or pacman ate the fruit);*/
typedef enum
{
	NotDisplaying,
	Displaying,
	Displayed
} FruitMode_t;

//Define fruit for pacman
typedef struct
{
	Fruit_t fruit;
	FruitMode_t mode;
	unsigned int start;		 // the time we started displaying this fruit at (in SDL_Ticks())
	unsigned int show;		 // the random time between 9000-10000 ms this fruit displays for
	int x;
	int y;
	int eaten;
	unsigned int timeEaten;
} DispFruit_t;

//Fruit in next lvl
Fruit_t fruit_nextlvl(int lvl);

void reset_fruit(DispFruit_t *dispfruit);

void show_fruit(DispFruit_t *dispFruit, int lvl);

int rand_time(void);

#endif