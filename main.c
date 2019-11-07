#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "board.c"

int main(int argc, char *argv[]) {
    srand(time(0));
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Legyel olimpiai bajnok!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, 0);
    if (window == NULL) {
        SDL_Log("Az ablak letrehozasa nem sikerult: %s.", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    // A sztring kiírása SDL-lel
    //felesleges, mert mindig csak egy jegyű szám lehet, így biztosan 9 karakternyi hely kell
    //char* kiiras = (char*) malloc(sizeof(char) * 9); /* string: Kocka: [int]\0 => 9 chars */
    char kiiras[9] = "Kocka: ";
    kiiras[7] = (char) dice();
    kiiras[8] = '\0';
    stringRGBA(renderer, 300, 280, kiiras, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);

    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {}

    /* ablak bezarasa */
    SDL_Quit();

    return 0;
}