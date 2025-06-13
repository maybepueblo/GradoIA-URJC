//
// Created by pueblo on 6/4/25.
//

#include "tListaEnlazadaInsertFinal.h"

#include <stddef.h>
#include <stdlib.h>

tListaIF* crearVaciaIF(tListaIF*lista) {
    *lista = NULL;
}

void insertarFinal(tListaIF*l, tElemento e) {
    tNodoIF *nodo = (tNodoIF*)malloc(sizeof(tNodoIF));
    asignarElemento(&(nodo->e), &e);
    if (*l == NULL) {
        *l = nodo;
    } else {
        tNodoIF* aux = *l;
        while (aux->p != NULL) {
            aux = aux->p;
        }
        aux->p = nodo;
    }
    nodo->p = NULL;
}

void imprimirListaIF(tListaIF l) {
    tNodoIF* aux = l;
    while (aux != NULL) {
        imprimirElemento(&(aux->e));
        aux = aux->p;
    }
}
