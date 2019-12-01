//
// Created by Simon on 2019-11-12.
//

#ifndef TARSAS_FAJLKEZELES_H
#define TARSAS_FAJLKEZELES_H

#include "jatek.h"

//bool beolvas(char* fajlnev);
Jatekos* beolvas(char* fajlnev, int* jatekosok_szama, int* elozo_jatekos, int* kov_jatekos);
void mentes(int jatekosszam, int elozo_id, int kov_id, Jatekos* jatekostomb);
void mezok_beolvasasa(Mezo* mezok_tombje);
char* fajlnev(void);


#endif //TARSAS_FAJLKEZELES_H
