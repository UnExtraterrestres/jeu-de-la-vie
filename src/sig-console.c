#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "sig-console.h"

#define DEFAULT_TERMINAL_BG ' '
#define DEFAULT_CAMERA_BG ' '
#define DEFAULT_BG ' '
#define DEFAULT_FG 'O'

int get_screen_side(char side_choice) {
    if (side_choice != 'w' && side_choice != 'h') {
        return -1;
    }

    FILE *fp;
    char path[1035];
    int side = -1;

    if (side_choice == 'w') {
        fp = popen("tput cols", "r");
    } else {
        fp = popen("tput lines", "r");
    }

    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    if (fgets(path, sizeof(path)-1, fp) != NULL) {
        side = atoi(path);
    }

    pclose(fp);
    return side;
}

int get_screen_width() {
    return get_screen_side('w');
}

int get_screen_height() {
    return get_screen_side('h');
}

void effacer(struct ecran *self) {
    if (NULL == self) {
        return;
    }

    for (int i = 0; i < self->hauteur * self->largeur; ++i) {
        self->image[i] = self->fond;
    }
}

struct ecran* ecran_create(int largeur, int hauteur) {
    if (0 >= largeur || 0 >= hauteur) {
        fprintf(stderr, "Error: ecran_create, invalid specified size.\n");
        return NULL;
    }

    struct ecran *res = malloc(sizeof(struct ecran));
    if (res != NULL) {
        res->largeur = largeur;
        res->hauteur = hauteur;
        res->fond = DEFAULT_BG;
        res->image = calloc(largeur * hauteur, sizeof(char));

        if (res->image == NULL) {
            free(res);
            return NULL;
        }
    }

    effacer(res);
    return res;
}

void afficher(struct ecran *self) {
    if (NULL == self) {
        return;
    }

    for (int y = 0; y < self->hauteur; ++y) {
        for (int x = 0; x < self->largeur; ++x) {
            printf("%c", self->image[y * self->largeur + x]);
        }
		printf("\n");
    }
}

int is_on_screen(int x, int y, struct ecran *ecr) {
    if (NULL == ecr) {
        return -1;
    }

    if (0 <= x && x < ecr->largeur && 0 <= y && y < ecr->hauteur) {
        return 0;
    }

    return -1;
}

int is_on_cam(double x, double y, struct camera *cam) {
    if (NULL == cam) {
        return -1;
    }

    double xmin = cam->x;
    double xmax = cam->x + cam->largeur;
    double ymin = cam->y;
    double ymax = cam->y + cam->hauteur;

    if (xmin <= x && x < xmax && ymin <= y && y < ymax) {
        return 0;
    }

    return -1;
}

void afficher_cam_pov(struct ecran *self, struct camera *cam) {
    if (NULL == self || NULL == cam) {
        fprintf(stderr, "Error: afficher_cam_pov NULL args.\n");
        return;
    }

	int width = get_screen_width();
    int height = get_screen_height();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            if (x >= cam->tx && x < cam->tx + cam->largeur && y >= cam->ty && y < cam->ty + cam->hauteur) {
                int cx = x - cam->tx;
                int cy = y - cam->ty;

                int pcx = cx + (int)cam->x;
                int pcy = cy + (int)cam->y;

                if (pcx >= 0 && pcx < self->largeur && pcy >= 0 && pcy < self->hauteur) {
                    printf("%c", self->image[pcy * self->largeur + pcx]);
                } else {
                    printf("%c", cam->fond);
                }
            } else {
                printf("%c", DEFAULT_TERMINAL_BG);
            }
        }
        printf("\n");
    }
}


void free_ecran(struct ecran *self) {
    if (NULL == self) {
        return;
    }

    free(self->image);
    free(self);
}

struct pixel* pixel_create_from(double x, double y, char pxl) {
    if (0.0 > x || 0.0 > y) {
        return NULL;
    }

    struct pixel *res = malloc(sizeof(struct pixel));
    if (NULL == res) {
        return NULL;
    }

    res->x = x;
    res->y = y;
    res->pxl = pxl;

    return res;
}

struct pixel* pixel_create(double x, double y) {
    if (0.0 > x || 0.0 > y) {
        return NULL;
    }

    return pixel_create_from(x, y, DEFAULT_FG);
}

void free_pixel(struct pixel *self) {
    if (NULL == self) {
        return;
    }

    free(self);
}

void placer_pixel(struct ecran *self, struct pixel *pxl) {
    if (NULL == self || NULL == pxl) {
        return;
    }

    if (0 <= (int)(pxl->x) && (int)(pxl->x) < self->largeur && 0 <= (int)(pxl->y) && (int)(pxl->y) < self->hauteur) {
        self->image[(int)(pxl->y) * self->largeur + (int)(pxl->x)] = pxl->pxl;
    }
}

void placer_pixel_from(struct ecran *self, double x, double y) {
    if (NULL == self || 0.0 > x || 0.0 > y) {
        return;
    }

    struct pixel *tmp = pixel_create(x, y);
    placer_pixel(self, tmp);
    free_pixel(tmp);
}

void retirer_pixel(struct ecran *self, struct pixel *pxl) {
    if (NULL == self || NULL == pxl) {
        return;
    }

    if (pxl->pxl != DEFAULT_BG) {
        pxl->pxl = DEFAULT_BG;
    }

    placer_pixel(self, pxl);
}

void retirer_pixel_from(struct ecran *self, double x, double y) {
    if (NULL == self || 0.0 > x || 0.0 > y) {
        return;
    }

    struct pixel *tmp = pixel_create_from(x, y, DEFAULT_BG);
    retirer_pixel(self, tmp);
    free_pixel(tmp);
}

struct camera* camera_create_from(int largeur, int hauteur, int tx, int ty, char fond, double x, double y) {
    if (0 >= largeur || 0 >= hauteur || 0 > tx || 0 > ty) {
        fprintf(stderr, "Error: camera_create invalid args.\n");
        return NULL;
    }

    struct camera *res = malloc(sizeof(struct camera));
    if (NULL == res) {
        return NULL;
    }

    res->largeur = largeur;
    res->hauteur = hauteur;
    res->tx = tx;
    res->ty = ty;
    res->fond = fond;
    res->x = x;
    res->y = y;

    return res;
}

struct camera* camera_create() {
    int largeur = get_screen_width();
    int hauteur = get_screen_height();

    return camera_create_from(largeur, hauteur, 0, 0, DEFAULT_CAMERA_BG, 0.0, 0.0);
}

void camera_free(struct camera *self) {
    if (NULL == self) {
        return;
    }

    free(self);
}

int move_tcamera(struct camera *cam, int dx, int dy)
{

	int x_min = 0 - cam->tx;
	int y_min = 0 - cam->ty;

	int x_max = get_screen_width() - (cam->tx + cam->largeur);
	int y_max = get_screen_height() - (cam->ty + cam->hauteur);

	if (NULL == cam || dx < x_min || dx > x_max || dy < y_min || dy > y_max)
	{
		fprintf(stderr, "Error: move_tcamera invalid args.\n");
		return -1;
	}

	cam->tx += dx;
	cam->ty += dy;

	return 0;
}


int move_pcamera(struct camera *cam, double dx, double dy)
{

	if (NULL == cam)
	{
		fprintf(stderr, "Error: move_pcamera invalid args.\n");
		return -1;
	}

	cam->x += dx;
	cam->y += dy;

	return 0;
}

int grow_tcamera(struct camera *cam, int dx, int dy)
{

	int width = get_screen_width();
    int height = get_screen_height();

	int new_larg = cam->largeur + dx;
	int new_haut = cam->hauteur + dy;

	if (NULL == cam || 0 >= new_larg || width < new_larg || 0 >= new_haut || height < new_haut)
	{
		fprintf(stderr, "Error: grow_tcamera invalid args.\n");
		return -1;
	}

	cam->largeur += dx;
	cam->hauteur += dy;

	return 0;
}
