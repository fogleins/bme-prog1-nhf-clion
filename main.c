#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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
    bool megkezdte = false;
    while (!megkezdte) {
        menu_kirajzolasa();
        int jatekosszam;
        switch (egeresbillentyu()) {
            case uj:
                /* TODO: paraméterek */
                /* a játékkezdés megerősítése ne kapja meg a 2 paramétert, helyette csak térjen vissza igazzal, ha
                 * megerősítették a játékkezdést, a memóriafoglalás a jatek_mainből/jatekkezdes.ből is hívható.
                 */
                //TODO: gombok kirajzolása?
                // jatekosszam_gombok_kirajzolasa();
                jatekkezdes(&jatekosszam);
                megkezdte = jatekkezdes_megerositese();
                if (megkezdte)
                    jatek_main(jatekostomb, &jatekosszam);
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