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


/********************************************************************************************************/

    if(typeDeTest != MODE_CONSOLE)//Permet de tester l'interface graphique
    {
        if(testGraphique==MENU_PRINCIPAL) // permet de tester la classe bouton
        {
            Bouton boutonMenu1;
            Bouton boutonMenu2;
            Bouton boutonQuitter;
            InterfaceGraphique menuPrincipal;

            std::string menuACreer;//Constante permettant de savoir le prochain menu affiché

            ///Partie Menu Principal

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

            ///Partie boutons
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

                ///gestion des events :
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

            ///Partie creation des menus
            if(menuACreer=="Resoudre")
            {
                bool sudokuApparait,sudokuAResoudre;
                InterfaceGraphique menuResoudre;
                Bouton boutonAleatoire;

                menuResoudre.nomImageFond="images/fond2.bmp";
                menuResoudre.chargerMenu();

                //initialisations diverses
                menuResoudre.initPolices();
                menuResoudre.texteTitre="Resolution de Sudoku";

                SDL_Flip(menuResoudre.fond);

                boutonAleatoire.fond=menuResoudre.fond;
                boutonAleatoire.zoomX=menuResoudre.zoomX;
                boutonAleatoire.zoomY=menuResoudre.zoomY;
                boutonAleatoire.tailleX=menuResoudre.tailleX;
                boutonAleatoire.tailleY=menuResoudre.tailleY;

                //paramètres du bouton aleatoire
                {
                    std::string a="images/BoutonSudoku.bmp";
                    boutonAleatoire.nomImageBouton=a;
                    a="polices/Cybernetica_Normal.ttf";
                    boutonAleatoire.nomPolice=a;
                    a="Apparition";
                    boutonAleatoire.messageBouton=a;
                    a="Apparaitre";
                    boutonAleatoire.event=a;
                    boutonAleatoire.couleurTexteBouton={255, 255, 255};
                    boutonAleatoire.taillePolice=70*menuResoudre.zoomX;
                    boutonAleatoire.positionBouton.x+=30*boutonAleatoire.zoomX;
                    boutonAleatoire.positionBouton.y+=30*boutonAleatoire.zoomY;
                }
                boutonAleatoire.chargerBouton();
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
                                            if( menuResoudre.event.button.x>boutonAleatoire.positionBouton.x &&
                                                menuResoudre.event.button.x<(boutonAleatoire.positionBouton.x+boutonAleatoire.positionBouton.w) &&
                                                menuResoudre.event.button.y>boutonAleatoire.positionBouton.y &&
                                                menuResoudre.event.button.y<(boutonAleatoire.positionBouton.y+boutonAleatoire.positionBouton.h))
                                                {
                                                    if(boutonAleatoire.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonAleatoire.event=="Apparaitre")
                                                    {
                                                        sudokuApparait=true;
                                                        menuResoudre.continuerEvent=false;
                                                        std::string a="Resolution";
                                                        boutonAleatoire.messageBouton=a;
                                                        boutonAleatoire.event=a;
                                                    }
                                                    else if(boutonAleatoire.event=="Resoudre")
                                                    {
                                                        menuACreer="Resoudre";
                                                        menuPrincipal.continuerEvent=false;
                                                    }
                                                }
                                            else if( menuPrincipal.event.button.x>boutonQuitter.positionBouton.x &&
                                                     menuPrincipal.event.button.x<(boutonQuitter.positionBouton.x+boutonQuitter.positionBouton.w) &&
                                                     menuPrincipal.event.button.y>boutonQuitter.positionBouton.y &&
                                                     menuPrincipal.event.button.y<(boutonQuitter.positionBouton.y+boutonQuitter.positionBouton.h))
                                                {
                                                    if(boutonQuitter.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonQuitter.event=="Apparaitre")
                                                        {
                                                            sudokuApparait=true;
                                                            menuResoudre.continuerEvent=false;
                                                            std::string a="Resolution";
                                                            boutonQuitter.messageBouton=a;
                                                            boutonQuitter.event=a;
                                                        }
                                                    else if(boutonQuitter.event=="Resoudre")
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

                if(sudokuApparait)
                {
                    ///Partie resolution

                    std::string tableauCases[20];//tableau contenant les valeurs de chaque ligne (taille : 9 ligne + 2 traits)
                    SDL_Surface *imageNombres[12]; // pareil mais pour les images


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

                    //affectation de la grille à des images sous forme de tableau :
                    // 1 ligne = 1 case
                    int line=0;
                    for(int ligne=0; ligne<9; ligne++)
                    {
                        for(int colonne=0; colonne<9; colonne++)
                        {
                            int8_t val = grille.getLC(ligne, colonne);
                            if(val>0 && val<=9)
                            {
                                tableauCases[line]+=" ";
                                tableauCases[line]+=std::to_string(val);
                                tableauCases[line]+=" ";
                            }
                            else
                            {
                                tableauCases[line]+=" ";
                                tableauCases[line]+="_";
                                tableauCases[line]+=" ";
                            }
                            if(colonne == 2 || colonne == 5)
                            {
                                tableauCases[line]+=" ";
                                tableauCases[line]+="|";
                                tableauCases[line]+=" ";
                            }
                        }
                        line++;
                        if(ligne == 2 || ligne == 5)
                        {
                            tableauCases[line]+=" ///////////////////////////// ";
                        }
                        line++;
                    }

                    menuResoudre.positionSudoku.x=(menuResoudre.tailleX-350*menuResoudre.zoomX)/2;
                    menuResoudre.positionSudoku.y=(menuResoudre.tailleY-400*menuResoudre.zoomY)/2;

                    //affichage de la grille, ligne par ligne
                    for(int ligne=0; ligne<20; ligne++)
                    {
                        imageNombres[ligne] = TTF_RenderText_Blended(menuResoudre.policeSudoku,tableauCases[ligne].c_str() ,menuResoudre.couleurN );
                        SDL_BlitSurface(imageNombres[ligne], NULL, menuResoudre.fond, &menuResoudre.positionSudoku);
                        menuResoudre.positionSudoku.y+=30;
                    }
                    boutonAleatoire.chargerBouton();
                    boutonQuitter.chargerBouton();
                    SDL_Flip(menuResoudre.fond);

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
                                            if( menuResoudre.event.button.x>boutonAleatoire.positionBouton.x &&
                                                menuResoudre.event.button.x<(boutonAleatoire.positionBouton.x+boutonAleatoire.positionBouton.w) &&
                                                menuResoudre.event.button.y>boutonAleatoire.positionBouton.y &&
                                                menuResoudre.event.button.y<(boutonAleatoire.positionBouton.y+boutonAleatoire.positionBouton.h))
                                                {
                                                    if(boutonAleatoire.event=="Quitter")
                                                        menuResoudre.quitter();
                                                    else if(boutonAleatoire.event=="Resolution")
                                                    {
                                                        sudokuAResoudre=true;
                                                        menuResoudre.continuerEvent=false;
                                                    }
                                                    else if(boutonAleatoire.event=="Apparaitre")
                                                    {
                                                        sudokuApparait=true;
                                                        menuResoudre.continuerEvent=false;
                                                        std::string a="Resolution";
                                                        boutonQuitter.messageBouton=a;
                                                        boutonQuitter.event=a;
                                                    }
                                                }
                                            else if( menuPrincipal.event.button.x>boutonQuitter.positionBouton.x &&
                                                     menuPrincipal.event.button.x<(boutonQuitter.positionBouton.x+boutonQuitter.positionBouton.w) &&
                                                     menuPrincipal.event.button.y>boutonQuitter.positionBouton.y &&
                                                     menuPrincipal.event.button.y<(boutonQuitter.positionBouton.y+boutonQuitter.positionBouton.h))
                                            {
                                                if(boutonQuitter.event=="Quitter")
                                                    menuResoudre.quitter();
                                                else if(boutonQuitter.event=="Apparaitre")
                                                    {
                                                        sudokuApparait=true;
                                                        menuResoudre.continuerEvent=false;
                                                        std::string a="Resolution";
                                                        boutonQuitter.messageBouton=a;
                                                        boutonQuitter.event=a;
                                                    }
                                                else if(boutonQuitter.event=="Resoudre")
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

                    if(sudokuAResoudre)
                    {
                        //Resolution
                        grille.completer();

                        //On enleve la precedente
                        menuResoudre.chargerMenu();
                        SDL_Flip(menuResoudre.fond);

                        //initialisation des parametres pour l'affichage
                        std::string tableauCasesResolu[20];//tableau contenant les valeurs de chaque ligne (taille : 9 ligne + 2 traits)
                        SDL_Surface *imageNombresResolu[12]; // pareil mais pour les images


                        //On crée la grille resolue
                        int lineResolu=0;
                        for(int ligne=0; ligne<9; ligne++)
                        {
                            for(int colonne=0; colonne<9; colonne++)
                            {
                                int8_t valResolu = grille.getLC(ligne, colonne);
                                if(valResolu>0 && valResolu<=9)
                                {
                                    tableauCasesResolu[lineResolu]+=" ";
                                    tableauCasesResolu[lineResolu]+=std::to_string(valResolu);
                                    tableauCasesResolu[lineResolu]+=" ";
                                }
                                else
                                {
                                    tableauCasesResolu[lineResolu]+=" ";
                                    tableauCasesResolu[lineResolu]+="X";
                                    tableauCasesResolu[lineResolu]+=" ";
                                }
                                if(colonne == 2 || colonne == 5)
                                {
                                    tableauCasesResolu[lineResolu]+=" ";
                                    tableauCasesResolu[lineResolu]+="|";
                                    tableauCasesResolu[lineResolu]+=" ";
                                }
                            }
                            lineResolu++;
                            if(ligne == 2 || ligne == 5)
                            {
                                tableauCasesResolu[lineResolu]+=" ///////////////////////////// ";
                            }
                            lineResolu++;
                        }

                        menuResoudre.positionSudoku.x=(menuResoudre.tailleX-350*menuResoudre.zoomX)/2;
                        menuResoudre.positionSudoku.y=(menuResoudre.tailleY-400*menuResoudre.zoomY)/2;


                        //affichage de la grille resolue, ligne par ligne
                        for(int ligne=0; ligne<20; ligne++)
                        {
                            imageNombresResolu[ligne] = TTF_RenderText_Blended(menuResoudre.policeSudoku,tableauCasesResolu[ligne].c_str() ,menuResoudre.couleurN );
                            SDL_BlitSurface(imageNombresResolu[ligne], NULL, menuResoudre.fond, &menuResoudre.positionSudoku);
                            menuResoudre.positionSudoku.y+=30;
                        }

                        SDL_Flip(menuResoudre.fond);
                        SDL_Delay(2500);
                    }
                }
            }
        }

/**********************************************************************************************************/

        if(testGraphique==RESOLUTION) // permet de tester la classe Resolution directement, sans passer par le menu
        {
            InterfaceGraphique menuResoudre;

            menuResoudre.nomImageFond="images/fond2.bmp";
            menuResoudre.chargerMenu();

            //initialisations diverses
            menuResoudre.initPolices();
            menuResoudre.texteTitre="Resolution de Sudoku";

            SDL_Flip(menuResoudre.fond);
            SDL_Delay(2000);

            ///Partie resolution

            std::string tableauCases[20];//tableau contenant les valeurs de chaque ligne (taille : 9 ligne + 2 traits)
            SDL_Surface *imageNombres[12]; // pareil mais pour les images

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

            //affectation de la grille à des images sous forme de tableau :
            // 1 ligne = 1 case
            int line=0;
            for(int ligne=0; ligne<9; ligne++)
            {
                for(int colonne=0; colonne<9; colonne++)
                {
                    int8_t val = grille.getLC(ligne, colonne);
                    if(val>0 && val<=9)
                    {
                        tableauCases[line]+=" ";
                        tableauCases[line]+=std::to_string(val);
                        tableauCases[line]+=" ";
                    }
                    else
                    {
                        tableauCases[line]+=" ";
                        tableauCases[line]+="X";
                        tableauCases[line]+=" ";
                    }
                    if(colonne == 2 || colonne == 5)
                    {
                        tableauCases[line]+=" ";
                        tableauCases[line]+="|";
                        tableauCases[line]+=" ";
                    }
                }
                line++;
                if(ligne == 2 || ligne == 5)
                {
                    tableauCases[line]+=" ///////////////////////////// ";
                }
                line++;
            }

            menuResoudre.positionSudoku.x=(menuResoudre.tailleX-350*menuResoudre.zoomX)/2;
            menuResoudre.positionSudoku.y=(menuResoudre.tailleY-400*menuResoudre.zoomY)/2;

            //affichage de la grille, ligne par ligne
            for(int ligne=0; ligne<20; ligne++)
            {
                imageNombres[ligne] = TTF_RenderText_Blended(menuResoudre.policeSudoku,tableauCases[ligne].c_str() ,menuResoudre.couleurN );
                SDL_BlitSurface(imageNombres[ligne], NULL, menuResoudre.fond, &menuResoudre.positionSudoku);
                menuResoudre.positionSudoku.y+=30;
            }
            SDL_Flip(menuResoudre.fond);
            SDL_Delay(2500);

            //Resolution
            grille.completer();

            //On enleve la precedente
            menuResoudre.chargerMenu();
            SDL_Flip(menuResoudre.fond);

            //initialisation des parametres pour l'affichage
            std::string tableauCasesResolu[20];//tableau contenant les valeurs de chaque ligne (taille : 9 ligne + 2 traits)
            SDL_Surface *imageNombresResolu[12]; // pareil mais pour les images


            //On crée la grille resolue
            int lineResolu=0;
            for(int ligne=0; ligne<9; ligne++)
            {
                for(int colonne=0; colonne<9; colonne++)
                {
                    int8_t valResolu = grille.getLC(ligne, colonne);
                    if(valResolu>0 && valResolu<=9)
                    {
                        tableauCasesResolu[lineResolu]+=" ";
                        tableauCasesResolu[lineResolu]+=std::to_string(valResolu);
                        tableauCasesResolu[lineResolu]+=" ";
                    }
                    else
                    {
                        tableauCasesResolu[lineResolu]+=" ";
                        tableauCasesResolu[lineResolu]+="X";
                        tableauCasesResolu[lineResolu]+=" ";
                    }
                    if(colonne == 2 || colonne == 5)
                    {
                        tableauCasesResolu[lineResolu]+=" ";
                        tableauCasesResolu[lineResolu]+="|";
                        tableauCasesResolu[lineResolu]+=" ";
                    }
                }
                lineResolu++;
                if(ligne == 2 || ligne == 5)
                {
                    tableauCasesResolu[lineResolu]+="/////////////////////////////";
                }
                lineResolu++;
            }

            menuResoudre.positionSudoku.x=(menuResoudre.tailleX-350*menuResoudre.zoomX)/2;
            menuResoudre.positionSudoku.y=(menuResoudre.tailleY-400*menuResoudre.zoomY)/2;

            //affichage de la grille resolue, ligne par ligne
            for(int ligne=0; ligne<20; ligne++)
            {
                imageNombresResolu[ligne] = TTF_RenderText_Blended(menuResoudre.policeSudoku,tableauCasesResolu[ligne].c_str() ,menuResoudre.couleurN );
                SDL_BlitSurface(imageNombresResolu[ligne], NULL, menuResoudre.fond, &menuResoudre.positionSudoku);
                menuResoudre.positionSudoku.y+=30;
            }
            SDL_Flip(menuResoudre.fond);
            SDL_Delay(5000);
        }
    }

  return EXIT_SUCCESS;
}
