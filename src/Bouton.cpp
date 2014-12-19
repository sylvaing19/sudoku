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
    SDL_WM_SetCaption("SuDoKu-Solver", NULL);
    TTF_Init();
    fond = SDL_SetVideoMode(tailleX, tailleY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Definition du fond : fullscreen, etc

    SDL_Flip(fond);

}

void Bouton::creerBouton(const char* imageFond, const char*  imageBouton ,const char* police, SDL_Color couleur, const char* message ,int x, int y)
{
    menu = SDL_LoadBMP(imageFond);

    policeBouton = TTF_OpenFont(police, 100);

    texteBouton = TTF_RenderText_Blended(policeBouton, message, couleur );
    positionBouton.x=x;
    positionBouton.y=y;

    positionFond.x=0;
    positionFond.y=0;

    SDL_BlitSurface(menu, NULL, fond, &positionFond);
    SDL_Flip(fond);
    SDL_Delay(1000);

    SDL_BlitSurface(texteBouton,NULL,fond , &positionBouton);
    SDL_Flip(fond);
    SDL_Delay(1000);
}

