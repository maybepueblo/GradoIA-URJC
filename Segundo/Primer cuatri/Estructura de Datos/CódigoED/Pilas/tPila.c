//
// Created by pueblo on 6/5/25.
//

#include "tPila.h"

#include <stddef.h>
#include <stdlib.h>

void crearPilaVacia(tPila*pila) {
    (*pila) = NULL;
}

void push(tPila*pila, tElemento *elem) {
    tNodoP* nodo = (tNodoP*)malloc(sizeof(tNodoP));
    asignarElemento(&(nodo->elem), elem);
    nodo->anterior = *pila;
    *pila = nodo;
}

void cima(tPila*pila, tElemento *destino) {
    if (!esPilaVacia(pila)) {
        asignarElemento(destino, &((*pila)->elem));
    }
}

void pop(tPila*pila) {
    if (!esPilaVacia(pila)) {
        tNodoP* aux = *pila;
        *pila = aux->anterior;
        free(aux);
    }
}

int esPilaVacia(tPila* pila) {
    return (*pila) == NULL;
}

void copiar(tPila*origen, tPila*destino) {
    tNodoP* auxnododest;

    if (!esPilaVacia(origen)) {
        tNodoP* auxnodoorigen = *origen;
        tNodoP* auxnododestino = (tNodoP*)malloc(sizeof(tNodoP));
        asignarElemento(&(auxnododestino->elem), &(auxnodoorigen->elem));
        auxnododestino->anterior = NULL;
        *destino = auxnododestino;
        auxnodoorigen = auxnodoorigen->anterior;

        while (auxnodoorigen != NULL) {
            auxnododest = auxnododestino;
            tNodoP* auxnododestino = (tNodoP*)malloc(sizeof(tNodoP));
            asignarElemento(&(auxnododestino->elem), &(auxnodoorigen->elem));
            auxnododestino->anterior = NULL;
            auxnododest->anterior = auxnododestino;
            auxnodoorigen = auxnodoorigen->anterior;
        }
    }
}

void destruir(tPila*pila) {
    while (!esPilaVacia(pila)) {
        pop(pila);
    }
}
