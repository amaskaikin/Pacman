#pragma once

#include "border.h"
#include "characters.h"
#include "features.h"

//
// Board rendering
//

void draw_border(Border_t *border);

//
// Pacman renderering
//

void draw_pacman_static(Pacman_t *pacman);
void draw_pacman(Pacman_t *pacman);
void draw_pacman_lives(int numLives);

//
// Pill renderering
//

void draw_pill_small(Pill_t *p);
void draw_small_pills(CollectPills_t *cp);
void draw_large_pills(CollectPills_t *cp);

