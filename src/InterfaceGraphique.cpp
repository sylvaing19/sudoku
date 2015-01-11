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

void InterfaceGraphique::chargerMenu()
{
    imageFond = SDL_LoadBMP("images/fond1.bmp");
    positionFond.x=0,positionFond.y=0;
    SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
}

//initialisation des differentes positions des images / textes et leurs tailles
void InterfaceGraphique::initPositions()
{
    //Le fond sert d'origine, 0;0
    positionFond.x=0,positionFond.y=0;

    //Position du titre : centré en x, 40(arbitraire)*zoom en y
    positionTitre.x = (tailleX-(texteTitre->w))/2;
    positionTitre.y = 50*zoomY;

    //Position bouton quitter
    positionBoutonQuitter.x = tailleX-50*zoomX;
    positionBoutonQuitter.y = 10*zoomY;

    //Position titre "au revoir" centré en tout
    positionAuRevoir.x= (tailleX-(texteTitre->w))/2;
    positionAuRevoir.y= (tailleY-(texteTitre->h))/2;

    //Positions menus
    positionMenu1.x=(tailleX-(boutonMenu1->w))/2;
    positionMenu1.y=positionTitre.y+(texteTitre->h)+(boutonMenu1->h)/3;

    positionMenu2.x=(tailleX-(boutonMenu2->w))/2;
    positionMenu2.y=positionMenu1.y+1.25*(boutonMenu1->h);

    //texte des menus, centrée dans l'image
    positionTexteMenu1.x= positionMenu1.x+(boutonMenu1->w-texteMenu1->w)/2;
    positionTexteMenu1.y= positionMenu1.y+(boutonMenu1->h-texteMenu1->h)/2;

    positionTexteMenu2.x= positionMenu2.x+(boutonMenu2->w-texteMenu2->w)/2;
    positionTexteMenu2.y= positionMenu2.y+(boutonMenu2->h-texteMenu2->h)/2;
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
    //Chargement des .bmp
    arret = SDL_LoadBMP("images/arret.bmp");
    imageFond = SDL_LoadBMP("images/fond1.bmp");
    boutonMenu1=SDL_LoadBMP("images/BoutonMenu.bmp");
    boutonMenu2=SDL_LoadBMP("images/BoutonMenu.bmp");

    //Transparence
    SDL_SetColorKey(boutonMenu1, SDL_SRCCOLORKEY, SDL_MapRGB(boutonMenu1->format, 255, 255, 255)); // met le blanc en transparent pour le bouton de menu
    SDL_SetColorKey(boutonMenu2, SDL_SRCCOLORKEY, SDL_MapRGB(boutonMenu2->format, 255, 255, 255)); // met le blanc en transparent pour le bouton de menu
    SDL_SetColorKey(arret, SDL_SRCCOLORKEY, SDL_MapRGB(arret->format, 255, 255, 255)); // met le blanc en transparent pour le bouton d'arret

    //On zoome / dezoome suivant les tailles d'ecran
    boutonMenu1 = zoomSurface(boutonMenu1, zoomX, zoomY, 0);
    boutonMenu2 = zoomSurface(boutonMenu2, zoomX, zoomY, 0);
    arret = zoomSurface(arret, zoomX, zoomX, 0);
    imageFond = zoomSurface(imageFond, zoomX, zoomX, 0);

    //textes initisalisés
    texteMenu1 = TTF_RenderText_Blended(policeMenu, "Nouvelle Partie", couleurN );
    texteMenu2 = TTF_RenderText_Blended(policeMenu, "Photo-doku", couleurN );
    texteAdieu = TTF_RenderText_Blended(policeAuRevoir, "Au revoir !", couleurR );
    textePret = TTF_RenderText_Blended(policeMenu, "Pret !", couleurGri );
    textePretAussi = TTF_RenderText_Blended(policeMenu, "Pret ici aussi !", couleurGri );
    texteTitre = TTF_RenderText_Blended(policeTitre, "SuDoKu Solver", couleurN );
}

//fonction pour le debut de l'interface : initialisation de tout (polices, images, positions, affichage du debut)
void InterfaceGraphique::initTout()
{
    initPolices();
    initImages();
    initPositions();
    afficherFixe();
    SDL_Delay(300);
}

//affichage des boutons cliquables
void InterfaceGraphique::afficherBoutons()
{
    SDL_BlitSurface(boutonMenu1 , NULL, fond, &positionMenu1);
    SDL_BlitSurface(texteMenu1, NULL, fond, &positionTexteMenu1);

    SDL_BlitSurface(arret, NULL, fond, &positionBoutonQuitter);

    SDL_BlitSurface(boutonMenu2 , NULL, fond, &positionMenu2);
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
    //animation, titre qui descend
    for(i=-50;i<=a;i++)
    {
        positionTitre.y=i;
        SDL_Flip(fond);
        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
        SDL_BlitSurface(texteTitre, NULL, fond, &positionTitre);

    }
    SDL_BlitSurface(texteTitre, NULL, fond, &positionTitre);
    SDL_Flip(fond);
    afficherBoutons();
}

//gestion de l'event "quitter" : clic sur le bouton d'arret ou echap
void InterfaceGraphique::quitter()
{
        continuerEvent = false;
        quitterAppli = true;
        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
        SDL_BlitSurface(texteAdieu, NULL, fond, &positionAuRevoir);
        SDL_Flip(fond);
        SDL_Delay(1500);
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
                    }
                    break;
                default:
                    ;
             }
    }
}
