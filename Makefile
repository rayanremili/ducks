all: main_jeu

Affichage.o: Affichage.c Affichage.h
	gcc -c -Wall Affichage.c

Canon.o: Canon.c Canon.h Affichage.h
	gcc -c -Wall Canon.c

Canard.o: Canard.c Canard.h Affichage.h
	gcc -c -Wall Canard.c

Flechette.o: Flechette.c Flechette.h Affichage.h
	gcc -c -Wall Flechette.c

Bombe.o: Bombe.c Bombe.h Affichage.h
	gcc -c -Wall Bombe.c

main_jeu.o: main_jeu.c Affichage.h Canon.h Flechette.h Canard.h Bombe.h
	gcc -c -Wall main_jeu.c

main_jeu: main_jeu.o Affichage.o Canon.o Flechette.o Canard.o Bombe.o
	gcc -o main_jeu main_jeu.o Affichage.o Canon.o Flechette.o Canard.o Bombe.o -lncurses

clean:
	rm -fr *~ *.o main_jeu
