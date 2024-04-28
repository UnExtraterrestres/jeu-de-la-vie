#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions-vie.h"


struct matrice* matrice_create(int largeur, int hauteur)
{

    struct matrice *res = malloc(sizeof(struct matrice));
    
    if (res != NULL)
    {
        res->largeur = largeur;
        res->hauteur = hauteur;
        res->cellules = calloc(largeur*hauteur, sizeof(int));
        
        if (res->cellules == NULL)
        {
            free(res);
            return NULL;
        }
    }
    
    return res;
}

void make_random_matrice(struct matrice *self)
{
    
    for (int y=0; y<self->hauteur; ++y)
    {
        for (int x=0; x<self->largeur; ++x)
        {
            if (rand()%2 == 0)
            {
                self->cellules[y*self->largeur+x] = 1;
            }
        }
    }
}

void free_matrice(struct matrice *self)
{
    free(self->cellules);
    free(self);
}

int get_etat_cellule(struct matrice *self, int x, int y)
{
    return self->cellules[y*self->largeur+x];
}

int get_nb_voisines(struct matrice *self, int x, int y)
{
    int res = 0;
    
    for (int dy=-1; dy<=1; ++dy)
    {
        for (int dx=-1; dx<=1; ++dx)
        {
            if (dx != 0 || dy != 0)
            {
                int nx = x+dx;
                int ny = y+dy;
                
                if (nx >= 0 && nx < self->largeur && ny >= 0 && ny < self->hauteur)
                {
                    res += self->cellules[ny*self->largeur+nx];
                }
            }
        }
    }
    
    return res;
}

int cellule_nait(int etat, int nb_voisines)
{
    return etat == 0 && nb_voisines == 3;
}

int cellule_meurt(int etat, int nb_voisines)
{
    return etat == 1 && (nb_voisines < 2 || nb_voisines > 3);
}

void set_etat_cellule(struct matrice *self, int x, int y, int etat)
{
    self->cellules[y*self->largeur+x] = etat;
}

void update(struct matrice *self)
{
    struct matrice *tmp = matrice_create(self->largeur, self->hauteur);
    
    if (tmp != NULL)
    {
        for (int y=0; y<self->hauteur; ++y)
        {
            for (int x=0; x<self->largeur; ++x)
            {
                int nb_voisines = get_nb_voisines(self, x, y);
                int etat = get_etat_cellule(self, x, y);
                
                if (cellule_nait(etat, nb_voisines))
                {
                    set_etat_cellule(tmp, x, y, 1);
                }
                else if (cellule_meurt(etat, nb_voisines))
                {
                    set_etat_cellule(tmp, x, y, 0);
                }
                else
                {
                    set_etat_cellule(tmp, x, y, etat);
                }
            }
        }
        
        memcpy(self->cellules, tmp->cellules, self->largeur*self->hauteur*sizeof(int));
        
        free_matrice(tmp);
    }
}

