#include "SDL.h"
#include "SDL_image.h"
#include "SDL_imageFilter.h"
#include "SDL_rotozoom.h"

#include "img_load.h"

char *red_dir = "images\\entities\\ghosts\\red\\";
char *pink_dir = "images\\entities\\ghosts\\pink\\";
char *cyan_dir = "images\\entities\\ghosts\\cyan\\";
char *orange_dir = "images\\entities\\ghosts\\orange\\";

SDL_Surface *load_img(const char *filename);

//
//hall sprites
//
SDL_Surface *double_corner_imgs[4];
SDL_Surface *single_corner_imgs[4];
SDL_Surface *tleft_imgs[4];
SDL_Surface *tright_imgs[4];
SDL_Surface *middle_imgs[4];
SDL_Surface *hall_imgs[4];

//
//corral sprites
//

SDL_Surface *corral_imgs[4];
SDL_Surface *corralSide_imgs[4];
SDL_Surface *corralGate;

//
//pacman sprites
//
SDL_Surface *pacman;
SDL_Surface *aniPacman[4][3];
SDL_Surface *deathPacman[11];
SDL_Surface *pacmanLifeIcon;

//
//ghost sprites
//

//ghosts have 4 colors * 2 images for main animatino
SDL_Surface *ghosts[4][4][2];

//
//feauters sprites
//

SDL_Surface *smallPill;
SDL_Surface *largePill;

//
//fruit images
//
SDL_Surface *cherryImage;
SDL_Surface *strawberryImage;
SDL_Surface *peachImage;
SDL_Surface *appleImage;
SDL_Surface *grapesImage;
SDL_Surface *galaxianImage;
SDL_Surface *bellImage;
SDL_Surface *keyImage;

void load_border_imgs(void);
void load_pacman_imgs(void);
void load_feature_imgs(void);
void load_ghost_imgs(void);
void load_fruit_imgs(void);

void set_border_imgs(void);
void set_pacman_imgs(void);
void set_feature_imgs(void);
void set_ghost_imgs(void);
void set_fruit_imgs(void);

void load_imgs(void)
{
	load_border_imgs();
	load_pacman_imgs();
	load_feature_imgs();
	load_ghost_imgs();
	load_fruit_imgs();
}

void set_imgs(void)
{
	set_border_imgs();
	set_pacman_imgs();
	set_feature_imgs();
	set_fruit_imgs();
	set_ghost_imgs();
}

void load_diags(SDL_Surface *imgs[4], const char *file)
{
	char dirStr[256];
	const char *extensions[] = {"UL", "UR", "BL", "BR"};
	int i;

	for (i = 0; i < 4; i++)
	{
		sprintf(dirStr, "%s%s%s", file, extensions[i], ".png");
		imgs[i] = load_img(dirStr);
	}
}

void load_dirs(SDL_Surface *imgs[4], const char *file)
{
	char dirStr[256];
	const char *extensions[] = {"U", "B", "L", "R"};
	int i;

	for (i = 0; i < 4; i++)
	{
		sprintf(dirStr, "%s%s%s", file, extensions[i], ".png");
		imgs[i] = load_img(dirStr);
	}
}

void load_border_imgs(void)
{
	load_diags(double_corner_imgs, "images\\map\\doublecorner");
	load_diags(single_corner_imgs, "images\\map\\singlecorner");
	load_diags(tleft_imgs, "images\\map\\tleft");
	load_diags(tright_imgs, "images\\map\\tright");
	load_dirs(middle_imgs, "images\\map\\middle");
	load_dirs(hall_imgs, "images\\map\\hallway");

	load_diags(corral_imgs, "images\\map\\corral\\corral");
	load_dirs(corralSide_imgs, "images\\map\\corral\\corral");
	corralGate = load_img("images\\map\\corral\\corralgate.png");
}

void set_border_imgs(void)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		SDL_FreeSurface(double_corner_imgs[i]);
		SDL_FreeSurface(single_corner_imgs[i]);
		SDL_FreeSurface(tleft_imgs[i]);
		SDL_FreeSurface(tright_imgs[i]);
		SDL_FreeSurface(middle_imgs[i]);
		SDL_FreeSurface(corral_imgs[i]);
		SDL_FreeSurface(corralSide_imgs[i]);
	}

	SDL_FreeSurface(corralGate);
}

void load_pacman_imgs(void)
{
	int i;
	char dirStr[256];
	pacman = load_img("images\\entities\\pacman\\pacman.png");
	pacmanLifeIcon = load_img("images\\entities\\pacman\\pac_life_icon.png");
	aniPacman[0][0] = load_img("images\\entities\\pacman\\l0.png");
	aniPacman[0][1] = load_img("images\\entities\\pacman\\l1.png");
	aniPacman[0][2] = aniPacman[0][0];

	aniPacman[1][0] = load_img("images\\entities\\pacman\\u0.png");
	aniPacman[1][1] = load_img("images\\entities\\pacman\\u1.png");
	aniPacman[1][2] = aniPacman[1][0];

	aniPacman[2][0] = load_img("images\\entities\\pacman\\r0.png");
	aniPacman[2][1] = load_img("images\\entities\\pacman\\r1.png");
	aniPacman[2][2] = aniPacman[2][0];

	aniPacman[3][0] = load_img("images\\entities\\pacman\\d0.png");
	aniPacman[3][1] = load_img("images\\entities\\pacman\\d1.png");
	aniPacman[3][2] = aniPacman[3][0];

	for (i = 0; i < 11; i++)
	{
		sprintf(dirStr, "%s%s%d%s", "images\\entities\\pacman\\death\\", "death", i, ".png");

		deathPacman[i] = load_img(dirStr);
	}
}

void set_pacman_imgs(void)
{
	int i;
	SDL_FreeSurface(pacman);
	SDL_FreeSurface(pacmanLifeIcon);

	SDL_FreeSurface(aniPacman[0][0]);
	SDL_FreeSurface(aniPacman[0][1]);
	SDL_FreeSurface(aniPacman[1][0]);
	SDL_FreeSurface(aniPacman[1][1]);
	SDL_FreeSurface(aniPacman[2][0]);
	SDL_FreeSurface(aniPacman[2][1]);
	SDL_FreeSurface(aniPacman[3][0]);
	SDL_FreeSurface(aniPacman[3][1]);
}

void load_feature_imgs(void)
{
	smallPill = load_img("images\\smallpill.png");
	largePill = load_img("images\\largepill.png");
}

void set_feature_imgs(void)
{
	SDL_FreeSurface(smallPill);
	SDL_FreeSurface(largePill);
}

void load_fruit_imgs(void)
{
	cherryImage     = load_img("images\\fruit\\cherry.png");
	strawberryImage = load_img("images\\fruit\\strawberry.png");
	peachImage      = load_img("images\\fruit\\peach.png");
	appleImage      = load_img("images\\fruit\\apple.png");
	grapesImage     = load_img("images\\fruit\\grapes.png");
	galaxianImage   = load_img("images\\fruit\\galaxian.png");
	bellImage       = load_img("images\\fruit\\bell.png");
	keyImage        = load_img("images\\fruit\\key.png");
}

void set_fruit_imgs(void)
{
	SDL_FreeSurface(cherryImage);
	SDL_FreeSurface(strawberryImage);
	SDL_FreeSurface(peachImage);
	SDL_FreeSurface(appleImage);
	SDL_FreeSurface(grapesImage);
	SDL_FreeSurface(galaxianImage);
	SDL_FreeSurface(bellImage);
	SDL_FreeSurface(keyImage);
}

char *get_ghost_dir(int type)
{
	switch (type)
	{
		case Blinky: return red_dir;
		case Inky:   return cyan_dir;
		case Pinky:  return pink_dir;
		case Clyde:  return orange_dir;
	}

	return NULL;
}

void load_ghost_imgs(void)
{
	char dirStr[256];
	int col, i;

	for (col = 0; col < 4; col++)
	{
		for (i = 0; i < 2; i++)
		{
			sprintf(dirStr, "%s%s%d%s", get_ghost_dir(col), "u", i, ".png");
			ghosts[col][0][i] = load_img(dirStr);

			sprintf(dirStr, "%s%s%d%s", get_ghost_dir(col), "d", i, ".png");
			ghosts[col][1][i] = load_img(dirStr);

			sprintf(dirStr, "%s%s%d%s", get_ghost_dir(col), "l", i, ".png");
			ghosts[col][2][i] = load_img(dirStr);

			sprintf(dirStr, "%s%s%d%s", get_ghost_dir(col), "r", i, ".png");
			ghosts[col][3][i] = load_img(dirStr);
		}
	}
}

void set_ghost_imgs(void)
{
	int i,j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			SDL_FreeSurface(ghosts[i][j][0]);
			SDL_FreeSurface(ghosts[i][j][1]);
		}
	}
}


SDL_Surface *load_img(const char *filename)
{
	//The img that's loaded
	SDL_Surface* loadedImage;
	//The optimized img that will be used
	SDL_Surface* optimizedImage = NULL;
	//Load the img using SDL_image
	loadedImage = IMG_Load(filename);

	printf("loading img: %s\n", filename);		

	//If the image loaded
	if(loadedImage != NULL)
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	}
	else
	{
		printf("Error opening image %s\n", filename);
		exit(1);
	}

	//Return the optimized image
	return optimizedImage;
}


SDL_Surface* double_corner_img(DiagDirect_t direction)
{
	return double_corner_imgs[direction];
}

SDL_Surface* single_corner_img(DiagDirect_t direction)
{
	return single_corner_imgs[direction];
}

SDL_Surface* middle_img(Direction_t direction)
{
	return middle_imgs[direction];
}

SDL_Surface* hall_img(Direction_t direction)
{
	return hall_imgs[direction];
}

SDL_Surface* tleft_img(DiagDirect_t direction)
{
	return tleft_imgs[direction];
}

SDL_Surface* tright_img(DiagDirect_t direction)
{
	return tright_imgs[direction];
}

SDL_Surface* corral_corner_img(DiagDirect_t direction)
{
	return corral_imgs[direction];
}

SDL_Surface* corral_side_img(Direction_t direction)
{
	return corralSide_imgs[direction];
}

SDL_Surface* corral_gate_img(void)
{
	return corralGate;
}

SDL_Surface* pacman_img(void)
{
	return pacman;
}

SDL_Surface* pacman_death_img(int i)
{
	return deathPacman[i];
}

SDL_Surface *pacman_ani_img(Direction_t dir, int frame)
{
	if (frame < 0 || frame > 4)
	{
		printf("invalid pacman frame: %d\n", frame);
		exit(1);
	}

	if (frame == 0) return pacman;

	switch(dir)
	{
		case Left:  return aniPacman[0][frame - 1];
		case Up:    return aniPacman[1][frame - 1];
		case Right: return aniPacman[2][frame - 1];
		case Down:  return aniPacman[3][frame - 1];
	}

	printf("incorrect enum value\n");
	exit(1);
}

SDL_Surface* pacman_life_img(void)
{
	return pacmanLifeIcon;
}

SDL_Surface* small_pill_img(void)
{
	return smallPill;
}

SDL_Surface* large_pill_img(void)
{
	return largePill;
}

SDL_Surface* get_fruit_img(Fruit_t fruit)
{
	switch (fruit)
	{
		case Cherry:     return cherryImage;
		case Strawberry: return strawberryImage;
		case Peach:      return peachImage;
		case Apple:      return appleImage;
		case Grapes:     return grapesImage;
		case Galaxian:   return galaxianImage;
		case Bell:       return bellImage;
		case Key:        return keyImage;
	}
}

SDL_Surface* ghost_img(GhostType_t type, Direction_t dir, int frame)
{
	return ghosts[type][dir][frame];
}
