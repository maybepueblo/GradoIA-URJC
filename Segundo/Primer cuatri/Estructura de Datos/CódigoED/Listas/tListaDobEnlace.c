//
// Created by pueblo on 6/5/25.
//

#include "tListaDobEnlace.h"

#include <stddef.h>
#include <stdlib.h>

void crearVaciaD(tListaD*l) {
    *l = NULL;
}

void insertarElementoD(tListaD*l, tElemento e) {
    tNodoD* nodo = (tNodoD*)malloc(sizeof(tNodoD));
    asignarElemento(&(nodo->e), &e);
    if (*l == NULL) {
        *l = nodo;
        nodo->previo = NULL;
        nodo->siguiente = NULL;
    } else {
        (*l)->previo = nodo;
        nodo->siguiente = *l;
        nodo->previo = NULL;
        *l = nodo;
    }
}

void borrarElementoD(tListaD*l, tElemento e) {
    tNodoD* aux = *l;
    while (aux != NULL && !compararElemento(&e, &(aux->e))) {
        aux = aux->siguiente;
    }
    if (aux == NULL) {
        return;
    }
    if (aux->previo == NULL) {
        *l = aux->siguiente;
    }
    if (aux->siguiente == NULL) {
        (aux->previo)->siguiente = NULL;
    }
    free(aux);
}


