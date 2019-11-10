#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ablakkezeles.h"
#include "menu.h"

/** a board.c-ben lévő globális rendererre mutat **/
//SDL_Renderer* main_renderer;

int main(int argc, char *argv[]) {
    srand(time(0));
    //main_renderer = renderer;
    ablak_letrehozasa(1024, 576);
    menu_kirajzolasa(); /* menu.c */

    return 0;
}

/*TODO: gombok megnyomására nyíljon új játék
 * (legyen megadható a játékosok száma!),
 * lehessen betölteni régi játékmenetet,
 * lehessen menteni az aktuális állást*/

/*TODO: játékmenet modul (structok, szabályok)
 * esetleg 3 élet, hogy lehessen passzolni a
 * rossz mezőket?*/

/*TODO: mezők tulajdonságainak megadása,
 * pálya véglegesítése (mezők száma, szín)*/

/*TODO: az ablak és renderer által foglalt
 * memória felszabadítása*/