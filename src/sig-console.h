#ifndef SIGCONSOLE_H
#define SIGCONSOLE_H

/**
 * @file sig-console.h
 * @brief Fichier d'en-tête contenant les déclarations pour la gestion d'une interface console.
 */

int get_screen_width();
int get_screen_height();

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

/**
 * @struct camera
 * @brief Structure représentant une camera.
 */
struct camera
{
    int largeur; /**< Largeur de la camera. */
    int hauteur; /**< Hauteur de la camera. */
    int tx;      /**< abscisse de la camera dans le terminal. */
    int ty;      /**< ordonnée de la camera dans le terminal. */
    char fond;

    double x;    /**< abscisse de la camera dans le plan. */
    double y;    /**< ordonnée de la camera dans le plan. */
};  // /!\ toujours les coordonnées du coin supérieur gauche du rectangle de la camera

/**
 * @brief Créer une nouvelle camera à partir des paramètres spécifiés
 *
 * @param largeur Largeur de la camera
 * @param hauteur Hauteur de la camera
 * @param tx Abscisse de la camera dans le terminal
 * @param ty Ordonnée de la camera dans le terminal
 * @param fond Fond de la camera
 * @param x Abscisse de la camera dans le plan
 * @param y Ordonnée de la camera dans le plan
 */
struct camera* camera_create_from(int largeur, int hauteur, int tx, int ty, char fond, double x, double y);

/**
 * @brief Créer une nouvelle camera en récupérant par défaut les dimensions de la console
 */
struct camera* camera_create();

/**
 * @brief Libère la mémoire allouée pour une camera.
 * 
 * @param self Pointeur vers la camera à libérer.
 */
void camera_free(struct camera *self);

/**
 * @brief Renvois si le pixel se trouve dans la camera ou non
 *
 * @param x Abscisse à vérifier
 * @param y Ordonnée à vérifier
 * @param cam Camera en question
 */
int is_on_cam(double x, double y, struct camera *cam);

/**
 * @brief Renvois si le pixel se trouve dans la camera ou non
 *      appel is_on_cam
 * @param pxl Pixel en question
 * @param cam Camera en question
 */
int is_pxl_on_cam(struct pixel *pxl, struct camera *cam);

/**
 * @brief Renvois si un pixel du terminal, par la vue de la camera
 *      ce retrouve sur l'image
 *
 * @param x Abscisse à vérifier
 * @param y Ordonnée à vérifier
 * @param ecr Ecran en question
 */
int is_on_screen(int x, int y, struct ecran *ecr);

/**
 * @brief Renvois si un pixel du terminal, par la vue de la camera
 *      ce retrouve sur l'image
 * @param pxl Pixel en question
 * @param cam Camera en question
 * @param ecr Ecran en question
 */
int is_pxl_on_screen(struct pixel *pxl, struct camera *cam, struct ecran *ecr);

/**
 * @brief Affiche le contenu d'un écran passant dans la vue de la camera.
 * 
 * @param self Pointeur vers l'écran à afficher.
 * @param cam Pointeur vers la camera
 */
void afficher_cam_pov(struct ecran *self, struct camera *cam);

/**
 * @brief Déplace la caméra dans le terminal
 *
 * @param cam Pointeur vers la caméra en question
 * @param dx delta en abscisse
 * @param dy delta en ordonnée
 * @return -1 en cas d'échec, 0 sinon
 */
int move_tcamera(struct camera *cam, int dx, int dy);

/**
 * @brief Déplace la caméra dans le plan
 *
 * @param cam Pointeur vers la caméra en question
 * @param dx delta en abscisse
 * @param dy delta en ordonnée
 * @return -1 en cas d'échec, 0 sinon
 */
int move_pcamera(struct camera *cam, double dx, double dy);

/**
 * @brief Augmente la caméra dans le terminal
 *
 * @param cam Pointeur vers la caméra en question
 * @param dx delta en largeur
 * @param dy delta en hauteur
 * @return -1 en cas d'échec, 0 sinon
 */
int grow_tcamera(struct camera *cam, int dx, int dy);

#endif /* SIGCONSOLE_H */
// Path: sig-console.c
