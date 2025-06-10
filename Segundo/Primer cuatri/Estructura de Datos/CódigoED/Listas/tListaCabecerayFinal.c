//
// Created by pueblo on 6/4/25.
//

#include "tListaCabecerayFinal.h"

#include <stddef.h>
#include <stdlib.h>

tListaCyF * crearVaciaCyF(tListaCyF *lista) {
    lista->inicio = NULL;
    lista->final = NULL;
}

void insertarCyFcabecera(tListaCyF *lista, tElemento e) {
    tNodoCyF *nodo = (tNodoCyF *)malloc(sizeof(tNodoCyF));
    asignarElemento(&(nodo->e), &e);
    nodo->p = lista->inicio;
    if (lista->inicio == NULL) {
        lista->final = nodo;
    }
    lista->inicio = nodo;
}

void insertarCyFfinal(tListaCyF *lista, tElemento e) {
    tNodoCyF *nodo = (tNodoCyF *)malloc(sizeof(tNodoCyF));
    asignarElemento(&(nodo->e), &e);
    nodo->p = lista->final;
    if (lista->final == NULL) {
        lista->inicio = nodo;
    }
    lista->final = nodo;
}

void imprimirListaCyF(tListaCyF *lista) {
    tNodoCyF *nodo = lista->inicio;
    while (nodo != NULL) {
        imprimirElemento(&(nodo->e));
        nodo = nodo->p;
    }
}

