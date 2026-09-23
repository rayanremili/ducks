#include <stdlib.h>
#include <string.h>
#include "Bombe.h"

/* Bombe tiree par un canard, descend vers le canon */

Liste_Bombe* Liste_Bombe_initialiser_vide(int hauteur_aff){
    Liste_Bombe *L = malloc(sizeof(Liste_Bombe));
    L->tete = NULL;
    L->ymax = hauteur_aff - 2;
    return L;
}

void Bombe_desallouer(Liste_Bombe **Lbombe){
    Bombe *tmp;
    while((*Lbombe)->tete != NULL){
        tmp = (*Lbombe)->tete;
        (*Lbombe)->tete = tmp->suiv;
        free(tmp);
    }
    free(*Lbombe);
    *Lbombe = NULL;
}

void ajouter_bombe(Liste_Bombe *Lbombe, int x, int y){
    Bombe *b = malloc(sizeof(Bombe));
    b->x = x;
    b->y = y;
    b->suiv = Lbombe->tete;
    Lbombe->tete = b;
}

void Bombe_action(Liste_Bombe *Lbombe){
    Bombe *curr = Lbombe->tete;
    Bombe *prev = NULL;

    while(curr != NULL){
        curr->x++; /* descend d'une case */

        /* supprime si elle touche le bas de l'ecran */
        if(curr->x >= Lbombe->ymax){
            if(prev == NULL){
                Lbombe->tete = curr->suiv;
                free(curr);
                curr = Lbombe->tete;
            } else {
                prev->suiv = curr->suiv;
                free(curr);
                curr = prev->suiv;
            }
        } else {
            prev = curr;
            curr = curr->suiv;
        }
    }
}

void Bombe_afficher(Liste_Bombe *Lbombe, Affichage *A){
    Bombe *b = Lbombe->tete;
    while(b != NULL){
        if(b->x >= 0 && b->x < A->H && b->y >= 0 && b->y < A->L)
            strcpy(A->tab[b->x][b->y], "\33[35mv");
        b = b->suiv;
    }
}

/* Retourne 1 si une bombe touche le canon et la supprime, 0 sinon */
int Interaction_Bombe_Canon(Liste_Bombe *Lbombe, int canon_x, int canon_y, int canon_l, int canon_h){
    Bombe *curr = Lbombe->tete;
    Bombe *prev = NULL;

    while(curr != NULL){
        /* le canon occupe les lignes [canon_x-2 .. canon_x+canon_h-1] et les colonnes [canon_y .. canon_y+canon_l-1] */
        int touche = (curr->x >= canon_x - 2 && curr->x < canon_x + canon_h && curr->y >= canon_y     && curr->y < canon_y + canon_l);

        if(touche){
            if(prev == NULL){
                Lbombe->tete = curr->suiv;
                free(curr);
                curr = Lbombe->tete;
            } else {
                prev->suiv = curr->suiv;
                free(curr);
                curr = prev->suiv;
            }
            return 1;
        } else {
            prev = curr;
            curr = curr->suiv;
        }
    }
    return 0;
}
