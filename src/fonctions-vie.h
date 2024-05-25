#ifndef FONCTIONSVIE_H
#define FONCTIONSVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @file fonctions-vie.h
 * @brief Fichier d'en-tête contenant les déclarations des fonctions pour le jeu de la vie.
 */

/**
 * @struct matrice
 * @brief Structure représentant une matrice pour le jeu de la vie.
 */
struct matrice
{
    int largeur;    /**< Largeur de la matrice. */
    int hauteur;    /**< Hauteur de la matrice. */
    int *cellules;  /**< Tableau représentant les cellules de la matrice. */
};

/**
 * @brief Crée une nouvelle matrice avec les dimensions spécifiées.
 * 
 * @param largeur Largeur de la matrice.
 * @param hauteur Hauteur de la matrice.
 * @return Pointeur vers la nouvelle matrice créée.
 */
struct matrice* matrice_create(int largeur, int hauteur);

/**
 * @brief Remplit la matrice avec des valeurs aléatoires (0 ou 1).
 * 
 * @param self Pointeur vers la matrice à remplir.
 * @param seed Graine d'initialisation pour le générateur de pseudo-aléatoire
 */
void make_random_matrice(struct matrice *self, long int seed);

/**
 * @brief Libère la mémoire allouée pour une matrice.
 * 
 * @param self Pointeur vers la matrice à libérer.
 */
void free_matrice(struct matrice *self);

/**
 * @brief Récupère l'état de la cellule aux coordonnées spécifiées dans la matrice.
 * 
 * @param self Pointeur vers la matrice.
 * @param x Coordonnée X de la cellule.
 * @param y Coordonnée Y de la cellule.
 * @return État de la cellule (0 ou 1).
 */
int get_etat_cellule(struct matrice *self, int x, int y);

/**
 * @brief Récupère le nombre de voisines vivantes d'une cellule aux coordonnées spécifiées dans la matrice.
 * 
 * @param self Pointeur vers la matrice.
 * @param x Coordonnée X de la cellule.
 * @param y Coordonnée Y de la cellule.
 * @return Nombre de voisines vivantes de la cellule.
 */
int get_nb_voisines(struct matrice *self, int x, int y);

/**
 * @brief Détermine si une cellule doit naître en fonction de son état actuel et du nombre de voisines vivantes.
 * 
 * @param etat État actuel de la cellule (0 ou 1).
 * @param nb_voisines Nombre de voisines vivantes de la cellule.
 * @return 1 si la cellule doit naître, 0 sinon.
 */
int cellule_nait(int etat, int nb_voisines);

/**
 * @brief Détermine si une cellule doit mourir en fonction de son état actuel et du nombre de voisines vivantes.
 * 
 * @param etat État actuel de la cellule (0 ou 1).
 * @param nb_voisines Nombre de voisines vivantes de la cellule.
 * @return 1 si la cellule doit mourir, 0 sinon.
 */
int cellule_meurt(int etat, int nb_voisines);

/**
 * @brief Définit l'état d'une cellule aux coordonnées spécifiées dans la matrice.
 * 
 * @param self Pointeur vers la matrice.
 * @param x Coordonnée X de la cellule.
 * @param y Coordonnée Y de la cellule.
 * @param etat Nouvel état de la cellule (0 ou 1).
 */
void set_etat_cellule(struct matrice *self, int x, int y, int etat);

/**
 * @brief Met à jour la matrice selon les règles du jeu de la vie.
 * 
 * @param self Pointeur vers la matrice à mettre à jour.
 */
void update(struct matrice *self);

#endif /* FONCTIONSVIE_H */
// Path: fonctions-vie.c
