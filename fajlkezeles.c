//
// Created by Simon on 2019-11-12.
//
// https://lazyfoo.net/tutorials/SDL/33_file_readi  ng_and_writing/index.php
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>

#include "fajlkezeles.h"
#include "jatek.h"
#include "debugmalloc.h"

/** Beolvas egy korábbi játékmenetet
 * @param fajlnev A beolvasandó fájl neve
 * @return igaz, ha a fájlt sikerült beolvasni
 */
// TODO: pointerként adja vissza a fájlt
bool beolvas(char* fajlnev) {
    SDL_RWops* fajl = SDL_RWFromFile(fajlnev, "r");
    if (fajl == NULL) {
        return false;
    }
    return true;
}

void mezok_beolvasasa(Mezo* mezok_tombje) {
    // A fájl felépítése: mezo_id\taranyermek\tlepes\tleiras
    //mezok_tombje = (Mezo*) malloc(40 * sizeof(Mezo));
    FILE* mezok = fopen("mezok.csv.txt", "rt");
    if (mezok == NULL) {
        SDL_Log("A fajl megnyitasa sikertelen. %s", SDL_GetError());
        SDL_Quit();
    }
    int mezo_id, mezo_ermek, mezo_lepes;
    char mezo_tul[90];
    for (int i = 0; i < 40; ++i) {
        fscanf(mezok, "%d;%d;%d;%[^\n] ", &mezo_id, &mezo_ermek, &mezo_lepes, mezo_tul);
        mezok_tombje[i].id = mezo_id;
        mezok_tombje[i].erem = mezo_ermek;
        mezok_tombje[i].lep = mezo_lepes;
        strcpy(mezok_tombje[i].tulajdonsag, mezo_tul);
    }
}