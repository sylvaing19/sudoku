#ifndef BOUTON_H
#define BOUTON_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Bouton
{
    public:
        Bouton();

        //Recupere les données d'affichage
        const SDL_VideoInfo* info;

        //taille des boutons / images
        int tailleX;
        int tailleY;

        //position des objets
        SDL_Rect positionBouton;
        SDL_Rect positionFond;
        SDL_Rect positionTexte;


        //Prototypes
        void creerBouton(const char* imageFond, const char* imageBouton ,const char* police,SDL_Color couleur,const char* message,int x, int y);

        //images
        SDL_Surface* fond;
        SDL_Surface* menu;
        SDL_Surface* imageBouton;
        SDL_Surface* texteBouton;

        //Polices
        TTF_Font *policeBouton=NULL;

    private:

};

#endif // BOUTON_H
