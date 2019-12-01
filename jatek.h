//
// Created by Simon on 2019-11-10.
//

#ifndef TARSAS_JATEK_H
#define TARSAS_JATEK_H

#include "main.h"

typedef struct Mezokoord {
    int x;
    int y;
} Mezokoord;

typedef struct Mezo {
    char tulajdonsag[100]; /**<a mező tulajdonsága*/
    int id; /**<a mező azonsoítója*/
    Mezokoord kozep; /**< a mező közepének koordinátái az ablakon*/
    int erem; /**<ennyi érmet ad rálépéskor, negatív, ha elvesz*/
    int lep; /**<rálépéskor ennyit léphetünk előre, (-) ha hátra*/
    int dob; /**< (-) ha megint dobhat, (+) ha kimarad*/
} Mezo;

typedef struct Jatekos {
    char nev[11];
    int id;     /**<a játékos azonosítója*/
    Jatekosszin szin; /**<a játékos bábujának színe*/
    int mezo_id; /**<ezen a sorszámú mezőn tartózkodik*/
    Mezo* mezo;   /**<ezen a mezőn tartozkodik éppen*/
    int ermek;  /**<ennyi érme van jelenleg*/
    int passz;  /**<ennyi mezőt passzolhat még (max 3)*/
    int kimarad; /**<ennyiszer marad ki a dobásból*/
    struct Jatekos* kov; /**<az őt követő játékos */
    struct Jatekos* elozo; /**<az őt megelőző játékos */
} Jatekos;

/** A játékmenet közben a dobókockára kattintáskor vagy kilépéskor kell*/
typedef enum Jatek_event {
    dob, /**<ha dob a kockával*/
    passz, /**<ha elhasznál egy passzot*/
    ment, /**<ha elmenti a játékmenetet*/
    bezar /**<ha bezárja az ablakot vagy kilépésre kattint*/
} Jatek_event;


void jatek_main(Jatekos* jatekostomb, int* elozo_jatekos, int* kov_jatekos, const int* jatekosszam, bool beolvasott);
void szabalyok(bool* vege, const int* jatekosszam, Jatekos* jatekostomb, const int* aktualis_jatekos, Mezo* mezok_tombje);
Jatek_event kattintas(void);
void jatekkezdes(int* jatekosok_szama, bool* sdlquit_esemeny);
bool jatekkezdes_megerositese(bool* sdlquit_esemeny);
void jatek_vege(Jatekos* jatekostomb);
Mezokoord mezo_kozepe(const int* mezo_id);

#endif //TARSAS_JATEK_H
