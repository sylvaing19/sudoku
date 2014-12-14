#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include "Grille.h"
#include "InterfaceGraphique.h"


using namespace std;

int main ( int argc, char** argv )
{
    InterfaceGraphique interface;
char center_env[] = "SDL_VIDEO_CENTERED=center";
SDL_putenv(center_env);

    interface.initTout();
    interface.intro();
    while(interface.continuer)
    {
      interface.menu();
    }
    if(interface.quitter==1)
        return EXIT_SUCCESS;
    return EXIT_SUCCESS;
}
