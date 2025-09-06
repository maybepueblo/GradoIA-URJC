//
// Created by pueblo on 6/5/25.
//

#include "tColaPrioridad.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void crearColaVacia(tColaPrioridad *c) {
    c->inicio = NULL;
    c->final = NULL;
}

void insertar(tColaPrioridad *c, tElemento e) {
    tNodoC* nodo = (tNodoC*)malloc(sizeof(tNodoC));
    asignarElemento(&(nodo->e), &e);
    nodo->prox = NULL;

    if (esColaVacia(*c)) {
        c->inicio = nodo;
        c->final = nodo;
    } else {
        tNodoC* actual = c->inicio; // Nodo para recorrer desde un inicio
        tNodoC* anterior = NULL;

        // Buscamos el punto correcto para insertar en orden descendente
        while (actual != NULL && mayor(obtenerPrioridad(&(actual->e)), obtenerPrioridad(&e))) {
            anterior = actual;
            actual = actual->prox;
        }

        if (anterior == NULL) { // Inicio
            nodo->prox = c->inicio;
            c->inicio = nodo;
        } else {
            anterior->prox = nodo;
            nodo->prox = actual;
        }
        if (nodo->prox == NULL) {
            c->final = nodo;
        }
    }
}

void eliminar(tColaPrioridad *c, tElemento e) {
    if (esColaVacia(*c)) return;
    tNodoC* actual = c->inicio;
    tNodoC* anterior = NULL;

    while (actual != NULL && !igual(obtenerPrioridad(&(actual->e)), obtenerPrioridad(&e))) {
        anterior = actual;
        actual = actual->prox;
    }
    if (actual == NULL) return;

    if (anterior == NULL) {
        c->inicio = actual->prox;
    } else {
        anterior->prox = actual->prox;
    }

    if (actual == c->final) {
        c->final = anterior;
    }

    free(actual);
}

void imprimirCola(tColaPrioridad c) {
    tNodoC* actual = c.inicio;
    while (actual != NULL) {
        printf("%d ", obtenerPrioridad(&(actual->e)));
        actual = actual->prox;
    }
    printf("\n");
}

int esColaVacia(tColaPrioridad c) {
    return c.inicio == NULL;
}
