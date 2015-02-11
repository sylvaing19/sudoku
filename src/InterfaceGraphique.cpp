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
    fond = SDL_SetVideoMode(tailleX, tailleY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); //Definition du fond : fullscreen, etc  | SDL_FULLSCREEN
}

//polices avec leurs tailles
void InterfaceGraphique::initPolices()
{
    policeTitre = TTF_OpenFont("polices/A Simple Life.ttf", 100*zoomX);
    policeAuRevoir= TTF_OpenFont("polices/SF_Toontime.ttf", 150*zoomX);
    policeSudoku = TTF_OpenFont("polices/Cybernetica_Normal.ttf", 30*zoomX);
}

//Fonctions pour charger les elements dans les buffers, prets à apparaitre : permet de faire apparaitre quoi que ce soit depuis n'importe quelle classe
void InterfaceGraphique::chargerTitre()
{
    SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
}

void InterfaceGraphique::chargerFondMenuPrincipal()
{
    imageFond = SDL_LoadBMP("images/fond1.bmp");
    positionFond.x=0,positionFond.y=0;
    SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
}

void InterfaceGraphique::initTitre()
{
    policeTitre = TTF_OpenFont("polices/A Simple Life.ttf", 120*zoomX);
    imageTitre = TTF_RenderText_Blended(policeTitre,texteTitre.c_str() , couleurR );

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
        //TODO : probleme de latence ici
        positionTitre.y=i;
        SDL_Flip(fond);
        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
        SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
    }
    SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
}

//gestion de l'event "quitter" : clic sur le bouton d'arret ou echap : coupe toute l'application directement.
void InterfaceGraphique::quitter()
{
        continuerEvent = false;
        quitterAppli = true;

        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);

        texteAdieu = TTF_RenderText_Blended(policeAuRevoir, "Au revoir !" , couleurB );
        positionAuRevoir.x = (tailleX-(texteAdieu->w))/2;
        positionAuRevoir.y = (tailleY-(texteAdieu->h)-100*zoomY)/2;

        SDL_BlitSurface(texteAdieu, NULL, fond, &positionAuRevoir);
        SDL_Flip(fond);
        SDL_Delay(1000);
        SDL_Quit();
}

/// Fonction la plus importante de ce module
// initialisation du menu principal : boutons, etc, et animations / gestion des events ...
void InterfaceGraphique::menuPrincipal()
{
    ///Partie Menu Principal

    //affichage fond : le menu principal
    nomImageFond="images/fond1.bmp";
    chargerFondMenuPrincipal();
    SDL_Flip(fond);

    //initialisations diverses
    initPolices();
    texteTitre="Sudoku-Solveur";

    //affiche le titre, animation d'intro
    initTitre();
    intro();

    //affichage des boutons
    initBoutonsMenuPrincipal();
    chargerBoutonsMenuPrincipal();
    SDL_Flip(fond);

    //gestion des evenements

    continuerEvent=true;
    while(continuerEvent)
    {
        eventMenuPrincipal();
    }

    //Fin de menu Principal
}


void InterfaceGraphique::initBoutonsMenuPrincipal()
{
    //attribution du fond
    boutonMenu1.fond=fond;
    boutonMenu2.fond=fond;
    boutonQuitter.fond=fond;

    //gestion du zoom, de la taille
    boutonMenu1.zoomX=zoomX;
    boutonMenu1.zoomY=zoomY;
    boutonMenu2.zoomX=zoomX;
    boutonMenu2.zoomY=zoomY;
    boutonQuitter.zoomX=zoomX;
    boutonQuitter.zoomY=zoomY;

    boutonMenu1.tailleX=tailleX;
    boutonMenu1.tailleY=tailleY;
    boutonMenu2.tailleX=tailleX;
    boutonMenu2.tailleY=tailleY;
    boutonQuitter.tailleX=tailleX;
    boutonQuitter.tailleY=tailleY;

    //paramètres du bouton 1
    {
        std::string a="images/BoutonMenu.bmp";
        boutonMenu1.nomImageBouton=a;
        a="polices/Cybernetica_Normal.ttf";
        boutonMenu1.nomPolice=a;
        a="Resolution";
        boutonMenu1.messageBouton=a;
        a="Resoudre";
        boutonMenu1.event=a;
        boutonMenu1.couleurTexteBouton={255, 0, 0};
        boutonMenu1.taillePolice=70*zoomX;
        boutonMenu1.centreX="oui";
        boutonMenu1.positionBouton.y+=(positionTitre.y+positionTitre.h
                                      +positionTitre.y+imageTitre->h)*zoomX;
    }
    boutonMenu1.chargerBouton();

    //paramètres du bouton 2
    {
        std::string a="images/BoutonMenu.bmp";
        boutonMenu2.nomImageBouton=a;
        a="polices/Cybernetica_Normal.ttf";
        boutonMenu2.nomPolice=a;
        a="Photo-Doku";
        boutonMenu2.messageBouton=a;
        a="Photodoku";
        boutonMenu2.couleurTexteBouton={255, 0, 0};
        boutonMenu2.taillePolice=70*zoomX;
        boutonMenu2.centreX="oui";
        boutonMenu2.positionBouton.y+=(boutonMenu1.positionBouton.y+(boutonMenu1.imageBouton->h)*3/2);
    }
    boutonMenu2.chargerBouton();

    //paramètres du bouton quitter
    {
        boutonQuitter.positionBouton.x=(tailleX-65*zoomX);
        boutonQuitter.positionBouton.y=15*zoomY;
        std::string a="images/arret.bmp";
        boutonQuitter.nomImageBouton=a;
        a="Quitter";
        boutonQuitter.event=a;
    }
    boutonQuitter.chargerBouton();
}


void InterfaceGraphique::chargerBoutonsMenuPrincipal()
{
    boutonQuitter.chargerBouton();
    boutonMenu2.chargerBouton();
    boutonMenu1.chargerBouton();
}

void InterfaceGraphique::eventMenuPrincipal()
{
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_KEYDOWN:  //Gestion clavier
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE: //Appuyer sur echap : quitte
                    quitter();
                    continuerEvent=false;//inutile car quittte deja mais explicite
                    break;
                default:
                    ;
            }
            break;

        case SDL_MOUSEBUTTONDOWN: //Gestion souris
            switch (event.button.button)
            {
                case SDL_BUTTON_LEFT :

                        //clic gauche souris
                        if(boutonQuitter.estClique(event))
                        {
                            if(boutonQuitter.event=="Quitter")
                            {
                                quitter();
                                continuerEvent=false;//inutile car quitte deja mais explicite
                            }
                            else if(boutonQuitter.event=="Resoudre")
                            {
                                menuACreer="Resoudre";
                                continuerEvent=false;
                            }
                        }

                        //clic sur le menu 1
                        else if(boutonMenu1.estClique(event))
                        {
                            if(boutonMenu1.event=="Quitter")
                            {
                                quitter();
                                continuerEvent=false;//inutile car quitte deja mais explicite
                            }
                            else if(boutonMenu1.event=="Resoudre")
                            {
                                menuACreer="Resoudre";
                                continuerEvent=false;
                            }
                        }

                        //clic sur le menu 2
                        else if(boutonMenu2.estClique(event))
                        {
                            if(boutonMenu2.event=="Quitter")
                            {
                                quitter();
                                continuerEvent=false;//inutile car quitte deja mais explicite
                            }
                            else if(boutonMenu2.event=="Resoudre")
                            {
                                menuACreer="Resoudre";
                                continuerEvent=false;
                            }
                        }
                    break;
                default:
                    ;
            }
            break;
        default:
            ;
    }
}


