/**
*	Header de la grrille graphique
*	 @author Théo
*	 @file hearders/GrilleGrahique.h
*/

#ifndef GRILLEGRAPHIQUE_H
#define GRILLEGRAPHIQUE_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <SDL_rotozoom.h>
#include "Grille.h"
#include "Bouton.h"
#include <time.h>

class GrilleGraphique
{
	public:
		/** Constructeur, initialise les couleurs, quelques positions */
        GrilleGraphique();

	private:
        //position des objets
        SDL_Rect positionFond;// position du fond : 0,0
        SDL_Rect positionSudoku;
		SDL_Rect positionSudokuVierge;

	public:

		bool erreurExistante; // booleen verifiant l'existance d'une erreur dans la grille graphique
        //images
        SDL_Surface* fond=NULL; //image du fond
		SDL_Surface *imageSudokuVierge = NULL; // image du sudoku vierge

        //taille des boutons / sudoku
        int tailleX;
        int tailleY;

        //zoom : gestion des differences de reslotion et taille d'ecran
        double zoomX,zoomY;

	private:
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

	public:
        ///La grille en elle meme : on la charge arès les algorithmes, cette classe ne fais qu'afficher  / gerer les clics
        Grille grille;
		Grille grilleResolue;

		/// Array contenant les boutons et les valeurs des cases de sudoku
		std::array<std::array< Bouton , 9>, 9>  sudokuBouton;

        ///prototypes de fonctions
        /** affiche la grille en version Graphique, prete à etre flippée	*/
        void creerGrilleGraph();
		/** affiche la grille en version Graphique, prete à etre flippée avec les cases fausses en rouge !	*/
		void afficherGrilleGraphIndice();

		/**	créé une grille partir d'un fichier texte	*/
		void creerGrilleGraphFichier();

		/** affiche la grille graphique qui doit avoir été bien initialisée*/
		void afficherGrille();

		/** affiche uniquement l'indice */
		void afficherIndice();



	private :
		/**	créé un bouton avec la valeur v a l'interieur
		*  @param le nombre ecrit sur le bouton
		*  @return le nouveau bouton le remplacant
		*/
		Bouton creerBouton(int v);
};

#endif // GRILLEGRAPHIQUE_H
