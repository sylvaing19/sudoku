#ifndef INTERFACEGRAPHIQUE_H
#define INTERFACEGRAPHIQUE_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_getenv.h>

class InterfaceGraphique
{
    public:
        InterfaceGraphique();

        //initialisation des differentes positions
        SDL_Rect positionTitre, positionBoutonQuitter,positionFond,positionAuRevoir;
        SDL_Rect positionMenu1,positionMenu2,positionMenu3;
        SDL_Rect positionTexteMenu1, positionTexteMenu2, positionTexteMenu3;

        //initialisation des surfaces (images)
        SDL_Surface *imageFond = NULL, *arret = NULL, *fond = NULL, *texteTitre = NULL;
        SDL_Surface *boutonMenu1=NULL,*boutonMenu2=NULL,*boutonMenu3=NULL,*texteMenu1=NULL,*texteMenu2=NULL,*texteMenu3=NULL;

        //initialisation des polices
        TTF_Font *policeTitre= NULL, *policeMenu = NULL,*policeAuRevoir=NULL;

        SDL_Event event;

        //diffferentes couleurs en RGB
        SDL_Color  couleurN = {255, 255, 255};
        SDL_Color  couleurB = {0, 0, 255};
        SDL_Color  couleurV = {0, 255, 0};
        SDL_Color  couleurR = {255, 0, 0};
        SDL_Color  couleurGri = {200, 240, 255};

        //change si l'user veux quitter, continuer
        int continuer=1;
        int quitter=0;

        //TODO : regler problemes resolution : si > ecran, créé un nouvel ecran
        int tailleX=1280;
        int tailleY=640;

        void initPositions();
        void initPolices();
        void initTout();
        void afficherFixe();
        void initImages();
        void intro();
        void menu();
        void afficherBoutons();

    private:

};

#endif // INTERFACEGRAPHIQUE_H
