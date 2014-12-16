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

TypeDeTest typeDeTest = MODE_CONSOLE;/// Permet de choisir le type de test à effectuer

int main ( int argc, char** argv )
{
    //Condition à conserver tant que le code est en phase de test.
    if(typeDeTest != MODE_GRAPHIQUE)//Permet de tester le code en console
    {

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
