#ifndef _BOMBE_H_
#define _BOMBE_H_

#include "Affichage.h"

/* Une bombe ennemie (descend vers le canon) */
typedef struct Bombe {
    int x, y;           /* position (ligne, colonne) */
    struct Bombe *suiv;
} Bombe;

typedef struct {
    Bombe *tete;
    int ymax;           /* ligne max (bas de l'ecran, zone canon) */
} Liste_Bombe;

Liste_Bombe* Liste_Bombe_initialiser_vide(int hauteur_aff);
void Bombe_desallouer(Liste_Bombe **Lbombe);
void ajouter_bombe(Liste_Bombe *Lbombe, int x, int y);
void Bombe_action(Liste_Bombe *Lbombe);
void Bombe_afficher(Liste_Bombe *Lbombe, Affichage *A);

/* Verifie si une bombe touche le canon, retourne 1 si touche */
int Interaction_Bombe_Canon(Liste_Bombe *Lbombe, int canon_x, int canon_y, int canon_l, int canon_h);

#endif
