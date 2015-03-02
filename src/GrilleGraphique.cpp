#include "GrilleGraphique.h"

GrilleGraphique::GrilleGraphique()
{
    positionSudoku.x=0;
    positionSudoku.y=0;
    taillePolice=30;
    std::string nomPolice="polices/Cybernetica_Normal.ttf";
    policeSudoku=TTF_OpenFont(nomPolice.c_str(), taillePolice);

	couleurN = { 0, 0, 0 };
	couleurB = { 0, 0, 255 };
	couleurV = { 0, 255, 0 };
	couleurR = { 255, 0, 0 };
	couleurGri = { 200, 240, 255 };
}

void GrilleGraphique::afficherGrilleGraph()
{
	imageSudokuVierge = SDL_LoadBMP("images/SudokuVierge.bmp");
	if (imageSudokuVierge == NULL)
	{
		printf("Probleme avec %s", imageSudokuVierge);
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
				sudokuBouton[ligne][colonne] = creerBouton(val);
			}
			else
			{// La valeur n'existe pas encore
				sudokuBouton[ligne][colonne] = creerBouton(0);
			}

			// On donne les positions des boutons
			sudokuBouton[ligne][colonne].positionBouton.x = posX + (58 - 47)/2 * zoomX;
			sudokuBouton[ligne][colonne].positionBouton.y = posY + (58 - 47)/2 * zoomY;
			
			// On avance vers le prochain bouton
			posX += 58 * zoomX + 1 ;

			//On charge le bouton
			sudokuBouton[ligne][colonne].chargerBouton();
			SDL_Flip(fond);
		}

		//on change de ligne
		posX = positionSudokuVierge.x + (58 - 47) / 2 * zoomX;
		posY += 58 * zoomY + 1 ;
    }
}

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
	bouton.couleurTexteBouton = { 255, 0, 0 };
	bouton.taillePolice = 20 * zoomX;

	//On attribue tout ce qu'il faut au nouveau bouton : fonds, zooms...
	bouton.fond = fond;
	bouton.zoomX = zoomX;
	bouton.zoomY = zoomY;
	bouton.tailleX = tailleX;
	bouton.tailleY = tailleY;

	return bouton;
}