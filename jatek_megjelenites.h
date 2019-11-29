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
//void parbeszed_char(TTF_Font* betu, char karakter, int y);
void jatekter_kirajzolasa(void);
void hatteres_szoveget_kiir(TTF_Font* betutipus, char* szoveg, int x, int y, SDL_Color betuszin, SDL_Color hatterszin);
int szoveg_poz_x(char* szoveg, TTF_Font* betutipus, int hova);
SDL_Color jatekosszin(Jatekosszin szin);
Jatekosszin szinenumma(SDL_Color szin);
Jatekosszin jatekos_szinvalasztas(bool* foglalt_szinek);
static int valasztott_szinek_szama(const bool* foglalt_szinek);
static void xet_rajzol(const bool* foglalt_szinek, SDL_Rect kulvonal);
static Jatekosszin szinfoglalas(Jatekosszin szin, bool* foglalt_szinek, SDL_Rect* kulvonal);
void szovegek_megjelenitese(Jatekos* soronkovetkezo);

#endif //TARSAS_JATEK_MEGJELENITES_H
