#include "Grille.h"

using namespace std;

Grille::Grille()
{
    data.fill(0);
}

int8_t Grille::getLC(int8_t ligne, int8_t colonne)
{
    return data[colonne + ligne*9];
}

int8_t Grille::getBloc(int8_t surCase, int8_t sousCase)
{
    return data[(surCase%3)*3 + sousCase%3 + 9*((surCase/3)*3 + sousCase/3)];
}

void Grille::setLC(int8_t valeur, int8_t ligne, int8_t colonne)
{
    data[colonne + ligne*9] = valeur;
}

void Grille::setBloc(int8_t valeur, int8_t surCase, int8_t sousCase)
{
    data[(surCase%3)*3 + sousCase%3 + 9*((surCase/3)*3 + sousCase/3)] = valeur;
}

void Grille::afficherConsole()
{
    for(int ligne=0; ligne<9; ligne++)
    {
        for(int colonne=0; colonne<9; colonne++)
        {
            int8_t val = getLC(ligne, colonne);
            if(val>0 && val<=9)
                printf("%d ", val);
            else
                printf("  ");
            if(colonne == 2 || colonne == 5)
                printf("│");
        }
        printf("\n");
        if(ligne == 2 || ligne == 5)
            printf("──────┼──────┼──────\n");
    }
    printf("\n");
}

bool Grille::estPlacable(int8_t valeur, int8_t ligne, int8_t colonne)
{
    if(valeur > 9 || valeur <= 0)//Vérifie que la valeur n'est pas absurde
        return false;
    else
    {
        int8_t
        surCase = colonne/3 + (ligne/3)*3,
        sousCase = colonne%3 + (ligne%3)*3;//Conversion des coordonnées ligne/colonne en sous-case/sur-case
        for(int i=0; i<9; i++)
        {
            if(i!=ligne && Grille::getLC(i, colonne) == valeur)//Test règle : un seul chiffre par colonne
                return false;
            if(i!=colonne && Grille::getLC(ligne, i) == valeur)//Test règle : un seul chiffre par ligne
                return false;
            if(i!=sousCase && Grille::getBloc(surCase, i) == valeur)//Test règle : un seul chiffre par sur-case
                return false;
        }
        return true;
    }
}

void Grille::remplirGrille()
{
    for(int ligne=0; ligne<9; ligne++)
    {
        for(int colonne=0; colonne<9; colonne++)
        {
            grille[ligne][colonne].clear();
            for(int i=1; i<=9; i++)
            {
                if(estPlacable(i, ligne, colonne) && Grille::getLC(ligne, colonne) == 0)
                {
                    grille[ligne][colonne].push_back(i);
                }
            }
        }
    }
}

bool Grille::placerSingletons()
{
    bool valeurRetour = false;
    for(int ligne=0; ligne<9; ligne++)
    {
        for(int colonne=0; colonne<9; colonne++)
        {
            if(grille[ligne][colonne].size() == 1)
            {
                valeurRetour = true;
                Grille::setLC(grille[ligne][colonne][0], ligne, colonne);
            }
        }
    }

    return valeurRetour;
}

bool Grille::completer()
{
    array<int8_t,81> data_backup = data;

    do
    {
        Grille::remplirGrille();
    }
    while(Grille::placerSingletons());

    return true;
}

bool Grille::estResolu()
{
    for(int i=0; i<81; i++)
    {
        if(data[i] == 0)
            return false;
    }
    return true;
}
