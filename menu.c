//
// Created by Simon on 2019-11-08.
//
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "ablakkezeles.h"
#include "jatek.h"
#include "menu.h"

SDL_Window* menu_kirajzolasa(void) {
    /// Háttér beállítása
    /* kép forrása:
     * https://www.pexels.com/photo/monopoly-board-game-on-brown-wooden-tabletop-776654/ */
    SDL_Texture* hatter = IMG_LoadTexture(renderer, "bg.jpg");
    if (hatter == NULL) {
        SDL_Log("Nem nyithato meg a kep. (%s)", IMG_GetError());
        exit(1);
    }
    SDL_RenderCopy(renderer, hatter, NULL, NULL);

    /// Menüpontok kirajzolása
    TTF_Init();
    TTF_Font *cim = TTF_OpenFont("myfrida-shadow-regular.otf", 65);
    TTF_Font *menupontok = TTF_OpenFont("myfrida-bold.otf", 26);
    if (cim == NULL) {
        SDL_Log("Nem lehetett betolteni a betutipust. (%s)", TTF_GetError());
        exit(1);
    }
    SDL_Color feher = { 255, 255, 255 };
    fancy_szoveget_kiir(cim, feher, "Fõmenü", 100);
//    /** alpha kódok: https://gist.github.com/lopspower/03fb1cc0ac9f32ef38f4 **/
    boxRGBA(renderer, 362, 255, 662, 305, 0xCB, 0x7D, 0x7D, 0xC7);
    boxRGBA(renderer, 362, 325, 662, 375, 0xCB, 0x7D, 0x7D, 0xC7);
    boxRGBA(renderer, 362, 415, 662, 465, 0xCB, 0x7D, 0x7D, 0xE6);
    fancy_szoveget_kiir(menupontok, feher, "Új játék", 265);
    fancy_szoveget_kiir(menupontok, feher, "Játékmenet betöltése", 337);
    fancy_szoveget_kiir(menupontok, feher, "Kilépés", 425);

    /// a változtatások megjelenítése a kimeneten
    /*TODO: a renderer nem frissül, a
     * háttér nem jelenik meg, javításch - kész */
    SDL_RenderPresent(renderer);
    egeresbillentyu();
    // a kép által foglalt memória felszabadítása
    SDL_DestroyTexture(hatter);
}
//TODO: a sztring bemenet biztos jó így?
static void fancy_szoveget_kiir(TTF_Font *betutipus, SDL_Color szin, char* szoveg, int y) {
    /* ha sajat kodban hasznalod, csinalj belole fuggvenyt! */
    /* felirat megrajzolasa, kulonfele verziokban */
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Rect hova = { 0, 0, 0, 0 };

    felirat = TTF_RenderUTF8_Blended(betutipus, szoveg, szin);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.x = (1024 - felirat->w) / 2;
    hova.y = y;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}

/* Ez a függvény a menüképernyőn
 * tartózkodáskor fellépő eseményeket
 * kezeli. A menüpontok elérhetőek
 * az egér és a billentyűzet
 * használatával is. */
static void egeresbillentyu(void) {
    bool kilepes = false;
    while (!kilepes) {
        SDL_Event esemeny;
        SDL_WaitEvent(&esemeny);
        switch (esemeny.type){
            case SDL_MOUSEBUTTONDOWN:
                // ha új játékot kezd
                if (esemeny.button.x >= 362 && esemeny.button.x <= 662 && esemeny.button.y >= 255 && esemeny.button.y <= 305) {
                    jatekkezdes();
                    //TODO: új játék
                }
                // ha játékmenetet tölt be
                if (esemeny.button.x >= 362 && esemeny.button.x <= 662 && esemeny.button.y >= 325 && esemeny.button.y <= 375) {
                    //TODO: fájl beolvasása
                }
                if (esemeny.button.x >= 362 && esemeny.button.x <= 662 && esemeny.button.y >= 415 && esemeny.button.y <= 465) {
                    SDL_Quit();
                    kilepes = true;
                }
                break;
            case SDL_KEYDOWN:
                // ha n (=new)
                if (esemeny.key.keysym.sym == SDLK_n) {
                    jatekkezdes();
                }
                // ha l (load)
                if (esemeny.key.keysym.sym == SDLK_l) {
                    /// ld fent
                }
                // ha q (quit)
                if (esemeny.key.keysym.sym == SDLK_q) {
                    kilepes = true;
                    SDL_Quit();
                }
                break;
            case SDL_QUIT:
                kilepes = true;
                ablak_bezarasa();
                break;
        }
    }
}