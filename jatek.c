//
// Created by Simon on 2019-11-10.
//
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>

#include "main.h"
#include "jatek.h"
#include "ablakkezeles.h"
#include "menu.h"

void jatek_main(void) {
    Jatekos* jatekostomb = jatekkezdes();
    jatekter_kirajzolasa();

    jatek_vege(jatekostomb);
}


/*Letisztítja az ablakot, bekér egy
 * 6nál nem nagyobb számot (játékosok
 * száma, és létrehoz egy Jatekos
 * típusú tömböt, amiben a játék
 * adatai lesznek tárolva*/
static Jatekos* jatekkezdes(void) {
    Jatekos* jatekosok_tombje;
    ablak_tisztitasa(renderer);
    TTF_Font *betu = TTF_OpenFont("myfrida-bold.otf", 55);
    fancy_szoveget_kiir(betu, szin(feher),"Add meg a játékosok számát", 576 / 3);
    SDL_RenderPresent(renderer);
    bool kilepes = false;
    int jatekosok_szama;
    while (!kilepes) {
        SDL_Event esemeny;
        SDL_WaitEvent(&esemeny);
        if (esemeny.type == SDL_KEYDOWN) {
            /// ez a switch elég foschnak néz ki, valahogy
            /// visszatérési értékként kéne megkapni a
            /// megadott számot
            /// talán ez:
            /// https://wiki.libsdl.org/SDLKeycodeLookup ?
            /// https://wiki.libsdl.org/SDL_GetKeyName
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
                    betu = TTF_OpenFont("myfrida-bold.otf", 60);
                    //fancy_szoveget_kiir(betu, feher, );
                    break;
            }
            if (kilepes) {
                jatekosok_tombje = (Jatekos*) malloc(jatekosok_szama * sizeof(Jatekos));
                //TODO: itt lehetne kilepes = false-szal továbblépni?
                if (jatekosok_tombje == NULL) {
                    SDL_Log("Nem sikerult memoriat foglalni a jatekosok szamara: %s", SDL_GetError());
                    exit(1);
                }
                return jatekosok_tombje;
            }
        }
    }
}

static void jatekter_kirajzolasa(void) {
    SDL_Texture* tabla = IMG_LoadTexture(renderer, "tabla_kicsi.jpg");
    if (tabla == NULL) {
        SDL_Log("Nem nyithato meg a kep. (%s)", IMG_GetError());
        exit(1);
    }
    SDL_RenderCopy(renderer, tabla, NULL, NULL);
    /*TODO: különféle mezők megjelenítése*/
    SDL_RenderPresent(renderer);
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