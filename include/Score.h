#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <time.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "EnumDifficulte.h"

/*
	La classe Score défini un objet de gestion du score du joueur.
*/
class Score
{
public:
	Score();	//Constructeur

	/* Initialise le score et commence le décompte du timer */
	void initScore(Difficulte);

	/* Interromp le décompte du timer */
	void stopTimer();

	/* Relance le décompte du timer */
	void restartTimer();

	/* Fonction à appeler pour indiquer qu'un indice à été utilisé */
	void indiceUtilise();

	/* Calcule et renvoie le score actuel */
	int getScore(void);

	/* Renvoi la place du score actuel dans le classement (permet de 
	déterminer s'il s'agit ou non d'un score classé avant d'utiliser save() ) 
	Supprime le fichier de sauvegarde si il est non conforme, et renvoi 1
	dans ce cas */
	unsigned int getRank(void);

	/* Sauvegarde le score courant dans le fichier des meilleurs scores
	à la place indiquée, en utilisant le nom passé en argument 
	Si le fichier de sauvegrade n'existe pas, il sera créé */
	void save(std::string name, unsigned int rank);

	/* Getter de la variable contenant le nombre de meilleurs scores stockés */
	unsigned int getNbOfHighscore(void);

	/* Setter de la variable contenant le nombre de meilleurs scores stockés */
	void setNbOfHighscore(unsigned int);

private:
	int initialScore;
	bool gamePaused;
	int nbIndices;
	time_t beginTime;
	time_t pausedTime;
	time_t pauseStartTime;
	unsigned int nbOfHighscore;
	std::string saveFile;
};

#endif //SCORE_H