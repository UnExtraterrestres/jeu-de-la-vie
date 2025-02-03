#ifndef SIGCONSOLE_H
#define SIGCONSOLE_H

/**
 * @file sig-console.h
 * @brief Fichier d'en-tête contenant les déclarations pour la gestion d'une interface console.
 */

/**
 * @struct ecran
 * @brief Structure représentant un écran console.
 */
struct ecran
{
    int largeur; /**< Largeur de l'écran. */
    int hauteur; /**< Hauteur de l'écran. */
    char fond;   /**< Couleur de fond de l'écran. */
    char *image; /**< Données de l'image de l'écran. */
};

/**
 * @brief Efface le contenu d'un écran.
 * 
 * @param self Pointeur vers l'écran à effacer.
 */
void effacer(struct ecran *self);

/**
 * @brief Crée un nouvel écran avec les dimensions spécifiées.
 * 
 * @param largeur Largeur de l'écran.
 * @param hauteur Hauteur de l'écran.
 * @return Pointeur vers le nouvel écran créé.
 */
struct ecran* ecran_create(int largeur, int hauteur);

/**
 * @brief Libère la mémoire allouée pour un écran.
 * 
 * @param self Pointeur vers l'écran à libérer.
 */
void free_ecran(struct ecran *self);

/**
 * @brief Affiche le contenu d'un écran.
 * 
 * @param self Pointeur vers l'écran à afficher.
 */
void afficher(struct ecran *self);

/**
 * @struct pixel
 * @brief Structure représentant un pixel sur l'écran.
 */
struct pixel
{
    double x;   /**< Coordonnée X du pixel. */
    double y;   /**< Coordonnée Y du pixel. */
    char pxl;   /**< Valeur du pixel. */
};

/**
 * @brief Crée un nouveau pixel avec les coordonnées et la valeur spécifiées.
 * 
 * @param x Coordonnée X du pixel.
 * @param y Coordonnée Y du pixel.
 * @param pxl Valeur du pixel.
 * @return Pointeur vers le nouveau pixel créé.
 */
struct pixel* pixel_create_from(double x, double y, char pxl);

/**
 * @brief Crée un nouveau pixel avec les coordonnées spécifiées.
 * 
 * @param x Coordonnée X du pixel.
 * @param y Coordonnée Y du pixel.
 * @return Pointeur vers le nouveau pixel créé.
 */
struct pixel* pixel_create(double x, double y);

/**
 * @brief Libère la mémoire allouée pour un pixel.
 * 
 * @param self Pointeur vers le pixel à libérer.
 */
void free_pixel(struct pixel *self);

/**
 * @brief Place un pixel sur l'écran spécifié.
 * 
 * @param ecran Pointeur vers l'écran où le pixel sera placé.
 * @param pixel Pointeur vers le pixel à placer.
 */
void placer_pixel(struct ecran *ecran, struct pixel *pixel);

/**
 * @brief Place un pixel sur l'écran spécifié aux coordonnées spécifiées.
 * 
 * @param ecran Pointeur vers l'écran où le pixel sera placé.
 * @param x Coordonnée X du pixel.
 * @param y Coordonnée Y du pixel.
 */
void placer_pixel_from(struct ecran *ecran, double x, double y);

/**
 * @brief Retire un pixel de l'écran spécifié.
 * 
 * @param ecran Pointeur vers l'écran duquel le pixel sera retiré.
 * @param pixel Pointeur vers le pixel à retirer.
 */
void retirer_pixel(struct ecran *ecran, struct pixel *pixel);

/**
 * @brief Retire un pixel de l'écran spécifié aux coordonnées spécifiées.
 * 
 * @param ecran Pointeur vers l'écran duquel le pixel sera retiré.
 * @param x Coordonnée X du pixel.
 * @param y Coordonnée Y du pixel.
 */
void retirer_pixel_from(struct ecran *ecran, double x, double y);

int get_screen_width();
int get_screen_height();

#endif /* SIGCONSOLE_H */
// Path: sig-console.c
