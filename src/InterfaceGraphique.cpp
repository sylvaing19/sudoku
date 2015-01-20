#include "InterfaceGraphique.h"

//Constructeur
InterfaceGraphique::InterfaceGraphique()
{
    //Initialisation du systeme SDL
    SDL_Init(SDL_INIT_VIDEO);

    //Recuperation des informations de l'utilisateur
    info = SDL_GetVideoInfo();

    //change si l'user veux quitter, continuer
    continuerEvent=true;
    quitterAppli=false;

    //La taille de l'ecran se recupere sur les infos
    tailleX=info->current_w ;
    tailleY=info->current_h ;

    //Zoom : mon ecran sert de reference (1280*640), et on divise la taille de tout le reste suivant les resolutions
    zoomX=((double)tailleX/1600);
    zoomY=((double)tailleY/900);

    //titre de la fenetre, initialisation de TTF, creation de la fenetre de fond
    SDL_WM_SetCaption("SuDoKu-Solver", NULL);
    TTF_Init();
    fond = SDL_SetVideoMode(tailleX, tailleY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); //Definition du fond : fullscreen, etc
}

//polices avec leurs tailles
void InterfaceGraphique::initPolices()
{
    policeTitre = TTF_OpenFont("polices/A Simple Life.ttf", 100*zoomX);
    policeMenu= TTF_OpenFont("polices/Cybernetica_Normal.ttf", 65*zoomX);
    policeAuRevoir= TTF_OpenFont("polices/SF_Toontime.ttf", 150*zoomX);
}

void InterfaceGraphique::chargerMenu()
{
    imageFond = SDL_LoadBMP("images/fond1.bmp");
    positionFond.x=0,positionFond.y=0;
    SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
}

void InterfaceGraphique::chargerTitre()
{
    SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
}

void InterfaceGraphique::initTitre()
{
    policeTitre = TTF_OpenFont("polices/A Simple Life.ttf", 100*zoomX);
    imageTitre = TTF_RenderText_Blended(policeTitre,texteTitre.c_str() , couleurN );

    //Position du titre : centré en x, (arbitraire)*zoom en y
    positionTitre.x = (tailleX-(imageTitre->w))/2;
    positionTitre.y = 50*zoomY;
}

//animation d'intro : titre qui apparait, et boutons apparaissant
void InterfaceGraphique::intro()
{
    int i;
    int a=positionTitre.y;
    //animation, titre qui descend
    for(i=-50;i<=a;i++)
    {
        positionTitre.y=i;
        SDL_Flip(fond);
        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
        chargerTitre();
    }
    SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
}

//gestion de l'event "quitter" : clic sur le bouton d'arret ou echap

void InterfaceGraphique::quitter()
{
        continuerEvent = false;
        quitterAppli = true;

        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);

        texteAdieu = TTF_RenderText_Blended(policeAuRevoir, "Au revoir !" , couleurN );
        positionAuRevoir.x = (tailleX-(texteAdieu->w))/2;
        positionAuRevoir.y = (tailleY-(texteAdieu->h))/2;

        SDL_BlitSurface(texteAdieu, NULL, fond, &positionAuRevoir);
        SDL_Flip(fond);

        SDL_Delay(500);
}


//gestion des events, clic sur les boutons
void InterfaceGraphique::eventMenu()
{
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_KEYDOWN:  //Gestion clavier
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE: //Appuyer sur echap : quitte
                    quitter();
                    break;
                default:
                    ;
            }
            break;
        case SDL_MOUSEBUTTONDOWN: //Gestion souris
            switch (event.button.button)
             {
                case SDL_BUTTON_LEFT ://Cas clic gauche souris
/*
                    //clic sur le bouton d'arret
                    if( event.button.x>positionBoutonQuitter.x && event.button.x<(positionBoutonQuitter.x+positionBoutonQuitter.w) && event.button.y>positionBoutonQuitter.y && event.button.y<(positionBoutonQuitter.y+positionBoutonQuitter.h))
                    {
                        quitter();
                    }

                    //clic sur le menu 1
                    else if( event.button.x>positionMenu1.x && event.button.x<(positionMenu1.x+positionMenu1.w) && event.button.y>positionMenu1.y && event.button.y<(positionMenu1.y+positionMenu1.h))
                    {
                        afficherFixe();
                        afficherBoutons();
                        SDL_BlitSurface(textePret, NULL, fond, &positionTitre);
                        SDL_Flip(fond);
                    }

                    //clic sur le menu 2
                    else if( event.button.x>positionMenu2.x && event.button.x<(positionMenu2.x+positionMenu2.w) && event.button.y>positionMenu2.y && event.button.y<(positionMenu2.y+positionMenu2.h))
                    {
                        afficherFixe();
                        afficherBoutons();
                        SDL_BlitSurface(textePretAussi, NULL, fond, &positionTitre);
                        SDL_Flip(fond);
                    }*/
                    break;
                default:
                    ;
             }
    }
}

