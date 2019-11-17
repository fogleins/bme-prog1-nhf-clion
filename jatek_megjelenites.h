//
// Created by Simon on 2019-11-17.
//

#ifndef TARSAS_JATEK_MEGJELENITES_H
#define TARSAS_JATEK_MEGJELENITES_H

#include <SDL_ttf.h>

void jatekosszam_gombok_kirajzolasa(void);
void parbeszed(TTF_Font* betu, char* uzenet, int y);
//void parbeszed_char(TTF_Font* betu, char karakter, int y);
void jatekter_kirajzolasa(void);
void hatteres_szoveget_kiir(TTF_Font* betutipus, char* szoveg, int x, int y, SDL_Color betuszin, SDL_Color hatterszin);
int szoveg_poz_x(char* szoveg, TTF_Font* betutipus, int hova);

#endif //TARSAS_JATEK_MEGJELENITES_H
