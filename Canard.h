#ifndef _CANARD_H_
#define _CANARD_H_

#include "Affichage.h"

typedef struct Canard {
    int x, y;              /* position : x=colonne, y=ligne */
    int direction;         /* +1 = droite, -1 = gauche */
    struct Canard *suiv;
} Canard;

typedef struct {
    Canard *tete;
    int nb;
    int nb_max;
    int pas;
    int largeur, hauteur;
    int x_min, x_max;     /* bornes horizontales (colonnes) */
    int y_min, y_max;     /* bornes verticales (lignes) pour apparition */
} Liste_Canard;

Liste_Canard* Liste_Canard_initialiser_vide(int largeur_aff, int hauteur_aff, int nivdiff, char *nomfic);
void Canard_desallouer(Liste_Canard **Lcanard);
void ajouter_canard(Liste_Canard *Lcanard);
void Canard_afficher(Liste_Canard *Lcanard, Affichage *A);
void Canard_action(Liste_Canard *Lcanard);

#endif
