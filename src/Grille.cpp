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
    array<int8_t,81> data_backup = data;//permet de restaurer les données initiales en cas d'échec de la résolution

    do//méthode de résolution par simple élimination des valeurs impossibles.
    {
        Grille::remplirGrille();
    }
    while(Grille::placerSingletons());//fin de la résolution par élimination
    /*
    Les grilles difficiles ne peuvent pas être intégralement résolues par élimination,
    à ce stade de l'algorithme elles sont seulement partiellement résolues. On vérifie
    si la grille est résolue ou non. Si elle ne l'est pas on passe à une résolution par
    hypothèses. On choisi la case qui contient le moins de possibilitées, et on teste
    successivement la résolution de la grille pour chaque possibilité. L'algorithme est
    récursif car on réutilise la méthode compéter() pour tenter compléter les grilles
    hypothétiques, et on utilise la valeur de retour pour savoir si l'hypothèse est bonne
    ou non. La garantie de non modification de la grille en cas d'échec de résolution par
    la méthode compléter() est fondamentale ici.
    */
    if(!Grille::estResolu())
    {
        int8_t ligne, colonne;
        /*Il suffit d'explorer les hypothèses d'une seule case pour toujours résoudre la
        grille, on choisit donc celle ayant le moins de possibilitées.
        */
        unsigned int nbHyp = Grille::minGrille(ligne, colonne);
        //Grille uneHypothese;//Nouvelle grille qui servira à tester les hypothèses
        /*for(int l=0; l<9; l++)//On rend cette grille identique à notre grille actuelle
        {
            for(int c=0; c<9; c++)
            {
                uneHypothese.setLC(Grille::getLC(l,c),l,c);
            }
        }*/
        for(unsigned int i=0; i<nbHyp; i++)//On teste successivement chacune des hypothèses
        {
            //uneHypothese.setLC(Grille::grille[ligne][colonne][i], ligne, colonne);
            Grille::setLC(Grille::grille[ligne][colonne][i], ligne, colonne);
            if(Grille::completer())//Si cette hypothèse était la bonne
            {/*
                for(int l=0; l<9; l++)//On recopie la grille hypothétique dans la grille réelle
                {
                    for(int c=0; c<9; c++)
                    {
                        Grille::setLC(uneHypothese.getLC(l,c),l,c);
                    }
                }*/
                return true;
            }
            //Si cette hypothèse était mauvaise, on passe à la suivante
        }
        //Si on arrive à cet endroit, c'est qu'aucune hypothèse n'était valide, la grille n'est donc pas soluble.
        data = data_backup;//On restaure la grille initiale
        return false;//On indique l'échec de la résolution
    }
    else
    {
        return true;
    }
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

unsigned int Grille::minGrille(int8_t& ligne, int8_t& colonne)
{
    unsigned int tailleMin = grille[0][0].size();

    for(int l=0; l<9; l++)
    {
        for(int c=1; c<9; c++)
        {
            if((grille[l][c].size() < tailleMin && grille[l][c].size() != 0) || tailleMin == 0)
            {
                tailleMin = grille[l][c].size();
                ligne = l;
                colonne = c;
            }
        }
    }
    return tailleMin;
}
