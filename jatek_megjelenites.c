//
// Created by Simon on 2019-11-17.
//

// Ebben a modulban a játék alatt szükséges megjelenítésért felelős függvények szerepelnek

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>

#include "jatek_megjelenites.h"
#include "ablakkezeles.h"
#include "menu.h"


/** Kirajzolja a játékosszám egérrel való megadásához szükséges gombokat */
void jatekosszam_gombok_kirajzolasa(void) {
    ablak_tisztitasa(renderer);
    int y = 190;
    char szam = '2';
    char kiir[2];
    int teglalap_x1 = 452, teglalap_y1 = 192, teglalap_x2 = teglalap_x1 + 120, teglalap_y2 = teglalap_y1 + 40;
    fancy_szoveget_kiir(betutipus(felkover48pt), szin(feher), "Add meg a játékosok számát:", 0, 80);
    for (int i = 2; i <= 6; ++i) {
        // téglalapok megrajzolása
        boxRGBA(renderer, teglalap_x1, teglalap_y1, teglalap_x2, teglalap_y2,
                szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 100);
        teglalap_y1 += 70;
        teglalap_y2 += 70;
        // számok kiírása
        kiir[0] = szam;
        kiir[1] = '\0';
        fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), kiir, 0, y);
        szam++;
        y += 70;
    }
    SDL_RenderPresent(renderer);
}

/** Letisztítja az ablakot és megjeleníti a paraméterként kapott üzenetet
 *
 * @param betu A megjelenítendő szöveg betűtípusa
 * @param uzenet A megjelenítendő szöveg
 * @param y A megjelenítendő szöveg föggőleges pozíciója az ablakon
 */
void parbeszed(TTF_Font* betu, char* uzenet, int y) {
    ablak_tisztitasa(renderer);
    fancy_szoveget_kiir(betu, szin(feher), uzenet, 0, y);
    SDL_RenderPresent(renderer);
}

/** Megjeleníti a játékmenet grafikus felületét */
void jatekter_kirajzolasa(void) {
    ablak_tisztitasa(renderer);
    //TODO: ezt fel kell szabadítani?
    SDL_Texture* tabla = IMG_LoadTexture(renderer, "tabla_kicsi.jpg");
    SDL_Rect cel = { 448, 0, 576, 576 };
    if (tabla == NULL) {
        SDL_Log("Nem nyithato meg a kep. (%s)", IMG_GetError());
        exit(1);
    }
    SDL_RenderCopy(renderer, tabla, NULL, &cel);

    /*TODO: különféle mezők megjelenítése*/

    TTF_Font *menupontok = TTF_OpenFont("myfrida-bold.otf", 26);
    if (menupontok == NULL) {
        SDL_Log("Nem lehetett betolteni a betutipust. (%s)", TTF_GetError());
        exit(1);
    }
    boxRGBA(renderer, 10, 10, 221, 60, szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);

    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), "Következik:", 4, 20);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(tabla);
}

/** Hátteres élsimított szöveget ír ki
 *
 * @param betutipus A megjelenítendő szöveg betűtípusa
 * @param szoveg A megjelenítendő szöveg
 * @param x A szöveg vízszintes pozíója
 * @param y A szöveg függőleges pozíciója
 * @param betuszin A megjelenítendő szöveg színe
 * @param hatterszin A megjelenítendő szöveg háttérszíne
 */
void hatteres_szoveget_kiir(TTF_Font* betutipus, char* szoveg, int x, int y, SDL_Color betuszin, SDL_Color hatterszin) {
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Rect hova = { 0, 0, 0, 0 };

    felirat = TTF_RenderUTF8_Shaded(betutipus, szoveg, betuszin, hatterszin);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.x = x;
    hova.y = y;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}

/** Visszaadja egy sztring szélességének a felét (középre igazításhoz)
 *
 * @param szoveg A vizsgált sztring
 * @param betutipus A felirat betűtípusa
 * @param hova Az az x koordináta, ahova a felirat közepét szeretnénk igazítani
 * @return A sztring szélessége
 */
int szoveg_poz_x(char* szoveg, TTF_Font* betutipus, int hova) {
    // a színnek a méret szempontjából nincs jelentősége
    int visszaad;
    SDL_Surface* felirat = TTF_RenderUTF8_Blended(betutipus, szoveg, szin(feher));
    // Ha 0, akkor középre igazítjuk
    if (hova == 0)
        visszaad = (1024 - felirat->w) / 2;
    // Különben a táblától bel oldali területre igazítjuk
    else {
        visszaad = (448 - felirat->w) / hova;
    }
    SDL_FreeSurface(felirat);
    return visszaad;
}