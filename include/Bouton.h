#ifndef BOUTON_H
#define BOUTON_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Bouton
{/// http://www.cplusplus.com/reference/stl/
    public:
        Bouton();

        //Recupere les données d'affichage
        const SDL_VideoInfo* info;

        //taille des boutons / images
        int tailleX;
        int tailleY;

        //position des objets
        SDL_Rect positionBouton;
        SDL_Rect positionFond;///Pourquoi publique ?
        SDL_Rect positionTexte;///Pourquoi publique ?

        /// http://www.cplusplus.com/reference/string/
        //Prototypes
        void creerBouton(const char* imageFond, const char* imageBouton ,const char* police,SDL_Color couleur,const char* message,int x, int y);

        //images
        SDL_Surface* fond;///Pourquoi publique ?
        SDL_Surface* menu;///Pourquoi publique ?
        SDL_Surface* imageBouton;///Pourquoi publique ?
        SDL_Surface* texteBouton;///Pourquoi publique ?

        //Polices
        TTF_Font *policeBouton=NULL;///Pourquoi publique ?

    private:
        ///Une méthode ou un attribut doit être PIRVE. Sauf si il est judicieux de l'utiliser depuis l'extérieur.
        ///A priori seules les méthodes d'affichage ou de mise en buffer seront publiques

};

#endif // BOUTON_H
