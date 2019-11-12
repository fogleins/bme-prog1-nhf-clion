//
// Created by Simon on 2019-11-08.
//
#include "main.h"

#ifndef TARSAS_ABLAKKEZELES_H
#define TARSAS_ABLAKKEZELES_H

SDL_Renderer *renderer;

void ablak_letrehozasa(int szelesseg, int magassag);
void ablak_bezarasa(void);
void ablak_tisztitasa(SDL_Renderer* renderer);
SDL_Color szin(Szinek szin);

#endif //TARSAS_ABLAKKEZELES_H
