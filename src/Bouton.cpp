#include "Bouton.h"

Bouton::Bouton()
{

//useless avec interface, necessaire pour tests

    //Initialisation du systeme  SDL
    SDL_Init(SDL_INIT_VIDEO);

    //Recuperation des informations de l'utilisateur
    info = SDL_GetVideoInfo();

     //La taille de l'ecran se recupere sur les infos
    tailleX=info->current_w ;
    tailleY=info->current_h ;

    //titre de la fenetre, initialisation de TTF, creation de la fenetre de fond
    SDL_WM_SetCaption("Test Classe Bouton", NULL);
    TTF_Init();
    fond = SDL_SetVideoMode(tailleX, tailleY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); //Definition du fond : fullscreen, etc

    SDL_Flip(fond);

}

void Bouton::creerBouton(const char* imageFond, const char*  nomImageBouton ,const char* police, SDL_Color couleur, const char* message ,int x, int y)
{
    //chargement des images
    menu = SDL_LoadBMP(imageFond);
    positionFond.x=0;
    positionFond.y=0;

    imageBouton=SDL_LoadBMP(nomImageBouton);
    SDL_SetColorKey(imageBouton, SDL_SRCCOLORKEY, SDL_MapRGB(imageBouton->format, 255, 255, 255)); // met le blanc en transparent pour le bouton
    positionBouton.x=x;
    positionBouton.y=y;

    //chargement du texte et police
    policeBouton = TTF_OpenFont(police, 100);
    texteBouton = TTF_RenderText_Blended(policeBouton, message, couleur);

    //gestion de la position du texte, centré
    positionTexte.x= positionBouton.x+(imageBouton->w-texteBouton->w)/2;
    positionTexte.y= positionBouton.y+(imageBouton->h-texteBouton->h)/2;

    //affichage du fond coloré
    SDL_BlitSurface(menu, NULL, fond, &positionFond);
    SDL_Flip(fond);
    SDL_Delay(1000);

    //affichage du bouton
    SDL_BlitSurface(imageBouton, NULL,fond , &positionBouton);
    SDL_BlitSurface(texteBouton,NULL,fond , &positionTexte);
    SDL_Flip(fond);
    SDL_Delay(1000);
}

