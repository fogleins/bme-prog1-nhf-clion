//
// Created by Simon on 2019-11-10.
//

#ifndef TARSAS_JATEK_H
#define TARSAS_JATEK_H

typedef struct Jatekos {
    char* nev;
    int id;
    int mezo;   /*ezen a mezőn tartozkodik éppen*/
    int ermek;  /*ennyi érme van jelenleg*/
    int passz;  /*ennyi mezőt passzolhat még (max 3)*/
} Jatekos;

typedef struct Mezo {
    char* tulajdonsag;
    int id;
    int erem; /*ennyi érmet ad, negatív, ha elvesz*/
    int lep; /*rálépéskor ennyit léphetünk előre, (-) ha hátra*/
} Mezo;

void jatekkezdes(void);

#endif //TARSAS_JATEK_H
