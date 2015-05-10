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
	La classe Score d�fini un objet de gestion du score du joueur.
*/
class Score
{
public:
	Score();	//Constructeur

	/* Initialise le score et commence le d�compte du timer */
	void initScore(Difficulte);

	/* Interromp le d�compte du timer */
	void stopTimer();

	/* Relance le d�compte du timer */
	void restartTimer();

	/* Fonction � appeler pour indiquer qu'un indice � �t� utilis� */
	void indiceUtilise();

	/* Calcule et renvoie le score actuel */
	int getScore(void);

	/* Renvoi la place du score actuel dans le classement (permet de 
	d�terminer s'il s'agit ou non d'un score class� avant d'utiliser save() ) 
	Supprime le fichier de sauvegarde si il est non conforme, et renvoi 1
	dans ce cas */
	unsigned int getRank(void);

	/* Sauvegarde le score courant dans le fichier des meilleurs scores
	� la place indiqu�e, en utilisant le nom pass� en argument 
	Si le fichier de sauvegrade n'existe pas, il sera cr�� */
	void save(std::string name, unsigned int rank);

	/* Getter de la variable contenant le nombre de meilleurs scores stock�s */
	unsigned int getNbOfHighscore(void);

	/* Setter de la variable contenant le nombre de meilleurs scores stock�s */
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