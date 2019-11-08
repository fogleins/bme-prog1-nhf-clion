#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "board.h"
#include "menu.h"

/** a board.c-ben lévő globális rendererre mutat **/
//SDL_Renderer* main_renderer;

int main(int argc, char *argv[]) {
    srand(time(0));
    //main_renderer = renderer;
    ablak_letrehozasa(1024, 576);
    menu_kirajzolasa(); /* menu.c */
    ablakra_kiir();
    ablak_bezarasa();

    return 0;
}