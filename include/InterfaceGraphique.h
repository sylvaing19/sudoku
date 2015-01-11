#ifndef INTERFACEGRAPHIQUE_H
#define INTERFACEGRAPHIQUE_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_getenv.h>
#include <SDL_video.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_rotozoom.h>
#include <string>



class InterfaceGraphique
{
    public:
        //constructeur
        InterfaceGraphique();

        //initialisation des differentes positions
        SDL_Rect positionTitre, positionBoutonQuitter,positionFond,positionAuRevoir;
        SDL_Rect positionMenu1,positionMenu2,positionMenu3;
        SDL_Rect positionTexteMenu1, positionTexteMenu2, positionTexteMenu3;

        //Recupere les données d'affichage
        const SDL_VideoInfo* info;

        //initialisation des surfaces (images)
        SDL_Surface *imageFond = NULL, *arret = NULL, *fond = NULL, *rotation = NULL, *texteTitre = NULL;
        SDL_Surface *boutonMenu1=NULL, *boutonMenu2=NULL, *boutonMenu3=NULL, *texteMenu1=NULL, *texteMenu2=NULL, *texteMenu3=NULL;
        SDL_Surface *textePret=NULL, *textePretAussi=NULL,*texteAdieu=NULL;

        //initialisation des polices
        TTF_Font *policeTitre= NULL, *policeMenu = NULL, *policeAuRevoir=NULL;

        //creation des evenements
        SDL_Event event;

        //diffferentes couleurs en RGB
        SDL_Color  couleurN = {255, 255, 255};
        SDL_Color  couleurB = {0, 0, 255};
        SDL_Color  couleurV = {0, 255, 0};
        SDL_Color  couleurR = {255, 0, 0};
        SDL_Color  couleurGri = {200, 240, 255};

        //booleens pour quitter l'appli
        bool continuerEvent;
        bool quitterAppli;

        //taille des boutons / images
        int tailleX;
        int tailleY;
        int tailleXArret;
        int tailleYArret;
        int tailleXMenu;
        int tailleYMenu;

        //zoom : gestion des differences de reslotion et taille d'ecran
        double zoomX,zoomY;

        std::string nomImageFond;

        //prototypes de fonction
        void initPositions();
        void initPolices();
        void initTout();
        void afficherFixe();
        void initImages();
        void intro();
        void menu();
        void afficherBoutons();
        void quitter();
        void chargerMenu();


    private:

};

#endif // INTERFACEGRAPHIQUE_H
