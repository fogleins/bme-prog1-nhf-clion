//
// Created by Simon on 2019-11-12.
//
// https://lazyfoo.net/tutorials/SDL/33_file_readi  ng_and_writing/index.php
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "fajlkezeles.h"

/* Beolvas egy korábbi játékmenetet
 * Visszatérési értéke igaz, ha a fájlt sikerült beolvasni,
 * hamis, ha a beolvasás sikertelen volt.
 * paramétere egy karaktertömb, ami a fájl elérési útja */
// TODO: pointerként adja vissza a fájlt
bool beolvas(char* fajlnev) {
    SDL_RWops* fajl = SDL_RWFromFile(fajlnev, "r");
    if (fajl == NULL) {
        return false;
    }
    return true;
}