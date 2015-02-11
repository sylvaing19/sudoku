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

enum TestGraph
{RESOLUTION,MENU_PRINCIPAL};

TypeDeTest typeDeTest = MODE_GRAPHIQUE;/// Permet de choisir le type de test à effectuer
TestGraph testGraphique = MENU_PRINCIPAL; /// Permet de choisir le type  de test graphique

/********************************************************************************************************/

int main ( int argc, char** argv )
{
    //Condition à conserver tant que le code est en phase de test.
    if(typeDeTest != MODE_GRAPHIQUE)//Permet de tester le code en console
    {
        Grille grille;

        grille.setLC(9,2,0);grille.setLC(9,3,1);
        grille.setLC(3,5,0);grille.setLC(5,4,1);
        grille.setLC(2,6,0);grille.setLC(6,6,1);
        grille.setLC(1,8,0);grille.setLC(5,2,2);grille.setLC(6,0,3);
        grille.setLC(6,3,2);grille.setLC(1,3,3);
        grille.setLC(2,4,2);grille.setLC(9,7,3);
        grille.setLC(8,7,2);grille.setLC(2,1,4);grille.setLC(9,1,5);
        grille.setLC(7,2,4);grille.setLC(2,5,5);
        grille.setLC(9,4,4);grille.setLC(6,8,5);grille.setLC(1,6,4);
        grille.setLC(3,7,4);grille.setLC(8,1,6);grille.setLC(6,2,7);
        grille.setLC(1,4,6);grille.setLC(7,4,7);grille.setLC(5,5,6);grille.setLC(9,5,7);
        grille.setLC(9,6,6);grille.setLC(9,0,8);grille.setLC(3,2,8);grille.setLC(2,3,8);grille.setLC(4,6,8);

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
        ///FIXME T_T ou save me plutot

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
    }

/********************************************************************************************************/

    if(typeDeTest != MODE_CONSOLE)//Permet de tester l'interface graphique
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
                    std::string a="images/BoutonSudoku.bmp";
                    boutonAleatoire.nomImageBouton=a;
                    a="polices/Cybernetica_Normal.ttf";
                    boutonAleatoire.nomPolice=a;
                    a="Aleatoire";
                    boutonAleatoire.messageBouton=a;
                    a="ApparitionAleatoire";
                    boutonAleatoire.event=a;
                    boutonAleatoire.couleurTexteBouton={255, 255, 255};
                    boutonAleatoire.taillePolice=70*menuResoudre.zoomX;
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
                    boutonManuel.taillePolice=70*boutonManuel.zoomX;
                    boutonManuel.positionBouton.x+=boutonAleatoire.positionBouton.x;
                    boutonManuel.positionBouton.y+=30*boutonAleatoire.zoomY+boutonAleatoire.positionBouton.y+ boutonAleatoire.positionBouton.h;
                }
                boutonManuel.chargerBouton();

                boutonQuitter.chargerBouton();

                SDL_Flip(menuResoudre.fond);

                ///gestion des events :
                menuResoudre.continuerEvent=true;
                while(menuResoudre.continuerEvent)
                {
                     SDL_WaitEvent(&menuResoudre.event);
                        switch(menuResoudre.event.type)
                        {
                            case SDL_KEYDOWN:  //Gestion clavier
                                switch(menuResoudre.event.key.keysym.sym)
                                {
                                    case SDLK_ESCAPE: //Appuyer sur echap : quitte
                                        menuResoudre.quitter();
                                        break;
                                    default:
                                        ;
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN: //Gestion souris
                                switch (menuResoudre.event.button.button)
                                {
                                    case SDL_BUTTON_LEFT :
                                            //clic gauche souris
                                            if(boutonAleatoire.estClique(menuResoudre.event))
                                                {
                                                    if(boutonAleatoire.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonAleatoire.event=="ApparitionAleatoire")
                                                    {
                                                        menuACreer="Aleatoire";
                                                        menuResoudre.continuerEvent=false;
                                                        std::string a="Resoudre";
                                                        boutonAleatoire.messageBouton=a;
                                                        boutonAleatoire.event=a;
                                                    }
                                                    else if(boutonAleatoire.event=="Resoudre")
                                                    {
                                                        menuACreer="Resoudre";
                                                        menuResoudre.continuerEvent=false;
                                                        sudokuAResoudre=true;
                                                   }
                                                    else if(boutonAleatoire.event=="Manuel")
                                                    {
                                                            menuACreer="Manuel";
                                                            menuResoudre.continuerEvent=false;
                                                            sudokuVide=true;
                                                    }
                                                }
                                            else if(boutonQuitter.estClique(menuResoudre.event))
                                                {
                                                    if(boutonQuitter.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonQuitter.event=="ApparitionAleatoire")
                                                    {
                                                            menuACreer="Aleatoire";
                                                            menuResoudre.continuerEvent=false;
                                                            std::string a="Resoudre";
                                                            boutonQuitter.messageBouton=a;
                                                            boutonQuitter.event=a;
                                                    }
                                                    else if(boutonQuitter.event=="Resoudre")
                                                    {
                                                            menuACreer="Resoudre";
                                                            menuResoudre.continuerEvent=false;
                                                    }
                                                    else if(boutonQuitter.event=="Manuel")
                                                    {
                                                            menuACreer="Manuel";
                                                            menuResoudre.continuerEvent=false;
                                                    }
                                                }
                                            else if(boutonManuel.estClique(menuResoudre.event))
                                                {
                                                    if(boutonManuel.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonManuel.event=="ApparitionAleatoire")
                                                    {
                                                            menuResoudre.continuerEvent=false;
                                                            std::string a="Resoudre";
                                                            boutonManuel.messageBouton=a;
                                                            boutonManuel.event=a;
                                                            menuACreer="Aleatoire";
                                                    }
                                                    else if(boutonManuel.event=="Resoudre")
                                                    {
                                                            menuACreer="Resoudre";
                                                            menuResoudre.continuerEvent=false;

                                                    }
                                                    else if(boutonManuel.event=="Manuel")
                                                    {
                                                            menuACreer="Manuel";
                                                            menuResoudre.continuerEvent=false;
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


                if( menuACreer=="Aleatoire")
                {
                    ///Partie resolution

                    //initialisations et definition de la  grille  utilisée par la partie graphique
                    GrilleGraphique grilleGraphique;

                    grilleGraphique.fond=menuResoudre.fond;
                    grilleGraphique.zoomX=menuResoudre.zoomX;
                    grilleGraphique.zoomY=menuResoudre.zoomY;
                    grilleGraphique.tailleX=menuResoudre.tailleX;
                    grilleGraphique.tailleY=menuResoudre.tailleY;

                    //definition de la grille, attribition (Numero, ligne, colonne)
                    Grille grille;
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

                    grilleGraphique.grille=grille;
                    grilleGraphique.afficherGrilleGraph();
                    grilleGraphique.grille.afficherConsole();

                    boutonAleatoire.chargerBouton();
                    boutonQuitter.chargerBouton();
                    SDL_Flip(menuResoudre.fond);

                    //gestion des evenements
                    menuResoudre.continuerEvent=true;
                    while(menuResoudre.continuerEvent)
                    {
                     SDL_WaitEvent(&menuResoudre.event);
                        switch(menuResoudre.event.type)
                        {
                            case SDL_KEYDOWN:  //Gestion clavier
                                switch(menuResoudre.event.key.keysym.sym)
                                {
                                    case SDLK_ESCAPE: //Appuyer sur echap : quitte
                                        menuResoudre.quitter();
                                        break;
                                    default:
                                        ;
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN: //Gestion souris
                                switch (menuResoudre.event.button.button)
                                {
                                    case SDL_BUTTON_LEFT :
                                            //clic gauche souris
                                           if(boutonAleatoire.estClique(menuResoudre.event))
                                                {
                                                    if(boutonAleatoire.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonAleatoire.event=="ApparitionAleatoire")
                                                    {
                                                        menuACreer="Aleatoire";
                                                        menuResoudre.continuerEvent=false;
                                                        std::string a="Resoudre";
                                                        boutonAleatoire.messageBouton=a;
                                                        boutonAleatoire.event=a;
                                                    }
                                                    else if(boutonAleatoire.event=="Resoudre")
                                                    {
                                                        menuACreer="Resoudre";
                                                        menuResoudre.continuerEvent=false;
                                                    }
                                                    else if(boutonAleatoire.event=="Manuel")
                                                    {
                                                        menuACreer="Manuel";
                                                        menuResoudre.continuerEvent=false;
                                                    }
                                                }
                                            else if(boutonQuitter.estClique(menuResoudre.event))
                                                {
                                                    if(boutonQuitter.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonQuitter.event=="ApparitionAleatoire")
                                                    {
                                                            menuACreer="Aleatoire";
                                                            menuResoudre.continuerEvent=false;
                                                            std::string a="Resoudre";
                                                            boutonQuitter.messageBouton=a;
                                                            boutonQuitter.event=a;
                                                    }
                                                    else if(boutonQuitter.event=="Resoudre")
                                                    {
                                                            menuACreer="Resoudre";
                                                            menuResoudre.continuerEvent=false;
                                                    }
                                                    else if(boutonQuitter.event=="Manuel")
                                                    {
                                                            menuACreer="Manuel";
                                                            menuResoudre.continuerEvent=false;
                                                    }
                                                }
                                            else if( boutonManuel.estClique(menuResoudre.event))
                                                {
                                                    if(boutonManuel.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonManuel.event=="ApparitionAleatoire")
                                                    {
                                                        menuACreer="Aleatoire";
                                                        menuResoudre.continuerEvent=false;
                                                        std::string a="Resoudre";
                                                        boutonManuel.messageBouton=a;
                                                        boutonManuel.event=a;
                                                    }
                                                    else if(boutonManuel.event=="Resoudre")
                                                    {
                                                        menuACreer="Resoudre";
                                                        menuResoudre.continuerEvent=false;
                                                    }
                                                    else if(boutonManuel.event=="Manuel")
                                                    {
                                                        menuACreer="Manuel";
                                                        menuResoudre.continuerEvent=false;
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
                    menuResoudre.grilleAleatoire();
                    if(menuResoudre.menuACreer=="Resoudre")
                        menuResoudre.resoudre();
                    if(menuResoudre.menuACreer=="Indice")
                    {
                        ;
                    }
                }
                if(menuResoudre.menuACreer=="Manuel")
                {
                    menuResoudre.grilleVide();
                    if(menuResoudre.menuACreer=="Resoudre")
                    {
                        ;
                    }
                    if(menuResoudre.menuACreer=="Indice")
                    {
                        menuResoudre.continuerEvent=true;
                        int valeurChangee=0;// initialisation de la valeur : si reste à 0, n'a pas été touchée par l'user
                        while(menuResoudre.continuerEvent)
                        {
                            ///GESTION CLICS SUR LES CASES
                                SDL_WaitEvent(&menuResoudre.event);
                                switch(menuResoudre.event.type)
                                {
                                    case SDL_KEYDOWN:  //Gestion clavier
                                    switch(menuResoudre.event.key.keysym.sym)
                                    {
                                        case SDLK_ESCAPE: //Appuyer sur echap : quitte
                                            menuResoudre.quitter();
                                            break;
                                        case SDLK_1:case SDLK_KP1:
                                            valeurChangee=1;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        case SDLK_2:case SDLK_KP2:
                                            valeurChangee=2;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        case SDLK_3:case SDLK_KP3:
                                            valeurChangee=3;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        case SDLK_4:case SDLK_KP4:
                                            valeurChangee=4;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        case SDLK_5:case SDLK_KP5:
                                            valeurChangee=5;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        case SDLK_6:case SDLK_KP6:
                                            valeurChangee=6;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        case SDLK_7:case SDLK_KP7:
                                            valeurChangee=7;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        case SDLK_8:case SDLK_KP8:
                                            valeurChangee=8;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        case SDLK_9:case SDLK_KP9:
                                            valeurChangee=9;
                                            break; // On entre le nombre, au NUMPAD ou clavier classique
                                        default:
                                            break;//autre : rien.
                                    }
                                menuResoudre.continuerEvent=false;
                                break;
                                }
                            if(valeurChangee==0)
                            {//La valeur n'a pas été changée
                                ;
                            }
                            else
                            {//On change la valeur de la case
                                ;
                            }

                        }
                        //sortie du while; traitement de la valeur
                    }
                }
                if(menuResoudre.menuACreer=="MenuPrincipal")
                {
                    ;
                }
            }
            if(menuPrincipal.menuACreer=="Photo-Doku")
            {
                ;
            }
        }
    }
  return EXIT_SUCCESS;
}
