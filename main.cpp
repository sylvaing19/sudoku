#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include "Grille.h"
#include "InterfaceGraphique.h"


using namespace std;

enum TypeDeTest
{MODE_CONSOLE, MODE_GRAPHIQUE, MODE_COMPOSITE};

TypeDeTest typeDeTest = MODE_GRAPHIQUE;/// Permet de choisir le type de test à effectuer
/*  MODE_GRAPHIQUE
*   MODE_CONSOLE
*/

int main ( int argc, char** argv )
{
    //Condition à conserver tant que le code est en phase de test.
    if(typeDeTest != MODE_GRAPHIQUE)//Permet de tester le code en console
    {
        Grille grille;
        ///Grille difficile
        /*
        grille.setLC(3,0,2);
        grille.setLC(7,0,4);
        grille.setLC(5,1,0);
        grille.setLC(1,1,2);
        grille.setLC(2,1,3);
        grille.setLC(2,2,0);
        grille.setLC(6,2,4);
        grille.setLC(1,2,6);
        grille.setLC(8,2,7);
        grille.setLC(7,3,3);
        grille.setLC(5,3,4);
        grille.setLC(6,3,6);
        grille.setLC(3,3,7);
        grille.setLC(8,4,0);
        grille.setLC(7,4,8);
        grille.setLC(4,5,1);
        grille.setLC(6,5,2);
        grille.setLC(9,5,4);
        grille.setLC(3,5,5);
        grille.setLC(5,6,1);
        grille.setLC(7,6,2);
        grille.setLC(4,6,4);
        grille.setLC(6,6,8);
        grille.setLC(7,7,5);
        grille.setLC(3,7,6);
        grille.setLC(2,7,8);
        grille.setLC(3,8,4);
        grille.setLC(7,8,6);
        //*/

        ///Grille facile
        //*
        grille.setBloc(5,0,3);
        grille.setBloc(3,0,4);
        grille.setBloc(8,0,8);
        grille.setBloc(2,1,2);
        grille.setBloc(7,1,4);
        grille.setBloc(8,1,5);
        grille.setBloc(5,1,6);
        grille.setBloc(9,1,7);
        grille.setBloc(6,2,2);
        grille.setBloc(7,2,7);
        grille.setBloc(3,2,8);
        grille.setBloc(1,3,0);
        grille.setBloc(9,3,1);
        grille.setBloc(3,3,2);
        grille.setBloc(8,3,3);
        grille.setBloc(2,3,5);
        grille.setBloc(5,4,1);
        grille.setBloc(3,4,3);
        grille.setBloc(7,4,5);
        grille.setBloc(6,4,7);
        grille.setBloc(5,5,3);
        grille.setBloc(4,5,5);
        grille.setBloc(3,5,6);
        grille.setBloc(1,5,7);
        grille.setBloc(2,5,8);
        grille.setBloc(6,6,0);
        grille.setBloc(1,6,1);
        grille.setBloc(7,6,6);
        grille.setBloc(4,7,1);
        grille.setBloc(3,7,2);
        grille.setBloc(7,7,3);
        grille.setBloc(2,7,4);
        grille.setBloc(6,7,6);
        grille.setBloc(2,8,0);
        grille.setBloc(4,8,4);
        grille.setBloc(5,8,5);
        //*/

        grille.afficherConsole();
        if(grille.completer())
        {
            printf("Grille résolue :\n");
            grille.afficherConsole();
        }
        else
            printf("Grille non résolue\n");
    }

    if(typeDeTest != MODE_CONSOLE)//Permet de tester l'interface graphique
    {
        InterfaceGraphique interface;

        interface.initTout();
        interface.intro();
        while(interface.continuerEvent)
        {
            interface.menu();
        }
        SDL_Quit();
    }

    return EXIT_SUCCESS;
}
