#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "ablakkezeles.h"
#include "menu.h"
#include "debugmalloc.h"
#include "jatek.h"
#include "fajlkezeles.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    Jatekos* jatekostomb = NULL;
    ablak_letrehozasa(1024, 576);
    // a játék megkezdéséig loopol, megjeleníti a menüt és regisztrálja a gombnyomásokat, kattintásokat
    bool megkezdte = false, beolvasott  = false, sdlquit_esemeny = false; /* SDL_QUIT event esetén true lesz, így a többi kód  */
    int jatekosnp = 0;
    int *kov_jatekos = &jatekosnp, *elozo_jatekos = &jatekosnp;
    while (!megkezdte) {
        menu_kirajzolasa();
        int jatekosszam;
        switch (egeresbillentyu()) {
            case uj:
                jatekkezdes(&jatekosszam, &sdlquit_esemeny);
                if (!sdlquit_esemeny) {
                    // megkezdte = jatekkezdes_megerositese(&sdlquit_esemeny);
                    megkezdte = jatekkezdes_megerositese(&sdlquit_esemeny);
                    if (megkezdte)
                        jatek_main(jatekostomb, elozo_jatekos, kov_jatekos, &jatekosszam, beolvasott);
                }
                else
                    megkezdte = true;
                break;
            case megnyit:
                jatekostomb = beolvas("jatekmenet.txt", &jatekosszam, elozo_jatekos, kov_jatekos);
                if (jatekostomb == NULL) {
                    SDL_Log("Nem sikerult a fájl beolvasasa. Biztosan letezik jatekmenet.txt allomany? (%s)",
                            SDL_GetError());
                    SDL_Quit();
                    exit(1);
                }
                megkezdte = true;
                beolvasott = true;
                jatek_main(jatekostomb, elozo_jatekos, kov_jatekos, &jatekosszam, beolvasott);
                break;
            case kilep:
                megkezdte = true;
                SDL_Quit();
                break;
        }
    }

    return 0;
}