#ifndef BOUTON_H
#define BOUTON_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Bouton
{
    public:
        Bouton();
        SDL_Rect position;
        std::string imageFond;
        std::string imageFondFocus;
        std::string nomPolice;
        std::string message;
    private:
        SDL_Rect positionTexte;
        SDL_Surface* fond;
        SDL_Surface* fondFocus;
        SDL_Surface* texte;
        TTF_Font* police;
};

#endif // BOUTON_H
