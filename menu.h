//
// Created by Simon on 2019-11-08.
//
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#ifndef TARSAS_MENU_H
#define TARSAS_MENU_H

SDL_Window* menu_kirajzolasa(void);
void fancy_szoveget_kiir(TTF_Font *betutipus, SDL_Color szin, char* szoveg, int y);
static void egeresbillentyu(void);

#endif //TARSAS_MENU_H
