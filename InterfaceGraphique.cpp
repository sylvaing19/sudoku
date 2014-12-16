#include "InterfaceGraphique.h"


InterfaceGraphique::InterfaceGraphique()
{
    //change si l'user veux quitter, continuer
    continuerEvent=true;
    quitterAppli=false;

    //TODO : regler problemes resolution : si > ecran, créé un nouvel ecran
    tailleX=1280;
    tailleY=640;

    zoomX=((double)tailleX/1200);
    zoomY=((double)tailleY/640);

    SDL_WM_SetCaption("SuDoKu-Solver", NULL);
    TTF_Init();
    fond = SDL_SetVideoMode(tailleX, tailleY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); //Definition du fond : fullscreen, etc
    }

//initialisation des differentes positions des images / textes et leurs tailles
void InterfaceGraphique::initPositions()
{
    tailleXArret=45*zoomX;
    tailleYArret=45*zoomY;
    tailleXMenu=613*zoomX;
    tailleYMenu=157*zoomY;

    positionTitre.x = tailleX*0.2*zoomX, positionTitre.y = 40*zoomY;
    positionBoutonQuitter.x = (tailleX-50*zoomX), positionBoutonQuitter.y = 10*zoomY;
    positionFond.x=0,positionFond.y=0;
    positionAuRevoir.x=tailleX*0.2*zoomX,positionAuRevoir.y=tailleY*0.25*zoomY;

    positionMenu1.x=tailleX*0.25*zoomX, positionMenu1.y=tailleY/3*zoomY;
    positionMenu2.x=positionMenu1.x, positionMenu2.y=positionMenu1.y+1.5*tailleYMenu;

    //texte des menus, centrée dans l'image
    positionTexteMenu1.x= positionMenu1.x+60*zoomX,positionTexteMenu1.y= (positionMenu1.y+50*zoomY);
    positionTexteMenu2.x= positionMenu2.x+120*zoomX,positionTexteMenu2.y= (positionMenu2.y+50*zoomY);
}

//polices avec leurs tailles
void InterfaceGraphique::initPolices()
{
    policeTitre = TTF_OpenFont("polices/A Simple Life.ttf", 100*zoomX);
    policeMenu= TTF_OpenFont("polices/Cybernetica_Normal.ttf", 65*zoomX);
    policeAuRevoir= TTF_OpenFont("polices/SF_Toontime.ttf", 150*zoomX);
}

//attribution des images à des variables, et gestion de transparence
void InterfaceGraphique::initImages()
{
    arret = SDL_LoadBMP("images/arret.bmp"); //met le bouton d'arret

    imageFond = SDL_LoadBMP("images/fond1.bmp");
    boutonMenu1=SDL_LoadBMP("images/BoutonMenu.bmp");
    boutonMenu2=SDL_LoadBMP("images/BoutonMenu.bmp");

    SDL_SetColorKey(boutonMenu1, SDL_SRCCOLORKEY, SDL_MapRGB(boutonMenu1->format, 255, 255, 255)); // met le blanc en transparent pour le bouton de menu
    SDL_SetColorKey(boutonMenu2, SDL_SRCCOLORKEY, SDL_MapRGB(boutonMenu2->format, 255, 255, 255)); // met le blanc en transparent pour le bouton de menu
    SDL_SetColorKey(arret, SDL_SRCCOLORKEY, SDL_MapRGB(arret->format, 255, 255, 255)); // met le blanc en transparent pour le bouton d'arret


    boutonMenu1 = zoomSurface(boutonMenu1, zoomX, zoomY, 0); //On zoome / dezoome sur le menu
    boutonMenu2 = zoomSurface(boutonMenu2, zoomX, zoomY, 0);
    arret = zoomSurface(arret, zoomX, zoomX, 0);
    imageFond = zoomSurface(imageFond, zoomX, zoomX, 0);


}

//fonction pour le debut de l'interface : initialisation de tout (polices, images, positions, affichage du debut)
void InterfaceGraphique::initTout()
{

    initPositions();
    SDL_Init(SDL_INIT_VIDEO);
    initImages();
    initPolices();
    afficherFixe();
    SDL_Delay(300);
}

//affichagee des boutons cliquables
void InterfaceGraphique::afficherBoutons()
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

//afffichage de tout ce qui est fixe et non cliquable
void InterfaceGraphique::afficherFixe()
{
    SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
    SDL_Flip(fond);
}

//animation d'intro : titre qui apparait, et boutons apparaissant
void InterfaceGraphique::intro()
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

void InterfaceGraphique::quitter()
{
        continuerEvent = false;
        quitterAppli = true;
        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
        texteTitre = TTF_RenderText_Blended(policeAuRevoir, "Au revoir !", couleurR );
        SDL_BlitSurface(texteTitre, NULL, fond, &positionAuRevoir);
        SDL_Flip(fond);
        SDL_Delay(500);
}

//gestion des events, clic sur les boutons
void InterfaceGraphique::menu()
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

                    //clic sur le bouton d'arret
                    if( event.button.x>positionBoutonQuitter.x && event.button.x<(positionBoutonQuitter.x+tailleXArret) && event.button.y>positionBoutonQuitter.y && event.button.y<(positionBoutonQuitter.y+tailleYArret))
                    {
                        quitter();
                    }

                    //clic sur le menu 1
                    else if( event.button.x>positionMenu1.x && event.button.x<(positionMenu1.x+tailleXMenu) && event.button.y>positionMenu1.y && event.button.y<(positionMenu1.y+tailleYMenu))
                    {
                        afficherFixe();
                        afficherBoutons();
                        texteTitre = TTF_RenderText_Blended(policeMenu, "Pret !", couleurGri );
                        SDL_BlitSurface(texteTitre, NULL, fond, &positionTitre);
                        SDL_Flip(fond);
                    }

                    //clic sur le menu 2
                    else if( event.button.x>positionMenu2.x && event.button.x<(positionMenu2.x+tailleXMenu) && event.button.y>positionMenu2.y && event.button.y<(positionMenu2.y+tailleYMenu))
                    {
                        afficherFixe();
                        afficherBoutons();
                        texteTitre = TTF_RenderText_Blended(policeMenu, "Pret ici aussi !", couleurGri );
                        SDL_BlitSurface(texteTitre, NULL, fond, &positionTitre);
                        SDL_Flip(fond);
                    }
                    break;
                default:
                    ;
             }
    }
}



/*Rotation :
#include <SDL_rotozoom.h>
rotation = rotozoomSurface(boutonMenu1, 10, 1, 0); //On transforme la surface image.

//On repositionne l'image en fonction de sa taille.

SDL_BlitSurface(rotation , NULL, fond, &positionMenu1); //On affiche la rotation de la surface image.
SDL_Flip(fond);*/
