//
// Created by pueblo on 6/9/25.
//

#ifndef TARBOLDIOSES_H
#define TARBOLDIOSES_H
#include "tDios.h"

typedef struct Nodo {
    tDios dios;
    struct Nodo *izq, *der;
} tNodo;

typedef tNodo *tArbol;

void crearArbolVacio(tArbol* arbol);
void construirArbolB(tArbol* arbol, tArbol izq, tDios dios, tArbol der);
int esArbolVacio(tArbol arbol);
void preordenArbol(tArbol arbol);
void existeDios(tArbol arbol, char* n);
void esPadre(tArbol arbol, tDios d1, tDios d2);

#endif //TARBOLDIOSES_H
