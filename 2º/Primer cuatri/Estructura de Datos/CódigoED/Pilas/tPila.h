//
// Created by pueblo on 6/5/25.
//

#ifndef TPILA_H
#define TPILA_H
#include "tElemento.h"

typedef struct nodoP {
    tElemento elem;
    struct nodoP* anterior;
} tNodoP;

typedef tNodoP* tPila;

void crearPilaVacia(tPila* pila);
void push(tPila* pila, tElemento* elem);
void cima(tPila* pila, tElemento* destino);
void pop(tPila* pila);
int esPilaVacia(tPila* pila);
void copiar (tPila* origen, tPila* destino);
void destruir(tPila* pila);

#endif //TPILA_H
