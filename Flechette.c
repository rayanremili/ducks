#include <stdlib.h>
#include <string.h>
#include "Flechette.h"

Liste_Flechette* Liste_Flechette_initialiser_vide(int hauteur_aff, int nivdiff){
    Liste_Flechette *L = malloc(sizeof(Liste_Flechette));
    L->tete = NULL;
    L->ymax = 0;
    L->depart_x = hauteur_aff - 3;
    L->x_min = 1;
    L->x_max = 0;
    L->cooldown = 0;
    L->cooldown_max = 8;
    return L;
}

void Liste_Flechette_set_bornes(Liste_Flechette *Lflech, int x_min, int x_max){
    Lflech->x_min = x_min;
    Lflech->x_max = x_max;
}

void Flechette_desallouer(Liste_Flechette **Lflech){
    Flechette *tmp;
    while((*Lflech)->tete != NULL){
        tmp = (*Lflech)->tete;
        (*Lflech)->tete = tmp->suiv;
        free(tmp);
    }
    free(*Lflech);
    *Lflech = NULL;
}

/* Retourne 1 si le tir est effectue, 0 si le joueur tire trop vite */
int ajouter_flechette(Liste_Flechette *Lflech, int x, int y){
    if(Lflech->cooldown > 0) return 0;

    Flechette *f = malloc(sizeof(Flechette));
    f->x = x;
    f->y = y;
    f->suiv = Lflech->tete;
    Lflech->tete = f;

    Lflech->cooldown = Lflech->cooldown_max;
    return 1;
}

void Flechette_action(Liste_Flechette *Lflech){
    if(Lflech->cooldown > 0) Lflech->cooldown--;

    Flechette *curr = Lflech->tete;
    Flechette *prev = NULL;

    while(curr != NULL){
        curr->x--;

        /* supprime la flechette si elle atteint le bord haut */
        if(curr->x <= Lflech->ymax){
            if(prev == NULL){
                Lflech->tete = curr->suiv;
                free(curr);
                curr = Lflech->tete;
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

void Flechette_afficher(Liste_Flechette *Lflech, Affichage *A){
    Flechette *f = Lflech->tete;
    while(f != NULL){
        if(f->x >= 0 && f->x < A->H && f->y >= 0 && f->y < A->L)
            strcpy(A->tab[f->x][f->y], "\33[41m^");
        f = f->suiv;
    }
}
