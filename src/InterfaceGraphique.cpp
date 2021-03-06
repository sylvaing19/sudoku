/**
*	Header de l'INTerface graphique
*	 @author Théo
*	 @file hearders/InterfaceGraphique.h
*/
#include "InterfaceGraphique.h"

//Constructeur
InterfaceGraphique::InterfaceGraphique() : score()
{
    //Initialisation du systeme SDL
    SDL_Init(SDL_INIT_VIDEO);
	
    //Recuperation des informations de l'utilisateur
    infosUser = SDL_GetVideoInfo();

    //change si l'user veux quitter, continuer
    continuerEvent=true;
    quitterAppli=false;

    //La taille de l'ecran se recupere sur les infos
	/*tailleX = 800;
	tailleY = 400;/*/
	tailleX=infosUser->current_w;
	tailleY=infosUser->current_h;

    //Zoom : mon ecran sert de reference (1600*900), et on divise la taille de tout le reste suivant les resolutions
    zoomX=((double)tailleX/1600);
    zoomY=((double)tailleY/900);

    //titre de la fenetre, initialisation de TTF, creation de la fenetre de fond
    SDL_WM_SetCaption("SuDoKu-Solver", NULL);
    TTF_Init();

	fond = SDL_SetVideoMode(tailleX, tailleY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Definition du fond : fullscreen, etc  | SDL_FULLSCREEN

	couleurN = { 1, 1, 1 };
	couleurB = { 0, 0, 255 };
	couleurV = { 0, 255, 0 };
	couleurR = { 255, 0, 0 };
	couleurGri = { 200, 240, 255 };

	nombreVies = 3;// nombre de vie, d'indices autorisés
	sudokuApparaitAleatoire = false, sudokuAResoudre = false; //initialisation de booleens
	svgTimer=0;

}



/********	Lancement des menus, resolution 	********/


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

/// Fonction la plus importante de ce module n2
// initialisation du menu resoudre : boutons, etc, et animations / gestion des events ...
void InterfaceGraphique::menuResoudre()
{
	nomImageFond = "images/fond2.bmp";
	chargerFond();

	//initialisations diverses
	initPolices();
	texteTitre = "Resolution de Sudoku";

	initBoutonsMenuResoudre();

	SDL_Flip(fond);

	continuerEvent = true;
	while (continuerEvent)
	{
		boutonAleatoire.chargerBouton();
		boutonQuitter.chargerBouton();
		boutonManuel.chargerBouton();

		eventMenuResoudre();
	}
}

/// gestion graphique de la resolution, ou son echec, de la grille
void InterfaceGraphique::resoudre()
{
    bool finiSansResoudre=false;
    if(grille.estEgale(grilleResolue))
        finiSansResoudre=true;

	//Resolution
	if (grille.completer()) // Si on a reussi
	{
        score.stopTimer();
        if(!finiSansResoudre)
            score.removeScore(score.getScore());

		//On enleve la precedente
		chargerFond();
		SDL_Flip(fond);

		initFondZoomTailleGrilleGraph(grilleGraphiqueResolue);
		grilleGraphiqueResolue.grille = grille;
		grilleGraphiqueResolue.grille.afficherConsole(); //affichage dans la console, pour le debug

		grilleGraphiqueResolue.creerGrilleGraph();
		SDL_Flip(fond);
		SDL_Delay(2500);//laisse le temps pour voir la grille

		animationFin();
        SDL_Quit();
        TTF_Quit();
	}
	else // sinon, pas solvable
	{
		chargerFond();
		afficherPasSolvable();
		SDL_Delay(2000);
        SDL_Quit();
        TTF_Quit();
	}
}

/// gestion graphique de la resolution, ou son echec, de la grille
void InterfaceGraphique::resoudreVide()
{
	bool finiSansResoudre = false;
	if (grille.estEgale(grilleResolue))
		finiSansResoudre = true;

	//Resolution
	if (grille.completer()) // Si on a reussi
	{
		//On enleve la precedente
		chargerFond();
		SDL_Flip(fond);

		initFondZoomTailleGrilleGraph(grilleGraphiqueResolue);
		grilleGraphiqueResolue.grille = grille;

		grilleGraphiqueResolue.creerGrilleGraph();
		SDL_Flip(fond);

		afficherAppuyerSurEchap();

		bool end = false;
		while (!end)
		{
			SDL_WaitEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
				end = true;
			case SDL_KEYDOWN:  //Gestion clavier
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE: //Appuyer sur echap : quitte
					end = true;
					break;
				default:
					;
				}
				break;
			default:
				;
			}
		}

		SDL_Quit();
		TTF_Quit();
	}
	else // sinon, pas solvable
	{
		chargerFond();
		afficherPasSolvable();
	
		SDL_Delay(2000);
		SDL_Quit();
		TTF_Quit();
	}
}

void InterfaceGraphique::menuPhoto()
{
	//affichage fond
	nomImageFond = "images/fond3.bmp";
	chargerFond();
	SDL_Flip(fond);

	//initialisations diverses
	initPolices();
	texteTitre = "Photo-Doku";

	afficherImageUser();
}



/********	Chargements, initialisations	********/


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
  //  initFondZoomTailleBouton(boutonMenu2);
    initFondZoomTailleBouton(boutonQuitter);

    //paramètres du bouton 1
    {
        std::string a="images/BoutonMenu.bmp";
        boutonMenu1.nomImageBouton=a;
        a="polices/Cybernetica_Normal.ttf";
        boutonMenu1.nomPolice=a;
        a="Jouer";
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
/*
    //paramètres du bouton 2
    {
        std::string a="images/BoutonMenu.bmp";
        boutonMenu2.nomImageBouton=a;
        a="polices/Cybernetica_Normal.ttf";
        boutonMenu2.nomPolice=a;
        a="Photo-Doku";
        boutonMenu2.messageBouton=a;
		boutonMenu2.event = a;
        boutonMenu2.couleurTexteBouton={255, 0, 0};
        boutonMenu2.taillePolice=70*zoomX;
        boutonMenu2.centreX="oui";
        boutonMenu2.positionBouton.y+=(boutonMenu1.positionBouton.y+(boutonMenu1.imageBouton->h)*3/2);
    }
    boutonMenu2.chargerBouton();*/

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

/// initialise tous les boutons du menu resoudre
void InterfaceGraphique::initBoutonsMenuResoudre()
{
	initFondZoomTailleBouton(boutonAleatoire);
	initFondZoomTailleBouton(boutonManuel);
	initFondZoomTailleBouton(boutonQuitter);
	initFondZoomTailleBouton(boutonIndice);

	//paramètres du bouton aleatoire
	{
		std::string a = "images/BoutonSudoku.bmp";
		boutonAleatoire.nomImageBouton = a;
		a = "polices/Cybernetica_Normal.ttf";
		boutonAleatoire.nomPolice = a;
		a = "Aleatoire";
		boutonAleatoire.messageBouton = a;
		a = "ApparitionAleatoire";
		boutonAleatoire.event = a;
		boutonAleatoire.couleurTexteBouton = { 255, 255, 255 };
		boutonAleatoire.taillePolice = 70 * zoomX;
		boutonAleatoire.positionBouton.x += 30 * boutonAleatoire.zoomX;
		boutonAleatoire.positionBouton.y += 30 * boutonAleatoire.zoomY;
	}
	boutonAleatoire.chargerBouton();

	//paramètres du bouton de generation à la main
	{
		std::string a = "images/BoutonSudoku.bmp";
		boutonManuel.nomImageBouton = a;
		a = "polices/Cybernetica_Normal.ttf";
		boutonManuel.nomPolice = a;
		a = "Vide";
		boutonManuel.messageBouton = a;
		a = "Manuel";
		boutonManuel.event = a;
		boutonManuel.couleurTexteBouton = { 255, 255, 255 };
		boutonManuel.taillePolice = 70 * zoomX;
		boutonManuel.positionBouton.x += boutonAleatoire.positionBouton.x;
		boutonManuel.positionBouton.y += 30 * boutonAleatoire.zoomY + boutonAleatoire.positionBouton.y + boutonAleatoire.positionBouton.h;
	}
	boutonManuel.chargerBouton();

	//paramètres du bouton quitter
	{
		boutonQuitter.positionBouton.x = (tailleX - 65 * zoomX);
		boutonQuitter.positionBouton.y = 15 * zoomY;
		std::string a = "images/arret.bmp";
		boutonQuitter.nomImageBouton = a;
		a = "Quitter";
		boutonQuitter.event = a;
	}
	boutonQuitter.chargerBouton();

	//parametre du bouton indice
	{
		std::string a = "images/BoutonSudoku.bmp";
		boutonIndice.nomImageBouton = a;
		a = "polices/Cybernetica_Normal.ttf";
		boutonIndice.nomPolice = a;
		a = "Indice";
		boutonIndice.messageBouton = a;
		a = "Indice";
		boutonIndice.event = a;
		boutonIndice.couleurTexteBouton = { 255, 255, 255 };
		boutonIndice.taillePolice = 70 * zoomX;
		boutonIndice.positionBouton.x += boutonManuel.positionBouton.x;
		boutonIndice.positionBouton.y += 30 * boutonAleatoire.zoomY + boutonManuel.positionBouton.y + boutonManuel.positionBouton.h;
	}
}

// charge les boutons du menu principal dans le buffer, prets  etre flippés
void InterfaceGraphique::chargerBoutonsMenuPrincipal()
{
    boutonQuitter.chargerBouton();
   // boutonMenu2.chargerBouton();
    boutonMenu1.chargerBouton();
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
		printf("Probleme avec %s", nomImageFond.c_str());
		SDL_Quit();
	}

	positionFond.x = 0, positionFond.y = 0;
	SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
}

//polices avec leurs tailles
void InterfaceGraphique::initPolices()
{
	policeTitre = policeEntrezUnChiffre = TTF_OpenFont("polices/A Simple Life.ttf", 100 * zoomX);
	if (policeTitre == NULL || policeEntrezUnChiffre == NULL)
	{
		SDL_Quit();
	}
	policeAuRevoir = TTF_OpenFont("polices/SF_Toontime.ttf", 150 * zoomX);
	if (policeAuRevoir == NULL)
	{
		SDL_Quit();
	}
	policeSudoku = TTF_OpenFont("polices/Cybernetica_Normal.ttf", 30 * zoomX);
	if (policeSudoku == NULL)
	{
		SDL_Quit();
	}
	policePasSolvable = TTF_OpenFont("polices/Cybernetica_Normal.ttf", 50 * zoomX);
	if (policePasSolvable == NULL)
	{
		SDL_Quit();
	}
	policeTimer = TTF_OpenFont("polices/Cybernetica_Normal.ttf", 20 * zoomX);
	if (policeTimer == NULL)
	{
		SDL_Quit();
	}
}

void InterfaceGraphique::initTitre()
{
	policeTitre = TTF_OpenFont("polices/A Simple Life.ttf", 120 * zoomX);
	imageTitre = TTF_RenderText_Blended(policeTitre, texteTitre.c_str(), couleurR);

	//Position du titre : centré en x, (arbitraire)*zoom en y
	positionTitre.x = (tailleX - (imageTitre->w)) / 2;
	positionTitre.y = 50 * zoomY;
}



/********	Gestion des evenements	********/


// Gere l'event dans le menu principal : quitter / creer une grille vide / creer une grille aleatoire
void InterfaceGraphique::eventMenuPrincipal()
{
	SDL_WaitEvent(&event);
	switch (event.type)
	{
   case SDL_QUIT:
        quitter();
	case SDL_KEYDOWN:  //Gestion clavier
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE: //Appuyer sur echap : quitte
			quitter();
			continuerEvent = false;//inutile car quittte deja mais explicite
			break;
		default:
			;
		}
		break;

	case SDL_MOUSEBUTTONDOWN: //Gestion souris
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:

			//clic gauche souris
			if (boutonQuitter.estClique(event))
			{
				boutonQuitter=eventBoutonClique(boutonQuitter);
			}

			//clic sur le menu 1
			else if (boutonMenu1.estClique(event))
			{
				boutonMenu1=eventBoutonClique(boutonMenu1);
			}

			//clic sur le menu 2
			/*else if (boutonMenu2.estClique(event))
			{
				boutonMenu2=eventBoutonClique(boutonMenu2);
			}*/
			break;
		default:
			;
		}
		break;
	default:
		;
	}
}

/// gere l'evenement dans le menu resoudre
void InterfaceGraphique::eventMenuResoudre()
{
    ///gestion des events :

    SDL_WaitEvent(&event);
    switch(event.type)
    {
   case SDL_QUIT:
            quitter();
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
						boutonAleatoire=eventBoutonClique(boutonAleatoire);
                    }
                    else if(boutonQuitter.estClique(event))
					{
						boutonQuitter=eventBoutonClique(boutonQuitter);
					}
					else if (boutonManuel.estClique(event))
					{
						boutonManuel = eventBoutonClique(boutonManuel);
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

/// gere l'entrée claavier du nombre afin de changer la case
Bouton InterfaceGraphique::eventChangerValeur(Bouton bouton)
{
	caseSuivante = false;
	continuerEventChangerValeur = true;
	int valeurChangee = 0;
	while (continuerEventChangerValeur)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
       case SDL_QUIT:
            quitter();
		case SDL_KEYDOWN:  //Gestion clavier
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE: //Appuyer sur echap : quitte
				quitter();
				break;
			case SDLK_SPACE: // appuyer sur espace : change de bouton
			{
				 caseSuivante = true;
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
				valeurChangee = 10;
				break;//autre : on vide la case.
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
	else if (valeurChangee == 10)
	{
		// cas où on vide la case
		bouton.messageBouton = " ";
		return bouton;
	}
	else
	{//On change la valeur de la case
		bouton.messageBouton = std::to_string(valeurChangee);
		bouton.modifieParUser = true;
		return bouton;
	}
}

/// gere l'evenement declenché par le bouton : quitte; lance le string du menu à creer... et retourne le nouveau bouton
Bouton InterfaceGraphique::eventBoutonClique(Bouton bouton)
{
	if (bouton.event == "Quitter")
		quitter();
	else if (bouton.event == "ApparitionAleatoire")
	{
		menuACreer = "Aleatoire";
		continuerEvent = false;
		std::string a = "Resoudre";
		bouton.messageBouton = a;
		bouton.event = a;
	}
	else if (bouton.event == "ApparitionAleatoireVide")
	{
		menuACreer = "Aleatoire";
		continuerEvent = false;
		std::string a = "ResoudreVide";
		bouton.event = a;
		a = "Resoudre";
		bouton.messageBouton = a;

	}
	else if (bouton.event == "Resoudre")
	{
		menuACreer = "Resoudre";
		continuerEvent = false;
	}
	else if (bouton.event == "Manuel")
	{
		menuACreer = "Manuel";
		continuerEvent = false;
	}
	else if (bouton.event == "Indice")
	{
		menuACreer = "Indice";
		continuerEvent = false;
	}
	else if (bouton.event == "Photo-Doku")
	{
		menuACreer = "Photo-Doku";
		continuerEvent = false;
	}
	else if (bouton.event == "Easy")
	{
        menuACreer="Easy";
		continuerEvent = false;
	}
	else if (bouton.event == "Medium")
	{
        menuACreer="Medium";
		continuerEvent = false;
	}
	else if (bouton.event == "Hard")
	{
        menuACreer="Hard";
		continuerEvent = false;
	}
	else if (bouton.event == "ResoudreVide")
	{
		menuACreer = "ResoudreVide";
		continuerEvent = false;
	}
	return bouton;
}

/// gestion des evenements dans le menu "resoudre"
void InterfaceGraphique::eventMenuResoudreAleatoire()
{
    if(svgTimer != score.getTimer()) // on ne change l'affichage que si le temps, en secondes, a vraiment changé
    // ie : si moins d'une seconde est passée, on ne change rien
    {
        // on enleve tout pour le timer
        SDL_BlitSurface(imageFond, NULL, fond, &positionFond);

        boutonAleatoire.chargerBouton();
        boutonQuitter.chargerBouton();
        boutonIndice.chargerBouton();
        chargerTimer();
        chargerCliquezSurUneCase();
        grilleGraphiqueAleatoire.afficherGrille();

        svgTimer=score.getTimer();
	}

	if (grilleGraphiqueAleatoire.estComplete())
	{
		resoudre();
		continuerEvent = false;
		return;
	}

	//gestion des evenements
	SDL_PollEvent(&event);
	switch (event.type)
	{
    case SDL_QUIT:
        quitter();
	case SDL_KEYDOWN:  //Gestion clavier
		switch (event.key.keysym.sym)
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
            case SDL_BUTTON_LEFT:

                //clic gauche souris
                if (boutonAleatoire.estClique(event))
                {
                    boutonAleatoire=eventBoutonClique(boutonAleatoire);
                }
                else if (boutonQuitter.estClique(event))
                {
                    boutonQuitter=eventBoutonClique(boutonQuitter);
                }
                else if (boutonIndice.estClique(event))
                {
                    grilleGraph = grilleGraphiqueAleatoire;// on met à jour la grille temporaire
                    indice();
                    grilleGraphiqueAleatoire=grilleGraph;
					SDL_Delay(100);
                }
                else for (int line = 0; line < 9; line++)
                {
                    for (int column = 0; column < 9; column++)
                    {
                        if (grilleGraphiqueAleatoire.sudokuBouton[line][column].estClique(event))//On verifie si le bouton est cliqué :
                        {
                            SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
                            chargerTimer();
                            boutonAleatoire.chargerBouton();
                            boutonQuitter.chargerBouton();
                            boutonIndice.chargerBouton();
                            grilleGraphiqueAleatoire.afficherGrille();//On enleve le "cliquez sur une case"
                            afficherEntrezUnChiffre();

                            grilleGraphiqueAleatoire.sudokuBouton[line][column] = eventChangerValeur(grilleGraphiqueAleatoire.sudokuBouton[line][column]);//Si tel est le cas, on change sa valeur par l'event dans cette fonction
                            int nouvelleValeur = std::atoi(grilleGraphiqueAleatoire.sudokuBouton[line][column].messageBouton.c_str());

                            grille.setLC(nouvelleValeur, line, column);//on met  jour la grille
                            grilleGraphiqueAleatoire.grille = grille;//Et la grille graphique

                            grilleGraphiqueAleatoire.sudokuBouton[line][column].chargerBouton();
                            grilleGraph = grilleGraphiqueAleatoire;// on met à jour la grille temporaire

                            SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
                            grilleGraphiqueAleatoire.afficherGrille();//On enleve le "cliquez sur une case"
                            chargerCliquezSurUneCase();
                            boutonAleatoire.chargerBouton();
                            boutonQuitter.chargerBouton();
                            boutonIndice.chargerBouton();
                            chargerTimer();
                            SDL_Flip(fond);
                        }
                    }
                    SDL_Flip(fond);
                }
                break;
            default:
                ;
		}
		break;
	}
}

///genere une grille vide et lance les evenenements suivants
void InterfaceGraphique::grilleVide()
{
	chargerFond();//On reset l'affichage
	SDL_Flip(fond);

	boutonIndice.chargerBouton();

	boutonAleatoire.event = "ApparitionAleatoireVide";
	boutonAleatoire = eventBoutonClique(boutonAleatoire);// on fais comme s'i lavait été cliqué, pour le transformer en bouton resoudre
	boutonAleatoire.chargerBouton();

	grilleGraphiqueVide.grille = grille;
	initFondZoomTailleGrilleGraph(grilleGraphiqueVide);
	grilleGraphiqueVide.creerGrilleGraph();

	grilleGraph = grilleGraphiqueVide;

	continuerEvent = true;
	int valeurChangee = 0;// initialisation de la valeur : si reste à 0, n'a pas été touchée par l'user

	while (continuerEvent)
	{
		if (grilleGraphiqueVide.estComplete())
		{
			resoudreVide();
			return;
		}

		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quitter();
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
				//clic gauche souris
				if (boutonAleatoire.estClique(event))
				{
					boutonAleatoire = eventBoutonClique(boutonAleatoire);
				}
				else if (boutonQuitter.estClique(event))
				{
					boutonQuitter = eventBoutonClique(boutonQuitter);
				}
				else if (boutonIndice.estClique(event))
				{
					grilleGraph = grilleGraphiqueVide;// on met à jour la grille temporaire
					indice();
					grilleGraphiqueVide = grilleGraph;// on met à jour la grille temporaire
					SDL_Delay(100);
				}
				else for (int line = 0; line < 9; line++)
				{
					for (int column = 0; column < 9; column++)
					{
						if (grilleGraphiqueVide.sudokuBouton[line][column].estClique(event))//On verifie si le bouton est cliqué :
						{
							grilleGraphiqueVide.sudokuBouton[line][column] = eventChangerValeur(grilleGraphiqueVide.sudokuBouton[line][column]);//Si tel est le cas, on change sa valeur par l'event dans cette fonction


							int nouvelleValeur = std::atoi(grilleGraphiqueVide.sudokuBouton[line][column].messageBouton.c_str());
							grille.setLC(nouvelleValeur, line, column);//on met  jour la grille
							grilleGraphiqueVide.grille = grille;//Et la grille graphique

							grilleGraphiqueVide.sudokuBouton[line][column].chargerBouton();
							SDL_Flip(fond);


							grilleGraph = grilleGraphiqueVide;// on met à jour la grille temporaire

						}
					}

				}
			}
		}
	}

	if (grilleGraphiqueVide.estComplete())
	{
		resoudreVide();
		return;
	}
}




/********	Generation des grilles	********/


///genere une grille aleatoire et lance les evenenements suivants
void InterfaceGraphique::grilleAleatoire()
{
    initFondZoomTailleGrilleGraph(grilleGraphiqueAleatoire);
	// on reinitialise le fond

	chargerFond();

    // On initialise tout, et on zoome ces boutons
    initFondZoomTailleBouton(boutonEasy);
    boutonEasy.zoomX/=2;

    initFondZoomTailleBouton(boutonMedium);
    boutonMedium.zoomX/=2;

    initFondZoomTailleBouton(boutonHard);
    boutonHard.zoomX/=2;


    //paramètres du bouton easy
	{
		boutonEasy.positionBouton.x = (tailleX/10* zoomX);
		boutonEasy.positionBouton.y = (tailleY/3 * zoomX);
		std::string a = "images/BoutonMenu.bmp";
		boutonEasy.nomImageBouton = a;
		a = "polices/Cybernetica_Normal.ttf";
		boutonEasy.nomPolice = a;
		a = "Easy";
        boutonEasy.messageBouton = a;
		boutonEasy.event = a;
		boutonEasy.couleurTexteBouton=couleurV;
        boutonEasy.taillePolice=90;

	}
	boutonEasy.chargerBouton();

	//paramètres du bouton medium
	{
		boutonMedium.positionBouton.x = (tailleX/9*zoomX+ boutonEasy.positionBouton.w+boutonEasy.positionBouton.x);
		boutonMedium.positionBouton.y = (tailleY/3 * zoomX);
		std::string a = "images/BoutonMenu.bmp";
		boutonMedium.nomImageBouton = a;
		a = "polices/Cybernetica_Normal.ttf";
		boutonMedium.nomPolice = a;
		a = "Medium";
		boutonMedium.event = a;
        boutonMedium.messageBouton = a;
        boutonMedium.couleurTexteBouton=couleurB;
        boutonMedium.taillePolice=90;
	}
	boutonMedium.chargerBouton();

	//paramètres du bouton hard
	{
		boutonHard.positionBouton.x = (tailleX/9* zoomX)+ boutonMedium.positionBouton.w+boutonMedium.positionBouton.x;
		boutonHard.positionBouton.y = (tailleY/3 * zoomX);
		std::string a = "images/BoutonMenu.bmp";
		boutonHard.nomImageBouton = a;
		a = "polices/Cybernetica_Normal.ttf";
		boutonHard.nomPolice = a;
		a = "Hard";
		boutonHard.event = a;
        boutonHard.messageBouton = a;
        boutonHard.couleurTexteBouton=couleurR;
        boutonHard.taillePolice=90;
	}
	boutonHard.chargerBouton();

	SDL_Flip(fond);



    bool clic=false;
    //gestion des evenements de la difficulté
    while(!clic)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
                quitter();
        case SDL_KEYDOWN:  //Gestion clavier
            switch (event.key.keysym.sym)
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
            case SDL_BUTTON_LEFT:
            {
                //clic gauche souris
                if (boutonEasy.estClique(event))
                {
                    clic=true;
                    boutonEasy=eventBoutonClique(boutonEasy);
                }
                else if (boutonMedium.estClique(event))
                {
                    clic=true;
                    boutonMedium=eventBoutonClique(boutonMedium);
                }
                else if (boutonHard.estClique(event))
                {
                    clic=true;
                    boutonHard=eventBoutonClique(boutonHard);
                }
                break;
            }
            default:
                ;
            }
            break;
        }
    }
    chargerFond();
	SDL_Flip(fond);

    if(menuACreer=="Easy")
       difficulte=FACILE ;
    else if(menuACreer=="Medium")
        difficulte=MOYEN ;
    else if(menuACreer=="Hard")
        difficulte=DIFFICILE;

    grille.generer(difficulte);

/*

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
    }*/

    score.initScore(difficulte);
	chargerTimer();

    grilleGraphiqueAleatoire.grille=grille;
    grilleGraphiqueAleatoire.creerGrilleGraph();
    grilleGraphiqueAleatoire.grille.afficherConsole();
	grilleGraph = grilleGraphiqueAleatoire;

	grilleResolue = grilleGraphiqueAleatoire.grille;
	grilleResolue.completer(); // on resoud la grille pour plus tard
	grilleGraphiqueAleatoire.grilleResolue = grilleResolue;
	grilleGraph.grilleResolue = grilleResolue;


    boutonAleatoire.chargerBouton();
    boutonQuitter.chargerBouton();
	boutonIndice.chargerBouton();
    SDL_Flip(fond);

    continuerEvent=true;
	chargerCliquezSurUneCase();
    while(continuerEvent)
    {
        eventMenuResoudreAleatoire();
	}
}



/********	Affichage basique de texte	********/

/// affiche le timer
void InterfaceGraphique::chargerTimer()
{
	long int temps = static_cast<long int> (score.getTimer());
	std::string stringTimer;
	stringTimer += "Temps :  ";
	stringTimer += std::to_string(temps);

	texteTimer = TTF_RenderText_Blended(policeTimer, stringTimer.c_str(), couleurB);
	if (texteTimer == NULL)
	{
		SDL_Quit();
	}
	positionTimer.x = tailleX / 2 - (texteTimer->w / 2)*zoomX;
	positionTimer.y = tailleY *9/10 - (texteTimer->h / 2)*zoomX;
	SDL_BlitSurface(texteTimer, NULL, fond, &positionTimer);
}

/// affiche un texte
void InterfaceGraphique::afficherEntrezUnChiffre()
{
	positionEntrezUnChiffre.y = 50 * zoomY;;
	texteEntreUnChiffre = TTF_RenderText_Blended(policeEntrezUnChiffre, "Entrez un Chiffre :", couleurB);
	positionEntrezUnChiffre.x = (boutonAleatoire.positionBouton.x + boutonAleatoire.positionBouton.w)* zoomX;

	SDL_BlitSurface(texteEntreUnChiffre, NULL, fond, &positionEntrezUnChiffre);
	SDL_Flip(fond);
}

/// affiche un texte
void InterfaceGraphique::afficherAppuyerSurEchap()
{
	positionEntrezUnChiffre.y = 50 * zoomY;;
	texteEntreUnChiffre = TTF_RenderText_Blended(policeEntrezUnChiffre, "Appuyez sur Echap :", couleurB);
	positionEntrezUnChiffre.x = (boutonAleatoire.positionBouton.x + boutonAleatoire.positionBouton.w)* zoomX;

	SDL_BlitSurface(texteEntreUnChiffre, NULL, fond, &positionEntrezUnChiffre);
	SDL_Flip(fond);
}

/// affiche un texte
void InterfaceGraphique::afficherPasSolvable()
{
	textePasSolvable = TTF_RenderText_Blended(policePasSolvable, "Pas solvable  :/ ", couleurR);
	positionPasSolvable.x =  tailleX / 2 - (textePasSolvable->w / 2 )*zoomX;
	positionPasSolvable.y =  tailleY / 2 - (textePasSolvable->h / 2 )*zoomY;

	SDL_BlitSurface(textePasSolvable, NULL, fond, &positionPasSolvable);
	SDL_Flip(fond);
}

/// affiche un texte
void InterfaceGraphique::chargerCliquezSurUneCase()
{
	texteCliquezSurUneCase = TTF_RenderText_Blended(policeEntrezUnChiffre, "Cliquez sur une case", couleurB);
	positionCliquezSurUneCase.x = (boutonAleatoire.positionBouton.x + boutonAleatoire.positionBouton.w )* zoomX;
	positionCliquezSurUneCase.y = 50 * zoomY;

	SDL_BlitSurface(texteCliquezSurUneCase, NULL, fond, &positionCliquezSurUneCase);
}


/********	Photo-Doku		********/

void InterfaceGraphique::afficherImageUser()
{
	// affiche l'ordre que l'user doit executer
	texteEntrezImage = TTF_RenderText_Blended(policeAuRevoir, "Choisissez l'image", couleurB);
	if (texteEntrezImage == NULL)
	{
		SDL_Quit();
	}

	positionEntrezImage.x = (tailleX - (texteEntrezImage->w)) / 2;
	positionEntrezImage.y = (tailleY - (texteEntrezImage->h)) / 2;
	SDL_BlitSurface(texteEntrezImage, NULL, fond, &positionEntrezImage);
	SDL_Flip(fond);

	SDL_Delay(1000);
	SDL_BlitSurface(imageFond, NULL, fond, &positionFond);


	nomImageUser = "photo/"; // toutes les images seront dans le dossier photo
	nomImageUser += "sudoku.bmp";	//TODO entrer l'image


	imageSudokuUser = SDL_LoadBMP(nomImageUser.c_str());
	if (imageSudokuUser == NULL)
	{
		SDL_Quit();
	}

	positionImageUser.x = (tailleX - (imageSudokuUser->w)) / 2;
	positionImageUser.y = (tailleY - (imageSudokuUser->h)) / 2;

	SDL_BlitSurface(imageSudokuUser, NULL, fond, &positionImageUser);
	SDL_Flip(fond);
	SDL_Delay(1000);
	SDL_Quit();
	return;
}


/********	Inclassables =(		********/

//animation d'intro : titre qui apparait, et boutons apparaissant
void InterfaceGraphique::intro()
{
	int i;
	int a = positionTitre.y;
	//animation, titre qui descend
	for (i = 0; i <= a; i+=3*zoomY)
	{
		positionTitre.y = i;

		SDL_BlitSurface(imageFond, NULL, fond, &positionFond);
		SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
		SDL_Flip(fond);
	}
	SDL_BlitSurface(imageTitre, NULL, fond, &positionTitre);
}

//gestion de l'event "quitter" : clic sur le bouton d'arret ou echap : coupe toute l'application directement.
int InterfaceGraphique::quitter()
{
	continuerEvent = false;
	quitterAppli = true;

	SDL_BlitSurface(imageFond, NULL, fond, &positionFond);

	texteAdieu = TTF_RenderText_Blended(policeAuRevoir, "Au revoir !", couleurB);
	positionAuRevoir.x = (tailleX - (texteAdieu->w)) / 2;
	positionAuRevoir.y = (tailleY - (texteAdieu->h) - 100 * zoomY) / 2;

	SDL_BlitSurface(texteAdieu, NULL, fond, &positionAuRevoir);
	SDL_Flip(fond);
	SDL_Delay(1000);
	SDL_Quit();
    return EXIT_SUCCESS;
}

/// gere les indices donnés à l'user : on affiche brievement l'indice
void InterfaceGraphique::indice()
{
    grilleGraph.afficherIndice();
    score.indiceUtilise();
	grille=grilleGraph.grille;// on met à jour la grille
	SDL_Flip(fond);
}

void InterfaceGraphique::animationFin()
{
    SDL_BlitSurface(imageFond, NULL, fond, &positionFond); // on enleve tout

    texteAdieu = TTF_RenderText_Blended(policeAuRevoir, "Grille finie ! Bravo !", couleurB);
	positionAuRevoir.x = (tailleX - (texteAdieu->w)) / 2;
	positionAuRevoir.y = (tailleY - (texteAdieu->h)) / 3;

    SDL_BlitSurface(texteAdieu, NULL, fond, &positionAuRevoir);

    std::string stringScore;
    stringScore="Score :  ";
    stringScore+=std::to_string(score.getScore());
    texteScore=TTF_RenderText_Blended(policeAuRevoir, stringScore.c_str(), couleurB);

    positionScore.x = (tailleX - (texteAdieu->w)) / 2;
	positionScore.y = positionAuRevoir.y+(texteAdieu->h)+(texteScore->h)/3;

    SDL_BlitSurface(texteScore, NULL, fond, &positionScore);


    SDL_Flip(fond);
	SDL_Delay(1500);

    positionArtifice.x =  (tailleX)/3 ;
	positionArtifice.y =  (tailleY)/3 +(rand()%5)*(tailleY)/10;

	positionArtifice2.x=  (tailleX)/3 +(rand()%5)*(tailleX)/10;
	positionArtifice2.y=  (tailleY)/3;

    positionArtifice3.x = (tailleX)/3 ;
	positionArtifice3.y = (tailleY)/3 -(rand()%5)*(tailleY)/10;

    positionArtifice4.x = (tailleX)/3 -(rand()%5)*(tailleX)/10;
	positionArtifice4.y = (tailleY)/3;

	for(int i=7;i<19;i++)
	{
        std::string stringImage;
        stringImage+= "images/artifice/frame-";
        if(1<=i && i<=9)
        {
            stringImage+="0";
        }

        stringImage += std::to_string(i);
        stringImage +=".bmp";


        artifice[i-7] = SDL_LoadBMP(stringImage.c_str());

        SDL_SetColorKey(artifice[i-7], SDL_SRCCOLORKEY, SDL_MapRGB(artifice[i-7]->format, 0, 0, 0)); // met le blanc en transparent pour le bouton
        artifice[i-7] = zoomSurface(artifice[i-7], 3*zoomX, 3*zoomY, 0);
	}

    for(int j=0;j<5;j++)
        for(int i=0;i<12;i++)
        {
            SDL_BlitSurface( artifice[i], NULL, fond, &positionArtifice);

            if(i<12-3)
                SDL_BlitSurface( artifice[i+3], NULL, fond, &positionArtifice2);
            else
                SDL_BlitSurface( artifice[i-12+3], NULL, fond, &positionArtifice2);

            if(i<12-5)
                SDL_BlitSurface( artifice[i+5], NULL, fond, &positionArtifice3);
            else
                SDL_BlitSurface( artifice[i-12+5], NULL, fond, &positionArtifice3);

            if(i<12-9)
                SDL_BlitSurface( artifice[i+9], NULL, fond, &positionArtifice4);
            else
                SDL_BlitSurface( artifice[i-12+9], NULL, fond, &positionArtifice4);

            SDL_Flip(fond);
            SDL_Delay(50);
            SDL_BlitSurface(imageFond, NULL, fond, &positionFond); // on enleve tout
            SDL_Delay(50);
        }

}


