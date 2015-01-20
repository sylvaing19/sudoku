#include "Bouton.h"

Bouton::Bouton()
{
    positionBouton.x=0;
    positionBouton.y=0;
}

/*Charge le bouton dans le buffer, gere ses positions*/
void Bouton::chargerBouton()
{
    imageBouton=SDL_LoadBMP(nomImageBouton.c_str()); //zoom a faire
    SDL_SetColorKey(imageBouton, SDL_SRCCOLORKEY, SDL_MapRGB(imageBouton->format, 255, 255, 255)); // met le blanc en transparent pour le bouton
    imageBouton = zoomSurface(imageBouton, zoomX, zoomY, 0);

    //gestion du centre
    if(centreX.size()!=0)
    {
        positionBouton.x+= abs(imageBouton->w-tailleX)/2;
    }
    if(centreY.size()!=0)
    {
        positionBouton.y+= abs(imageBouton->h-tailleY)/2;
    }

    imageBouton = rotozoomSurface (imageBouton, 0, zoomX, 0);
    SDL_BlitSurface(imageBouton, NULL, fond, &positionBouton);

    if(nomPolice.size()!=0)
    {
        //chargement du texte et police
        policeBouton = TTF_OpenFont(nomPolice.c_str(), taillePolice);
        texteBouton = TTF_RenderText_Blended(policeBouton, messageBouton.c_str(), couleurTexteBouton);

        //gestion de la position du texte, centré
        positionTexte.x= positionBouton.x+(imageBouton->w-texteBouton->w)/2;
        positionTexte.y= positionBouton.y+(imageBouton->h-texteBouton->h)/2;

        texteBouton = rotozoomSurface (texteBouton, 0, zoomX, 0);
        SDL_BlitSurface(texteBouton, NULL, fond, &positionTexte);
    }
}


