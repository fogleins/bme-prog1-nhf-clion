#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "ablakkezeles.h"
#include "menu.h"
#include "debugmalloc.h"
#include "jatek.h"
#include "fajlkezeles.h"
#include "jatek_megjelenites.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    Jatekos* jatekostomb = NULL;
    //main_renderer = renderer;
    ablak_letrehozasa(1024, 576);
    // a játék megkezdéséig loopol, megjeleníti a menüt és regisztrálja a gombnyomásokat, kattintásokat
    bool megkezdte = false, sdlquit_esemeny = false; /* SDL_QUIT event esetén true lesz, így a többi kód  */
    while (!megkezdte) {
        menu_kirajzolasa();
        int jatekosszam;
        switch (egeresbillentyu()) {
            case uj:
                jatekkezdes(&jatekosszam, &sdlquit_esemeny);
                if (!sdlquit_esemeny) {
                    megkezdte = jatekkezdes_megerositese(&sdlquit_esemeny);
                    if (megkezdte)
                        jatek_main(jatekostomb, &jatekosszam);
                }
                else
                    megkezdte = true;
                break;
            case megnyit:
                //TODO: fájl beolvasása
                jatekostomb = beolvas("jatekmenet.txt");
                break;
            case kilep:
                megkezdte = true;
                SDL_Quit();
                break;
        }
    }

    //TODO: talán lehet while is
//    if (!sdlquit_esemeny) {
//        /*
//         * bábuk kirajzolása
//         * dobás -> bábuk mozgatása + megfelelő szövegek kiírása
//         * játék vége ellenőrzése
//         *
//         */
//    }

    //TODO: memóriaszivárgás ellenőrzése
    debugmalloc_log_file("C:\\Users\\Simon\\Google Drive\\BME\\prog1\\debugmalloc_output.txt");

    return 0;
}

/*TODO: az ablak és renderer által foglalt
 * memória felszabadítása*/