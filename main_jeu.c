#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ncurses.h>
#include<string.h>

#include"Canon.h"
#include"Affichage.h"
#include"Flechette.h"
#include"Canard.h"
#include"Bombe.h"

// Liste des évènements possibles
enum evenement {CONTINUE, ECHAP, VICTOIRE, DEFAITE};
    // CONTINUE: le jeu debute ou continue
    // ECHAP: la touche ESC a été utilisée
    // VICTOIRE: 10 canards abattus
    // DEFAITE: le canon a perdu toutes ses vies (Partie B)

/* Coeur du jeu contenant la boucle événementielle */
void Jeu_Tir(int tailleL, int tailleH, int nivdiff);





/* Supprime les flechettes et canards en collision, retourne le nombre de touches */
int Interaction_Flechette_Canard(Liste_Flechette *Lflech, Liste_Canard *Lcanard){
    int nb_touches = 0;
    Flechette *f = Lflech->tete;
    Flechette *f_prev = NULL;

    while(f != NULL){
        int touche = 0;
        Canard *c = Lcanard->tete;
        Canard *c_prev = NULL;

        while(c != NULL && !touche){
            /* canard : x=colonne de depart, y=ligne ; flechette : x=ligne, y=colonne */
            if(f->x == c->y && f->y >= c->x && f->y < c->x + Lcanard->largeur){
                touche = 1;
                nb_touches++;
                if(c_prev == NULL) Lcanard->tete = c->suiv;
                else               c_prev->suiv = c->suiv;
                free(c);
                Lcanard->nb--;
            } else {
                c_prev = c;
                c = c->suiv;
            }
        }

        if(touche){
            if(f_prev == NULL){ Lflech->tete = f->suiv; free(f); f = Lflech->tete; }
            else               { f_prev->suiv = f->suiv; free(f); f = f_prev->suiv; }
        } else {
            f_prev = f;
            f = f->suiv;
        }
    }
    return nb_touches;
}

/* Affiche les vies restantes sous forme de coeurs en haut a gauche */
void afficher_vies(Affichage *A, int vies, int ligne, int col_debut){
    int i;
    for(i = 0; i < vies; i++){
        if(col_debut + i*2 < A->L - 1)
            strcpy(A->tab[ligne][col_debut + i*2], "\33[31m\xE2\x99\xA5");
    }
}





int main(int argv, char **argc){

  if (argv!=4){
     printf("Usage: %s <largeur> <hauteur> <niveau de difficulté>\n",argc[0]);
     printf("  Niveau 1 = Partie A (tir aux canards)\n");
     printf("  Niveau 2+ = Partie B (les canards ripostent !)\n");
     exit(2);
  }
  srand(time(NULL));

  Jeu_Tir(atoi(argc[1]), atoi(argc[2]), atoi(argc[3]));
  
  return EXIT_SUCCESS;
  
}




void Jeu_Tir(int tailleL, int tailleH, int nivdiff){

  int ch;   /* Récupération de la saisie clavier, valeur # pour fin de jeu */
  enum evenement res; /* Retour des évènements  */
  int score = 0;
  int compteur = 0;
  int score_victoire = 10;

  /* Partie B active si niveau >= 2 */
  int mode_riposte = (nivdiff >= 2);
  int vies = 3;

  /* Les canards apparaissent plus vite selon le niveau */
  int freq_canard = 25 - nivdiff * 2;
  if(freq_canard < 8) freq_canard = 8;

  /* En Partie B, les canards tirent toutes les freq_tir_ennemi iterations */
  int freq_tir_ennemi = 30 - nivdiff * 3;
  if(freq_tir_ennemi < 10) freq_tir_ennemi = 10;

  /* Initialisation de ncurses et du clavier */
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  halfdelay(1);  /* Temps d'exécution max de getch à 1/10ème de seconde */
  
  /* Initialisation des éléments du jeu */
  
  res= CONTINUE;
  
  Affichage *A=Affichage_initialiser(tailleL, tailleH);  

  Canon *C = Canon_initialiser(0, tailleL, tailleH);
  enum action_canon actC;

  Liste_Flechette *Lflech = Liste_Flechette_initialiser_vide(tailleH, nivdiff);
  Liste_Flechette_set_bornes(Lflech, 1, tailleL - 2);

  Liste_Canard *Lcanard = Liste_Canard_initialiser_vide(tailleL, tailleH, nivdiff, NULL);

  Liste_Bombe *Lbombe = NULL;
  if(mode_riposte)
      Lbombe = Liste_Bombe_initialiser_vide(tailleH);

  
  /* Boucle événementielle du jeu */ 
  do{
  
    ch = getch(); /* Si aucune touche utilisée, getch renvoie -1 */
    compteur++;

    /* Apparition periodique de nouveaux canards */
    if(compteur % freq_canard == 0)
        ajouter_canard(Lcanard);

    Canard_action(Lcanard);
    Flechette_action(Lflech);

    /* Partie B : tir des canards et collision avec le canon */
    if(mode_riposte && Lbombe != NULL){
        if(compteur % freq_tir_ennemi == 0 && Lcanard->tete != NULL){
            Canard *tireur = Lcanard->tete;
            ajouter_bombe(Lbombe, tireur->y, tireur->x + Lcanard->largeur / 2);
        }
        Bombe_action(Lbombe);
        if(Interaction_Bombe_Canon(Lbombe, C->xpos, C->ypos, C->largeur, C->hauteur)){
            vies--;
            if(vies <= 0) res = DEFAITE;
        }
    }

    score += Interaction_Flechette_Canard(Lflech, Lcanard);
    if(score >= score_victoire) res = VICTOIRE;

    Affichage_vider(A);
    Affichage_cadre(A);
    if(mode_riposte) afficher_vies(A, vies, 1, 2);
    Canon_afficher(C, A);   
    Canard_afficher(Lcanard, A);
    Flechette_afficher(Lflech, A); 
    if(mode_riposte && Lbombe != NULL) Bombe_afficher(Lbombe, A);
    Affichage_dessiner(A);

    if(mode_riposte)
        printf("[ RIPOSTE ] Score: %d/%d | Vies: %d | Canards: %d | ESPACE=tirer (ESC pour Sortir)\33[1E",
               score, score_victoire, vies, Lcanard->nb);
    else
        printf("Pour jouer: utiliser les flèches, SPACE pour tirer (ESC pour Sortir)\33[1E\33[1E");
    fflush(stdout);  /* Force l'affichage complet */

      
    if ( ch!=-1 ){ /* Si une touche a été appuyée */

     switch(ch) {  
        case 27:  /* Code ASCII de la touche ESC-Echap */
           res=ECHAP;
           break;                  
        case KEY_LEFT: 
           actC = Gauche_canon;
           break; 
        case KEY_RIGHT: 
           actC = Droite_canon;
           break;
        case 32:  /* Code ASCII de la touche ESPACE */
           ajouter_flechette(Lflech, C->xpos - 3, C->ypos + C->largeur/2);
           break;        
        default:
           break;           
       }
               
       if (res!=ECHAP && res!=VICTOIRE && res!=DEFAITE){
	 // Zone des actions dirigeant un élément
          Canon_action(C, actC);      
       }
           
     }
     
     // Zone des actions d'éléments agissant automatiquement

  } while (res== CONTINUE);
  
     
  if (res==ECHAP)
      printf("\n\nVous avez taper ESC pour sortir. \33[1E\n");
  else if(res==VICTOIRE)
      printf("\n\n  *** VICTOIRE ! %d canards abattus ! ***\33[1E\n", score);
  else if(res==DEFAITE)
      printf("\n\n  *** DEFAITE... Score: %d/%d ***\33[1E\n", score, score_victoire);

  printf("\33[1EAppuyez sur une touche pour sortir\33[1E\n");          
  do{
      ch = getch();
  }while(ch==-1);
  

  endwin(); /* Doit obligatoirement etre mis en fin de programme pour remettre le terminal en etat */  
  
  Affichage_desallouer(&A);  
  Canon_desallouer(&C);
  Flechette_desallouer(&Lflech);
  Canard_desallouer(&Lcanard);
  if(mode_riposte && Lbombe != NULL) Bombe_desallouer(&Lbombe);
  
}
