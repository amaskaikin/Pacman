#include <stdio.h>
#include <stdlib.h>

#include "border.h"
#include "img_load.h"

int isvalid_sq(Border_t *border, int x, int y)
{
	if (x < 0 || y < 0) return 0;
	if (x >= BORDER_LENGTH || y >= BORDER_HEIGHT) return 0;

	return border->borderSquares[x][y].walkable;
}
	
int isteleport_sq(int x, int y)
{
	if (x == -1 && y == 14) return 1;
	else if (x == 28 && y == 14) return 1;
	else return 0;
}

void load_border(Border_t *border, const char* file)
{
	FILE *f = fopen(file, "r");
	int walkable = 0;
	char c = 'a';
	int x = 0;
	int y = 0;
	SDL_Surface *img = NULL;

	if (f == NULL)
	{
		printf("Can't find file %s \n", file);
		exit(1);
	}

	while (((c = fgetc(f)) != EOF))
	{
		if (c == '\n' || c == 13) continue; //continue if a newline

		switch(c)
		{
			case '0': img = double_corner_img(BotLeft);		break;
			case '1': img = double_corner_img(BotRight);	break;
			case '2': img = double_corner_img(TopLeft);     break;
			case '3': img = double_corner_img(TopRight);    break;

			case '4': img = single_corner_img(BotLeft);		break;
			case '5': img = single_corner_img(BotRight);	break;
			case '6': img = single_corner_img(TopLeft);     break;
			case '7': img = single_corner_img(TopRight);    break;

			case '8': img = tleft_img(TopRight);            break;
			case '9': img = tleft_img(TopLeft);             break;
			case 'a': img = tleft_img(BotLeft);				break;
			case 'b': img = tleft_img(BotRight);			break;

			case 'c': img = tright_img(TopLeft);            break;
			case 'd': img = tright_img(BotRight);			break;
			case 'e': img = tright_img(BotLeft);			break;
			case 'f': img = tright_img(TopRight);           break;

			case 'g': img = hall_img(Up);					break;
			case 'h': img = hall_img(Down);					break;
			case 'i': img = hall_img(Left);					break;
			case 'j': img = hall_img(Right);				break;

			case 'k': img = middle_img(Left);               break;
			case 'l': img = middle_img(Right);              break;
			case 'm': img = middle_img(Up);                 break;
			case 'n': img = middle_img(Down);               break;

			case 'o': img = corral_corner_img(TopLeft);     break;
			case 'p': img = corral_corner_img(TopRight);    break;
			case 'q': img = corral_corner_img(BotLeft);     break;
			case 'r': img = corral_corner_img(BotRight);    break;

			case 's': img = corral_side_img(Up);               break;
			case 't': img = corral_side_img(Down);             break;
			case 'u': img = corral_side_img(Left);             break;
			case 'v': img = corral_side_img(Right);            break;

			case 'w': img = corral_gate_img();                 break;

			case '.': /* pill */
				
				walkable = 1;
				break;
			case '*': /*Large pill */
				
				walkable = 1;
				break;
			case ',': // empty, walkable square
				walkable = 1;
				break;
			case ' ': //empty, nonwalkable square
				walkable = 0;
				break;
			default:
				printf("Error loading character: %c (int: %d) at coordinate (%d, %d) in boardfile %s\n", c, c, x, y, file);
				exit(1);
				break;
		}
		border->borderSquares[x][y].img = img;
		border->borderSquares[x][y].walkable = walkable;

		img = NULL;
		walkable = 0;
		x++;

		if (x == BORDER_LENGTH)
		{
			x = 0;
			y++;
		}
	}

	fclose(f);
}