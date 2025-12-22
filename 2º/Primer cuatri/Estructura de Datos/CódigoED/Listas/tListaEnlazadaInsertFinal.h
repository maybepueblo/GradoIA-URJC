//
// Created by pueblo on 6/4/25.
//

#ifndef TLISTAENLAZADAINSERTFINAL_H
#define TLISTAENLAZADAINSERTFINAL_H
#include "tElemento.h"

typedef struct NodoIF {
    tElemento e;
    struct NodoIF *p;
} tNodoIF;

typedef tNodoIF* tListaIF;

tListaIF* crearVaciaIF(tListaIF* lista);
void insertarFinal(tListaIF* l, tElemento e);
void imprimirListaIF(tListaIF l);

#endif //TLISTAENLAZADAINSERTFINAL_H
