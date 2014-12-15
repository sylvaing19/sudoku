#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>/*
#include "Grille.h"*/
#include "InterfaceGraphique.h"


using namespace std;

int main ( int argc, char** argv )
{
    InterfaceGraphique interface;

    interface.initTout();
    interface.intro();
    while(interface.continuer)
    {
      interface.menu();
    }
    if(interface.quitter==1)
    {
        SDL_Quit();
        return EXIT_SUCCESS;
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}
