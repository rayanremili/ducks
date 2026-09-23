#ifndef _FLECHETTE_H_
#define _FLECHETTE_H_

#include "Affichage.h"

typedef struct Flechette {
    int x, y;
    struct Flechette *suiv;
} Flechette;

typedef struct {
    Flechette *tete;
    int ymax;           /* ligne min (haut de l'ecran) */
    int depart_x;       /* ligne de depart */
    int x_min, x_max;  /* bornes colonnes (pour rebond partie B) */
    int cooldown;       /* iterations restantes avant de pouvoir retirer */
    int cooldown_max;   /* duree du cooldown (ex: 5 iterations) */
} Liste_Flechette;

Liste_Flechette* Liste_Flechette_initialiser_vide(int hauteur_aff, int nivdiff);
void Liste_Flechette_set_bornes(Liste_Flechette *Lflech, int x_min, int x_max);
void Flechette_desallouer(Liste_Flechette **Lflech);
int  ajouter_flechette(Liste_Flechette *Lflech, int x, int y); /* retourne 1 si ok, 0 si cooldown */
void Flechette_action(Liste_Flechette *Lflech);
void Flechette_afficher(Liste_Flechette *Lflech, Affichage *A);

#endif
