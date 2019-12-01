//
// Created by Simon on 2019-11-17.
//

#ifndef TARSAS_JATEK_MEGJELENITES_H
#define TARSAS_JATEK_MEGJELENITES_H

#include <SDL_ttf.h>
#include <stdbool.h>
#include "main.h"
#include "jatek.h"

void jatekosszam_gombok_kirajzolasa(void);
void parbeszed(TTF_Font* betu, char* uzenet, int y);
void jatekter_kirajzolasa(void);
int szoveg_poz_x(char* szoveg, TTF_Font* betutipus, int hova);
SDL_Color jatekosszin(Jatekosszin szin);
Jatekosszin jatekos_szinvalasztas(bool* foglalt_szinek);
static int valasztott_szinek_szama(const bool* foglalt_szinek);
static void xet_rajzol(const bool* foglalt_szinek, SDL_Rect kulvonal);
static Jatekosszin szinfoglalas(Jatekosszin szin, bool* foglalt_szinek, SDL_Rect* kulvonal);
void szovegek_megjelenitese(Jatekos* soronkovetkezo, const int* dobokocka);
void babuk_megjelenitese(Jatekos* soronkovetkezo, Mezokoord hova);
void gyoztes_megjelenitese(Jatekos* gyoztes);

#endif //TARSAS_JATEK_MEGJELENITES_H
