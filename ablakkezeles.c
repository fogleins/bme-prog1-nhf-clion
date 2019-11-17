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
void ablak_tisztitasa(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, szin(hatter).r, szin(hatter).g, szin(hatter).b, 255);
    SDL_RenderPresent(renderer);
}

//TODO: ez nem kell (?)
void ablak_bezarasa(void) {
//    /* varunk a kilepesre */
//    SDL_Event ev;
//    //while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {}
//
//    /* ablak bezarasa */
    SDL_Quit();
}

/** visszaad egy SDL_Color típusú színt
 *
 *  @param szin main.h-ban definiált színek valamelyike
 *  @return Egy SDL_Color típusú rgb szín
 */
SDL_Color szin(Szinek szin) {
    int r, g, b, a = 255;
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
            break;
        case flatred:
            r = 0xE7;
            g = 0x4C;
            b = 0x3C;
            a = 80;
            break;
        case zold:
            r = 0;
            g = 255;
            b = 0;
            break;
        case flatgreen:
            r = 46;
            g = 204;
            b = 113;
            a = 99;
            break;
        case kek:
//            r = 66;
//            g = 135;
//            b = 245;
            r = 66;
            g = 170;
            b = 245;
            a = 80;
            break;
        case hatter:
            r = 203; //0xCB; //203
            g = 125; //0x7D; //125
            b = 125; //0x7D; //125
            break;
        case hatter_sotet:
            r = 173; //0xAD
            g = 102; //0x66
            b = 102; //0x66;
            break;
        default:
            // fekete
            //TODO
            r = 0;
            g = 0;
            b = 0;
            break;
    }
    SDL_Color color = { r, g, b, a };
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