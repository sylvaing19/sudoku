#include "GrilleGraphique.h"

GrilleGraphique::GrilleGraphique()
{
    positionSudoku.x=0;
    positionSudoku.y=0;
    taillePolice=30;
    std::string nomPolice="polices/Cybernetica_Normal.ttf";
    policeSudoku=TTF_OpenFont(nomPolice.c_str(), taillePolice);
}

void GrilleGraphique::afficherGrilleGraph()
{
    std::string tableauCases[20];//tableau contenant les valeurs de chaque ligne (taille : 9 ligne + 2 traits)
    SDL_Surface *imageNombres[20]; // pareil mais pour les images

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

    positionSudoku.x=(tailleX-350*zoomX)/2;
    positionSudoku.y=(tailleY-400*zoomY)/2;

    //affichage de la grille, ligne par ligne
    for(int ligne=0; ligne<20; ligne++)
    {
        imageNombres[ligne] = TTF_RenderText_Blended(policeSudoku, tableauCases[ligne].c_str(),{0,0,0} );
        SDL_BlitSurface(imageNombres[ligne], NULL, fond, &positionSudoku);
        positionSudoku.y+=30;
    }

}
