#Makefile du programme sudoku

#Liste des fichiers objet
OBJS=Bouton.o Grille.o GrilleGraphique.o InterfaceGraphique.o main.o

#Compilateur utilisé : GCC
CC=g++

#Options de compilation
#Mode débug
CFLAGS=-Wall -g -std=c++11
#Mode release
#CFLAG=-Wall -O


main: $(OBJS)
	$(CC) -I/usr/include/SDL $(CFLAGS) $(OBJS) -lSDL -lSDLmain -lSDL_ttf -lSDL_gfx -lSDL_image -o sudoku
Bouton.o: Bouton.h Bouton.cpp
Grille.o: Grille.h Grille.cpp
GrilleGraphique.o: GrilleGraphique.h GrilleGraphique.cpp Grille.h Bouton.h
InterfaceGraphique.o: InterfaceGraphique.h InterfaceGraphique.cpp Bouton.h Grille.h GrilleGraphique.h
main.o: main.cpp Grille.h InterfaceGraphique.h
clean:
	rm $(OBJS)
