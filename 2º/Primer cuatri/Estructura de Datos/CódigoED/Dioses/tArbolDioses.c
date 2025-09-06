
//
// Created by pueblo on 6/9/25.
//

#include "tArbolDioses.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void crearArbolVacio(tArbol* arbol) {
    arbol == NULL;
}

void construirArbolB(tArbol*arbol, tArbol izq, tDios dios, tArbol der) {
    *arbol = (tArbol)malloc(sizeof(tNodo));
    asignarElemento(&((*arbol)->dios),dios);
    (*arbol)->izq = izq;
    (*arbol)->der = der;
}

int esArbolVacio(tArbol arbol) {
    return arbol == NULL;
}

void preordenArbol(tArbol arbol) {
    if (esArbolVacio(arbol)) return;
    imprimirDios(arbol->dios);
    preordenArbol(arbol->izq);
    preordenArbol(arbol->der);
}

void existeDios(tArbol arbol, char *n) {
    if (esArbolVacio(arbol)) return;
    tNodo* aux = arbol;
    if (compararDios(aux->dios, n)) {
        printf("Existe");
        return;
    } else {
        existeDios(aux->izq, n);
        existeDios(aux->der, n);
    }
    printf("No existe");
}

void esPadre(tArbol arbol, tDios d1, tDios d2) {
    if (esArbolVacio(arbol)) return;
    tNodo* aux = arbol;
    if (compararNombres(aux->dios, d1)) {
        tNodo* izq = aux->izq;
        tNodo* der = aux->der;
        if ((izq && compararNombres(izq->dios, d2)) || (der && compararNombres(izq->dios, d2))) {
            printf("%s padre de %s", d1.name, d2.name);
        } else {
            printf("No padre de %s", d1.name);
            return;
        }
    } else {
        esPadre(arbol->izq, d1, d2);
        esPadre(arbol->der, d1, d2);
    }
}