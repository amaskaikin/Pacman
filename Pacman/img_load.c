#include "SDL.h"
#include "SDL_image.h"
#include "SDL_imageFilter.h"
#include "SDL_rotozoom.h"

#include "img_load.h"

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

void load_border_imgs(void);

void set_border_imgs(void);

void load_imgs(void)
{
	load_border_imgs();
}

void set_imgs(void)
{
	set_border_imgs();
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
