#ifndef _DRAW
#define _DRAW

#include "border.h"
#include "characters.h"
#include "features.h"

//
// Board rendering
//

void draw_border(Border_t *border);
void draw_border_flash(Border_t *border);

//
// Pacman renderering
//

void draw_pacman_static(Pacman_t *pacman);
void draw_pacman(Pacman_t *pacman);
void draw_pacman_lives(int numLives);
void draw_pacman_death(Pacman_t *pacman, unsigned int timeSinceDeath);

//
// Ghost rendering
//

void draw_ghost(Ghost_t *ghost);
void draw_scared_ghost(Ghost_t *ghost);

//
// Pill renderering
//

void draw_pill_small(Pill_t *p);
void draw_small_pills(CollectPills_t *cp);
void draw_large_pills(CollectPills_t *cp, int flashing);

//
// Fruit renderering
//

void draw_fruit_indicators(int currentLevel);
void draw_fruit_game(int currentLevel);

#endif

