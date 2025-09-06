//
// Created by pueblo on 10/29/24.
//

#ifndef TLISTAORDENADA_H
#define TLISTAORDENADA_H
#include "tElemento.h"

typedef struct NodoO {
    tElemento info;
    struct NodoO* siguiente;
} tNodoO;

typedef tNodoO* tListaO;

// Constructora generadora
void crearVaciaOrd(tListaO* l);
tListaO mezclar(tListaO*l1, tListaO*l2);

// Constructora no generadora
void insertarOrd(tElemento elem, tListaO* l);
void leerOrdenada(tListaO* l);

// Observadora selectora

// Observadora

#endif //TLISTAORDENADA_H
