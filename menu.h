//
// Created by Simon on 2019-11-08.
//
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "main.h"

#ifndef TARSAS_MENU_H
#define TARSAS_MENU_H

void menu_kirajzolasa(void);
void fancy_szoveget_kiir(TTF_Font *betutipus, SDL_Color szin, char* szoveg, int x, int y);
Gomb egeresbillentyu(void);

#endif //TARSAS_MENU_H
