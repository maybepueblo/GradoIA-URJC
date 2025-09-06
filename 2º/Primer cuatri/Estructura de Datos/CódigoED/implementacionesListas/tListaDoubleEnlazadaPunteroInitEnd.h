//
// Created by pueblo on 10/29/24.
//

#ifndef TLISTADOUBLEENLAZADAPUNTEROINITEND_H
#define TLISTADOUBLEENLAZADAPUNTEROINITEND_H

#include "tElemento.h"

typedef struct NodoEPIE {
    tElemento info;
    struct NodoEPIE* siguiente;
} tNodoEPIE;

typedef struct Lista {
    tNodoEPIE* principio;
    tNodoEPIE* final;
} tListaEPIE;

// Constructora generadora
void crearListaEPIEVacia(tListaEPIE* l);

// Constructora no generadora
void insertarElementoPE(tElemento elem, tListaEPIE* l);
void borrarElementoPE(tElemento elem, tListaEPIE* l);

// Observadora selectora
tElemento obtenerFinal(tListaEPIE* l);

// Observadora no selectora
int esVaciaEPIE(tListaEPIE* l);

#endif //TLISTADOUBLEENLAZADAPUNTEROINITEND_H
