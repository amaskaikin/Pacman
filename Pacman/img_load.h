#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "direction.h"
#include "characters.h"
#include "features.h"

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
SDL_Surface* pacman_ani_img(Direction_t dir, int frame);
SDL_Surface* pacman_death_img(int i);

SDL_Surface* small_pill_img(void);
SDL_Surface* large_pill_img(void);

SDL_Surface* get_fruit_img(Fruit_t fruit);

SDL_Surface* ghost_img(GhostType_t type, Direction_t dir, int frame);