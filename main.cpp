#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include "Grille.h"
#include "InterfaceGraphique.h"
#include "Score.h"

using namespace std;

enum TypeDeTest
{MODE_CONSOLE, MODE_GRAPHIQUE, TEST_UNITAIRE};

enum TestGraph
{RESOLUTION,MENU_PRINCIPAL};


TypeDeTest typeDeTest = MODE_CONSOLE;/// Permet de choisir le type de test à effectuer

TestGraph testGraphique = MENU_PRINCIPAL; /// Permet de choisir le type  de test graphique

/********************************************************************************************************/

int main ( int argc, char** argv )
{
    //Condition à conserver tant que le code est en phase de test.
    if(typeDeTest == MODE_CONSOLE)//Permet de tester le code en console
    {
		/*
        Grille grille;

        grille.setLC(9,2,0);grille.setLC(9,3,1);grille.setLC(3,5,0);grille.setLC(5,4,1);
        grille.setLC(2,6,0);grille.setLC(6,6,1); grille.setLC(1,8,0);grille.setLC(5,2,2);
		grille.setLC(6,0,3);  grille.setLC(6,3,2);grille.setLC(1,3,3);grille.setLC(2,4,2);
		grille.setLC(9,7,3); grille.setLC(8,7,2);grille.setLC(2,1,4);grille.setLC(9,1,5);
        grille.setLC(7,2,4);grille.setLC(2,5,5);grille.setLC(9,4,4);grille.setLC(6,8,5);
		grille.setLC(1,6,4);grille.setLC(3,7,4);grille.setLC(8,1,6);grille.setLC(6,2,7);
        grille.setLC(1,4,6);grille.setLC(7,4,7);grille.setLC(5,5,6);grille.setLC(9,5,7);
        grille.setLC(9,6,6);grille.setLC(9,0,8);grille.setLC(3,2,8);grille.setLC(2,3,8);
		grille.setLC(4,6,8);

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

        grille.afficherConsole();
        if(grille.completer())
        {
            printf("Grille résolue :\n");
            grille.afficherConsole();
        }
        else
        {
            printf("Grille non résolue\n");
            grille.afficherConsole();
        }
		grille.afficherConsole();

		/*
		int beaucoup = 20;
		for (int i = 0; i < beaucoup; i++)
		{
			grille.vider();
			grille.completerRand();
			grille.afficherConsole();
		}
		*/
		/*
		Score score;
		score.initScore(Difficulte::MOYEN);
		SDL_Delay(1000);
		score.stopTimer();
		cout << "Score : " << score.getScore() << endl;
		int rang = score.getRank();
		cout << "Rang : " << rang << endl;
		score.save("MOA", rang);
		//*/

		Grille grille;
		grille.generer(Difficulte::DIFFICILE);
		grille.afficherConsole();
		grille.completer(true);
		grille.afficherConsole();

    }

/********************************************************************************************************/

    if(typeDeTest == MODE_GRAPHIQUE)//Permet de tester l'interface graphique
    {
        if(testGraphique==MENU_PRINCIPAL) // permet de tester la classe bouton
        {
            InterfaceGraphique menuPrincipal;
            menuPrincipal.menuPrincipal();

            if(menuPrincipal.menuACreer=="Resoudre") ///Bienvenue dans l'arbre graphique !
            {
                InterfaceGraphique menuResoudre;
                menuResoudre.menuResoudre();

                if( menuResoudre.menuACreer=="Aleatoire")
                {
                    menuResoudre.grilleAleatoire();
					if (menuResoudre.menuACreer == "Resoudre")
					{
						menuResoudre.resoudre();
					}
                }
                if(menuResoudre.menuACreer=="Manuel")
                {
                    menuResoudre.grilleVide();
                    if(menuResoudre.menuACreer=="Resoudre")
                    {
						menuResoudre.resoudre();
                    }
                }
                if(menuResoudre.menuACreer=="MenuPrincipal")
                {
                    ;
                }
            }
            if(menuPrincipal.menuACreer=="Photo-Doku")
            {
				InterfaceGraphique menuPhoto;
				menuPhoto.menuPhoto();
            }
        }
    }

	/********************************************************************************************************/

	if (typeDeTest == TEST_UNITAIRE)
	{
		Grille grilleARemplir, grilleComplete;
		grilleARemplir.getFromFile("test_unitaire");
		grilleComplete.getFromFile("test_unitaire_resolu");
		grilleARemplir.completer();
		if (grilleARemplir.testResolution(grilleComplete))
			cout << "Megabwabwa ! Tout fonctionne !" << endl;// RLY ?
		else
			cout << "Pas de panique ! Ca marche juste pas !" << endl;
	}



  return EXIT_SUCCESS;
}
