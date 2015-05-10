/**
*	Header de l'INTerface graphique
*	 @author Théo
*	 @file hearders/InterfaceGraphique.h
*/


#ifndef INTERFACEGRAPHIQUE_H
#define INTERFACEGRAPHIQUE_H

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_getenv.h>
#include <SDL_rotozoom.h>

#include "Bouton.h"
#include "Grille.h"
#include "GrilleGraphique.h"
#include "Score.h"
#include "EnumDifficulte.h"


class InterfaceGraphique
{
    public:
        /** constructeur : gere l'initialisation de la SDL et des couleurs	*/
        InterfaceGraphique();

	private :
        ///declaration des differentes positions
        SDL_Rect positionTitre, positionBoutonQuitter,positionFond,positionAuRevoir;
		SDL_Rect positionMenu1, positionMenu2, positionMenu3;
        SDL_Rect positionTexteMenu1, positionTexteMenu2, positionTexteMenu3;
		SDL_Rect positionSudoku, positionEntrezUnChiffre, positionCliquezSurUneCase, positionPasSolvable;
		SDL_Rect positionImageUser, positionEntrezImage;
		SDL_Rect positionArtifice,positionArtifice2,positionArtifice3,positionArtifice4;
		SDL_Rect positionScore;
        SDL_Rect positionEasy, positionMedium, positionHard;


        ///Recupere les données d'affichage
        const SDL_VideoInfo* infosUser;

        ///declaration des surfaces (images)
		SDL_Surface *imageFond, *fond, *rotation, *titre;
		SDL_Surface *textePret, *textePretAussi, *texteAdieu, *imageTitre;
		SDL_Surface *texteEntreUnChiffre, *texteCliquezSurUneCase, *textePasSolvable;
		SDL_Surface *texteEntrezImage;
		SDL_Surface *imageSudokuUser, *texteScore, *texteHard, *texteEasy, *texteMedium;


        ///initialisation des polices
		TTF_Font *policeTitre, *policeAuRevoir, *policeSudoku, *policeEntrezUnChiffre, *policePasSolvable, *policeScore;

        ///creation des evenements
        SDL_Event event;

        ///diffferentes couleurs en RGB
        SDL_Color  couleurN;
        SDL_Color  couleurB;
        SDL_Color  couleurV;
        SDL_Color  couleurR;
        SDL_Color  couleurGri;

        ///booleens pour quitter l'appli
        bool continuerEvent;
        bool quitterAppli;
		bool continuerEventChangerValeur;//booleen gerant l'evenement de changement de valeur d'une case

        ///liste des boutons apppartenant à ce menu

        ///taille des boutons / images necesseaires, transferées d'une classe à l'autre
		int tailleX;
        int tailleY;
        int tailleXMenu;
        int tailleYMenu;

        ///zoom : gestion des differences de reslotion et taille d'ecran
        double zoomX,zoomY;

        ///string d'entrée
		std::string nomImageFond, texteTitre, nomImageUser;

        /// tableau pour le gif animé de feu d'artifice
        std::array< SDL_Surface* , 18> artifice;
        std::string nomImageArtifice;


	public:
        ///Constante permettant de savoir le prochain menu affiché
        std::string menuACreer;

	private:
        /// booleens divers
		bool sudokuApparaitAleatoire, sudokuAResoudre, sudokuVide, caseSuivante;

		/// nombre d'indices, de vies que l'user a
		int nombreVies;

        ///prototypes de fonction

        /**	initialise les differentes polices utilisées	*/
        void initPolices();
		/**	initialise le titre affiché		*/
        void initTitre();
        /**	initialise les boutons  du menu Principal		*/
        void initBoutonsMenuPrincipal();
        /**	initialise les boutons  du menu resoudre	*/
        void initBoutonsMenuResoudre();
        void initFondZoomTailleBouton(Bouton & bouton);
        void initFondZoomTailleGrilleGraph(GrilleGraphique & grilleGraphique);

	public:
        /**	initialise le menu principal, et effectue tout ce qui le concerne	*/
        void menuPrincipal();

        /** initialise le menu resoudre, effectue tout ce qui le concerne */
        void menuResoudre();

		/** initialise le menu photo-doku et tout ce qui s'y rapporte	*/
		void menuPhoto();

        /** animation de fin, quand on a resolu la grille */
        void animationFin();


	private:
        /**	animation d'introduction	*/
        void intro();

        /** fonction quitter , quitte la SDL et l'application */
        void quitter();

		/** Pareil mais pour la reussite */
		void grilleFinie();



        /** initialise et charge le menu dans le buffer, pret à etre affiché */
        void chargerFond();
        /**	charge le titre dans le buffer, pret à etre affiché */
        void chargerTitre();
        /** charge les boutons du menu Principal */
        void chargerBoutonsMenuPrincipal();

		/** affiche la grille entrée par l'utilisateur	*/
		void afficherImageUser();

        /** fonction gerant les evenements du menu Principal : clics, touches... */
        void eventMenuPrincipal();
        /** fonction gerant les evenements du menu Resoudre : clics, touches... */
        void eventMenuResoudre();
			/** fonction gerant les evenements du menu Resoudre Aleatoirement: clics, touches... */
            void eventMenuResoudreAleatoire();
			/** fonction gerant les evenements du menu Resoudre une grille vide: clics, touches... */
            void eventMenuResoudreVideManuelle();

	public:
        /**	fait apparaitre une grille aleatoire	*/
        void grilleAleatoire();
        /**	fait apparaitre une grille vide à remplir */
        void grilleVide();

        /**	resoud la grille et l'affiche */
        void resoudre();
	private:
		/**	change la valeur d'une case donnée
		*  @param le bouton a changer
		*  @return le nouveau bouton le remplacant
		*/
		Bouton eventChangerValeur(Bouton bouton);

		/** affiche le texte demandant à l'user de rentrer un chiffre	*/
		void afficherEntrezUnChiffre();
		/** affiche le texte demandant à l'user de cliquer	*/
		void afficherCliquezSurUneCase();
		/**	affiche le texte "désolé, c'est pas solvable" */
		void afficherPasSolvable();

		/** gere les boutons et leurrs effets au clic de l'user
		*  @param le bouton a verifier
		*  @return le nouveau bouton le remplacant
		*/
		Bouton eventBoutonClique(Bouton bouton);

		/** gere l'apparition d'indices pour l'user	*/
		void indice();

		/** gestion du score */
        Score score;
        Difficulte difficulte;


        //les differents boutons, cliquables ou non, avec action ou non, utilisés

        ///boutons du menu principal
        Bouton boutonMenu1;
        Bouton boutonMenu2;

        ///bouton quitter, commun à tous les menus
        Bouton boutonQuitter;

        /// boutons pour le menu Resolution
        Bouton boutonAleatoire;
        Bouton boutonManuel;
		Bouton boutonIndice;

        ///boutons de difficulté
        Bouton boutonEasy;
        Bouton boutonMedium;
        Bouton boutonHard;

        //les grilles, vides ou non

        ///Grilles algorithmiques
        Grille grille;
		Grille grilleResolue;

        ///grille utilisée par la partie graphique
        GrilleGraphique grilleGraphiqueAleatoire;
		GrilleGraphique grilleGraphiqueResolue;
		GrilleGraphique grilleGraphiqueVide;

		///grille generique
		GrilleGraphique grilleGraph;
};

#endif // INTERFACEGRAPHIQUE_H
