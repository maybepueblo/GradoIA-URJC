//
// Created by pueblo on 6/9/25.
//

#include "tABB.h"

#include <stddef.h>
#include <stdlib.h>

void crearABBVacio(tABB*arbol) {
    *arbol = NULL;
}

int esABBVacio(tABB arbol) {
    return arbol == NULL;
}

void construir(tABB*arbol, tElemento e) {
    if (esABBVacio(*arbol)) {
        *arbol = (tABB)malloc(sizeof(nodoABB));
        asignarElemento(&(*arbol)->info, e);
        (*arbol)->izq = NULL;
        (*arbol)->der = NULL;
    } else {
        tElemento r;
        asignarElemento(&r, (*arbol)->info);
        if (e.premio < r.premio) {
            construir(&(*arbol)->izq, e);
        } else {
            construir(&(*arbol)->der, e);
        }
    }
}

void inorden(tABB arbol) {
    if (esABBVacio(arbol)) return;
    inorden(arbol->izq);
    mostrarElemento(arbol->info);
    inorden(arbol->der);
}

void premiomasbajoSINRECURSIVIDAD(tABB arbol, tElemento *elem) {
    if (esABBVacio(arbol)) return;
    tABB actual = arbol;
    while (actual != NULL) {
        asignarElemento(elem, actual->info);
        actual = actual->izq;
    }
}

void premiomasbajoRECURSIVO(tABB arbol, tElemento *elem) {
    if (esABBVacio(arbol)) return;
    asignarElemento(elem, arbol->info);
    premiomasbajoRECURSIVO(arbol->izq, elem);
}

void eliminar(tABB *arbol, tElemento e) {
    if (esABBVacio(*arbol)) return;

    tElemento actual = (*arbol)->info;

    if (e.premio < actual.premio) {
        eliminar(&((*arbol)->izq), e);
    } else if (e.premio > actual.premio) {
        eliminar(&((*arbol)->der), e);
    } else {
        // Nodo encontrado
        if ((*arbol)->izq == NULL && (*arbol)->der == NULL) {
            // Caso 1: sin hijos
            free(*arbol);
            *arbol = NULL;
        } else if ((*arbol)->izq == NULL) {
            // Caso 2: solo hijo derecho
            tABB temp = *arbol;
            *arbol = (*arbol)->der;
            free(temp);
        } else if ((*arbol)->der == NULL) {
            // Caso 2: solo hijo izquierdo
            tABB temp = *arbol;
            *arbol = (*arbol)->izq;
            free(temp);
        } else {
            // Caso 3: dos hijos
            // Buscar el sucesor inmediato (menor de la rama derecha)
            tElemento min;
            premiomasbajoSINRECURSIVIDAD((*arbol)->der, &min);
            asignarElemento(&(*arbol)->info, min); // Reemplazar
            eliminar(&((*arbol)->der), min);       // Eliminar el nodo duplicado
        }
    }
}

int altura(tABB arbol) {
    if (esABBVacio(arbol))
        return -1; // Altura de árbol vacío
    int altIzq = altura(arbol->izq);
    int altDer = altura(arbol->der);
    return 1 + (altIzq > altDer ? altIzq : altDer);
}

int esEquilibrado(tABB arbol) {
    if (esABBVacio(arbol))
        return 1;
    int altIzq = altura(arbol->izq);
    int altDer = altura(arbol->der);
    int balanceado = (abs(altIzq - altDer) <= 1);
    return balanceado && esEquilibrado(arbol->izq) && esEquilibrado(arbol->der);
}


