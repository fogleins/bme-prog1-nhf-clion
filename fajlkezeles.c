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
//bool beolvas(char* fajlnev) {
//    SDL_RWops* fajl = SDL_RWFromFile(fajlnev, "r");
//    if (fajl == NULL) {
//        return false;
//    }
//    return true;
//}

/** Beolvassa egy korábban elmentett játékmenet adatait.
 *
 * @param fajlnev A beolvasandó fájl elérési útja
 * @return A beolvasott adatokkal feltöltött Jatekos típusú tömbre mutató pointer
 */
Jatekos* beolvas(char* fajlnev) {
    FILE* fp = fopen(fajlnev, "rt");
    int jatekosok_szama, kov_jatekos;
    // a fájl első sora: [int] jatekosok_szama [int] kov_jatekos_id
    fscanf(fp, "%d %d", &jatekosok_szama, &kov_jatekos);
    Jatekos* jatekostomb = (Jatekos*) malloc(jatekosok_szama* sizeof(Jatekos));
    for (int i = 0; i < jatekosok_szama; ++i) {
        fscanf(fp, "%d %d %d %d %d", &jatekostomb[i].id, &jatekostomb[i].mezo, &jatekostomb[i].ermek,
                &jatekostomb[i].szin, &jatekostomb[i].passz);
    }
    fclose(fp);
    return jatekostomb;
}

/** Fájlba írja a jelenlegi játékmenet adatait.
 *
 * @param fajlnev A létrehozandó vagy felülírandó fájl elérési útja
 * @param jatekosszam A játékban résztvevő játékosok száma
 * @param kov_id A soron következő játékos azonosítója
 * @param jatekostomb A játékosok adatait tartalmazó tömb
 */
void mentes(char* fajlnev, int jatekosszam, int kov_id, Jatekos* jatekostomb) {
    FILE* fp = fopen(fajlnev, "wt");
    fprintf(fp, "%d %d", jatekosszam, kov_id);
    for (int i = 0; i < jatekosszam; ++i) {
        fprintf(fp, "%d %d %d %d %d", jatekostomb[i].id, jatekostomb[i].mezo, jatekostomb[i].ermek,
                jatekostomb[i].szin, jatekostomb[i].passz);
    }
    fclose(fp);
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