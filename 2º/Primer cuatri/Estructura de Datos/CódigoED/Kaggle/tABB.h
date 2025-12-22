//
// Created by pueblo on 6/9/25.
//

#ifndef TABB_H
#define TABB_H
#include "tElemento.h"

typedef struct nodo {
    tElemento info;
    struct nodo *izq, *der;
} nodoABB;

typedef nodoABB* tABB;

void crearABBVacio(tABB *arbol);
int esABBVacio(tABB arbol);
void construir(tABB *arbol, tElemento e);
void inorden(tABB arbol);
void premiomasbajoSINRECURSIVIDAD(tABB arbol, tElemento *elem);
void premiomasbajoRECURSIVO(tABB arbol, tElemento *elem);

void eliminar(tABB *arbol, tElemento e);

int altura(tABB arbol);
int esEquilibrado(tABB arbol);

#endif //TABB_H
