/**
*	Header de la grrille graphique
*	 @author Théo
*	 @file hearders/GrilleGrahique.h
*/

#include "GrilleGraphique.h"

/// constructeur
GrilleGraphique::GrilleGraphique()
{
    positionSudoku.x=0;
    positionSudoku.y=0;
    taillePolice=30;
    std::string nomPolice="polices/Cybernetica_Normal.ttf";
    policeSudoku=TTF_OpenFont(nomPolice.c_str(), taillePolice);
	if (policeSudoku == NULL)
	{
		printf("Probleme avec %s", nomPolice.c_str());
		SDL_Quit();
	}

	couleurN = { 1, 1, 1 };
	couleurB = { 0, 0, 255 };
	couleurV = { 0, 120, 0 };
	couleurR = { 255, 0, 0 };
	couleurGri = { 200, 240, 255 };

	srand(time(NULL));
}

/// fonction affichant une grille graphique correspondant à la grille sans indice
void GrilleGraphique::creerGrilleGraph()
{
	imageSudokuVierge = SDL_LoadBMP("images/SudokuVierge.bmp");
	if (imageSudokuVierge == NULL)
	{
		printf("Probleme avec images/SudokuVierge.bmp");
		SDL_Quit();
	}

	//Position du sudoku : centré en x, et en y qu'on affiche
	positionSudokuVierge.x = tailleX/2 -  ((imageSudokuVierge->w)) / 2 *zoomX;
	positionSudokuVierge.y = tailleY/2 - ((imageSudokuVierge->h)) / 2 *zoomY;

	SDL_SetColorKey(imageSudokuVierge, SDL_SRCCOLORKEY, SDL_MapRGB(imageSudokuVierge->format, 255, 255, 255)); // met le blanc en transparent pour le sudoku
	imageSudokuVierge = zoomSurface(imageSudokuVierge, zoomX, zoomY, 0);
	SDL_BlitSurface(imageSudokuVierge, NULL, fond, &positionSudokuVierge);
	SDL_Flip(fond);

	// Sauvegarde des positions
	int posX = positionSudokuVierge.x + (58 - 47) / 2 * zoomX;
	int posY = positionSudokuVierge.y + (58 - 47) / 2 * zoomY;

	//affectation des valeurs dans les cases
    int line=0;
    for(int ligne=0; ligne<9; ligne++)
    {
		for (int colonne = 0; colonne<9; colonne++)
		{
			int8_t val = grille.getLC(ligne, colonne);
			if (val>0 && val <= 9)
			{//On prend la valeur
				if (sudokuBouton[ligne][colonne].modifieParUser)
				{
					sudokuBouton[ligne][colonne] = creerBouton(val);
					sudokuBouton[ligne][colonne].couleurTexteBouton = couleurB;
					sudokuBouton[ligne][colonne].modifieParUser = true;
				}
				else
				{
					sudokuBouton[ligne][colonne] = creerBouton(val);
					sudokuBouton[ligne][colonne].couleurTexteBouton = couleurN;
					sudokuBouton[ligne][colonne].modifieParUser = false;
				}
			}
			else
			{// La valeur n'existe pas encore
				sudokuBouton[ligne][colonne] = creerBouton(0);
			}

			//On verifie si la grille est solvable, si non, on met la valeur en rouge

			// On donne les positions des boutons
			sudokuBouton[ligne][colonne].positionBouton.x = posX + (58 - 47)/2 * zoomX;
			sudokuBouton[ligne][colonne].positionBouton.y = posY + (58 - 47)/2 * zoomY;

			// On avance vers le prochain bouton
			posX += 58 * zoomX + 1 ;

			//On charge le bouton
			sudokuBouton[ligne][colonne].chargerBouton();
            printf("Bouton en %d / %d chargé \n", ligne, colonne);

		}

		//on change de ligne
		posX = positionSudokuVierge.x + (58 - 47) / 2 * zoomX;
		posY += 58 * zoomY + 1 ;
    }

	SDL_Flip(fond);
}


/// fonction affichant une grille graphique correspondant à la grille avec indice
void GrilleGraphique::afficherGrilleGraphIndice()
{
	imageSudokuVierge = SDL_LoadBMP("images/SudokuVierge.bmp");
	if (imageSudokuVierge == NULL)
	{
		printf("Probleme avec images / SudokuVierge.bmp");
		SDL_Quit();
	}

	//Position du sudoku : centré en x, et en y qu'on affiche
	positionSudokuVierge.x = tailleX / 2 - ((imageSudokuVierge->w)) / 2 * zoomX;
	positionSudokuVierge.y = tailleY / 2 - ((imageSudokuVierge->h)) / 2 * zoomY;

	//booleen verifiant l'existance d'erreur
	erreurExistante = false;

	SDL_SetColorKey(imageSudokuVierge, SDL_SRCCOLORKEY, SDL_MapRGB(imageSudokuVierge->format, 255, 255, 255)); // met le blanc en transparent pour le sudoku
	imageSudokuVierge = zoomSurface(imageSudokuVierge, zoomX, zoomY, 0);
	SDL_BlitSurface(imageSudokuVierge, NULL, fond, &positionSudokuVierge);
	SDL_Flip(fond);

	afficherIndice();

	SDL_Flip(fond);

}

void GrilleGraphique::afficherIndice()
{
	// Sauvegarde des positions
	int posX = positionSudokuVierge.x + (58 - 47) / 2 * zoomX;
	int posY = positionSudokuVierge.y + (58 - 47) / 2 * zoomY;

	//affectation des valeurs dans les cases
	int line = 0;
	for (int ligne = 0; ligne<9; ligne++)
	{
		for (int colonne = 0; colonne<9; colonne++)
		{
			int8_t val = grille.getLC(ligne, colonne);
			if (val>0 && val <= 9)
			{//On prend la valeur
				if (!grille.estPlacable(val, ligne, colonne))// Si il y a une erreur
				{
					sudokuBouton[ligne][colonne].couleurTexteBouton = couleurR;
					sudokuBouton[ligne][colonne].modifieErreur = true;
					erreurExistante = true;
					sudokuBouton[ligne][colonne].chargerBouton();
					SDL_Flip(fond);
				}
				else
				{ // si il n'y a pas de veritable erreur mais que la valeur ne permet pas la resolution
					int8_t valResolue = grilleResolue.getLC(ligne, colonne);
					if (valResolue>0 && valResolue <= 9)
						if (!(valResolue == val))
						{
							sudokuBouton[ligne][colonne].modifieErreur = true;
							sudokuBouton[ligne][colonne].couleurTexteBouton = couleurR;
							erreurExistante = true;
							sudokuBouton[ligne][colonne].chargerBouton();
							SDL_Flip(fond);
						}
						else
						{
							sudokuBouton[ligne][colonne].modifieErreur = false;
						}
				}
			}

			//On verifie si la grille est solvable, si non, on met la valeur en rouge

			// On donne les positions des boutons
			sudokuBouton[ligne][colonne].positionBouton.x = posX + (58 - 47) / 2 * zoomX;
			sudokuBouton[ligne][colonne].positionBouton.y = posY + (58 - 47) / 2 * zoomY;

			// On avance vers le prochain bouton
			posX += 58 * zoomX + 1;
		}

		//on change de ligne
		posX = positionSudokuVierge.x + (58 - 47) / 2 * zoomX;
		posY += 58 * zoomY + 1;
	}

	bool indicePlace=false;
	if (!erreurExistante)
		while (!indicePlace)
		{
			int colonneRand = rand() % 9;
			int ligneRand = rand() % 9;
			if (grille.getLC(ligneRand, colonneRand) == 0)
			{// La valeur n'existe pas encore
				int val = grilleResolue.getLC(ligneRand, colonneRand);

				int svgPosX = sudokuBouton[ligneRand][colonneRand].positionBouton.x;
				int svgPosY = sudokuBouton[ligneRand][colonneRand].positionBouton.y;

				sudokuBouton[ligneRand][colonneRand] = creerBouton(val);
				grille.setLC(val, ligneRand, colonneRand);

				sudokuBouton[ligneRand][colonneRand].positionBouton.x = svgPosX;
				sudokuBouton[ligneRand][colonneRand].positionBouton.y = svgPosY;

				sudokuBouton[ligneRand][colonneRand].couleurTexteBouton = couleurV;

				indicePlace = true;
				sudokuBouton[ligneRand][colonneRand].chargerBouton();
			}
		}

		SDL_Flip(fond);
}

bool GrilleGraphique::estComplete()
{
	bool estComplete = true;
	for (int ligne = 0; ligne<9; ligne++)
	{
		for (int colonne = 0; colonne<9; colonne++)
		{
			if (sudokuBouton[ligne][colonne].messageBouton  != "0")
				estComplete=false;
		}
	}
	return estComplete;
}

void GrilleGraphique::afficherGrille()
{
	SDL_BlitSurface(imageSudokuVierge, NULL, fond, &positionSudokuVierge);
    for (int ligne = 0; ligne<9; ligne++)
    {
        for (int colonne = 0; colonne<9; colonne++)
        {
            sudokuBouton[ligne][colonne].chargerBouton();
        }
    }
    SDL_Flip(fond);
}

/// fonction creant une grille  partir d'un fichier
void GrilleGraphique::creerGrilleGraphFichier()
{
	// partie lecture du fichier

	// on affiche la grille qu'on vient de creer
	creerGrilleGraph();
}


/// créé un bouton avec la valeur de sudoku dessus : chaque case du sudoku est un bouton cliquable
Bouton GrilleGraphique::creerBouton(int v)
{
	Bouton bouton;
	std::string strTemp = "images/boutonValeurSudoku.bmp"; // string temporaire
	bouton.nomImageBouton = strTemp;
	strTemp = "polices/Cybernetica_Normal.ttf";
	bouton.nomPolice = strTemp;

	if (v == 0)
		strTemp = " ";
	else
		strTemp = std::to_string(v);

	bouton.messageBouton = strTemp;
	bouton.taillePolice = 20 * zoomX;

	//On attribue tout ce qu'il faut au nouveau bouton : fonds, zooms...
	bouton.fond = fond;
	bouton.zoomX = zoomX;
	bouton.zoomY = zoomY;
	bouton.tailleX = tailleX;
	bouton.tailleY = tailleY;

	return bouton;
}



