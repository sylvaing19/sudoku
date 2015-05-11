#include "Grille.h"

using namespace std;

Grille::Grille()
{
    data.fill(0);
	srand(time(NULL));
}

void Grille::vider()
{
	data.fill(0);
	for (int ligne = 0; ligne < 9; ligne++)
	{
		for (int colonne = 0; colonne < 9; colonne++)
		{
			grille[ligne][colonne].clear();
		}
	}
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

bool Grille::completer(bool verifierUnicite)
{
	/*
	Création d'un point de restauration des données initiales en cas d'échec de la résolution
	*/
	array<int8_t, 81> data_backup = data;
	array<array<vector<int8_t>, 9>, 9> grille_backup = grille;

	/*
	Résolution par simple élimination des valeurs impossibles
	*/
    do
    {
        Grille::remplirGrille();
    }
    while(Grille::placerSingletons());//fin de la résolution par élimination

	/*
	Pour une grille non faisable, il est possible que la méthode par élimination aboutisse
	à une grille fausse, on vérifie donc cette éventualité.
	*/
	if (!this->estCorrecte())
	{//On restaure la grille initiale
		data = data_backup;
		grille = grille_backup;
		return false;//On indique que la grille était infaisable
	}


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
    if(!this->estComplete())
    {
        int8_t ligne, colonne;
		array<int8_t, 81> data_before_hyp = data, data_correcte;
		array<array<vector<int8_t>, 9>, 9> grille_before_hyp = grille;
        /*
        Il suffit d'explorer les hypothèses d'une seule case pour toujours résoudre la
        grille, on choisit donc celle ayant le moins de possibilitées.
        */
        unsigned int nbHyp = this->minGrille(ligne, colonne);
		unsigned int nbHypCorrectes = 0;

        for(unsigned int i=0; i<nbHyp; i++)//On teste successivement chacune des hypothèses
        {
			this->setLC(this->grille[ligne][colonne][i], ligne, colonne);
			if (this->completer(verifierUnicite))
			{
				if (verifierUnicite)
				{
					data_correcte = data;
					data = data_before_hyp;
					grille = grille_before_hyp;
					nbHypCorrectes++;
				}
				else
				{
					return true;
				}
			}
            //Si cette hypothèse était mauvaise, on passe à la suivante (ou bien si on veut toutes les tester)
        }

		if (nbHypCorrectes == 1)
		{
			data = data_correcte;
			return true;
		}

        /* Si on arrive à cet endroit, c'est qu'aucune hypothèse n'était valide,
		ou bien que plusieurs solutions existent tandis que verifierUnicite
		était à true, la grille n'est donc pas solvable. */

		//On restaure la grille initiale
        data = data_backup;
		grille = grille_backup;
        return false;//On indique l'échec de la résolution
    }
    else
    {
        return true;
    }
}

bool Grille::estComplete()
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
	ligne = 0;
	colonne = 0;

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

bool Grille::estCorrecte()
{
	for (int ligne = 0; ligne < 9; ligne++)
	{
		for (int colonne = 0; colonne < 9; colonne++)
		{
			int8_t valeur = this->getLC(ligne, colonne);
			if (valeur != 0 && !this->estPlacable(valeur, ligne, colonne))
				return false;
		}
	}
	return true;
}

bool Grille::completerRand()
{
	/*
	Création d'un point de restauration des données initiales en cas d'échec de la résolution
	*/
	array<int8_t, 81> data_backup = data;
	array<array<vector<int8_t>, 9>, 9> grille_backup = grille;

	/*
	Résolution par simple élimination des valeurs impossibles
	*/
	do
	{
		Grille::remplirGrille();
	} while (Grille::placerSingletons());//fin de la résolution par élimination

	/*
	Pour une grille non faisable, il est possible que la méthode par élimination aboutisse
	à une grille fausse, on vérifie donc cette éventualité.
	*/
	if (!this->estCorrecte())
	{//On restaure la grille initiale
		data = data_backup;
		grille = grille_backup;
		return false;//On indique que la grille était infaisable
	}


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
	if (!this->estComplete())
	{
		int8_t ligne, colonne;
		/*
		Il suffit d'explorer les hypothèses d'une seule case pour toujours résoudre la
		grille, on choisit donc celle ayant le moins de possibilitées.
		*/
		unsigned int nbHyp = this->minGrille(ligne, colonne);

		unsigned int premiereHyp = rand() % nbHyp;
		for (unsigned int i = 0; i<nbHyp; i++)//On teste successivement chacune des hypothèses
		{
			this->setLC(this->grille[ligne][colonne][(i+premiereHyp)%nbHyp], ligne, colonne);
			if (this->completerRand())
				return true;
			//Si cette hypothèse était mauvaise, on passe à la suivante
		}
		//Si on arrive à cet endroit, c'est qu'aucune hypothèse n'était valide, la grille n'est donc pas solvable.

		//On restaure la grille initiale
		data = data_backup;
		grille = grille_backup;
		return false;//On indique l'échec de la résolution
	}
	else
	{
		return true;
	}
}


void Grille::generer(Difficulte difficulte)
{
	data.fill(0);
	completerRand();

	vector<unsigned int> tabIndicesSupprimables;
	array<int, 10> nbChiffresRestant;
	unsigned int nbReveles = 81;

	for (unsigned int i = 0; i < 81; i++)
	{
		tabIndicesSupprimables.push_back(i);
	}
	for (int i = 1; i <= 9; i++)
	{
		nbChiffresRestant[i] = 9;
	}

	while (nbReveles > 34)
	{
		supprimerCaseRandom(tabIndicesSupprimables, nbChiffresRestant, nbReveles);
	}

	bool continuer = true;
	while (nbReveles > 28 && continuer)
	{
		continuer = supprimerCaseRandom(tabIndicesSupprimables, nbChiffresRestant, nbReveles);
	}
}

bool Grille::supprimerCaseRandom(vector<unsigned int>& tabIndicesSupprimables, array<int, 10>& nbChiffresRestant, unsigned int& nbReveles)
{
	unsigned int r = rand() % tabIndicesSupprimables.size();

	unsigned int indiceSupprime = tabIndicesSupprimables[r];
	int8_t valeurSupprime = data[indiceSupprime];


	array<int8_t, 81> data_backup = data;
	data[indiceSupprime] = 0;
	bool suppressionPossible = completer(true);
	data = data_backup;
	tabIndicesSupprimables.erase(tabIndicesSupprimables.begin() + r);
	if (suppressionPossible)
	{
		data[indiceSupprime] = 0;
		nbChiffresRestant[valeurSupprime]--;
		if (nbChiffresRestant[valeurSupprime] == 1)
		{
			bool nonTrouve = true;
			unsigned int i = 0;
			while (nonTrouve && i < 81)
			{
				if (data[i] == valeurSupprime)
					nonTrouve = false;
				else
					i++;
			}
			vector<unsigned int>::iterator it = find(tabIndicesSupprimables.begin(), tabIndicesSupprimables.end(), i);
			if (it != tabIndicesSupprimables.end())
				tabIndicesSupprimables.erase(it);
		}
		nbReveles--;
	}
	return suppressionPossible;
}

bool Grille::getFromFile(string nomFichier)
{
	ifstream fichier(nomFichier.c_str(), ios::in);
	if (fichier)
	{
		int chiffre;
		for (int i = 0; i < 81; i++)
		{
			fichier >> chiffre;
			this->data[i] = int8_t(chiffre);
		}
		fichier.close();
		return true;
	}
	else
		return false;
}

bool Grille::sauvegarder(string nomFichier)
{
	ofstream fichier(nomFichier.c_str(), ios::out | ios::trunc);
	if (fichier)
	{
		for (int i = 0; i < 81; i++)
		{
			fichier << int(this->data[i]) << " ";
		}
		fichier.close();
		return true;
	}
	else
		return false;
}

bool Grille::testResolution(Grille grilleRef)
{
	if (this->completer())
	{
		bool grillesIdentiques = true;
		for (int ligne = 0; ligne < 9; ligne++)
		{
			for (int colonne = 0; colonne < 9; colonne++)
			{
				if (this->getLC(ligne, colonne) != grilleRef.getLC(ligne, colonne))
					grillesIdentiques = false;
			}
		}
		return grillesIdentiques;
	}
	else
	{
		return true;
	}
}

bool Grille::estEgale(Grille grilleAutre)
{
    for (int ligne = 0; ligne < 9; ligne++)
	{
		for (int colonne = 0; colonne < 9; colonne++)
		{
			int8_t valeur = this->getLC(ligne, colonne);
            int8_t valeurAutre = grilleAutre.getLC(ligne, colonne);

			if (! (valeur==valeurAutre) )
				return false;
		}
	}
	return true;


}
