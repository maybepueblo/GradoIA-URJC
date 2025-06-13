//
// Created by pueblo on 6/5/25.
//

#ifndef TLISTADOBENLACE_H
#define TLISTADOBENLACE_H
#include "tElemento.h"

typedef struct tNodoD {
    tElemento e;
    struct tNodoD * siguiente, * previo;
} tNodoD;

typedef tNodoD *tListaD;

void crearVaciaD(tListaD* l);
void insertarElementoD(tListaD* l, tElemento e);
void borrarElementoD(tListaD* l, tElemento e);
void imprimirD(tListaD l);

#endif //TLISTADOBENLACE_H
