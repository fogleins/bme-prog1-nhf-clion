//
// Created by Simon on 2019-11-07.
//
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ablakkezeles.h"
#include "debugmalloc.h"


/** Létrehoz egy ablakot és egy renderert
 *
 * @param szelesseg Az ablak szélessége
 * @param magassag Az ablak magassága
 */
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

/** Letörli az ablak tartalmát */
void ablak_tisztitasa(SDL_Renderer* megjelenito) {
    SDL_RenderClear(megjelenito);
    SDL_SetRenderDrawColor(megjelenito, szin(hatter).r, szin(hatter).g, szin(hatter).b, 255);
    SDL_RenderPresent(megjelenito);
}

/** Visszaad egy SDL_Color típusú színt
 *
 *  @param szin main.h-ban definiált színek valamelyike
 *  @return Egy SDL_Color típusú szín
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
            color = (SDL_Color) { 66, 170, 245, 80 };
            break;
        case hatter:
            color = (SDL_Color) { 203, 125, 125, a };
            break;
        case hatter_sotet:
            color = (SDL_Color) { 173, 102, 102, a };
            break;
    }
    return color;
}

/** Visszaad egy TTF_Font típusú betűtípusra mutató pointert
 *
 *  @param betutipus Az ablakkezeles.h-ban definiált betűtípusok valamelyike
 *  @return NULL, ha nem definiált betűtípust ad meg a hívó
 */
TTF_Font* betutipus(Betuk betutipus) {
    char* nev = "myfrida-bold.otf";
    int meret;
    switch (betutipus) {
        case normal120pt:
            nev = "myfrida-regular.otf";
            meret = 150;
            break;
        case felkover60pt:
            meret = 60;
            break;
        case felkover48pt:
            meret = 48;
            break;
        case felkover36pt:
            meret = 36;
            break;
        case felkover30pt:
            meret = 30;
            break;
        case felkover24pt:
            meret = 24;
            break;
        default:
            return NULL;
    }
    return TTF_OpenFont(nev, meret);
}