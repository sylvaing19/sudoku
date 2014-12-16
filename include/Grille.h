#ifndef GRILLE_H
#define GRILLE_H
#include <array>

/**
La classe Grille définit une grille de sudoku de 9*9 cases.
Elle permet de modifier et/ou de consulter les valeurs contenues dans les cases,
ainsi que de remplir la grille selon les règles du sudoku.
Les valeurs contenues dans la grille sont des entiers compris entre 0 et 9 inclus.
La valeur 0 correspond à une case vide.
*/


class Grille
{
    public:
        Grille();

        void afficherConsole();

        int8_t getLC(int8_t ligne, int8_t colonne);///Renvoie la valeur de la case repérée en ligne/colonne (idexé de 0 à 8)
        int8_t getBloc(int8_t surCase, int8_t sousCase);///Renvoie la valeur de la case repérée en bloc/sous-bloc (indexé de 0 à 8)
        void setLC(int8_t valeur, int8_t ligne, int8_t colonne);///Place 'valeur' dans la case repérée en ligne/colonne
        void setBloc(int8_t valeur, int8_t surCase, int8_t sousCase);///Place 'valeur' dans la case repérée en bloc/sous-bloc
        bool estPlacable(int8_t valeur, int8_t ligne, int8_t colonne);///Ne modifie pas la grille. Renvoi Vrai si 'valeur' est un chiffre plaçable compte tenu des valeurs présentes dans la grille, selon les règles du sudoku
        bool completer();///Complète la grille si possible. Renvoi 'vrai' si la résolution a réussi, 'faux' sinon, en cas d'échec la grille n'est pas modifiée
    private:
        std::array<int8_t,81> data;//Tableau de taille fixe contenant la donnée
};

#endif // GRILLE_H

/**
     colonne
      0 1 2  3 4 5  6 7 8
ligne╔═╤═╤═╦═╤═╤═╦═╤═╤═╗
  0  ╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
  1  ╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
  2  ╠═╪═╪═╬═╪═╪═╬═╪═╪═╣
  3  ╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
  4  ╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
  5  ╠═╪═╪═╬═╪═╪═╬═╪═╪═╣
  6  ╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
  7  ╟─┼─┼─╫─┼─┼─╫─┼─┼─╢
  8  ╚═╧═╧═╩═╧═╧═╩═╧═╧═╝

ligne = (a/3)*3 + b/3
colonne = (a%3)*3 + b%3

surCase = colonne/3 + (ligne/3)*3
sousCase = colonne%3 + (ligne%3)*3

             sous-case
                 ↓
sur-case -> 0══╤══╤══1══╤══╤══2══╤══╤══╗
        .   ║ 0  1  2 ║ 0  1  2 ║ 0  1  2 ║
        .   ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
        .   ║ 3  4  5 ║ 3  4  5 ║ 3  4  5 ║
        .   ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
        .   ║ 6  7  8 ║ 6  7  8 ║ 6  7  8 ║
        .-> 3══╪══╪══4══╪══╪══5══╪══╪══╣
        .   ║  │  │  ║  │  │  ║  │  │  ║
        .   ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
        .   ║  │  │  ║  │  │  ║  │  │  ║
        .   ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
        .   ║  │  │  ║  │  │  ║  │  │  ║
        .-> 6══╪══╪══7══╪══╪══8══╪══╪══╣
        .   ║  │  │  ║  │  │  ║  │  │  ║
        .   ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
        .   ║  │  │  ║  │  │  ║  │  │  ║
        .   ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
        .   ║  │  │  ║  │  │  ║  │  │  ║
        .   ╚══╧══╧══╩══╧══╧══╩══╧══╧══╝

ligne = (a/3)*3 + b/3
colonne = (a%3)*3 + b%3
**/
