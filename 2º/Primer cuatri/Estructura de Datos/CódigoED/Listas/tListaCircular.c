//
// Created by pueblo on 6/4/25.
//

#include "tListaCircular.h"

#include <stddef.h>
#include <stdlib.h>

void iniciarLista(tListaC*l) {
    *l = NULL;
}

void insertarNodoC(tListaC*l, tElemento e) {
    tNodoC* nodo = (tNodoC*)malloc(sizeof(tNodoC));
    asignarElemento(&(nodo->e), &e);
    if (l == NULL) {
        nodo->p = nodo;
        *l = nodo;
    }
    else {
        nodo->p = (*l)->p;
        (*l)->p = nodo;
    }
}

void imprimirListaC(tListaC l) {
    if (l == NULL) return; // Lista vacía
    tNodoC* aux = l->p; // El primer nodo es el siguiente al último
    do {
        imprimirElemento(&(aux->e));
        aux = aux->p;
    } while (aux != l->p); // Volvemos al principio
}
