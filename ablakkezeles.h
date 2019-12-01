//
// Created by Simon on 2019-11-08.
//
#include <SDL2/SDL_ttf.h>

#include "main.h"

#ifndef TARSAS_ABLAKKEZELES_H
#define TARSAS_ABLAKKEZELES_H

SDL_Renderer *renderer;

void ablak_letrehozasa(int szelesseg, int magassag);
void ablak_tisztitasa(SDL_Renderer* renderer);
SDL_Color szin(Szinek szin);
TTF_Font* betutipus(Betuk betutipus);

#endif //TARSAS_ABLAKKEZELES_H
