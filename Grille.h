/*#ifndef GRILLE_H
#define GRILLE_H
#include <array>

class Grille
{
    public:
        Grille();
        int8_t getLC(int8_t ligne, int8_t colonne);
        int8_t getBloc(int8_t surCase, int8_t sousCase);
        void setLC(int8_t valeur, int8_t ligne, int8_t colonne);
        void setBloc(int8_t valeur, int8_t surCase, int8_t sousCase);
        bool estPlacable(int8_t valeur, int8_t ligne, int8_t colonne);
        bool completer();   ///Renvoi faux si la grille est infaisable. Vrai si la résolution a réussi.
    private:
        std::array<int8_t,81> data;
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
**/


/**
     colonne
       0  1  2   3  4  5   6  7  8
ligne╔══╤══╤══╦══╤══╤══╦══╤══╤══╗
  0  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
  1  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
  2  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╠══╪══╪══╬══╪══╪══╬══╪══╪══╣
  3  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
  4  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
  5  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╠══╪══╪══╬══╪══╪══╬══╪══╪══╣
  6  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
  7  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╟──┼──┼──╫──┼──┼──╫──┼──┼──╢
  8  ║  │  │  ║  │  │  ║  │  │  ║
  .  ╚══╧══╧══╩══╧══╧══╩══╧══╧══╝

ligne = (a/3)*3 + b/3
colonne = (a%3)*3 + b%3
**/
