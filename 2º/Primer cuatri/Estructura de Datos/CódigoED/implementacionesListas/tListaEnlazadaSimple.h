//
// Created by pueblo on 10/29/24.
//

#ifndef TLISTAENLAZADASIMPLE_H
#define TLISTAENLAZADASIMPLE_H
#include "tElemento.h"

typedef struct NodoES {
    tElemento info;
    struct NodoES* siguiente;
} tNodoES;

typedef tNodoES* tListaES;

// Constructora generadora
void crearListaESvacia(tListaES* l);

// Constructora no generadora
void insertarElemento(tElemento elem, tListaES* l);
void borrarElemento(tElemento elem, tListaES*l);
// Función meramente auxiliar para poder hacer un insertarElemento por final mucho más sólido
void insertarCabeceraAux(tElemento elem, tListaES*l);


// Observadora selector
tElemento obtenerPrimero(tListaES* l);

// Observadora no selectora
int esVacia(tListaES* l);

#endif //TLISTAENLAZADASIMPLE_H
