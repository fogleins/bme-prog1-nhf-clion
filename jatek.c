//
// Created by Simon on 2019-11-10.
//
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "jatek.h"
#include "ablakkezeles.h"
#include "menu.h"

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
    Jatekos* jatekosok_tombje;
    bool kilepes = false;
    int jatekosok_szama;
    TTF_Font *betu = TTF_OpenFont("myfrida-bold.otf", 60);
    parbeszed(betu, "Add meg a játékosok számát: ", 576 / 6);
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
                    //TTF_Font *betu = TTF_OpenFont("myfrida-bold.otf", 60);
                    //fancy_szoveget_kiir(betu, feher, );
                    break;
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
                                    SDL_Log("Nem sikerult memoriat foglalni a jatekosok szamara: %s", SDL_GetError());
                                    kilepes = false;
                                    //exit(0);
                                }
                                else return jatekosok_tombje;
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
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(tabla);
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