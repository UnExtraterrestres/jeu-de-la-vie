#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "sig-console.h"

#define DEFAULT_BG ' '
#define DEFAULT_FG 'O'


void effacer(struct ecran *self)
{
	
	for (int i=0; i<self->hauteur*self->largeur; ++i)
	{
		self->image[i] = self->fond;
	}
}

struct ecran* ecran_create(int largeur, int hauteur)
{
	
	struct ecran *res = malloc(sizeof(struct ecran));
	
	if (res != NULL)
	{
		res->largeur = largeur;
		res->hauteur = hauteur -1;
		res->fond = DEFAULT_BG;
		res->image = calloc(largeur*hauteur, sizeof(char));

		if (res->image == NULL)
		{
			
			free(res);
			return NULL;
		}
	}

	effacer(res);
	
	return res;
}


void afficher(struct ecran *self)
{
	
	for (int y=0; y<self->hauteur; ++y)
	{
		
		for (int x=0; x<self->largeur; ++x)
		{
			
			printf("%c", self->image[y*self->largeur+x]);
		}
		printf("\n");
	}
}


void free_ecran(struct ecran *self)
{

	free(self->image);
	free(self);
}


struct pixel* pixel_create_from(double x, double y, char pxl)
{
    struct pixel *res = malloc(sizeof(struct pixel));
    if (res != NULL)
    {
        res->x = x;
        res->y = y;
        res->pxl = pxl;
    }
    return res;
}

struct pixel* pixel_create(double x, double y)
{

	return pixel_create_from(x, y, DEFAULT_FG);
}

void free_pixel(struct pixel *self)
{
	free(self); self = NULL;
}

void placer_pixel(struct ecran *self, struct pixel *pxl)
{

	if (0<=(int)(pxl->x) && (int)(pxl->x)<self->largeur 
		&& 0<=(int)(pxl->y) && (int)(pxl->y)<self->hauteur)
	{
		self->image[(int)(pxl->y)*self->largeur+(int)(pxl->x)] = pxl->pxl;
	}
}

void placer_pixel_from(struct ecran *self, double x, double y)
{

	struct pixel *tmp = pixel_create(x, y);

	placer_pixel(self, tmp);

	free_pixel(tmp);
}

void retirer_pixel(struct ecran *self, struct pixel *pxl)
{

	if (pxl->pxl != DEFAULT_BG)
	{
		pxl->pxl = DEFAULT_BG;
	} 

	placer_pixel(self, pxl);
}

void retirer_pixel_from(struct ecran *self, double x, double y)
{

	struct pixel *tmp = pixel_create_from(x, y, DEFAULT_BG);

	retirer_pixel(self, tmp);

	free_pixel(tmp);
}

int get_screen_side(char side_choice)
{

	if (side_choice != 'w' && side_choice != 'h')
	{
		return -1;
	}

	FILE *fp;
	char path[1035];
	int side = -1;

	if (side_choice == 'w')
	{
		fp = popen("tput cols", "r");
	} else
	{
		fp = popen("tput lines", "r");
	}

	if (fp == NULL)
	{
		perror("popen");
		exit(EXIT_FAILURE);
	}

	if (fgets(path, sizeof(path)-1, fp) != NULL) {
        side = atoi(path);
    }

    pclose(fp);

    return side;
}

int get_screen_width()
{

    return get_screen_side('w');
}

int get_screen_height()
{

   return get_screen_side('h');
}
