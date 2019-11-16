#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ablakkezeles.h"
#include "menu.h"
#include "debugmalloc.h"

int main(int argc, char *argv[]) {
    srand(time(0));
    //main_renderer = renderer;
    ablak_letrehozasa(1024, 576);
    menu_kirajzolasa();
    //TODO: memóriaszivárgás ellenőrzése
    debugmalloc_log_file("C:\\Users\\Simon\\Google Drive\\BME\\prog1\\debugmalloc_output.txt");
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