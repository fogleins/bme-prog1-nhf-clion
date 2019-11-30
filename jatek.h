//
// Created by Simon on 2019-11-10.
//

#ifndef TARSAS_JATEK_H
#define TARSAS_JATEK_H

#include "main.h"

typedef struct Jatekos {
    char nev[11];
    int id;     /**<a játékos azonosítója*/
    Jatekosszin szin; /**<a játékos bábujának színe*/
    int mezo;   /**<ezen a mezőn tartozkodik éppen*/
    int ermek;  /**<ennyi érme van jelenleg*/
    int passz;  /**<ennyi mezőt passzolhat még (max 3)*/
    int kimarad; /**<ennyiszer marad ki a dobásból*/
} Jatekos;

typedef struct Mezokoord {
    int x;
    int y;
} Mezokoord;

typedef struct Mezo {
    char tulajdonsag[90]; /**<a mező tulajdonsága*/
    int id; /**<a mező azonsoítója*/
    Mezokoord kozep; /**< a mező közepének koordinátái az ablakon*/
    int erem; /**<ennyi érmet ad rálépéskor, negatív, ha elvesz*/
    int lep; /**<rálépéskor ennyit léphetünk előre, (-) ha hátra*/
} Mezo;

typedef struct Jatek {
    Jatekos* tomb; /**< a játékosok tulajdonságait tartalmazó tömb */
    int jatekosszam; /**< a játékosok száma */
} Jatek;

void jatek_main(Jatekos* jatekostomb, const int* jatekosszam);
void jatekkezdes(int* jatekosok_szama, bool* sdlquit_esemeny);
bool jatekkezdes_megerositese(bool* sdlquit_esemeny);
//bool jatekkezdes_megerositese(Jatekos *tomb, int jatekosszam);
static bool memfoglalas(Jatekos* tomb, int jatekosszam);
static void jatek_vege(Jatekos* jatekostomb);
static int kocka(void);
char* sdl_sztring(void);
Mezokoord mezo_kozepe(const int* mezo_id);

#endif //TARSAS_JATEK_H
