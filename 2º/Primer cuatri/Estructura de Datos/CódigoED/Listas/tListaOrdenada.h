//
// Created by pueblo on 6/4/25.
//

#ifndef TLISTAORDENADA_H
#define TLISTAORDENADA_H
#include "tElemento.h"

typedef struct tNodoO {
    tElemento e;
    struct tNodoO* p;
} tNodoO;

typedef tNodoO* tListaO;

void crearVaciaO(tListaO* l);
void insertarOrd(tListaO* l, tElemento e);
tListaO mezclar(tListaO* l1, tListaO* l2);

#endif //TLISTAORDENADA_H
