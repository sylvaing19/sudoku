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

            std::string menuACreer;//Constante permettant de savoir le prochain menu affiché

            /*Partie Menu Principal*/

            //affichage fond : le menu principal
            menuPrincipal.nomImageFond="images/fond1.bmp";
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
                    boutonMenu1.taillePolice=70*menuPrincipal.zoomX;
                    boutonMenu1.centreX="oui";
                    boutonMenu1.positionBouton.y+=(menuPrincipal.positionTitre.y+menuPrincipal.positionTitre.h
                                                  +menuPrincipal.positionTitre.y+menuPrincipal.imageTitre->h)*menuPrincipal.zoomX;
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
                    boutonMenu2.taillePolice=70*menuPrincipal.zoomX;
                    boutonMenu2.centreX="oui";
                    boutonMenu2.positionBouton.y+=(boutonMenu1.positionBouton.y+(boutonMenu1.imageBouton->h)*3/2);
                }
                boutonMenu2.chargerBouton();

                //paramètres du bouton quitter
                {
                    std::string a="Quitter";
                    boutonMenu1.messageBouton=a;
                    boutonQuitter.positionBouton.x=(menuPrincipal.tailleX-65*menuPrincipal.zoomX);
                    boutonQuitter.positionBouton.y=15*menuPrincipal.zoomY;
                    a="images/arret.bmp";
                    boutonQuitter.nomImageBouton=a;
                    a="Quitter";
                    boutonQuitter.event=a;
                }
                boutonQuitter.chargerBouton();

                SDL_Flip(boutonMenu1.fond);//Les boutons sont alors apparus.

                /*gestion des events : */
                while(menuPrincipal.continuerEvent)
                {
                     SDL_WaitEvent(&menuPrincipal.event);
                        switch(menuPrincipal.event.type)
                        {
                            case SDL_KEYDOWN:  //Gestion clavier
                                switch(menuPrincipal.event.key.keysym.sym)
                                {
                                    case SDLK_ESCAPE: //Appuyer sur echap : quitte
                                        menuPrincipal.quitter();
                                        break;
                                    default:
                                        ;
                                }
                                break;
                            case SDL_MOUSEBUTTONDOWN: //Gestion souris
                                switch (menuPrincipal.event.button.button)
                                {
                                    case SDL_BUTTON_LEFT :


                                            //clic gauche souris
                                            if( menuPrincipal.event.button.x>boutonQuitter.positionBouton.x &&
                                                menuPrincipal.event.button.x<(boutonQuitter.positionBouton.x+boutonQuitter.positionBouton.w) &&
                                                menuPrincipal.event.button.y>boutonQuitter.positionBouton.y &&
                                                menuPrincipal.event.button.y<(boutonQuitter.positionBouton.y+boutonQuitter.positionBouton.h))
                                            {
                                                if(boutonQuitter.event=="Quitter")
                                                    menuPrincipal.quitter();
                                                else if(boutonQuitter.event=="Resoudre")
                                                {
                                                    menuACreer="Resoudre";
                                                    menuPrincipal.continuerEvent=false;
                                                }
                                            }


                                            //clic sur le menu 1
                                            else if( menuPrincipal.event.button.x>boutonMenu1.positionBouton.x &&
                                                     menuPrincipal.event.button.x<(boutonMenu1.positionBouton.x+boutonMenu1.positionBouton.w) &&
                                                     menuPrincipal.event.button.y>boutonMenu1.positionBouton.y &&
                                                     menuPrincipal.event.button.y<(boutonMenu1.positionBouton.y+boutonMenu1.positionBouton.h))
                                            {
                                               if(boutonMenu1.event=="Quitter")
                                                    menuPrincipal.quitter();
                                                else if(boutonMenu1.event=="Resoudre")
                                                {
                                                    menuACreer="Resoudre";
                                                    menuPrincipal.continuerEvent=false;
                                                }
                                            }


                                            //clic sur le menu 2
                                            else if( menuPrincipal.event.button.x>boutonMenu2.positionBouton.x &&
                                                     menuPrincipal.event.button.x<(boutonMenu2.positionBouton.x+boutonMenu2.positionBouton.w) &&
                                                     menuPrincipal.event.button.y>boutonMenu2.positionBouton.y &&
                                                     menuPrincipal.event.button.y<(boutonMenu2.positionBouton.y+boutonMenu2.positionBouton.h))
                                            {
                                               if(boutonMenu2.event=="Quitter")
                                                    menuPrincipal.quitter();
                                                else if(boutonMenu2.event=="Resoudre")
                                                {
                                                    menuACreer="Resoudre";
                                                    menuPrincipal.continuerEvent=false;
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
            }
            /*Partie creation des menus */
            if(menuACreer=="Resoudre")
            {
                InterfaceGraphique menuResoudre;

                menuResoudre.nomImageFond="images/fond2.bmp";
                menuResoudre.chargerMenu();

                //initialisations diverses
                menuResoudre.initPolices();
                menuResoudre.texteTitre="Resolution de Sudoku";

                SDL_Flip(menuResoudre.fond);
                SDL_Delay(2000);

                /*Partie resolution desudoku*/

                std::string tableauCases[12];//tableau contenant les valeurs de chaque ligne (taille : 9 ligne + 2 traits)
                SDL_Surface *imageNombres[12]; // pareil mais pour les images
                menuResoudre.positionSudoku.x=30;
                menuResoudre.positionSudoku.y=30;

                Grille grille;
                {
                ///Grille difficile
                grille.setLC(3,0,2);grille.setLC(7,0,4);grille.setLC(5,1,0);
                grille.setLC(1,1,2);grille.setLC(2,1,3);grille.setLC(2,2,0);
                grille.setLC(6,2,4);grille.setLC(1,2,6);grille.setLC(8,2,7);
                grille.setLC(7,3,3);grille.setLC(5,3,4);grille.setLC(6,3,6);
                grille.setLC(3,3,7);grille.setLC(8,4,0);grille.setLC(7,4,8);
                grille.setLC(4,5,1);grille.setLC(6,5,2);grille.setLC(9,5,4);
                grille.setLC(3,5,5);grille.setLC(5,6,1);grille.setLC(7,6,2);
                grille.setLC(4,6,4);grille.setLC(6,6,8);grille.setLC(7,7,5);
                grille.setLC(3,7,6);grille.setLC(3,8,4);grille.setLC(7,8,6);
                }
                //affectation de la gille à des images
                for(int ligne=0; ligne<9; ligne++)
                {
                    if(ligne != 2 && ligne != 5)
                        for(int colonne=0; colonne<9; colonne++)
                        {
                            if(colonne != 2 && colonne != 5)
                            {
                                int8_t val = grille.getLC(ligne, colonne);
                                if(val>0 && val<=9)
                                    tableauCases[ligne]+=(int)val;
                                else
                                    tableauCases[ligne]+="  ";
                            }
                        }
                }
                /*
                //affichage de la grille
                for(int ligne=0; ligne<9; ligne++)
                {
                   imageNombres[ligne] = TTF_RenderText_Blended(menuResoudre.policeSudoku,tableauCases[ligne].c_str() , menuResoudre.couleurN );
                   SDL_BlitSurface(imageNombres[ligne], NULL, menuResoudre.fond, &menuResoudre.positionSudoku);
                   menuResoudre.positionSudoku.y+=30;

                   printf("%s", tableauCases[ligne].c_str());
                }
                SDL_Flip(menuResoudre.fond);
                SDL_Delay(100);*/
            }


            return EXIT_SUCCESS;
        }
    }
}
