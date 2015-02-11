#ifndef INTERFACEGRAPHIQUE_H
#define INTERFACEGRAPHIQUE_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_getenv.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_rotozoom.h>
#include <string>
#include "Bouton.h"



class InterfaceGraphique
{
    public:
        ///constructeur
        InterfaceGraphique();

        ///initialisation des differentes positions
        SDL_Rect positionTitre, positionBoutonQuitter,positionFond,positionAuRevoir;
        SDL_Rect positionMenu1,positionMenu2,positionMenu3;
        SDL_Rect positionTexteMenu1, positionTexteMenu2, positionTexteMenu3;
        SDL_Rect positionSudoku;

        ///Recupere les données d'affichage
        const SDL_VideoInfo* info;

        ///initialisation des surfaces (images)
        SDL_Surface *imageFond = NULL, *fond = NULL, *rotation = NULL, *titre = NULL;
        SDL_Surface *textePret=NULL, *textePretAussi=NULL,*texteAdieu=NULL,*imageTitre;


        ///initialisation des polices
        TTF_Font *policeTitre= NULL,*policeAuRevoir=NULL, *policeSudoku=NULL;

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

        ///liste des boutons apppartenant à ce menu

        ///taille des boutons / images
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



        ///prototypes de fonction

        ///initialise les differentes polices utilisées
        void initPolices();
        ///initialise le titre affiché
        void initTitre();
        ///initialise les boutons  du menu Principal
        void initBoutonsMenuPrincipal();

        ///initialise l'interface : menu principal, et effectue tout ce qui le concerne
        void menuPrincipal();

        ///animation d'introduction
        void intro();

        ///fonction quitter , quitte la SDL et l'application
        void quitter();

        ///charge le menu dans le buffer, pret à etre affiché
        void chargerFondMenuPrincipal();
        ///charge le titre dans le buffer, pret à etre affiché
        void chargerTitre();
        ///charge les boutons du menu Principal
        void chargerBoutonsMenuPrincipal();

        ///fonction gerant les evenements du menu Prrincipal : clics, touches...
        void eventMenuPrincipal();

    private:
        //les differents boutons, cliquables ou non, avec action ou non, utilisés

        ///boutons du menu principal
        Bouton boutonMenu1;
        Bouton boutonMenu2;

        ///bouton quitter, commun à tous les menus
        Bouton boutonQuitter;

};

#endif // INTERFACEGRAPHIQUE_H
