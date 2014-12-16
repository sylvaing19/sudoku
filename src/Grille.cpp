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

bool Grille::estPlacable(int8_t valeur, int8_t ligne, int8_t colonne)
{
    if(valeur > 9 || valeur <= 0)
        return false;
    else
    {
        int8_t
        surCase = colonne/3 + (ligne/3)*3,
        sousCase = colonne%3 + (ligne%3)*3;
        for(int i=0; i<9; i++)
        {
            if(i!=ligne && Grille::getLC(i, colonne) == valeur)
                return false;
            if(i!=colonne && Grille::getLC(ligne, i) == valeur)
                return false;
            if(i!=sousCase && Grille::getBloc(surCase, i) == valeur)
                return false;
        }


        return true;
    }
}

bool Grille::completer()
{
    return false;
}
