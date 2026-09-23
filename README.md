Titre: Jeu de Tir aux Canards
Auteurs: Rayan REMILI (12510125) et Ahcene ZOUAGUI (12504142)

Description du programme:
Jeu de tir en mode texte dans le terminal. Un canon se déplace horizontalement
en bas de l'écran. Des cibles traversent l'écran de gauche à droite ou de
droite à gauche. Le joueur tire des fléchettes pour les abattre.

Partie A (niveau 1) :
Les cibles sont affichées en ">>>" ou "<<<" selon leur direction de déplacement.
Le joueur tire des fléchettes "^" avec ESPACE. Un délai de rechargement de 8
itérations empêche de tirer en continu. La victoire est atteinte à 10 cibles
abattues.

Partie B (niveau 2+) - les cibles ripostent :
En plus du jeu de base, les cibles tirent des bombes "v" vers le bas en
direction du canon. Le joueur dispose de 3 vies, affichées en haut à gauche
sous forme de coeurs. Chaque bombe qui touche le canon coûte une vie. La partie
se termine par une défaite si toutes les vies sont perdues.

Installation: Utiliser la commande make pour utiliser le Makefile
Dépendance: libncurses (sudo apt-get install libncurses5-dev libncursesw5-dev)

Usage: ./main_jeu <largeur> <hauteur> <niveau de difficulté>
  <largeur>  largeur de l'écran de jeu (au moins 30)
  <hauteur>  hauteur de l'écran de jeu (au moins 20)
  <niveau>   1 = Partie A, 2+ = Partie B (plus le niveau est élevé, plus
             les cibles sont nombreuses et tirent vite)

Exemples:
  ./main_jeu 80 40 1   -> Partie A
  ./main_jeu 80 40 2   -> Partie B
  ./main_jeu 80 40 3   -> Partie B niveau difficile

Important: pour jouer sur un grand écran (200 100 par ex), agrandir la fenêtre
du terminal et réduire la police (CTRL-)

Contrôles:
  Flèche gauche  : déplacer le canon à gauche
  Flèche droite  : déplacer le canon à droite
  ESPACE         : tirer (délai de rechargement entre chaque tir)
  ESC            : quitter le jeu

Fichiers:
  Affichage.h / Affichage.c  : gestion de la grille d'affichage (fourni)
  Canon.h / Canon.c          : le canon du joueur (fourni)
  Flechette.h / Flechette.c  : liste chainée de fléchettes + cooldown (Ex. 1)
  Canard.h / Canard.c        : liste chainée de cibles (Ex. 2)
  Bombe.h / Bombe.c          : liste chainée de bombes ennemies (Partie B)
  main_jeu.c                 : boucle événementielle, collisions, score, vies

Fin du jeu: touche ESC, victoire (10 cibles abattues) ou défaite (Partie B)

Difficultés rencontrées:
Le sens des coordonnées (x=ligne, y=colonne) a causé un bug dans la détection
de collision entre fléchettes et cibles, corrigé en vérifiant soigneusement
les champs x/y de chaque struct.
