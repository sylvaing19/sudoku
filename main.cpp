#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include "Grille.h"
#include "InterfaceGraphique.h"
#include "Bouton.h"


using namespace std;

enum TypeDeTest
{MODE_CONSOLE, MODE_GRAPHIQUE, MODE_COMPOSITE};

enum TestGraph
{CLASSE_BOUTON,MENU_PRINCIPAL};

TypeDeTest typeDeTest = MODE_GRAPHIQUE;/// Permet de choisir le type de test à effectuer

TestGraph testGraphique = CLASSE_BOUTON; /// Permet de choisir le type  de test graphique

int main ( int argc, char** argv )
{
    //Condition à conserver tant que le code est en phase de test.
    if(typeDeTest != MODE_GRAPHIQUE)//Permet de tester le code en console
    {
        Grille grille;
        {
        ///Grille difficile

        //*
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
        /*
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
        }
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

    if(typeDeTest != MODE_CONSOLE)//Permet de tester l'interface graphique
    {
        if(testGraphique==CLASSE_BOUTON) // permet de tester la classe bouton
        {
            Bouton boutonMenu1;
            Bouton boutonMenu2;
            Bouton boutonQuitter;
            InterfaceGraphique menuPrincipal;

            /*Partie Menu Principal*/

            //affichage fond : le menu principal
            menuPrincipal.chargerMenu();
            SDL_Flip(menuPrincipal.fond);
            SDL_Delay(100);

            //initialisations diverses
            menuPrincipal.initPolices();
            menuPrincipal.texteTitre="Sudoku-Solveur";

            //affiche le titre et intro
            menuPrincipal.initTitre();
            menuPrincipal.intro();

            /*Partie boutons*/
            {
                //attribution du fond
                boutonMenu1.fond=menuPrincipal.fond;
                boutonMenu2.fond=menuPrincipal.fond;
                boutonQuitter.fond=menuPrincipal.fond;

                //gestion du zoom, de la taille
                boutonMenu1.zoomX=menuPrincipal.zoomX;
                boutonMenu1.zoomY=menuPrincipal.zoomY;
                boutonMenu2.zoomX=menuPrincipal.zoomX;
                boutonMenu2.zoomY=menuPrincipal.zoomY;
                boutonQuitter.zoomX=menuPrincipal.zoomX;
                boutonQuitter.zoomY=menuPrincipal.zoomY;

                boutonMenu1.tailleX=menuPrincipal.tailleX;
                boutonMenu1.tailleY=menuPrincipal.tailleY;
                boutonMenu2.tailleX=menuPrincipal.tailleX;
                boutonMenu2.tailleY=menuPrincipal.tailleY;
                boutonQuitter.tailleX=menuPrincipal.tailleX;
                boutonQuitter.tailleY=menuPrincipal.tailleY;

                //paramètres du bouton 1
                {
                    std::string a="images/BoutonMenu.bmp";
                    boutonMenu1.nomImageBouton=a;
                    a="polices/Cybernetica_Normal.ttf";
                    boutonMenu1.nomPolice=a;
                    a="Resolution";
                    boutonMenu1.messageBouton=a;
                    a="Resoudre";
                    boutonMenu1.event=a;
                    boutonMenu1.couleurTexteBouton={255, 0, 0};
                    boutonMenu1.taillePolice=60*menuPrincipal.zoomX;
                    boutonMenu1.centreX="oui";
                    boutonMenu1.positionBouton.y+=(60+menuPrincipal.positionTitre.y+menuPrincipal.imageTitre->h);
                }
                boutonMenu1.chargerBouton();

                //paramètres du bouton 2
                {
                    std::string a="images/BoutonMenu.bmp";
                    boutonMenu2.nomImageBouton=a;
                    a="polices/Cybernetica_Normal.ttf";
                    boutonMenu2.nomPolice=a;
                    a="Photo-Doku";
                    boutonMenu2.messageBouton=a;
                    a="Photodoku";
                    boutonMenu1.messageBouton=a;
                    boutonMenu2.couleurTexteBouton={255, 0, 0};
                    boutonMenu2.taillePolice=60*menuPrincipal.zoomX;
                    boutonMenu2.centreX="oui";
                    boutonMenu2.positionBouton.y+=(boutonMenu1.positionBouton.y+(boutonMenu1.imageBouton->h)*3/2);
                }
                boutonMenu2.chargerBouton();

                //paramètres du bouton quitter
                {
                    std::string a="Quitter";
                    boutonMenu1.messageBouton=a;
                    boutonQuitter.positionBouton.x=(menuPrincipal.tailleX-65);
                    boutonQuitter.positionBouton.y=15;
                    a="images/arret.bmp";
                    boutonQuitter.nomImageBouton=a;
                }
                boutonQuitter.chargerBouton();

                SDL_Flip(boutonMenu1.fond);//Les boutons sont alors apparus.
                SDL_Delay(1000);
            }

            SDL_Quit();
        }
    }
    return EXIT_SUCCESS;
}
