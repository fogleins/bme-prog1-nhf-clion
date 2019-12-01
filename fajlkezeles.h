//
// Created by Simon on 2019-11-12.
//

#ifndef TARSAS_FAJLKEZELES_H
#define TARSAS_FAJLKEZELES_H

#include "jatek.h"

//bool beolvas(char* fajlnev);
Jatekos* beolvas(char* fajlnev);
void mentes(int jatekosszam, int kov_id, Jatekos* jatekostomb);
void mezok_beolvasasa(Mezo* mezok_tombje);
char* fajlnev(void);


#endif //TARSAS_FAJLKEZELES_H
