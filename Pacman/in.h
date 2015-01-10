#pragma once

#include "SDL.h"
#include "direction.h"

#define MAX_KEYS 323

//Call at the end of each round of keypresses. If this isn't called key_pressed() and key_released() will not work.
void keyevents_finished(void);

//Handles when a key is pressed down.
void handle_keydown(int keycode);

//Handles when a key is pressed up.
void handle_keyup(int keycode);

//Returns true if the current direction is currently pressed down.
//A direction can be bound to multiple keypressed, making this function input-method agnostic.
int dir_key_held(Direction_t direction);

//This function sets the input direction to the last direction that was pressed and is still currently pressed.
//If no direction is pressed, the input direction is not assigned to.
//If multiple directions were pressed at the same time-instance, this function prioritises Up, Left, Down, Right.
//It returns true to indicate a direction is currently pressed, and false if no direction is pressed.
int dir_pressed_now(Direction_t *direction);

//Tests if a particular key is pressed. Uses the SDLK keycode constants.
int key_held(int key);

//Tests if the key was pressed this frame.
int key_pressed(int key);

//Tests if the key was released this frame.
int key_released(int key);