#ifndef GRILLE_H
#define GRILLE_H
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <array>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include "EnumDifficulte.h"



/**
*La classe Grille définit une grille de sudoku de 9*9 cases.
*Elle permet de modifier et/ou de consulter les valeurs contenues dans les cases,
*ainsi que de remplir la grille selon les règles du sudoku.
*Les valeurs contenues dans la grille sont des entiers compris entre 0 et 9 inclus.
*La valeur 0 correspond à une case vide.
* @author Sylvain 
*/


class Grille
{
    public:
		/** Constructeur */
        Grille();

		/** Affiche la grille dans la console */
        void afficherConsole();

		/** Renvoie la valeur de la case repérée en ligne/colonne (idexé de 0 à 8) 
		* @param la ligne et la colonne de la case
		* @return le nombre voulu
		*/
        int8_t getLC(int8_t ligne, int8_t colonne);
		/** Renvoie la valeur de la case repérée en bloc/sous-bloc (indexé de 0 à 8)
		* @param les reperes du bloc
		* @return le nombre voulu
		*/
        int8_t getBloc(int8_t surCase, int8_t sousCase);
		/** Place 'valeur' dans la case repérée en ligne/colonne
		* @param la valeur et l'emplacement  de la case 
		*/
        void setLC(int8_t valeur, int8_t ligne, int8_t colonne);
		/** Place 'valeur' dans la case repérée en bloc/sous-bloc
		* @param la valeur et l'emplacement  de la case
		*/
        void setBloc(int8_t valeur, int8_t surCase, int8_t sousCase);
		/** Ne modifie pas la grille. Renvoi Vrai si 'valeur' est un chiffre plaçable compte tenu des valeurs présentes dans la grille, selon les règles du sudoku
		* @param la valeur et l'emplacement de la case
		* @return si le chiffre est placable
		*/
        bool estPlacable(int8_t valeur, int8_t ligne, int8_t colonne);
		/** Complète la grille si possible. Renvoi 'vrai' si la résolution a réussi, 'faux' sinon, en cas d'échec la grille n'est pas modifiée
		* @return si la grille est completable
		*/
        bool completer(bool verifierUnicite = false);
		/** Idem que completer() mais si il existe plusieurs solutions celle qui sera choisie le sera de manière aléatoire
		* @return si la grille est completable
		*/
		bool completerRand();

		void generer(Difficulte);

		/** Réinitialise tous les attributs de la grille : data et grille	*/
		void vider();
		/** Récupère une grille de sudoku depuis un fichier texte et la place dans le membre 'data'. 
		* @param le nom du fichier
		* @return Renvoi vrai si le fichier est correcte, faux sinon.
		*/
		bool getFromFile(std::string nomFichier);
		/** Sauvegarde le membre 'data' dans un fichier texte. 
		* @param le nom du fichier
		* @return Renvoi vrai si la sauvegarde a fonctionné, faux sinon.
		*/
		bool sauvegarder(std::string nomFichier);
		/** 
		* Test unitaire comme promis !
		* @param la grille
		* @return Renvoi Vrai si tout va bien. Renvoi Vrai si tout va bien.
		*/
		bool testResolution(Grille grilleRef);

    private:
        std::array<int8_t,81> data;//Tableau de taille fixe contenant la grille de sudoku
        std::array<std::array<std::vector<int8_t>,9>,9> grille;//Tableau contenant la liste des chiffres possibles pour chaque case

		/** Remplis les possibilitées dans Grille à partir de 'data'.*/
        void remplirGrille();
		/** Parcours 'grille' et pour chaque case ayant une seule possibilité, place la valeur dans 'data'.
		* @return Renvoie False s'il n'y a aucun singleton, True sinon.
		*/
        bool placerSingletons();
		/** 
		* @return Renvoi vrai si la grille ne contient aucune case valant 0, mais ne vérifie pas le respect des règles !
		*/
        bool estComplete();
		/** Vérifie le respect des règles du sudoku en ignorant les cases vides.
		* @return  Renvoi vrai si la grille respecte les règles.
		*/
		bool estCorrecte();
		/** Place dans les arguments (passés en référence) les coordonnées de la case de 'grille' qui contient le tableau non vide le plus petit. Si il en existe plusieurs, on choisi la dernière rencontrée. La fonction renvoie la longueur du tableau en question.
		*/
		unsigned int minGrille(int8_t& ligne, int8_t& colonne);
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
