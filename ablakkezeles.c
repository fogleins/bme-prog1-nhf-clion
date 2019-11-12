//
// Created by Simon on 2019-11-07.
//
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "main.h"
#include "ablakkezeles.h"


/** létrehoz egy ablakot és egy renderert **/
//TODO: pointereket adjon vissza (window és rederer)
void ablak_letrehozasa(int szelesseg, int magassag) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Legyel olimpiai bajnok!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szelesseg, magassag, 0);
    if (window == NULL) {
        SDL_Log("Az ablak letrehozasa nem sikerult: %s.", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);
}

void ablak_tisztitasa(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void ablak_bezarasa(void) {
    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {}

    /* ablak bezarasa */
    SDL_Quit();
}

/* visszaad egy SDL_Color típusú színt */
SDL_Color szin(Szinek szin) {
    int r, g, b;
    switch (szin) {
        case feher:
            r = 255;
            g = 255;
            b = 255;
            break;
        case piros:
            r = 255;
            g = 0;
            b = 0;
        default:
            // fekete
            r = 0;
            g = 0;
            b = 0;
            break;
    }
    SDL_Color color = {r, g, b};
    return color;
}