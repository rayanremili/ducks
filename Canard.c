#include <stdlib.h>
#include <string.h>
#include "Canard.h"

/* Canard affiché en ">>>" ou "<<<" selon sa direction, taille 3x1 */

Liste_Canard* Liste_Canard_initialiser_vide(int largeur_aff, int hauteur_aff, int nivdiff, char *nomfic){
    Liste_Canard *L = malloc(sizeof(Liste_Canard));
    L->tete = NULL;
    L->nb = 0;
    L->nb_max = 2 + nivdiff;
    L->pas = 1;
    L->largeur = 3;
    L->hauteur = 1;
    L->x_min = 1;
    L->x_max = largeur_aff - L->largeur - 1;
    L->y_min = 1;
    L->y_max = hauteur_aff - 8; /* on laisse de la place pour le canon en bas */
    return L;
}

void Canard_desallouer(Liste_Canard **Lcanard){
    Canard *tmp;
    while((*Lcanard)->tete != NULL){
        tmp = (*Lcanard)->tete;
        (*Lcanard)->tete = tmp->suiv;
        free(tmp);
    }
    free(*Lcanard);
    *Lcanard = NULL;
}

void ajouter_canard(Liste_Canard *Lcanard){
    if(Lcanard->nb >= Lcanard->nb_max) return;

    Canard *c = malloc(sizeof(Canard));
    c->direction = (rand() % 2 == 0) ? 1 : -1;

    /* part du bord gauche s'il va a droite, du bord droit sinon */
    c->x = (c->direction == 1) ? Lcanard->x_min : Lcanard->x_max;

    if(Lcanard->y_max > Lcanard->y_min)
        c->y = Lcanard->y_min + rand() % (Lcanard->y_max - Lcanard->y_min);
    else
        c->y = Lcanard->y_min;

    c->suiv = Lcanard->tete;
    Lcanard->tete = c;
    Lcanard->nb++;
}

void Canard_afficher(Liste_Canard *Lcanard, Affichage *A){
    Canard *c = Lcanard->tete;
    int j;
    while(c != NULL){
        for(j = 0; j < Lcanard->largeur; j++){
            int col = c->x + j;
            int row = c->y;
            if(row >= 0 && row < A->H && col >= 0 && col < A->L){
                if(c->direction == 1)
                    strcpy(A->tab[row][col], "\33[33m>");
                else
                    strcpy(A->tab[row][col], "\33[33m<");
            }
        }
        c = c->suiv;
    }
}

void Canard_action(Liste_Canard *Lcanard){
    Canard *curr = Lcanard->tete;
    Canard *prev = NULL;

    while(curr != NULL){
        curr->x += Lcanard->pas * curr->direction;

        /* supprime le canard s'il est sorti de l'ecran */
        int sorti = (curr->x < Lcanard->x_min - Lcanard->largeur) ||
                    (curr->x > Lcanard->x_max + Lcanard->largeur);

        if(sorti){
            Lcanard->nb--;
            if(prev == NULL){
                Lcanard->tete = curr->suiv;
                free(curr);
                curr = Lcanard->tete;
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
