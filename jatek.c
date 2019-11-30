//
// Created by Simon on 2019-11-10.
//
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "jatek.h"
#include "jatek_megjelenites.h"
#include "ablakkezeles.h"
#include "fajlkezeles.h"
#include "menu.h"
#include "debugmalloc.h"

// Hogy a Sleep linuxon is működjön
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void jatek_main(Jatekos* jatekostomb, const int* jatekosszam) {
    Mezo mezok_tombje[40];
    mezok_beolvasasa(mezok_tombje);
    for (int i = 0; i < 40; ++i)
        mezok_tombje[i].kozep = mezo_kozepe(&i);
    for (int i = 0; i < 10; ++i) {
        printf("%s\n", mezok_tombje[i].tulajdonsag);
    }

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
        jatekostomb[i].mezo = mezok_tombje[jatekostomb[i].mezo_id];
        jatekostomb[i].ermek = 0;
        jatekostomb[i].passz = 3;
        jatekostomb[i].kimarad = 0;
        jatekostomb[i].nev[0] = ((char) (48 + i + 1));
        jatekostomb[i].nev[1] = '\0';
        //strcat(jatekostomb[i].nev, ". jatekos");
        SDL_strlcat(jatekostomb[i].nev, ". játékos", 13);
    }
    if (valasztott_szin == j_kilep) {
        free(jatekostomb);
        SDL_Quit();
        return;
    }
    Sleep(300);
    bool vege = false;
    int kov_jatekos = 0;
    SDL_RenderClear(renderer);
    while (!vege) {
        //SDL_RenderPresent(renderer);
        //SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, szin(hatter).r, szin(hatter).g, szin(hatter).b, 255);
        jatekter_kirajzolasa();
        Sleep(20);
//        SDL_RenderPresent(renderer);
//        SDL_RenderClear(renderer);
        szovegek_megjelenitese(&jatekostomb[kov_jatekos]);

        // TODO: ne villogjon (legyenek a függvények által rajzolt alakzatok egy texturbe rakva?)
        for (int i = 0; i < *jatekosszam; ++i) {
            babuk_megjelenitese(&jatekostomb[i], mezo_kozepe(&jatekostomb[i].mezo.id));
        }
        Sleep(1000);
        if (kov_jatekos == *jatekosszam - 1)
            kov_jatekos = 0;
        else kov_jatekos++;
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }


    Sleep(150000);

    //TODO: játék vége fgv javítása
    jatek_vege(jatekostomb);
}


/**
 * Letisztítja az ablakot, bekér egy 6nál nem nagyobb számot (játékosok száma)
 * @param jatekosok_szama A játékosok száma
 */
void jatekkezdes(int* jatekosok_szama, bool* sdlquit_esemeny) {
    //TODO: ez null?
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

//TODO: ez a függvény
/** Visszaadja a jelenlegi játékmenet tulajdnoságait (pl. játékosszám)
 *
 * @return A játék jellemzői
 */
//Jatek tulajdonsagok(void) {
//    jatek = Jatek {};
//    return jatek;
//}

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
                        megerositette = true;
                        return true;
                    case SDLK_m:
                    case SDLK_f:
                        megerositette = true;
                        return false;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (megerosites_esemeny.button.y >= 334 && megerosites_esemeny.button.y <= 384) {
                    if (megerosites_esemeny.button.x >= 297 && megerosites_esemeny.button.x <= 497) {
                        //menu_kirajzolasa();
                        megerositette = true;
                        return false;
                    }
                    if (megerosites_esemeny.button.x >= 527 && megerosites_esemeny.button.x <= 727) {
                        ablak_tisztitasa(renderer);
                        megerositette = true;
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

/** Memóriát foglal a játékosok számára
 *
 * @param tomb Ez a pointer fog a foglalt memóriaterületre mutatni
 * @param jatekosszam A játékosok száma
 * @return true, ha a memóriafoglalás sikerült
 */
//static bool memfoglalas(Jatekos* tomb, int jatekosszam) {
//    tomb = (Jatekos*) malloc(jatekosszam * sizeof(Jatekos));
//    //TODO: itt lehetne kilepes = false-szal továbblépni?
//    if (tomb == NULL) {
//        SDL_Log("Nem sikerult memoriat foglalni a jatekosok szamara: %s", SDL_GetError());
//        return false;
//    }
//    else return true;
//}

/** A játék befejezésekor kerül hívásra. Felszabadítja a lefoglalt memóriát és bezárja az ablakot
 *
 * @param jatekostomb A felszabadítandó memóriaterületre mutató Jatekos típusú pointer
 */
static void jatek_vege(Jatekos* jatekostomb) {
    /*TODO: eredménykijelzés, stb*/
    free(jatekostomb);
    SDL_Quit();
}

//TODO: ez kell?
// Kockadobást szimulál
//static int kocka(void) {
//    return rand() % 6 + 1;
//}

//TODO ez a függvény
/** Sztring bemenet kezelése */
// https://wiki.libsdl.org/Tutorials/TextInput
char* sdl_sztring(void) {
    char* str = "";
    bool kilepes = false;
    SDL_StartTextInput();
    while (!kilepes) {
        SDL_Event esemeny;
        if (SDL_PollEvent(&esemeny)) {
            switch (esemeny.type) {
                case SDL_QUIT:
                    kilepes = true;
                    break;
                case SDL_TEXTINPUT:
                    strcat(str, esemeny.text.text);
                    break;
            }
        }
    }
    return str;
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
        return (Mezokoord) { kozep0.x, kozep0.y - 61 - 44 * (*mezo_id - 1) };
    if (*mezo_id == 10)
        return kozep10;
    if (*mezo_id < 20)
        return (Mezokoord) { kozep10.x + 61 + 44 * (*mezo_id - 1), kozep10.y };
    if (*mezo_id == 20)
        return kozep20;
    if (*mezo_id < 30)
        return (Mezokoord) { kozep20.x, kozep20.y + 61 + 44 * (*mezo_id - 1) };
    if (*mezo_id == 30)
        return kozep30;
    if (*mezo_id < 40)
        return (Mezokoord) { kozep30.x - 61 - 44 * (*mezo_id - 1), kozep0.y };
}