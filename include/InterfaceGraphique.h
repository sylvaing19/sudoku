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


class InterfaceGraphique
{
    public:
        ///constructeur
        InterfaceGraphique();

        ///initialisation des differentes positions			// Ce commentaire est faux ! Tu n'initialise rien ici, et tu ne dois rien initialiser !
        SDL_Rect positionTitre, positionBoutonQuitter,positionFond,positionAuRevoir;
        SDL_Rect positionMenu1,positionMenu2,positionMenu3;
        SDL_Rect positionTexteMenu1, positionTexteMenu2, positionTexteMenu3;
		SDL_Rect positionSudoku, positionEntrezUnChiffre, positionCliquezSurUneCase, positionPasSolvable;

        ///Recupere les données d'affichage
        const SDL_VideoInfo* info;//nom dégeu !

        ///initialisation des surfaces (images)
		/*
		ON N'INITIALISE RIEN DANS LE .H !!!!!!
		L'initialisation se fait dans le constructeur.
		*/
        SDL_Surface *imageFond = NULL, *fond = NULL, *rotation = NULL, *titre = NULL;
		SDL_Surface *textePret = NULL, *textePretAussi = NULL, *texteAdieu = NULL, *imageTitre = NULL;
		SDL_Surface *texteEntreUnChiffre = NULL, *texteCliquezSurUneCase = NULL, *textePasSolvable = NULL;


        ///initialisation des polices
		/*
		Idem... 
		*/
		TTF_Font *policeTitre = NULL, *policeAuRevoir = NULL, *policeSudoku = NULL, *policeEntrezUnChiffre=NULL, *policePasSolvable=NULL;

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
		bool continuerEventChangerValeur;//C'est quoiiiii ???!

        ///liste des boutons apppartenant à ce menu

        ///taille des boutons / images
		/*
		Mais ça fout quoi là ça ???
		c'est des membres de la classe bouton !
		*/
        int tailleX;
        int tailleY;
        int tailleXMenu;
        int tailleYMenu;

        ///zoom : gestion des differences de reslotion et taille d'ecran
        double zoomX,zoomY;

        ///string d'entrée
        std::string nomImageFond, texteTitre;
        ///Constante permettant de savoir le prochain menu affiché
        std::string menuACreer;
		/*
		I see what you did here...
		Si tu veux régler les variables tailleX, tailleY, nomImage, etc...
		étape 1 : tu ajoute a la classe Bouton une méthode d'initialisation prenant en argument les variables qui t'intéressent
		étape 2 : tu as deux possibilitées
			soit tu as une fonction d'initialisation dans InterfaceGraphqie qui prendra en argument toutes les variables en question pour initialiser les boutons
			soit tu mets les attributs de type Bouton en public et tu fais interfaceGraphique.bouton1.init(nomImage, position, etc...);
		*/

        /// booleens divers
		bool sudokuApparaitAleatoire, sudokuAResoudre, sudokuVide,caseSuivante;

		/// nombre d'indices, de vies que l'user a
		int nombreVies;

        ///prototypes de fonction

        ///initialise les differentes polices utilisées
        void initPolices();
        ///initialise le titre affiché
        void initTitre();
        ///initialise les boutons  du menu Principal
        void initBoutonsMenuPrincipal();
        ///initialise les boutons  du menu resoudre
        void initBoutonsMenuResoudre();
        void initFondZoomTailleBouton(Bouton & bouton);
        void initFondZoomTailleGrilleGraph(GrilleGraphique & grilleGraphique);

        ///initialise le menu principal, et effectue tout ce qui le concerne
        void menuPrincipal();

        /// initialise le menu resoudre, effectue tout ce qui le concerne
        void menuResoudre();

        ///animation d'introduction
        void intro();

        ///fonction quitter , quitte la SDL et l'application
        void quitter();

        ///initialise et charge le menu dans le buffer, pret à etre affiché
        void chargerFond();
        ///charge le titre dans le buffer, pret à etre affiché
        void chargerTitre();
        ///charge les boutons du menu Principal
        void chargerBoutonsMenuPrincipal();

        ///fonction gerant les evenements du menu Principal : clics, touches...
        void eventMenuPrincipal();
        ///fonction gerant les evenements du menu Resoudre : clics, touches...
        void eventMenuResoudre();
            void eventMenuResoudreAleatoire();
            void eventMenuResoudreVideManuelle();
            void eventMenuResoudreGrilleVide();

        ///fait apparaitre une grille aleatoire
        void grilleAleatoire();
        ///fait apparaitre une grille vide à remplir
        void grilleVide();

        ///resoud la grille et l'affiche
        void resoudre();

		//change la valeur d'une case donnée
		Bouton eventChangerValeur(Bouton bouton);

		// affiche le texte demandant à l'user de rentrer un chiffre
		void afficherEntrezUnChiffre();
		// affiche le texte demandant à l'user de cliquer
		void afficherCliquezSurUneCase();
		//affiche le texte "désolé, c'est pas solvable"
		void afficherPasSolvable();

		// gere les boutons et leurrs effets au clic de l'user
		Bouton eventBoutonClique(Bouton bouton);

		// gere l'apparition d'indices pour l'user
		void indice();

    private:
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

        //les grilles, vides ou non

        ///Grille algorithmique
        Grille grille;

        ///grille utilisée par la partie graphique
        GrilleGraphique grilleGraphiqueAleatoire;
		GrilleGraphique grilleGraphiqueResolue;
		GrilleGraphique grilleGraphiqueVide;

		///grille generique
		GrilleGraphique grilleGraph;
};

#endif // INTERFACEGRAPHIQUE_H
