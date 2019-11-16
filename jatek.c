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
#include "ablakkezeles.h"
#include "menu.h"

static void jatekosszam_gombok_kirajzolasa();

void jatek_main(void) {
    Jatekos* jatekostomb = jatekkezdes();
    jatekter_kirajzolasa();

    ///a tesztelés idejére kikommentelve
    //TODO: játék vége fgv javítása
    //jatek_vege(jatekostomb);
}


/*Letisztítja az ablakot, bekér egy
 * 6nál nem nagyobb számot (játékosok
 * száma, és létrehoz egy Jatekos
 * típusú tömböt, amiben a játék
 * adatai lesznek tárolva*/
static Jatekos* jatekkezdes(void) {
    Jatekos *jatekosok_tombje;
    bool kilepes = false;
    int jatekosok_szama;
    TTF_Font *betu = TTF_OpenFont("myfrida-bold.otf", 48);
    parbeszed(betu, "Add meg a játékosok számát: ", 576 / 8);
    jatekosszam_gombok_kirajzolasa();
    while (!kilepes) {
        SDL_Event esemeny;
        SDL_WaitEvent(&esemeny);
        switch (esemeny.type) {
            /// ez a switch elég foschnak néz ki, valahogy
            /// visszatérési értékként kéne megkapni a
            /// megadott számot
            /// talán ez:
            /// https://wiki.libsdl.org/SDLKeycodeLookup ?
            /// https://wiki.libsdl.org/SDL_GetKeyName
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
                        //TTF_Font *betu = TTF_OpenFont("myfrida-bold.otf", 60);
                        //fancy_szoveget_kiir(betu, feher, );
                        break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if (esemeny.button.x >= 452 && esemeny.button.x <= 492) {
                    // 2
                    if (esemeny.button.y >= 192 && esemeny.button.y <= 232) {

                    }
                    // 3
                    if (esemeny.button.y >= 262 && esemeny.button.y <= 302) {
                        jatekosok_szama = 3;
                        kilepes = true;
                        SDL_Quit();
                    }
                    // 4
                    if (esemeny.button.y >= 332 && esemeny.button.y <= 372) {

                    }
                    // 5
                    if (esemeny.button.y >= 402 && esemeny.button.y <= 442) {

                    }
                    // 6
                    if (esemeny.button.y >= 472 && esemeny.button.y <= 512) {

                    }
                }
                break;
            case SDL_QUIT:
                SDL_Quit();
        }

        if (kilepes) {
            parbeszed(betu, "Folytatod?", 150);
            bool megerositette = false;
            while (!megerositette) {
                // a játékkezdés megerősítése
                SDL_Event megerosites_esemeny;
                SDL_WaitEvent(&megerosites_esemeny);
                if (esemeny.type == SDL_KEYDOWN) {
                    //TODO: ezek működjenek egérrel is
                    switch (megerosites_esemeny.key.keysym.sym) {
                        case SDLK_i:
                        case SDLK_y:
                            jatekosok_tombje = (Jatekos *) malloc(jatekosok_szama * sizeof(Jatekos));
                            //TODO: itt lehetne kilepes = false-szal továbblépni?
                            if (jatekosok_tombje == NULL) {
                                SDL_Log("Nem sikerult memoriat foglalni a jatekosok szamara: %s",
                                        SDL_GetError());
                                kilepes = false;
                                //exit(0);
                            } else return jatekosok_tombje;
                            break;
                        case SDLK_n:
                            megerositette = true;
                            kilepes = false;
                            ablak_tisztitasa(renderer);
                            parbeszed(betu, "Add meg a játékosok számát: ", 576 / 6);
                            break;
                        case SDLK_m:
                        case SDLK_f:
                            megerositette = true;
                            menu_kirajzolasa();
                            break;
                    }
                }
            }
        }
    }
}

static void jatekosszam_gombok_kirajzolasa(void) {
    TTF_Font *betu = TTF_OpenFont("myfrida-bold.otf", 36);
    int y = 190;
    char szam = '2';
    char kiir[2];
    int teglalap_x1 = 452, teglalap_y1 = 192, teglalap_x2 = teglalap_x1 + 120, teglalap_y2 = teglalap_y1 + 40;
    for (int i = 2; i <= 6; ++i) {
        // téglalapok megrajzolása
        boxRGBA(renderer, teglalap_x1, teglalap_y1, teglalap_x2, teglalap_y2,
                      szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 100);
        teglalap_y1 += 70;
        teglalap_y2 += 70;
        // számok kiírása
        kiir[0] = szam;
        kiir[1] = '\0';
        fancy_szoveget_kiir(betu, szin(feher), kiir, y);
        szam++;
        y += 70;
    }
    SDL_RenderPresent(renderer);
}

/* kiírja a paraméterként kapott üzenetet
 * az eventet nem vizsgálja */
static void parbeszed(TTF_Font* betu, char* uzenet, int y) {
    ablak_tisztitasa(renderer);
    fancy_szoveget_kiir(betu, szin(feher), uzenet, y);
    SDL_RenderPresent(renderer);
}

static void jatekter_kirajzolasa(void) {
    ablak_tisztitasa(renderer);
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
    //hatteres_szoveget_kiir(menupontok, "Következik: ", 10, 10, szin(feher), szin(hatter_sotet));

    boxRGBA(renderer, 10, 10, 221, 60, szin(hatter_sotet).r, szin(hatter_sotet).g, szin(hatter_sotet).b, 0xC7);
//    boxRGBA(renderer, 362, 325, 662, 375, 0xCB, 0x7D, 0x7D, 0xC7);
//    boxRGBA(renderer, 362, 415, 662, 465, 0xCB, 0x7D, 0x7D, 0xE6);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(tabla);
}

// ez hátteres szöveget ír ki, gyorsabb a renderelés
static void hatteres_szoveget_kiir(TTF_Font* betutipus, char* szoveg, int x, int y, SDL_Color betuszin, SDL_Color hatterszin) {
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

static void jatek_vege(Jatekos* jatekostomb) {
    /*TODO: eredménykijelzés, stb*/
    free(jatekostomb);
    SDL_Quit();
}

/** kockadobást szimulál **/
static int kocka(void) {
    return rand() % 7;
}

/* sztring bemenet kezelése */
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
                    /* Add new text onto the end of our text */
                    strcat(str, esemeny.text.text);
                    break;
            }
        }
    }
    return str;
}