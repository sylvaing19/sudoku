
/*author Théo*/

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>

/*********************************************************************************/

SDL_Rect positionTitre, positionBoutonQuitter,positionFond,positionAuRevoir;
SDL_Rect positionMenu1,positionMenu2,positionMenu3;
SDL_Rect positionTexteMenu1, positionTexteMenu2, positionTexteMenu3;

SDL_Surface *imageFond = NULL, *arret = NULL, *fond = NULL, *texteTitre = NULL;
SDL_Surface *boutonMenu1=NULL,*boutonMenu2=NULL,*boutonMenu3=NULL,*texteMenu1=NULL,*texteMenu2=NULL,*texteMenu3=NULL;

TTF_Font *policeTitre= NULL, *policeMenu = NULL,*policeAuRevoir=NULL;

SDL_Event event;

SDL_Color  couleurN = {255, 255, 255};
SDL_Color  couleurB = {0, 0, 255};
SDL_Color  couleurV = {0, 255, 0};
SDL_Color  couleurR = {255, 0, 0};
SDL_Color  couleurGri = {200, 240, 255};

int continuer=1;
int quitter=0;

/*********************************************************************************/

void initPositions();
void initPolices();
void initTout();
void afficherFixe();
void initImages();
void intro();
void menu();
void afficherBoutons();
void Interface();

/*********************************************************************************/



void Interface()
{
     initTout();
    intro();
    while(continuer)
    {
      menu();
    }
    if(quitter==1);
}
/*********************************************************************************/

//initialise les positions de chaque surface
void initPositions()
{
    positionTitre.x = 270, positionTitre.y = 40;
    positionBoutonQuitter.x = 10, positionBoutonQuitter.y = 10;
    positionFond.x=0,positionFond.y=0;
    positionAuRevoir.x=200,positionAuRevoir.y=150;
    positionMenu1.x=350, positionMenu1.y=170;
    positionMenu2.x=350, positionMenu2.y=350;
    positionTexteMenu1.x= (positionMenu1.x+60),positionTexteMenu1.y= (positionMenu1.y+50);
    positionTexteMenu2.x= (positionMenu2.x+120),positionTexteMenu2.y= (positionMenu2.y+50);
}

//Indique les polices, et leurs tailles
void initPolices()
{
    policeTitre = TTF_OpenFont("A Simple Life.ttf", 100);
    policeMenu= TTF_OpenFont("Cybernetica_Normal.ttf", 65);
    policeAuRevoir= TTF_OpenFont("SF_Toontime.ttf", 150);
}

//Attribution des images et du fond à des variables
void initImages()
{
    fond = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE);
    arret = SDL_LoadBMP("arret.bmp"); //met le bouton d'arret
    imageFond = SDL_LoadBMP("fond1.bmp");
    boutonMenu1=SDL_LoadBMP("BoutonMenu.bmp");
    boutonMenu2=SDL_LoadBMP("BoutonMenu.bmp");
    SDL_SetColorKey(boutonMenu1, SDL_SRCCOLORKEY, SDL_MapRGB(boutonMenu1->format, 255, 255, 255)); // met le blanc en transparent pour le bouton de menu
    SDL_SetColorKey(boutonMenu2, SDL_SRCCOLORKEY, SDL_MapRGB(boutonMenu2->format, 255, 255, 255)); // met le blanc en transparent pour le bouton de menu
}

//Debut de l'affichage à l'user
void initTout()
{
    SDL_WM_SetCaption("SuDoKu-Solver", NULL);
    TTF_Init();
    initPositions();
    SDL_Init(SDL_INIT_VIDEO);
    initImages();
    initPolices();
    afficherFixe();
    SDL_Delay(300);
}

//Affiche les boutons utiles à l'user
void afficherBoutons()
{
    SDL_BlitSurface(boutonMenu1 , NULL, fond, &positionMenu1);
    SDL_BlitSurface(boutonMenu2 , NULL, fond, &positionMenu2);
    SDL_BlitSurface(arret, NULL, fond, &positionBoutonQuitter);
    texteMenu1 = TTF_RenderText_Blended(policeMenu, "Nouvelle Partie", couleurN );
    texteMenu2 = TTF_RenderText_Blended(policeMenu, "Photo-doku", couleurN );
    SDL_BlitSurface(texteMenu1, NULL, fond, &positionTexteMenu1);
    SDL_BlitSurface(texteMenu2, NULL, fond, &positionTexteMenu2);
    SDL_Flip(fond);
}

//affiche le fond, et tout ce qui est fixe
void afficherFixe()
{
    SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
    SDL_Flip(fond);
}

//animation d'intro
void intro()
{
    int i;
    int a=positionTitre.y;
    for(i=-50;i<=a;i++)
    {
        SDL_Delay(20);
        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
        positionTitre.y=i;
        texteTitre = TTF_RenderText_Blended(policeTitre, "SuDoKu Solver", couleurN );
        SDL_BlitSurface(texteTitre, NULL, fond, &positionTitre);
        SDL_Flip(fond);
    }
    SDL_Delay(200);
    afficherBoutons();
}

//gestion des events de l'user
void menu()
{
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_KEYDOWN:  //Gestion clavier
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE: //Appuyer sur echap : quitte
                    continuer = 0;
                    quitter = 1;
                    break;
                default:
                    ;
            }
            break;
        case SDL_MOUSEBUTTONDOWN: //Gestion souris
            switch (event.button.button)
             {
                case SDL_BUTTON_LEFT ://Cas clic gauche souris
                    if( event.button.x>positionBoutonQuitter.x && event.button.x<(positionBoutonQuitter.x+45) && event.button.y>positionBoutonQuitter.y && event.button.y<(positionBoutonQuitter.y+45))
                    {
                        continuer=0;
                        quitter = 1;
                        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
                        texteTitre = TTF_RenderText_Blended(policeAuRevoir, "Au revoir !", couleurR );
                        SDL_BlitSurface(texteTitre, NULL, fond, &positionAuRevoir);
                        SDL_Flip(fond);
                        SDL_Delay(500);
                    }
                    if( event.button.x>positionMenu1.x && event.button.x<(positionMenu1.x+613) && event.button.y>positionMenu1.y && event.button.y<(positionMenu1.y+157))
                    {
                        afficherFixe();
                        afficherBoutons();
                        texteTitre = TTF_RenderText_Blended(policeMenu, "Pret !", couleurGri );
                        SDL_BlitSurface(texteTitre, NULL, fond, &positionTitre);
                        SDL_Flip(fond);
                        SDL_Delay(100);
                    }
                    if( event.button.x>positionMenu2.x && event.button.x<(positionMenu2.x+613) && event.button.y>positionMenu2.y && event.button.y<(positionMenu2.y+157))
                    {
                        afficherFixe();
                        afficherBoutons();
                        texteTitre = TTF_RenderText_Blended(policeMenu, "Pret ici aussi !", couleurGri );
                        SDL_BlitSurface(texteTitre, NULL, fond, &positionTitre);
                        SDL_Flip(fond);
                        SDL_Delay(100);
                    }
                    break;
                default:
                    ;
             }
    }
}

