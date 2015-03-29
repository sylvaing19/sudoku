#Makefile du programme sudoku

#Liste des fichiers objet
OBJS=Bouton.o Grille.o GrilleGraphique.o InterfaceGraphique.o main.o

#Compilateur utilisé : GCC
CC=gcc

#Options de compilation
#Mode débug
CFLAGS=-Wall -g
#Mode release
#CFLAG=-Wall -O


main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lSDL -lSDLmain -lSDL_ttf -lSDL_gfx -lSDL_image -o -std=c++11 sudoku
Bouton.o: Bouton.h Bouton.cpp
Grille.o: Grille.h Grille.cpp
GrilleGraphique.o: GrilleGraphique.h GrilleGraphique.cpp Grille.h Bouton.h
InterfaceGraphique.o: InterfaceGraphique.h InterfaceGraphique.cpp Bouton.h Grille.h GrilleGraphique.h
main.o: main.cpp Grille.h InterfaceGraphique.h
clean:
	rm $(OBJS)
