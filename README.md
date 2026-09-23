Title: Duck Shooting Game
Authors: Rayan REMILI and Ahcene ZOUAGUI

Program Description:
A text-based shooting game played in the terminal. A cannon moves horizontally
at the bottom of the screen. Targets move across the screen from left to right
or from right to left. The player shoots darts to destroy them.

Part A (Level 1):
Targets are displayed as ">>>" or "<<<" depending on their movement direction.
The player shoots "^" darts using the SPACE key. A reload delay of 8 iterations
prevents continuous shooting. Victory is achieved after destroying 10 targets.

Part B (Level 2+) – Targets Fight Back:
In addition to the basic gameplay, the targets shoot "v" bombs downward toward
the cannon. The player has 3 lives, displayed in the top-left corner as hearts.
Each bomb that hits the cannon costs one life. The game ends in defeat if all
lives are lost.

Installation: Use the make command to build the project using the Makefile.
Dependency: libncurses (sudo apt-get install libncurses5-dev libncursesw5-dev)

Usage: ./main_jeu <width> <height> <difficulty level> <width>   width of the game screen (at least 30) <height>  height of the game screen (at least 20) <level>   1 = Part A, 2+ = Part B (the higher the level, the more targets
there are and the faster they shoot)

Examples:
./main_jeu 80 40 1   -> Part A
./main_jeu 80 40 2   -> Part B
./main_jeu 80 40 3   -> Part B, hard difficulty

Important: To play on a large screen (for example, 200 100), enlarge the
terminal window and reduce the font size (CTRL-).

Controls:
Left arrow   : move the cannon to the left
Right arrow  : move the cannon to the right
SPACE        : shoot (reload delay between each shot)
ESC          : quit the game

Files:
Affichage.h / Affichage.c  : display grid management (provided)
Canon.h / Canon.c          : player cannon (provided)
Flechette.h / Flechette.c  : linked list of darts + cooldown (Ex. 1)
Canard.h / Canard.c        : linked list of targets (Ex. 2)
Bombe.h / Bombe.c          : linked list of enemy bombs (Part B)
main_jeu.c                 : event loop, collisions, score, lives

End of the Game: ESC key, victory (10 targets destroyed), or defeat (Part B).

Difficulties Encountered:
The coordinate system (x = row, y = column) caused a bug in collision detection
between darts and targets. This was fixed by carefully checking the x/y fields
of each struct.
