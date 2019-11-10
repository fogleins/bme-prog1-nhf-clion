//
// Created by Simon on 2019-11-10.
//
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>

#include "jatek.h"
#include "ablakkezeles.h"

Jatekos* jatekosok_tombje;

/*Letisztítja az ablakot, bekér egy
 * 6nál nem nagyobb számot (játékosok
 * száma, és létrehoz egy Jatekos
 * típusú tömböt, amiben a játék
 * adatai lesznek tárolva*/
void jatekkezdes(void) {
    ablak_tisztitasa(renderer);
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
                    jatekosok_szama = 2;
                    kilepes = true;
                    break;
                case SDLK_3:
                    jatekosok_szama = 3;
                    kilepes = true;
                    break;
                case SDLK_4:
                    jatekosok_szama = 4;
                    kilepes = true;
                    break;
                case SDLK_5:
                    jatekosok_szama = 5;
                    kilepes = true;
                    break;
                case SDLK_6:
                    jatekosok_szama = 6;
                    kilepes = true;
                    break;
            }
            if (kilepes) {
                jatekosok_tombje = (Jatekos*) malloc(jatekosok_szama * sizeof(Jatekos));
                //TODO: itt lehetne kilepes = false-szal továbblépni?
                if (jatekosok_tombje == NULL) {
                    SDL_Log("Nem sikerult memoriat foglalni a jatekosok szamara: %s", SDL_GetError());
                    exit(1);
                }
            }
        }
    }
}

void jatek_vege(void) {
    /*TODO: eredménykijelzés, stb*/
    free(jatekosok_tombje);
    SDL_Quit();
}

/** kockadobást szimulál **/
int kocka(void) {
    return rand() % 7;
}