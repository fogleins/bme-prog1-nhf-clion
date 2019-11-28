//
// Created by Simon on 2019-11-07.
//
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include "main.h"
#include "ablakkezeles.h"
#include "debugmalloc.h"


/** Létrehoz egy ablakot és egy renderert */
//TODO: pointereket adjon vissza (window és rederer)
//TODO: ablakot is fel kell szabadítani?
void ablak_letrehozasa(int szelesseg, int magassag) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Legyél olimpiai bajnok!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szelesseg, magassag, 0);
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

/** letörli az ablak tartalmát */
void ablak_tisztitasa(SDL_Renderer* megjelenito) {
    SDL_RenderClear(megjelenito);
    SDL_SetRenderDrawColor(megjelenito, szin(hatter).r, szin(hatter).g, szin(hatter).b, 255);
    SDL_RenderPresent(megjelenito);
}

/** visszaad egy SDL_Color típusú színt
 *
 *  @param szin main.h-ban definiált színek valamelyike
 *  @return Egy SDL_Color típusú rgb szín
 */
SDL_Color szin(Szinek szin) {
    int a = 255;
    SDL_Color color;
    switch (szin) {
        case feher:
            color = (SDL_Color) { 255, 255, 255, a };
            break;
        case piros:
            color = (SDL_Color) { 255, 0, 0, a };
            break;
        case flatred:
            // https://flatuicolors.com/
            color = (SDL_Color) { 0xE7, 0x4C, 0x3C, 80 };
            break;
        case zold:
            color = (SDL_Color) { 0, 255, 0, a };
            break;
        case flatgreen:
            color = (SDL_Color) { 46, 204, 113, 99 };
            break;
        case kek:
//            r = 66;
//            g = 135;
//            b = 245;
            color = (SDL_Color) { 66, 170, 245, 80 };
            break;
        case hatter:
            color = (SDL_Color) { 203, 125, 125, a };
            break;
        case hatter_sotet:
            color = (SDL_Color) { 173, 102, 102, a };
            break;
        default:
            //TODO: fekete?
            color = (SDL_Color) { 0, 0, 0, a };
            break;
    }
    return color;
}

/** Visszaad egy TTF_Font típusú betűtípusra mutató pointert
 *
 *  @param betutipus A main.h-ban definiált betűtípusok valamelyike
 *  @return NULL, ha nem definiált betűtípust ad meg a hívó
 */
TTF_Font* betutipus(Betuk betutipus) {
    char* nev;
    int meret;
    switch (betutipus) {
        case felkover60pt:
            nev = "myfrida-bold.otf";
            meret = 60;
            break;
        case felkover48pt:
            nev = "myfrida-bold.otf";
            meret = 48;
            break;
        case felkover36pt:
            nev = "myfrida-bold.otf";
            meret = 36;
            break;
        case felkover30pt:
            nev = "myfrida-bold.otf";
            meret = 30;
            break;
        default:
            return NULL;
    }
    return TTF_OpenFont(nev, meret);
    //TODO: ha NULL
}