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
    //TODO: háttérszín
    SDL_SetRenderDrawColor(renderer, szin(hatter).r, szin(hatter).g, szin(hatter).b, szin(hatter).a);
    SDL_RenderPresent(renderer);
    //TODO: ezt fel kell szabadítani?
    SDL_Texture* tabla = IMG_LoadTexture(renderer, "tabla_kicsi.jpg");
    SDL_Rect cel = { 448, 0, 576, 576 };
    if (tabla == NULL) {
        SDL_Log("Nem nyithato meg a kep. (%s)", IMG_GetError());
        exit(1);
    }
    SDL_RenderCopy(renderer, tabla, NULL, &cel);

    TTF_Font *menupontok = TTF_OpenFont("myfrida-bold.otf", 26);
    if (menupontok == NULL) {
        SDL_Log("Nem lehetett betolteni a betutipust. (%s)", TTF_GetError());
        exit(1);
    }

    // "következő" gomb
    boxRGBA(renderer, 20, 30, 428, 90, szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    fancy_szoveget_kiir(betutipus(felkover30pt), szin(feher), "Következik:", 448 / 4, 45);

    // dobott szám kiírása
    boxRGBA(renderer, 20, 110, 214, 160, szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    char dobott_szam[2];
    dobott_szam[0] = (rand() % 6 + 1) + 48;
    dobott_szam[1] = '\0';
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), dobott_szam, (20 + 214) / 2, 115);

    // érmek kiírása
    boxRGBA(renderer, 234, 110, 428, 160, szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    char ermek_szama[2];
    //TODO: ez a játékos structból, a 6-os csak a teszteléshez van
    ermek_szama[0] = '6';
    ermek_szama[1] = '\0';
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), ermek_szama, 330, 115);

    // passzok száma
    boxRGBA(renderer, 20, 180, 214, 230, szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    //TODO: ez a játékos struct passz elemével egyenlő
    char passzok_szama[2];
    passzok_szama[0] = (rand() % 3 + 1) + 48;
    passzok_szama[1] = '\0';
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), passzok_szama, (20 + 214) / 2, 185);

    // passzolás
    boxRGBA(renderer, 234, 180, 428, 230, szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), "Passz", 330, 185);

    //TODO: színválasztás
    // mező tartalmának kiírása
    //boxRGBA(renderer, 20, 258, 428, 468, szin(kek).r, szin(kek).g, szin(kek).b, szin(kek).a);
    boxRGBA(renderer, 20, 258, 428, 468, szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, szin(hatter_sotet).a);

    // kilépés gomb kiírása
    boxRGBA(renderer, 20, 496, 214, 546, szin(flatred).r, szin(flatred).g, szin(flatred).b, szin(flatred).a);
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), "Kilépés", (20 + 214) / 2, 501);

    // mentés gomb kiírása
    boxRGBA(renderer, 234, 496, 428, 546, szin(flatgreen).r, szin(flatgreen).g, szin(flatgreen).b, szin(flatgreen).a);
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), "Mentés", 330, 501);

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

/** Visszaadja egy sztring közepének a pozícióját adott pixelhez igazításhoz
 *
 * @param szoveg A vizsgált sztring
 * @param betutipus A felirat betűtípusa
 * @param hova Az az x koordináta, ahova a felirat közepét szeretnénk igazítani, téglalap esetén az x koordináták átlaga
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
        int kul = 448 - (hova + felirat->w / 2);
        visszaad = (448 - felirat->w) - kul;
    }
    SDL_FreeSurface(felirat);
    return visszaad;
}