#pragma once

//28 across, 36 down, 16 pixels each square.
#define SCREEN_TITLE "Pacman"
#define SCREEN_WIDTH 448
#define SCREEN_HEIGHT 576

//Defines the main states the program can be in.
typedef enum
{
	Start,
	Game
} ProgramState_t;

