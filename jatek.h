//
// Created by Simon on 2019-11-10.
//

#ifndef TARSAS_JATEK_H
#define TARSAS_JATEK_H

typedef struct Jatekos {
    char* nev;
    int id;     /**<a játékos azonosítója*/
    int mezo;   /**<ezen a mezőn tartozkodik éppen*/
    int ermek;  /**<ennyi érme van jelenleg*/
    int passz;  /**<ennyi mezőt passzolhat még (max 3)*/
} Jatekos;

typedef struct Mezo {
    char tulajdonsag[90]; /**<a mező tulajdonsága*/
    int id; /**<a mező azonsoítója*/
    int erem; /**<ennyi érmet ad rálépéskor, negatív, ha elvesz*/
    int lep; /**<rálépéskor ennyit léphetünk előre, (-) ha hátra*/
} Mezo;

typedef struct Jatek {
    Jatekos* tomb; /**< a játékosok tulajdonságait tartalmazó tömb */
    int jatekosszam; /**< a játékosok száma */
} Jatek;
void jatek_main(Jatekos* jatekostomb);
Jatekos* jatekkezdes(void);
bool jatekkezdes_megerositese(void);
//bool jatekkezdes_megerositese(Jatekos *tomb, int jatekosszam);
static bool memfoglalas(Jatekos* tomb, int jatekosszam);
static void jatek_vege(Jatekos* jatekostomb);
static int kocka(void);
char* sdl_sztring(void);

#endif //TARSAS_JATEK_H
