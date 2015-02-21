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
	//tailleX = 800;
	//tailleY = 640;

	tailleX=info->current_w ;
	tailleY=info->current_h;

    //Zoom : mon ecran sert de reference (1280*640), et on divise la taille de tout le reste suivant les resolutions
    zoomX=((double)tailleX/1600);
    zoomY=((double)tailleY/900);

    //titre de la fenetre, initialisation de TTF, creation de la fenetre de fond
    SDL_WM_SetCaption("SuDoKu-Solver", NULL);
    TTF_Init();
	fond = SDL_SetVideoMode(tailleX, tailleY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); //Definition du fond : fullscreen, etc  | SDL_FULLSCREEN

	couleurN = { 0, 0, 0 };
	couleurB = { 0, 0, 255 };
	couleurV = { 0, 255, 0 };
	couleurR = { 255, 0, 0 };
	couleurGri = { 200, 240, 255 };
}

//polices avec leurs tailles
void InterfaceGraphique::initPolices()
{
	policeTitre = policeEntrezUnChiffre= TTF_OpenFont("polices/A Simple Life.ttf", 100 * zoomX);
    policeAuRevoir= TTF_OpenFont("polices/SF_Toontime.ttf", 150*zoomX);
    policeSudoku = TTF_OpenFont("polices/Cybernetica_Normal.ttf", 30*zoomX);
	policePasSolvable = TTF_OpenFont("polices/Cybernetica_Normal.ttf", 50 * zoomX);
}

//Fonctions pour charger les elements dans les buffers, prets à apparaitre : permet de faire apparaitre quoi que ce soit depuis n'importe quelle classe
void InterfaceGraphique::chargerTitre()
{
    SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
}

void InterfaceGraphique::chargerFond()
{
    imageFond = SDL_LoadBMP(nomImageFond.c_str());
	if (imageFond == NULL)
	{
		printf("Probleme avec %s", imageFond);
		SDL_Quit();
	}

    positionFond.x=0,positionFond.y=0;
    SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
}

void InterfaceGraphique::initTitre()
{
    policeTitre = TTF_OpenFont("polices/A Simple Life.ttf", 120*zoomX);
    imageTitre = TTF_RenderText_Blended(policeTitre,texteTitre.c_str() , couleurR );

    //Position du titre : centré en x, (arbitraire)*zoom en y
	positionTitre.x = (tailleX - (imageTitre->w)) / 2 ;
    positionTitre.y = 50*zoomY;
}

//animation d'intro : titre qui apparait, et boutons apparaissant
void InterfaceGraphique::intro()
{
    int i;
    int a=positionTitre.y;
    //animation, titre qui descend
    for(i=0;i<=a;i++)
    {
        //TODO : probleme de latence ici
        positionTitre.y=i;
		SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
		SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
        SDL_Flip(fond);
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
    //affichage fond : le menu principal
    nomImageFond="images/fond1.bmp";
    chargerFond();
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

// Initialise le bouton en argument, lui mettant son fond associé, la taille de l'image, etc
void InterfaceGraphique::initFondZoomTailleBouton(Bouton & bouton)
{
    bouton.fond=fond;
    bouton.zoomX=zoomX;
    bouton.zoomY=zoomY;
    bouton.tailleX=tailleX;
    bouton.tailleY=tailleY;
}

// Initialise la grille graphique en argument, lui mettant son fond associé, la taille de l'image, etc
void InterfaceGraphique::initFondZoomTailleGrilleGraph(GrilleGraphique &grilleGraph)
{
	grilleGraph.fond = fond;
	grilleGraph.zoomX = zoomX;
	grilleGraph.zoomY = zoomY;
	grilleGraph.tailleX = tailleX;
	grilleGraph.tailleY = tailleY;
}

// initialise tous les boutons apppartenant au menu principal
void InterfaceGraphique::initBoutonsMenuPrincipal()
{
    //gestion du zoom, de la taille
    initFondZoomTailleBouton(boutonMenu1);
    initFondZoomTailleBouton(boutonMenu2);
    initFondZoomTailleBouton(boutonQuitter);

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

// charge les boutons du menu principal dans le buffer, prets  etre flippés
void InterfaceGraphique::chargerBoutonsMenuPrincipal()
{
    boutonQuitter.chargerBouton();
    boutonMenu2.chargerBouton();
    boutonMenu1.chargerBouton();
}

// Gere l'event dans le menu principal : quitter / creer une grille vide / creer une grille aleatoire
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

/// Fonction la plus importante de ce module n2
// initialisation du menu resoudre : boutons, etc, et animations / gestion des events ...
void InterfaceGraphique::menuResoudre()
{
    nomImageFond="images/fond2.bmp";
    chargerFond();

    //initialisations diverses
    initPolices();
    texteTitre="Resolution de Sudoku";

    initBoutonsMenuResoudre();

    SDL_Flip(fond);

    continuerEvent=true;
    while(continuerEvent)
    {
        eventMenuResoudre();
    }
}

void InterfaceGraphique::initBoutonsMenuResoudre()
{
    initFondZoomTailleBouton(boutonAleatoire);
    initFondZoomTailleBouton(boutonManuel);
    initFondZoomTailleBouton(boutonQuitter);

    //paramètres du bouton aleatoire
    {
        std::string a="images/BoutonSudoku.bmp";
        boutonAleatoire.nomImageBouton=a;
        a="polices/Cybernetica_Normal.ttf";
        boutonAleatoire.nomPolice=a;
        a="Aleatoire";
        boutonAleatoire.messageBouton=a;
        a="ApparitionAleatoire";
        boutonAleatoire.event=a;
        boutonAleatoire.couleurTexteBouton={255, 255, 255};
        boutonAleatoire.taillePolice=70*zoomX;
        boutonAleatoire.positionBouton.x+=30*boutonAleatoire.zoomX;
        boutonAleatoire.positionBouton.y+=30*boutonAleatoire.zoomY;
    }
    boutonAleatoire.chargerBouton();

    //paramètres du bouton de generation à la main
    {
        std::string a="images/BoutonSudoku.bmp";
        boutonManuel.nomImageBouton=a;
        a="polices/Cybernetica_Normal.ttf";
        boutonManuel.nomPolice=a;
        a="Manuel";
        boutonManuel.messageBouton=a;
        a="Manuel";
        boutonManuel.event=a;
        boutonManuel.couleurTexteBouton={255, 255, 255};
        boutonManuel.taillePolice=70*zoomX;
        boutonManuel.positionBouton.x+=boutonAleatoire.positionBouton.x;
        boutonManuel.positionBouton.y+=30*boutonAleatoire.zoomY+boutonAleatoire.positionBouton.y+ boutonAleatoire.positionBouton.h;
    }
    boutonManuel.chargerBouton();

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

void InterfaceGraphique::eventMenuResoudre()
{
    ///gestion des events :

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
            case SDL_BUTTON_LEFT :
                    //clic gauche souris
                    if(boutonAleatoire.estClique(event))
                        {
                            if(boutonAleatoire.event=="Quitter")
                                quitter();
                            else if(boutonAleatoire.event=="ApparitionAleatoire")
                            {
                                menuACreer="Aleatoire";
                                continuerEvent=false;
                                std::string a="Resoudre";
                                boutonAleatoire.messageBouton=a;
                                boutonAleatoire.event=a;
                            }
                            else if(boutonAleatoire.event=="Resoudre")
                            {
                                menuACreer="Resoudre";
                                continuerEvent=false;
                                sudokuAResoudre=true;
                           }
                            else if(boutonAleatoire.event=="Manuel")
                            {
                                    menuACreer="Manuel";
                                    continuerEvent=false;
                                    sudokuVide=true;
                            }
                        }
                    else if(boutonQuitter.estClique(event))
                        {
                            if(boutonQuitter.event=="Quitter")
                                quitter();
                            else if(boutonQuitter.event=="ApparitionAleatoire")
                            {
                                    menuACreer="Aleatoire";
                                    continuerEvent=false;
                                    std::string a="Resoudre";
                                    boutonQuitter.messageBouton=a;
                                    boutonQuitter.event=a;
                            }
                            else if(boutonQuitter.event=="Resoudre")
                            {
                                    menuACreer="Resoudre";
                                    continuerEvent=false;
                            }
                            else if(boutonQuitter.event=="Manuel")
                            {
                                    menuACreer="Manuel";
                                    continuerEvent=false;
                            }
                        }
                    else if(boutonManuel.estClique(event))
                        {
                            if(boutonManuel.event=="Quitter")
                                quitter();
                            else if(boutonManuel.event=="ApparitionAleatoire")
                            {
                                    continuerEvent=false;
                                    std::string a="Resoudre";
                                    boutonManuel.messageBouton=a;
                                    boutonManuel.event=a;
                                    menuACreer="Aleatoire";
                            }
                            else if(boutonManuel.event=="Resoudre")
                            {
                                    menuACreer="Resoudre";
                                    continuerEvent=false;
                            }
                            else if(boutonManuel.event=="Manuel")
                            {
                                    menuACreer="Manuel";
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

void InterfaceGraphique::grilleAleatoire()
{
    initFondZoomTailleGrilleGraph(grilleGraphiqueAleatoire);

    //definition de la grille, attribition (Numero, ligne, colonne)  TODO : Faire quelque chose de VRAIMENT aleatoire
    {
        grille.setLC(3,0,2);grille.setLC(7,0,4);grille.setLC(5,1,0);
        grille.setLC(1,1,2);grille.setLC(2,1,3);grille.setLC(2,2,0);
        grille.setLC(6,2,4);grille.setLC(1,2,6);grille.setLC(8,2,7);
        grille.setLC(7,3,3);grille.setLC(5,3,4);grille.setLC(6,3,6);
        grille.setLC(3,3,7);grille.setLC(8,4,0);grille.setLC(7,4,8);
        grille.setLC(4,5,1);grille.setLC(6,5,2);grille.setLC(9,5,4);
        grille.setLC(3,5,5);grille.setLC(5,6,1);grille.setLC(7,6,2);
        grille.setLC(4,6,4);grille.setLC(6,6,8);grille.setLC(7,7,5);
        grille.setLC(3,7,6);grille.setLC(3,8,4);grille.setLC(7,8,6);

        //Soluce :
        //781 643 259
        //634 529 817
        //925 871 463
        //
        //896 157 342
        //452 398 176
        //317 462 598
        //
        //263 715 984
        //578 934 621
        //149 286 735
    }

    grilleGraphiqueAleatoire.grille=grille;
    grilleGraphiqueAleatoire.afficherGrilleGraph();
    grilleGraphiqueAleatoire.grille.afficherConsole();

    boutonAleatoire.chargerBouton();
    boutonQuitter.chargerBouton();
    SDL_Flip(fond);

    continuerEvent=true;
	afficherCliquezSurUneCase();
    while(continuerEvent)
    {
        eventMenuResoudreAleatoire();
    }
}

void InterfaceGraphique::grilleVide()
{
	//TODO faire apparaitre une grille vide puis appeler eventMenuResoudreGrilleVide
	grilleGraphiqueVide.grille = grille;
	initFondZoomTailleGrilleGraph(grilleGraphiqueVide);
	grilleGraphiqueVide.afficherGrilleGraph();
	SDL_Flip(fond);

	continuerEvent = true;
	int valeurChangee = 0;// initialisation de la valeur : si reste à 0, n'a pas été touchée par l'user

	afficherCliquezSurUneCase();

	while (continuerEvent)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_KEYDOWN:  //Gestion clavier
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE: //Appuyer sur echap : quitte
						quitter();
				}
			case SDL_MOUSEBUTTONDOWN: //Gestion souris
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT://clic gauche souris
						for (int line = 0; line < 9; line++)
						{
							for (int column = 0; column < 9; column++)
							{
								if (grilleGraphiqueVide.sudokuBouton[line][column].estClique(event))//On verifie si le bouton est cliqué :
								{
									SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
									boutonQuitter.chargerBouton();
									grilleGraphiqueVide.afficherGrilleGraph();//On enleve le "cliquez sur une case"

									afficherEntrezUnChiffre();

									grilleGraphiqueVide.sudokuBouton[line][column] = eventChangerValeur(grilleGraphiqueVide.sudokuBouton[line][column]);//Si tel est le cas, on change sa valeur par l'event dans cette fonction
									int nouvelleValeur = std::atoi(grilleGraphiqueVide.sudokuBouton[line][column].messageBouton.c_str());
									grille.setLC(nouvelleValeur, line, column);//on met  jour la grille
									grilleGraphiqueVide.grille = grille;//Et la grille graphique

									grilleGraphiqueVide.afficherGrilleGraph();
								}
							}
						}
					}
		}
	}
}

Bouton InterfaceGraphique::eventChangerValeur(Bouton bouton)
{
	continuerEventChangerValeur = true;
	int valeurChangee = 0;
	while (continuerEventChangerValeur)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_KEYDOWN:  //Gestion clavier
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE: //Appuyer sur echap : quitte
				quitter();
				break;
			case SDLK_SPACE: // appuyer sur espace : change de bouton
			{
				return bouton;
			}
			case SDLK_1:case SDLK_KP1:
				valeurChangee = 1;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			case SDLK_2:case SDLK_KP2:
				valeurChangee = 2;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			case SDLK_3:case SDLK_KP3:
				valeurChangee = 3;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			case SDLK_4:case SDLK_KP4:
				valeurChangee = 4;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			case SDLK_5:case SDLK_KP5:
				valeurChangee = 5;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			case SDLK_6:case SDLK_KP6:
				valeurChangee = 6;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			case SDLK_7:case SDLK_KP7:
				valeurChangee = 7;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			case SDLK_8:case SDLK_KP8:
				valeurChangee = 8;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			case SDLK_9:case SDLK_KP9:
				valeurChangee = 9;
				break; // On entre le nombre, au NUMPAD ou clavier classique
			default:
				break;//autre : rien.
			}
			continuerEventChangerValeur = false;
			break;
		}
	}
	continuerEvent = true;
	if (valeurChangee == 0)
	{//La valeur n'a pas été changée
		return bouton;
	}
	else
	{//On change la valeur de la case
		bouton.messageBouton = std::to_string(valeurChangee);
		return bouton;
	}
}

void InterfaceGraphique::afficherEntrezUnChiffre()
{
	//Position du titre : centré en x, (arbitraire)*zoom en y
	positionEntrezUnChiffre.y = 50 * zoomY;;
	texteEntreUnChiffre = TTF_RenderText_Blended(policeEntrezUnChiffre, "Entrez un Chiffre :", couleurB);
	positionEntrezUnChiffre.x = (tailleX) / 2 - texteEntreUnChiffre->w /2;

	SDL_BlitSurface(texteEntreUnChiffre, NULL, fond, &positionEntrezUnChiffre);
	SDL_Flip(fond);
}

void InterfaceGraphique::afficherPasSolvable()
{
	textePasSolvable = TTF_RenderText_Blended(policePasSolvable, "Pas solvable  :/ ", couleurR);
	positionPasSolvable.x = (tailleX) / 2 - textePasSolvable->w / 2;
	positionPasSolvable.y = (tailleY) / 2 - textePasSolvable->h / 2;
	SDL_BlitSurface(textePasSolvable, NULL, fond, &positionPasSolvable);
	SDL_Flip(fond);
}

void InterfaceGraphique::afficherCliquezSurUneCase()
{
	texteCliquezSurUneCase = TTF_RenderText_Blended(policeEntrezUnChiffre, "Cliquez sur une case", couleurB);
	positionCliquezSurUneCase.x = (tailleX) / 2 - texteCliquezSurUneCase->w/2;
	positionCliquezSurUneCase.y = 50 * zoomY;;
	SDL_BlitSurface(texteCliquezSurUneCase, NULL, fond, &positionCliquezSurUneCase);
	SDL_Flip(fond);
}

void InterfaceGraphique::eventMenuResoudreAleatoire()
{
    //gestion des evenements
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
                case SDL_BUTTON_LEFT :

                        //clic gauche souris
                       if(boutonAleatoire.estClique(event))
                            {
                                if(boutonAleatoire.event=="Quitter")
                                    quitter();
                                else if(boutonAleatoire.event=="ApparitionAleatoire")
                                {
                                    menuACreer="Aleatoire";
                                    continuerEvent=false;
                                    std::string a="Resoudre";
                                    boutonAleatoire.messageBouton=a;
                                    boutonAleatoire.event=a;
                                }
                                else if(boutonAleatoire.event=="Resoudre")
                                {
                                    menuACreer="Resoudre";
                                    continuerEvent=false;
                                }
                                else if(boutonAleatoire.event=="Manuel")
                                {
                                    menuACreer="Manuel";
                                    continuerEvent=false;
                                }
                            }
                        else if(boutonQuitter.estClique(event))
                            {
                                if(boutonQuitter.event=="Quitter")
                                    quitter();
                                else if(boutonQuitter.event=="ApparitionAleatoire")
                                {
                                        menuACreer="Aleatoire";
                                        continuerEvent=false;
                                        std::string a="Resoudre";
                                        boutonQuitter.messageBouton=a;
                                        boutonQuitter.event=a;
                                }
                                else if(boutonQuitter.event=="Resoudre")
                                {
                                        menuACreer="Resoudre";
                                        continuerEvent=false;
                                }
                                else if(boutonQuitter.event=="Manuel")
                                {
                                        menuACreer="Manuel";
                                        continuerEvent=false;
                                }
                            }
                        else if( boutonManuel.estClique(event))
                            {
                                if(boutonManuel.event=="Quitter")
                                    quitter();
                                else if(boutonManuel.event=="ApparitionAleatoire")
                                {
                                    menuACreer="Aleatoire";
                                    continuerEvent=false;
                                    std::string a="Resoudre";
                                    boutonManuel.messageBouton=a;
                                    boutonManuel.event=a;
                                }
                                else if(boutonManuel.event=="Resoudre")
                                {
                                    menuACreer="Resoudre";
                                    continuerEvent=false;
                                }
                                else if(boutonManuel.event=="Manuel")
                                {
                                    menuACreer="Manuel";
                                    continuerEvent=false;
                                }
                            }
						else for (int line = 0; line < 9; line++)
						{
							for (int column = 0; column < 9; column++)
							{
								if (grilleGraphiqueAleatoire.sudokuBouton[line][column].estClique(event))//On verifie si le bouton est cliqué :
								{
									SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
									boutonAleatoire.chargerBouton();
									boutonQuitter.chargerBouton();

									grilleGraphiqueAleatoire.afficherGrilleGraph();//On enleve le "cliquez sur une case"

									afficherEntrezUnChiffre();

									grilleGraphiqueAleatoire.sudokuBouton[line][column] = eventChangerValeur(grilleGraphiqueAleatoire.sudokuBouton[line][column]);//Si tel est le cas, on change sa valeur par l'event dans cette fonction
									int nouvelleValeur = std::atoi(grilleGraphiqueAleatoire.sudokuBouton[line][column].messageBouton.c_str());
									grille.setLC(nouvelleValeur, line, column);//on met  jour la grille
									grilleGraphiqueAleatoire.grille = grille;//Et la grille graphique

									grilleGraphiqueAleatoire.afficherGrilleGraph();
								}
							}
						}
                    break;
                default:
                    ;
            }
            break;
    }
}

void InterfaceGraphique::resoudre()
{
    //Resolution
	if (grille.completer()) // Si on a reussi
	{
		//On enleve la precedente
		chargerFond();
		SDL_Flip(fond);

		initFondZoomTailleGrilleGraph(grilleGraphiqueResolue);
		grilleGraphiqueResolue.grille = grille;
		grilleGraphiqueResolue.grille.afficherConsole(); //affichage dans la console, pour le debug

		grilleGraphiqueResolue.afficherGrilleGraph();
		SDL_Flip(fond);
		SDL_Delay(2500);//laisse letemps pour voir la grille
	}
	else // sinon, pas solvable
	{
		chargerFond();
		afficherPasSolvable();
		SDL_Flip(fond);
		SDL_Delay(2000);
	}
}





