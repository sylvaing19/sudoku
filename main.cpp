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
