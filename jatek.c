//
// Created by Simon on 2019-11-10.
//
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>

#include "main.h"
#include "jatek.h"
#include "jatek_megjelenites.h"
#include "ablakkezeles.h"
#include "fajlkezeles.h"
#include "menu.h"
#include "debugmalloc.h"

void jatek_main(Jatekos* jatekostomb, const int* jatekosszam) {
    Mezo mezok_tombje[40];
    mezok_beolvasasa(mezok_tombje);
    for (int i = 0; i < 40; ++i)
        mezok_tombje[i].kozep = mezo_kozepe(&i);

    jatekostomb = (Jatekos*) malloc(*jatekosszam * sizeof(Jatekos));
    if (jatekostomb == NULL) {
        SDL_Log("A memóriafoglalás sikertelen: %s", SDL_GetError());
        exit(1);
    }
    // hamis, ha nem foglalták még, egyébként igaz
    bool foglalt_szinek[6];
    for (int j = 0; j < 6; ++j)
        foglalt_szinek[j] = false;
    Jatekosszin valasztott_szin;
    SDL_RenderClear(renderer);
    for (int i = 0; i < *jatekosszam; ++i) {
        valasztott_szin = jatekos_szinvalasztas(foglalt_szinek);
        if (valasztott_szin == j_kilep)
            break;
        jatekostomb[i].id = i;
        jatekostomb[i].szin = valasztott_szin;
        jatekostomb[i].mezo_id = 0;
        jatekostomb[i].mezo = &mezok_tombje[jatekostomb[i].mezo_id];
        jatekostomb[i].ermek = 0;
        jatekostomb[i].passz = 3;
        jatekostomb[i].kimarad = 0;
        jatekostomb[i].nev[0] = ((char) (48 + i + 1));
        jatekostomb[i].nev[1] = '\0';
        SDL_strlcat(jatekostomb[i].nev, ". játékos", 13);
        if (i != *jatekosszam - 1)
            jatekostomb[i].kov = &jatekostomb[i + 1];
        else jatekostomb[i].kov = &jatekostomb[0];
    }
    if (valasztott_szin == j_kilep) {
        free(jatekostomb);
        SDL_Quit();
        return;
    }
    SDL_Delay(100);
    bool elso = true, vege = false;
    int p = 0;
    int* aktualis_jatekos = &p;
    Jatekos *soron_levo;
    Jatek_event mire_kattintott;
    SDL_SetRenderDrawColor(renderer, szin(hatter).r, szin(hatter).g, szin(hatter).b, 255);
    SDL_RenderClear(renderer);
    jatekter_kirajzolasa();
    SDL_RenderPresent(renderer);

    while (!vege) {
        soron_levo = &jatekostomb[*aktualis_jatekos];
        SDL_SetRenderDrawColor(renderer, szin(hatter).r, szin(hatter).g, szin(hatter).b, 255);
        SDL_RenderClear(renderer);
        jatekter_kirajzolasa();

        //TODO: első kilépésnél az egyik 2x jön
//        if (elso) {
//            int dobokocka = 0;
//            szovegek_megjelenitese(&jatekostomb[0], &dobokocka);
//            SDL_RenderPresent(renderer);
//            elso = false;
//            SDL_SetRenderDrawColor(renderer, szin(hatter).r, szin(hatter).g, szin(hatter).b, 255);
//            SDL_RenderClear(renderer);
//            jatekter_kirajzolasa();
//            szabalyok(&vege, jatekosszam, jatekostomb, aktualis_jatekos, mezok_tombje);
//        }

        if (*aktualis_jatekos == *jatekosszam - 1 && soron_levo->kimarad < 0)
            { /* nem változik */ }
        else if (*aktualis_jatekos == *jatekosszam - 1)
            *aktualis_jatekos = 0;
        else
            *aktualis_jatekos += 1;

        mire_kattintott = kattintas();
        if (elso) {
            mire_kattintott = dob;
            *aktualis_jatekos = jatekostomb[0].id;
            elso = false;
        }
        if (mire_kattintott == dob) {
            szabalyok(&vege, jatekosszam, jatekostomb, aktualis_jatekos, mezok_tombje);
        }
        if (mire_kattintott == passz && soron_levo->passz > 0)
            soron_levo->passz--;
        if (mire_kattintott == ment) {
            //TODO: fájlnév
            mentes("teszt.txt", *jatekosszam, *aktualis_jatekos, jatekostomb);
        }
        if (mire_kattintott == bezar) {
            mentes("teszt.txt", *jatekosszam, *aktualis_jatekos, jatekostomb);
            break;
        }
    }

    //TODO: játék vége fgv javítása
    jatek_vege(jatekostomb);
}

/** A játékosok mozgásakor változó értékeket kezeli
 *
 * @param vege Igazra állítja, ha valaki megnyerte a játékot
 * @param jatekosszam A játékosok száma
 * @param jatekostomb A játékosok adatait tartalmazó tömb
 * @param aktualis_jatekos Az éppen következő játékos azonosítója
 * @param mezok_tombje A mezők adatait tartalmazó tömb
 */
void szabalyok(bool* vege, const int* jatekosszam, Jatekos* jatekostomb, const int* aktualis_jatekos, Mezo* mezok_tombje) {
    int dobokocka, elozo_mezo, kov_mezo;
    Jatekos* soron_levo;
    Jatekos *gyoztes = NULL;
    soron_levo = &jatekostomb[*aktualis_jatekos];

    dobokocka = (rand() % 6 + 1);
    elozo_mezo = soron_levo->mezo_id;
    kov_mezo = soron_levo->mezo_id += dobokocka;
    if (elozo_mezo < 40 && kov_mezo >= 40)
        soron_levo->mezo_id -= 40;
    soron_levo->mezo = &mezok_tombje[soron_levo->mezo_id];

    //TODO
    // mezők speciális tulajdonságai átvétele a játékosoknak
//            soron_levo->ermek += soron_levo->mezo.erem;
//            soron_levo->mezo_id += soron_levo->mezo.lep;
//            soron_levo->mezo = mezok_tombje[soron_levo->mezo_id];
//            soron_levo->kimarad += soron_levo->mezo.dob;
//            soron_levo->kimarad += soron_levo->mezo.dob;
//            while (soron_levo->kimarad < 0) {
//                soron_levo->ermek += soron_levo->mezo.erem;
//                soron_levo->mezo_id += soron_levo->mezo.lep;
//                soron_levo->mezo = mezok_tombje[soron_levo->mezo_id];
//                soron_levo->kimarad += soron_levo->mezo.dob;
//            }
//            if (soron_levo->ermek < 0)
//                soron_levo->ermek = 0;
//            if (soron_levo->mezo_id < 0)
//                soron_levo->mezo_id += 40;
    if (soron_levo->kimarad < 0)
        szovegek_megjelenitese(soron_levo, &dobokocka);
    else
        szovegek_megjelenitese(jatekostomb[*aktualis_jatekos].kov, &dobokocka);

    for (int i = 0; i < *jatekosszam; ++i)
        babuk_megjelenitese(&jatekostomb[i], mezo_kozepe(&jatekostomb[i].mezo->id));
    SDL_RenderPresent(renderer);

    if (soron_levo->ermek >= 15 && soron_levo->mezo_id == 29) {
        *vege = true;
        gyoztes = soron_levo;
        gyoztes_megjelenitese(gyoztes);
    }
}

/** A játék során mire kattint a játékos
 *
 * @return A kattintott gombhoz rendelt tulajdonság
 */
Jatek_event kattintas(void) {
    while (true) {
        SDL_Event esemeny;
        SDL_WaitEvent(&esemeny);
        switch (esemeny.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (esemeny.button.x >= 234 && esemeny.button.y >= 180 && esemeny.button.x <= 428 && esemeny.button.y <= 230)
                    return passz;
                if (esemeny.button.x >= 20 && esemeny.button.y >= 180 && esemeny.button.x <= 214 && esemeny.button.y <= 230)
                    return dob;
                if (esemeny.button.x >= 234 && esemeny.button.y >= 496 && esemeny.button.x <= 428 && esemeny.button.y <= 546)
                    return ment;
                if (esemeny.button.x >= 20 && esemeny.button.y >= 496 && esemeny.button.x <= 214 && esemeny.button.y <= 546)
                    return bezar;
                break;
            case SDL_QUIT:
                return bezar;
        }
    }
}

/**
 * Letisztítja az ablakot, bekér egy 6nál nem nagyobb számot (játékosok száma)
 * @param jatekosok_szama A játékosok száma
 */
void jatekkezdes(int* jatekosok_szama, bool* sdlquit_esemeny) {
    Jatekos *jatekosok_tombje = NULL;
    bool kilepes = false;
    parbeszed(betutipus(felkover48pt), "Add meg a játékosok számát: ", 576 / 8);
    jatekosszam_gombok_kirajzolasa();
    while (!kilepes) {
        SDL_Event esemeny;
        SDL_WaitEvent(&esemeny);
        switch (esemeny.type) {
            /*TODO: visszatérési értékként kéne megkapni a megadott számot
             * talán ez:
             * https://wiki.libsdl.org/SDLKeycodeLookup ?
             * https://wiki.libsdl.org/SDL_GetKeyName
             */
            case SDL_KEYDOWN:
                switch (esemeny.key.keysym.sym) {
                    case SDLK_2:
                    case SDLK_KP_2:
                        *jatekosok_szama = 2;
                        kilepes = true;
                        break;
                    case SDLK_3:
                    case SDLK_KP_3:
                        *jatekosok_szama = 3;
                        kilepes = true;
                        break;
                    case SDLK_4:
                    case SDLK_KP_4:
                        *jatekosok_szama = 4;
                        kilepes = true;
                        break;
                    case SDLK_5:
                    case SDLK_KP_5:
                        *jatekosok_szama = 5;
                        kilepes = true;
                        break;
                    case SDLK_6:
                    case SDLK_KP_6:
                        *jatekosok_szama = 6;
                        kilepes = true;
                        break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if (esemeny.button.x >= 452 && esemeny.button.x <= 572) {
                    if (esemeny.button.y >= 192 && esemeny.button.y <= 232) {
                        *jatekosok_szama = 2;
                        kilepes = true;
                    }
                    if (esemeny.button.y >= 262 && esemeny.button.y <= 302) {
                        *jatekosok_szama = 3;
                        kilepes = true;
                    }
                    if (esemeny.button.y >= 332 && esemeny.button.y <= 372) {
                        *jatekosok_szama = 4;
                        kilepes = true;
                    }
                    if (esemeny.button.y >= 402 && esemeny.button.y <= 442) {
                        *jatekosok_szama = 5;
                        kilepes = true;
                    }
                    if (esemeny.button.y >= 472 && esemeny.button.y <= 512) {
                        *jatekosok_szama = 6;
                        kilepes = true;
                    }
                }
                break;
            //TODO: itt felszabadul a foglalt memória?
            case SDL_QUIT:
                jatek_vege(jatekosok_tombje);
                *sdlquit_esemeny = true;
                return;
        }
    }
}

/** Megkérdezi a felhasználót, hogy biztosan meg szeretné-e kezdeni a játékot
 *
 * @param tomb A játékostömb, aminek memóriát kell foglalni
 * @param jatekosszam A játékosok száma
 * @return true, ha megkezdi a játékot
 */
bool jatekkezdes_megerositese(bool* sdlquit_esemeny) {
    ablak_tisztitasa(renderer);
    parbeszed(betutipus(felkover48pt), "Folytatod?", 150);
    boxRGBA(renderer, 297, 334, 497, 384, szin(kek).r, szin(kek).g, szin(kek).b, 100);
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), "Fõmenü", (297 + 497) / 2, 340);
    boxRGBA(renderer, 527, 334, 727, 384, szin(zold).r, szin(zold).g, szin(zold).b, 100);
    fancy_szoveget_kiir(betutipus(felkover36pt), szin(feher), "Igen", (527 + 727) / 2, 340);

    SDL_RenderPresent(renderer);
    bool megerositette = false;
    while (!megerositette) {
        SDL_Event megerosites_esemeny;
        SDL_WaitEvent(&megerosites_esemeny);
        switch (megerosites_esemeny.type) {
            case SDL_KEYDOWN:
                switch (megerosites_esemeny.key.keysym.sym) {
                    case SDLK_i:
                    case SDLK_y:
                        return true;
                    case SDLK_m:
                    case SDLK_f:
                        return false;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (megerosites_esemeny.button.y >= 334 && megerosites_esemeny.button.y <= 384) {
                    if (megerosites_esemeny.button.x >= 297 && megerosites_esemeny.button.x <= 497)
                        return false;
                    if (megerosites_esemeny.button.x >= 527 && megerosites_esemeny.button.x <= 727) {
                        ablak_tisztitasa(renderer);
                        return true;
                    }
                }
                break;
            case SDL_QUIT:
                // itt még nem kell felszabadítani memóriát
                *sdlquit_esemeny = true;
                return false;
        }
    }
}

/** A játék befejezésekor kerül hívásra. Felszabadítja a lefoglalt memóriát és bezárja az ablakot
 *
 * @param jatekostomb A felszabadítandó memóriaterületre mutató Jatekos típusú pointer
 */
static void jatek_vege(Jatekos* jatekostomb) {
    /*TODO: eredménykijelzés, stb*/
    free(jatekostomb);
    SDL_Quit();
}

/** Visszaadja egy mező közepének koordinátáit
 *
 * @param mezo_id A mező száma
 * @return A mező közepének koordinátái
 */
Mezokoord mezo_kozepe(const int* mezo_id) {
    //500; 523 #0;; 500; 462 #1;; 500; 418 #2;; 500; 375 #3 500, 331
    //          61           44             43              44
    Mezokoord kozep0 = { 500, 523 };
    Mezokoord kozep10 = { 500, 53 };
    Mezokoord kozep20 = { 970, 53 };
    Mezokoord kozep30 = { 970, 523 };
    if (*mezo_id == 0)
        return kozep0;
    if (*mezo_id < 10)
        return (Mezokoord) { kozep0.x, kozep0.y - 61 - 45 * (*mezo_id - 1) };
    if (*mezo_id == 10)
        return kozep10;
    if (*mezo_id < 20)
        return (Mezokoord) { kozep10.x + 61 + 45 * (*mezo_id - 11), kozep10.y };
    if (*mezo_id == 20)
        return kozep20;
    if (*mezo_id < 30)
        return (Mezokoord) { kozep20.x, kozep20.y + 61 + 45 * (*mezo_id - 20) };
    if (*mezo_id == 30)
        return kozep30;
    if (*mezo_id < 40)
        return (Mezokoord) { kozep30.x - 61 - 45 * (*mezo_id - 31), kozep0.y };
}