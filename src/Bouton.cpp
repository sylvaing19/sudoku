#include "Bouton.h"

/// Constructeur
Bouton::Bouton()
{
    positionBouton.x=0;
    positionBouton.y=0;
	modifieParUser = false;
	dejaLoad=false;
	policeDejaLoad=false;
	modifieErreur = false;

    couleurN = { 1, 1, 1 };
	couleurB = { 0, 0, 255 };
	couleurV = { 0, 255, 0 };
	couleurR = { 255, 0, 0 };
	couleurGri = { 200, 240, 255 };


    couleurTexteBouton=couleurN;
}


void Bouton::loaderImage()
{
    const char* stringImageBouton = nomImageBouton.c_str();
    imageBouton = SDL_LoadBMP(stringImageBouton); //zoom a faire

	if (imageBouton == NULL)
	{
        SDL_Quit();
	}

    SDL_SetColorKey(imageBouton, SDL_SRCCOLORKEY, SDL_MapRGB(imageBouton->format, 255, 255, 255)); // met le blanc en transparent pour le bouton
    imageBouton = zoomSurface(imageBouton, zoomX, zoomY, 0);

    //gestion du centre
    if(centreX.size()!=0)
    {
        positionBouton.x= (abs(imageBouton->w-tailleX)/2);
    }
    if(centreY.size()!=0)
    {
        positionBouton.y+= (abs(imageBouton->h-tailleY)/2);
    }

    dejaLoad=true;
}

///Charge le bouton dans le buffer, gere ses positions
void Bouton::chargerBouton()
{
    if(!dejaLoad)
        loaderImage();

    if(!policeDejaLoad)
        loaderPolice();

    SDL_BlitSurface(imageBouton, NULL, fond, &positionBouton);

	if (nomPolice.size() != 0)
    {
        //s'il n'y a pas d'erreurs, on met en bleu
        if(modifieParUser && !modifieErreur)
            couleurTexteBouton=couleurB;
        texteBouton = TTF_RenderText_Blended(policeBouton, messageBouton.c_str(), couleurTexteBouton);
        texteBouton = rotozoomSurface (texteBouton, 0, zoomX, 0);

        //gestion de la position du texte, centré
        positionTexte.x= (positionBouton.x+(imageBouton->w-texteBouton->w)/2);
        positionTexte.y= (positionBouton.y+(imageBouton->h-texteBouton->h)/2);

        SDL_BlitSurface(texteBouton, NULL, fond, &positionTexte);
    }
}

void Bouton::loaderPolice()
{
    if (nomPolice.size() != 0)
    {
        //chargement du texte et police
        const char* stringPolice=nomPolice.c_str();
        policeBouton = TTF_OpenFont(stringPolice, taillePolice);
		if (policeBouton == NULL)
		{
			SDL_Quit();
		}
    }

    policeDejaLoad=true;

}

/// verifie si le bouton en argument est cliqué, et renvoie un booleen repondant à la question "est-ce cliqué ?"
bool Bouton::estClique(SDL_Event event)
{
    return event.button.x>(positionBouton.x) &&
           event.button.x<(positionBouton.x+positionBouton.w) &&
           event.button.y>(positionBouton.y) &&
           event.button.y<(positionBouton.y+positionBouton.h);
}


