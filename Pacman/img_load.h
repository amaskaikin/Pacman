#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "direction.h"
#include "characters.h"

void load_imgs(void);
void set_imgs(void);

SDL_Surface* double_corner_img(DiagDirect_t direction);
SDL_Surface* single_corner_img(DiagDirect_t direction);

SDL_Surface* tleft_img(DiagDirect_t direction);
SDL_Surface* tright_img(DiagDirect_t direction);

SDL_Surface* middle_img(Direction_t direction);
SDL_Surface* hall_img(Direction_t direction);

SDL_Surface* corral_corner_img(DiagDirect_t direction);
SDL_Surface* corral_side_img(Direction_t direction);
SDL_Surface* corral_gate_img(void);

SDL_Surface* pacman_img(void);
SDL_Surface* pacman_life_img(void);