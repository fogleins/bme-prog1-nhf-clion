//
// Created by Simon on 2019-11-12.
//
// https://lazyfoo.net/tutorials/SDL/33_file_readi  ng_and_writing/index.php
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

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
 * @return A beolvasott adatokkal feltöltött Jatekos típusú tömbre mutató pointer; NULL, ha a fájl nem nyitható meg
 */
Jatekos* beolvas(char* fajlnev, int* jatekosok_szama, int* elozo_jatekos, int* kov_jatekos) {
    FILE* fp = fopen(fajlnev, "rt");
    if (fp == NULL) return NULL;
    // a fájl első sora: [int] jatekosok_szama [int] kov_jatekos_id
    fscanf(fp, "%d %d", jatekosok_szama, kov_jatekos);
    Jatekos* jatekostomb = (Jatekos*) malloc(*jatekosok_szama * sizeof(Jatekos));
    for (int i = 0; i < *jatekosok_szama; ++i) {
        fscanf(fp, "%d %d %d %d %d", &jatekostomb[i].id, &jatekostomb[i].mezo_id, &jatekostomb[i].ermek,
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
void mentes(const int jatekosszam, const int elozo_id, const int kov_id, Jatekos* jatekostomb) {
    char* nev = fajlnev();
    FILE* fp = fopen(nev, "wt");
    free(nev);
    fprintf(fp, "%d %d %d\n", jatekosszam, elozo_id, kov_id);
    for (int i = 0; i < jatekosszam; ++i) {
        fprintf(fp, "%d %d %d %d %d\n", i, jatekostomb[i].mezo_id, jatekostomb[i].ermek,
                jatekostomb[i].szin, jatekostomb[i].passz);
    }
    fclose(fp);
}

void mezok_beolvasasa(Mezo* mezok_tombje) {
    // A fájl felépítése: mezo_id;aranyermek;lepes;kimarad;leiras
    FILE* mezok = fopen("mezok.csv.txt", "rt");
    if (mezok == NULL) {
        SDL_Log("A fajl megnyitasa sikertelen. %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    int mezo_id, mezo_ermek, mezo_lepes, mezo_dobas;
    char mezo_tul[110];
    for (int i = 0; i < 40; ++i) {
        fscanf(mezok, "%d;%d;%d;%d;%[^\n] ", &mezo_id, &mezo_ermek, &mezo_lepes, &mezo_dobas, mezo_tul);
        mezok_tombje[i].id = mezo_id;
        mezok_tombje[i].erem = mezo_ermek;
        mezok_tombje[i].lep = mezo_lepes;
        mezok_tombje[i].dob = mezo_dobas;
        SDL_strlcpy(mezok_tombje[i].tulajdonsag, mezo_tul, 110);
    }
}

char* fajlnev(void) {
    char* nev = (char*) malloc(20 * sizeof(char));
    time_t ido = time(NULL);
    struct tm helyi = *localtime(&ido);
    sprintf(nev, "%d%02d%02d-%02d%02d%02d.txt", helyi.tm_year + 1900, helyi.tm_mon + 1, helyi.tm_mday,
            helyi.tm_hour, helyi.tm_min, helyi.tm_sec);
    return nev;
}