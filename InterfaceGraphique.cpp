#include "InterfaceGraphique.h"


InterfaceGraphique::InterfaceGraphique()
{
    SDL_WM_SetCaption("SuDoKu-Solver", NULL);
    TTF_Init();
    fond = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE| SDL_DOUBLEBUF);
}

//initialisation des differentes positions des images / textes
void InterfaceGraphique::initPositions()
{
    positionTitre.x = 270, positionTitre.y = 40;
    positionBoutonQuitter.x = 10, positionBoutonQuitter.y = 10;
    positionFond.x=0,positionFond.y=0;
    positionAuRevoir.x=200,positionAuRevoir.y=150;
    positionMenu1.x=350, positionMenu1.y=170;
    positionMenu2.x=350, positionMenu2.y=350;

    //texte des menus, centrée dans l'image
    positionTexteMenu1.x= (positionMenu1.x+60),positionTexteMenu1.y= (positionMenu1.y+50);
    positionTexteMenu2.x= (positionMenu2.x+120),positionTexteMenu2.y= (positionMenu2.y+50);
}

//polices avec leurs tailles
void InterfaceGraphique::initPolices()
{
    policeTitre = TTF_OpenFont("polices/A Simple Life.ttf", 100);
    policeMenu= TTF_OpenFont("polices/Cybernetica_Normal.ttf", 65);
    policeAuRevoir= TTF_OpenFont("polices/SF_Toontime.ttf", 150);
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
}

//fonction pour le debut de l'interface : initialisation de tout (polices, images, positions, affichage du debut)
void InterfaceGraphique::initTout()
{

    initPositions();
    SDL_Init(SDL_INIT_VIDEO);
    initImages();
    initPolices();
    afficherFixe();
    SDL_Delay(00);
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

                    //clic sur le bouton d'arret
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

                    //clic sur le menu 1
                    if( event.button.x>positionMenu1.x && event.button.x<(positionMenu1.x+613) && event.button.y>positionMenu1.y && event.button.y<(positionMenu1.y+157))
                    {
                        afficherFixe();
                        afficherBoutons();
                        texteTitre = TTF_RenderText_Blended(policeMenu, "Pret !", couleurGri );
                        SDL_BlitSurface(texteTitre, NULL, fond, &positionTitre);
                        SDL_Flip(fond);
                        SDL_Delay(100);
                    }

                    //clic sur le menu 2
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
