#include "Score.h"

using namespace std;

Score::Score()
{
	initialScore = 0;
	gamePaused = true;
	nbIndices = 0;
	nbOfHighscore = 3;
	saveFile = "highscore/highscore.txt";
	pausedTime = 0;
}

void Score::initScore(Difficulte difficulte)
{
	switch (difficulte)
	{
	case FACILE:
		initialScore = 3000;
		break;
	case MOYEN:
		initialScore = 5000;
		break;
	case DIFFICILE:
		initialScore = 8000;
		break;
	default:
		break;
	}

	gamePaused = false;
	nbIndices = 0;
	beginTime = time(NULL);
	pausedTime = 0;
}

void Score::removeScore(int pointsToRemove)
{
    initialScore-=pointsToRemove;
}

void Score::stopTimer()
{
	gamePaused = true;
	pauseStartTime = time(NULL);
}

void Score::restartTimer()
{
	gamePaused = false;
	time_t currentTime = time(NULL);
	pausedTime += currentTime - pauseStartTime;
}

void Score::indiceUtilise()
{
	nbIndices++;
}

int Score::getScore()
{
	time_t currentTime = time(NULL);
	time_t playTime;
	if (gamePaused)
		playTime = pauseStartTime - beginTime - pausedTime;
	else
		playTime = currentTime - beginTime - pausedTime;

	return initialScore - 200 * nbIndices - 100 * playTime / 60;
}

unsigned int Score::getRank()
{
	ifstream fichier(saveFile.c_str(), ios::in);
	if (fichier)
	{
		unsigned int realNbOfHighscore = 0;
		bool fichierNonConforme = false;
		string rangCourant, nomCourant;
		int scoreCourant;
		vector<string> rang, nom;
		vector<int> score;
		for (unsigned int i = 0; i < nbOfHighscore; i++)
		{
			if (fichier >> rangCourant >> nomCourant >> scoreCourant)
			{
				realNbOfHighscore++;
				rang.push_back(rangCourant);
				nom.push_back(nomCourant);
				score.push_back(scoreCourant);
				if (rang[i].size() < 2 || rang[i][0] != '#' || atoi(rang[i].substr(1).c_str()) != i + 1)
				{
					fichierNonConforme = true;
				}
			}
		}
		realNbOfHighscore = min(realNbOfHighscore, nbOfHighscore);

		int scoreAClasser = getScore();
		unsigned int rangDuScore = realNbOfHighscore + 1;
		if (score[0] < scoreAClasser)
			rangDuScore = 1;

		for (unsigned int i = 1; i < realNbOfHighscore; i++)
		{
			if (score[i - 1] > scoreAClasser && score[i] <= scoreAClasser)
				rangDuScore = i + 1;
			if (score[i - 1] < score[i])
				fichierNonConforme = true;
		}

		fichier.close();
		if (fichierNonConforme)
		{
			remove(saveFile.c_str());
			return 1;
		}
		else
			return rangDuScore;
	}
	else
		return 1;
}

void Score::save(string name, unsigned int rank)
{
	fstream fichier(saveFile.c_str(), ios::in | ios::out | ios::ate);
	fichier.seekp(0, ios::beg);

	string rang, nom, score, rangS, nomS, scoreS;

	do
	{
		fichier >> rang >> nom >> score;
	} while (atoi(rang.substr(1).c_str()) != rank - 1);
	fichier << '#' << rank << ' ' << name << ' ' << getScore() << endl;

	int curseur;
	bool endOfFile = false;

	do
	{
		curseur = fichier.tellp();
		if (!(fichier >> rangS >> nomS >> scoreS))
		{
			endOfFile = true;
		}
		fichier.seekp(curseur, ios::beg);
		fichier << rang << ' ' << nom << ' ' << score << endl;
		rang = rangS;
		nom = nomS;
		score = scoreS;
	} while (!endOfFile);

}


unsigned int Score::getNbOfHighscore()
{
	return nbOfHighscore;
}

void Score::setNbOfHighscore(unsigned int nbOfHighscore)
{
	this->nbOfHighscore = nbOfHighscore;
}
