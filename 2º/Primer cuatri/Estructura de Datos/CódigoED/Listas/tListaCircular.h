//
// Created by pueblo on 6/4/25.
//

#ifndef TLISTACIRCULAR_H
#define TLISTACIRCULAR_H
#include "tElemento.h"

typedef struct tNodoC {
    tElemento e;
    struct tNodoC *p;
} tNodoC;

typedef tNodoC* tListaC;

void iniciarLista(tListaC *l);
void insertarNodoC(tListaC *l, tElemento e);
void imprimirListaC(tListaC l);


#endif //TLISTACIRCULAR_H
