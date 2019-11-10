//
// Created by Simon on 2019-11-08.
//

#ifndef TARSAS_ABLAKKEZELES_H
#define TARSAS_ABLAKKEZELES_H

SDL_Renderer *renderer;

int dice(void);
void ablak_letrehozasa(int szelesseg, int magassag);
void ablakra_kiir(void);
void ablak_bezarasa(void);
void ablak_tisztitasa(SDL_Renderer* renderer);

#endif //TARSAS_ABLAKKEZELES_H
