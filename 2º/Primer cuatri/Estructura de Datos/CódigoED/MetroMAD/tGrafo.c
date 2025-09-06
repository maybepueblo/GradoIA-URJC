//
// Created by pueblo on 6/10/25.
//

#include "tGrafo.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void crearGrafoVacio(tGrafo*g) {
    *g = NULL;
}

void insertarOrigen(tGrafo*g, tElemento origen) {
    if (!perteneceOrigenes(*g, origen)) {
        tGrafo aux = *g;
        while (aux != NULL && aux->sig != NULL) { // Esto es para meterlo al final del grafo
            aux = aux->sig;
        }
        tNodoL *nuevoNodo = (tNodoL*)malloc(sizeof(tNodoL));
        asignar(&nuevoNodo->info, origen);
        nuevoNodo->ady = NULL;
        nuevoNodo->sig = NULL;
        if (aux!= NULL) {
            aux->sig = nuevoNodo;
        } else {
            *g = nuevoNodo;
        }
    }
}

void insertarDestino(tGrafo*g, tElemento origen, tElemento destino) {
    if (!perteneceOrigenes(*g, origen)) {
        insertarOrigen(g, origen);
    }
    if (!perteneceOrigenes(*g, destino)) {
        insertarOrigen(g, destino);
    }
    tGrafo aux = *g;
    if (!perteneceDestinos(*g, origen, destino)) {
        while (!comparar(aux->info, origen) && !comparar(aux->info, destino)) {
            aux = aux->sig;
        }
        if (comparar(aux->info, origen)) {
            introducirAdy(aux, destino);
        } else {
            introducirAdy(aux, origen);
        }
        aux = aux->sig;
        while (!comparar(aux->info, origen) && !comparar(aux->info, destino)) {
            aux = aux->sig;
        }
        if (comparar(aux->info, origen)) {
            introducirAdy(aux, destino);
        } else {
            introducirAdy(aux, origen);
        }
    }
}

int esGrafoVacio(tGrafo g) {
    return g == NULL;
}

int perteneceOrigenes(tGrafo g, tElemento origen) {
    if (esGrafoVacio(g)) return 0;
    if (comparar(g->info, origen)) {
        return 1;
    } else {
        return perteneceOrigenes(g->sig, origen);
    }
}

int perteneceDestinos(tGrafo g, tElemento origen, tElemento destino) {
    while (!comparar(g->info, origen)) {
        g = g->sig;
    }
    listaAdy aux = g->ady;
    if (aux == NULL) return 0; // Si la lista de ady es vacía
    if (comparar(aux->info, destino)) {
        return 1;
    } else {
        return perteneceAdy(aux->sig, destino);
    }
}

void listaAdyacencia(tGrafo g, tElemento origen, listaAdy*adyacentes) {
    while (g != NULL && g->sig != NULL) {
        if (comparar(g->info, origen)) {
            *adyacentes = g->ady;
            return;
        } else {
            g = g->sig;
        }
    }
}

void mostrarlista(listaAdy l) {
    while (l != NULL) {
        printf("\n");
        mostrar(l->info);
        l = l->sig;
    }
}

int perteneceAdy(listaAdy l, tElemento destino) {
    if (l == NULL) return 0;
    if (comparar(l->info, destino)) {
        return 1;
    } else {
        return perteneceAdy(l->sig, destino);
    }
}

void introducirAdy(tGrafo aux, tElemento elem) {
    listaAdy aux2 = aux->ady;
    while (aux2 != NULL && aux2->sig != NULL) {
        aux2 = aux2->sig;
    }
    tNodo *nuevonodo = (tNodo*)malloc(sizeof(tNodo));
    asignar(&nuevonodo->info, elem);
    nuevonodo->sig = NULL;
    if (aux2 != NULL) {
        aux2->sig = nuevonodo;
    } else {
        aux->ady = nuevonodo;
    }
}