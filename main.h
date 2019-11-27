//
// Created by Simon on 2019-11-12.
//

#ifndef TARSAS_MAIN_H
#define TARSAS_MAIN_H

/** Értékeket lásd: ablakkezeles.c szin függvényében */
typedef enum Szinek {
    feher,
    piros,
    flatred,
    zold,
    flatgreen,
    kek,
    hatter,
    hatter_sotet
} Szinek;

typedef enum Jatekosszin {
    j_piros,
    j_narancs,
    j_sarga,
    j_zold,
    j_kek,
    j_lila,
    j_kilep
} Jatekosszin;

typedef enum Betuk {
    felkover60pt,
    felkover48pt,
    felkover36pt,
    felkover30pt
} Betuk;

// a menu_kirajzolasa visszatérési értékei
typedef enum Gomb {
    uj,
    megnyit,
    kilep
} Gomb;
#endif //TARSAS_MAIN_H
