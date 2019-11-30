//
// Created by Simon on 2019-11-17.
//

// Ebben a modulban a játék alatt szükséges megjelenítésért felelős függvények szerepelnek

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <string.h>

#include "jatek_megjelenites.h"
#include "ablakkezeles.h"
#include "menu.h"
#include "jatek.h"


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
    ablak_tisztitasa(renderer);
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

    // "következő" gomb
    boxRGBA(renderer, 20, 30, 428, 90,
            szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    fancy_szoveget_kiir(betutipus(felkover30pt),
            szin(feher), "Következik:", 448 / 4, 45);

    // dobott szám kiírása
    boxRGBA(renderer, 20, 110, 214, 160,
            szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    //dobókocka ikon
    // https://www.flaticon.com/free-icon/dice_2102123
    SDL_Texture* kocka = IMG_LoadTexture(renderer, "dice3.png");
    SDL_Rect celterulet_kocka = { 35, 120, 30, 30};
    SDL_RenderCopy(renderer, kocka, NULL, &celterulet_kocka);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(kocka);

    // érmek kiírása
    boxRGBA(renderer, 234, 110, 428, 160,
            szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    // érem ikon
    // https://www.kissclipart.com/medal-png-grey-clipart-gold-medal-silver-medal-h1kus5/download-clipart.html - erem.png
    // https://www.flaticon.com/free-icon/medal_321854 - medal.png
    SDL_Texture* erem = IMG_LoadTexture(renderer, "medal.png");
    SDL_Rect celterulet_erem = { 250, 120, 30, 30 };
    SDL_RenderCopy(renderer, erem, NULL, &celterulet_erem);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(erem);

    // passzok száma
    boxRGBA(renderer, 20, 180, 214, 230,
            szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);

    // passzolás
    boxRGBA(renderer, 234, 180, 428, 230,
            szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), "Passz", 330, 185);

    //TODO: mező tartalmának kiírása
    //boxRGBA(renderer, 20, 258, 428, 468, szin(kek).r, szin(kek).g, szin(kek).b, szin(kek).a);
    boxRGBA(renderer, 20, 258, 428, 468,
            szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, szin(hatter_sotet).a);

    // kilépés gomb kiírása
    boxRGBA(renderer, 20, 496, 214, 546,
            szin(flatred).r, szin(flatred).g, szin(flatred).b, szin(flatred).a);
    fancy_szoveget_kiir(betutipus(felkover36pt),
            szin(feher), "Kilépés", (20 + 214) / 2, 501);

    // mentés gomb kiírása
    boxRGBA(renderer, 234, 496, 428, 546,
            szin(flatgreen).r, szin(flatgreen).g, szin(flatgreen).b, szin(flatgreen).a);
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

/** A játékosk által választható színek
 *
 * @param szin A szín neve
 * @return SDL_Color típusú szín
 */
SDL_Color jatekosszin(Jatekosszin szin) {
    SDL_Color color;
    switch (szin) {
        case j_piros:
            color = (SDL_Color) { 235, 64, 52, 255 };
            break;
        case j_narancs:
            color = (SDL_Color) { 252, 186, 3, 255 };
            break;
        case j_sarga:
            color = (SDL_Color) { 248, 255, 0, 255 };
            break;
        case j_zold:
            color = (SDL_Color) { 50, 168, 82, 255 };
            break;
        case j_kek:
            color = (SDL_Color) { 66, 135, 245, 255 };
            break;
        case j_lila:
            color = (SDL_Color) { 128, 0, 128, 255 };
            break;
    }
    return color;
}

// TODO: kell?
/** SDL_Color-t alakít vissza enummá
 *
 * @return A szín neve
 */
Jatekosszin szinenumma(SDL_Color szin) {
    // piros
    if (szin.r == 235 && szin.g == 64 && szin.b == 52)
        return j_piros;
    // sárga
    if (szin.r == 248 && szin.g == 255 && szin.b == 0)
        return j_sarga;
    // zöld
    if (szin.r == 50 && szin.g == 168 && szin.b == 82)
        return j_zold;
    // kék
    if (szin.r == 66 && szin.g == 135 && szin.b == 245)
        return j_kek;
    // lila
    if (szin.r == 128 && szin.g == 0 && szin.b == 128)
        return j_lila;
    // narancssárga
    if (szin.r == 252 && szin.g == 186 && szin.b == 3)
        return j_narancs;
}

/** Kirajzol egy képernyőt, melyen a játékosok színeket választhatnak
 *
 * @param foglalt_szinek A lefoglalt színek tömbje
 * @return A szín neve
 */
Jatekosszin jatekos_szinvalasztas(bool* foglalt_szinek) {
    fancy_szoveget_kiir(betutipus(felkover48pt), szin(feher), "Válassz színt:", 0, 100);
    SDL_Rect korvonal;
    for (int i = 0; i < 6; ++i) {
        korvonal = (SDL_Rect) { 222 + i * 100, 250, 80, 80 };
        // TODO: miért kell levonni 2-t ahhoz, hogy ne lógjon ki a szín a keretből?
        boxRGBA(renderer, korvonal.x, korvonal.y, korvonal.x + korvonal.w - 2, korvonal.y + korvonal.h - 2,
                jatekosszin(j_piros + i).r, jatekosszin(j_piros + i).g,
                jatekosszin(j_piros + i).b, jatekosszin(j_piros + i).a);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &korvonal);
        xet_rajzol(foglalt_szinek, korvonal);
    }
    SDL_RenderPresent(renderer);
    // eventek kezelése
    bool valasztott = false; /* az adott játékos választott-e új színt (=amit még mások nem) */
    int valasztottak_szama_event_elott = valasztott_szinek_szama(foglalt_szinek);
    while (!valasztott) {
        SDL_Event esemeny;
        SDL_WaitEvent(&esemeny);
        switch (esemeny.type) {
            case SDL_MOUSEBUTTONDOWN:
                // TODO: ne legyen sorminta
                if (esemeny.button.y >= 250 && esemeny.button.y <= 330) {
                    if (!foglalt_szinek[j_piros] && esemeny.button.x >= 222 && esemeny.button.x <= 302)
                        return szinfoglalas(j_piros, foglalt_szinek, &korvonal);
                    if (!foglalt_szinek[j_narancs] && esemeny.button.x >= 322 && esemeny.button.x <= 402)
                        return szinfoglalas(j_narancs, foglalt_szinek, &korvonal);
                    if (!foglalt_szinek[j_sarga] && esemeny.button.x >= 422 && esemeny.button.x <= 502)
                        return szinfoglalas(j_sarga, foglalt_szinek, &korvonal);
                    if (!foglalt_szinek[j_zold] && esemeny.button.x >= 522 && esemeny.button.x <= 602)
                        return szinfoglalas(j_zold, foglalt_szinek, &korvonal);
                    if (!foglalt_szinek[j_kek] && esemeny.button.x >= 622 && esemeny.button.x <= 702)
                        return szinfoglalas(j_kek, foglalt_szinek, &korvonal);
                    if (!foglalt_szinek[j_lila] && esemeny.button.x >= 722 && esemeny.button.x <= 802)
                        return szinfoglalas(j_lila, foglalt_szinek, &korvonal);
                    if (valasztott_szinek_szama(foglalt_szinek) == valasztottak_szama_event_elott + 1)
                        valasztott = true;
                }
                break;
            case SDL_QUIT:
                //TODO: játék vége, memóriaszabadítás
                return j_kilep;
        }
    }
}

/** Visszadja, hogy eddig hány szín lett kiválasztva
 *
 * @param foglalt_szinek A színek foglalását tároló bool tömb
 * @return A foglalt színek száma
 */
static int valasztott_szinek_szama(const bool* foglalt_szinek) {
    int valasztott_szinek_szama = 0;
    for (int i = 0; i > 6; i++) {
        if (foglalt_szinek[i])
            valasztott_szinek_szama++;
    }
    return valasztott_szinek_szama;
}

/** A már kivalasztott színek gombjára x-et tesz
 *
 * @param foglalt_szinek A foglalt színeket tároló bool tömb
 * @param korvonal A színek gombjainak koordinátái
 */
static void xet_rajzol(const bool* foglalt_szinek, SDL_Rect korvonal) {
    for (int i = 0; i < 6; ++i) {
        korvonal.x = 222 + i * 100;
        if (foglalt_szinek[i])
            fancy_szoveget_kiir(betutipus(normal120pt), szin(piros), "X",
                    (korvonal.x + korvonal.x + korvonal.w) / 2, korvonal.y - 50);
    }
    SDL_RenderPresent(renderer);
}

/** Lefoglal egy színt egy-egy játékosnak, a már foglalt színekre x-et tesz
 *
 * @param szin A lefoglalt szín
 * @param foglalt_szinek A foglalt színeket tároló tömb
 * @param korvonal A gomb koordinátái
 * @return A lefoglalt szín
 */
static Jatekosszin szinfoglalas(Jatekosszin szin, bool* foglalt_szinek, SDL_Rect* korvonal) {
    foglalt_szinek[szin] = true;
    xet_rajzol(foglalt_szinek, *korvonal);
    return szin;
}

/** A játéktáblán az aktuális játékos váltásakor megváltozó feliratokat írja ki
 *
 * @param soronkovetkezo A következő játékos
 */
void szovegek_megjelenitese(Jatekos* soronkovetkezo) {
    char dobott_szam[2];
    dobott_szam[0] = (char) ((rand() % 6 + 1) + 48);
    dobott_szam[1] = '\0';
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), dobott_szam, (20 + 214) / 2, 115);

    //TODO: ez a játékos struct passz elemével egyenlő
    char passzok_szama[2];
    passzok_szama[0] = (char) (soronkovetkezo->passz + 48);
    passzok_szama[1] = '\0';
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), passzok_szama, (20 + 214) / 2, 185);

    char ermek_szama[2];
    //TODO: ez a játékos structból, a 6-os csak a teszteléshez van
    ermek_szama[0] = (char) (soronkovetkezo->ermek + 48);
    ermek_szama[1] = '\0';
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), ermek_szama, 330, 115);

    SDL_RenderPresent(renderer);
}

void babuk_megjelenitese(Jatekos* soronkovetkezo) {
    int x = 200, y = 200, r = 8;
    SDL_Color szin = jatekosszin(soronkovetkezo->szin);
    filledCircleRGBA(renderer, x, y, r, szin.r, szin.g, szin.b, szin.a);
    circleRGBA(renderer, x, y, r, 0, 0, 0, 255);

    SDL_RenderPresent(renderer);
}