#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "board.c"

int main(int argc, char *argv[]) {
    srand(time(0));
    ablak_letrehozasa(1024, 576);
    ablakra_kiir();
    ablak_bezarasa();

    return 0;
}