//
// Created by Simon on 2019-11-10.
//
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "jatek.h"
#include "jatek_megjelenites.h"
#include "ablakkezeles.h"
#include "fajlkezeles.h"
#include "menu.h"
#include "debugmalloc.h"

void jatek_main(void) {
    Mezo mezok_tombje[40];
    mezok_beolvasasa(mezok_tombje);
    Jatekos* jatekostomb = jatekkezdes();
    ablak_tisztitasa(renderer);
    jatekter_kirajzolasa();

    //a tesztelés idejére kikommentelve
    //TODO: játék vége fgv javítása
    if (jatekostomb != NULL)
        jatek_vege(jatekostomb);
}


/**
 * Letisztítja az ablakot, bekér egy 6nál nem nagyobb számot (játékosok száma)
 * @return Dinamikusan foglalt memóriaterületre mutató Játékos típusú pointer
 */
static Jatekos* jatekkezdes(void) {
    //TODO: ez null?
    Jatekos *jatekosok_tombje = NULL;
    bool kilepes = false;
    int jatekosok_szama;
    TTF_Font *betu = betutipus(felkover48pt);
    parbeszed(betu, "Add meg a játékosok számát: ", 576 / 8);
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
                        jatekosok_szama = 2;
                        kilepes = true;
                        break;
                    case SDLK_3:
                    case SDLK_KP_3:
                        jatekosok_szama = 3;
                        kilepes = true;
                        break;
                    case SDLK_4:
                    case SDLK_KP_4:
                        jatekosok_szama = 4;
                        kilepes = true;
                        break;
                    case SDLK_5:
                    case SDLK_KP_5:
                        jatekosok_szama = 5;
                        kilepes = true;
                        break;
                    case SDLK_6:
                    case SDLK_KP_6:
                        jatekosok_szama = 6;
                        kilepes = true;
                        break;
                    default:
                        kilepes = false;
                        break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if (esemeny.button.x >= 452 && esemeny.button.x <= 572) {
                    // 2
                    if (esemeny.button.y >= 192 && esemeny.button.y <= 232) {
                        jatekosok_szama = 2;
                        kilepes = true;
                    }
                    // 3
                    if (esemeny.button.y >= 262 && esemeny.button.y <= 302) {
                        jatekosok_szama = 3;
                        kilepes = true;
                    }
                    // 4
                    if (esemeny.button.y >= 332 && esemeny.button.y <= 372) {
                        jatekosok_szama = 4;
                        kilepes = true;
                    }
                    // 5
                    if (esemeny.button.y >= 402 && esemeny.button.y <= 442) {
                        jatekosok_szama = 5;
                        kilepes = true;
                    }
                    // 6
                    if (esemeny.button.y >= 472 && esemeny.button.y <= 512) {
                        jatekosok_szama = 6;
                        kilepes = true;
                    }
                }
                break;
            //TODO: itt felszabadul a foglalt memória?
            case SDL_QUIT:
                kilepes = true;
                //jatek_vege(jatekosok_tombje);
                jatek_vege(NULL);
                break;
        }
        if (kilepes) {
            kilepes = jatekkezdes_megerositese(jatekosok_tombje, jatekosok_szama);
        }
    }
    return jatekosok_tombje;
}

/** Megkérdezi a felhasználót, hogy biztosan meg szeretné-e kezdeni a játékot
 *
 * @param tomb A játékostömb, aminek memóriát kell foglalni
 * @param jatekosszam A játékosok száma
 * @return true, ha megkezdi a játékot
 */
static bool jatekkezdes_megerositese(Jatekos* tomb, int jatekosszam) {
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
            //TODO: ezek működjenek egérrel is
            case SDL_KEYDOWN:
                switch (megerosites_esemeny.key.keysym.sym) {
                    case SDLK_i:
                    case SDLK_y:
                        return memfoglalas(tomb, jatekosszam);
                    case SDLK_n:
                        megerositette = true;
                        //ablak_tisztitasa(renderer);
                        // parbeszed(betutipus(felkover48pt), "Add meg a játékosok számát: ", 576 / 6);
                        jatekosszam_gombok_kirajzolasa();
                        break;
                    case SDLK_m:
                    case SDLK_f:
                        menu_kirajzolasa();
                        return false;
                }
            case SDL_MOUSEBUTTONDOWN:
                if (megerosites_esemeny.button.y >= 334 && megerosites_esemeny.button.y <= 384) {
                    if (megerosites_esemeny.button.x >= 297 && megerosites_esemeny.button.x <= 497) {
                        menu_kirajzolasa();
                        return false;
                    }
                    if (megerosites_esemeny.button.x >= 527 && megerosites_esemeny.button.x <= 727) {
                        ablak_tisztitasa(renderer);
                        return memfoglalas(tomb, jatekosszam);
                    }
                }
                break;
            case SDL_QUIT:
                // itt még nem kell felszabadítani memóriát
                SDL_Quit();
                break;
        }
    }
}

/** memóriát foglal a játékosok számára
 *
 * @param tomb Ez a pointer fog a foglalt memóriaterületre mutatni
 * @param jatekosszam A játékosok száma
 * @return true, ha a memóriafoglalás sikerült
 */
static bool memfoglalas(Jatekos* tomb, int jatekosszam) {
    tomb = (Jatekos *) malloc(jatekosszam * sizeof(Jatekos));
    //TODO: itt lehetne kilepes = false-szal továbblépni?
    if (tomb == NULL) {
        SDL_Log("Nem sikerult memoriat foglalni a jatekosok szamara: %s", SDL_GetError());
        return false;
    }
    else return true;
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