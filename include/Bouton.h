#ifndef BOUTON_H
#define BOUTON_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <SDL_rotozoom.h>
#include <cmath>


class Bouton
{
    public:
        Bouton();

        //Recupere les données d'affichage
        const SDL_VideoInfo* info;

        //taille des boutons / images
        int tailleX;
        int tailleY;

        //zoom : gestion des differences de reslotion et taille d'ecran
        double zoomX,zoomY;

        //Non vides si le bouton est centré quelque part
        std::string centreX;
        std::string centreY;

        //taille de la police
        int taillePolice;

        //position des objets
        SDL_Rect positionFond;// position du fond : 0,0
        SDL_Rect positionBouton;

        //images
        SDL_Surface* fond=NULL; //image du fond : rien
        SDL_Surface* imageBouton=NULL; //image des boutons principaux
        SDL_Surface* texteBouton=NULL; //texte qu'il y a sur les boutons

        //Polices
        TTF_Font *policeBouton=NULL; //POlice sur les boutons principaux

        //Noms à entrer
        std::string nomImageFond, nomImageBouton , nomPolice, messageBouton,event;
        SDL_Color couleurTexteBouton;

        ///Prototypes de fonctions

        // charge le bouton dans le buffer, pret à flipper
        void chargerBouton();
        // renvoie un booleen : vrai si le bouton est cliqué, faux sinon
        bool estClique(SDL_Event event);

   private:
        SDL_Rect positionTexte;// position du texte sur les boutons

}
;

#endif // BOUTON_H
