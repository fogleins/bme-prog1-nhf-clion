//
// Created by Simon on 2019-11-08.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "board.h"
#include "menu.h"

SDL_Window* menu_kirajzolasa(void) {
    SDL_Texture* hatter = IMG_LoadTexture(renderer, "tabla.jpg");

    SDL_RenderCopy(renderer, hatter, NULL, NULL);

    // a változtatások megjelenítése a kimeneten
    /*TODO: a renderer nem frissül, a
     * háttér nem jelenik meg, javításch */
    SDL_RenderPresent(renderer);

    // a kép által foglalt memória felszabadítása
    SDL_DestroyTexture(hatter);
}