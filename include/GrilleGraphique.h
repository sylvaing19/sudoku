#ifndef GRILLEGRAPHIQUE_H
#define GRILLEGRAPHIQUE_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <SDL_rotozoom.h>
#include "Grille.h"

class GrilleGraphique
{
    public:
        GrilleGraphique();

        //position des objets
        SDL_Rect positionFond;// position du fond : 0,0
        SDL_Rect positionSudoku;

        //images
        SDL_Surface* fond=NULL; //image du fond

        //taille des boutons / sudoku
        int tailleX;
        int tailleY;

        //zoom : gestion des differences de reslotion et taille d'ecran
        double zoomX,zoomY;

        //taille de la police des chiffres
        int taillePolice;

        //police
        TTF_Font *policeSudoku=NULL;

        //diffferentes couleurs en RGB
        SDL_Color  couleurN;
        SDL_Color  couleurB;
        SDL_Color  couleurV;
        SDL_Color  couleurR;
        SDL_Color  couleurGri;

        ///La grille en elle meme : on la charge arès les algorithmes, cette classe ne fais qu'afficher  / gerer les clics
        Grille grille;

        ///prototypes de fonctions
        // affiche la grille en version Graphique, prete à etre flippée
        void afficherGrilleGraph();



};

#endif // GRILLEGRAPHIQUE_H
