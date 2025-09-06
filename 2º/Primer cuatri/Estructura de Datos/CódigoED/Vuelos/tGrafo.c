//
// Created by pueblo on 6/10/25.
//

#include "tGrafo.h"

#include <stdlib.h>

int perteneceAdy(listaAdy listaAdy, tElemento destino);
void introducirAdyacencia(tGrafo aux, tElemento elem);
void actualizarElemsGrafo(tGrafo g, tElemento elem);
void actualizarElemsGrafoAdy(listaAdy lista, tElemento elem);

void crearGrafoVacio(tGrafo*g) {
    *g = NULL;
}

void insertarOrigen(tGrafo*g, tElemento origen) {
    if (!perteneceOrigenes(*g, origen)) {
        tGrafo aux = *g;
        while (aux != NULL && aux->sig != NULL) {
            aux = aux->sig;
        }
        tNodoL* nuevoNodo = (tNodoL*)malloc(sizeof(tNodoL));
        asignar(&nuevoNodo->info, origen);
        nuevoNodo->ady = NULL;
        nuevoNodo->sig = NULL;
        if (aux != NULL) {
            aux->sig = nuevoNodo;
        } else {
            *g = nuevoNodo;
        }
    }
}

void insertarDestino(tGrafo*g, tElemento elem) {
    if (!perteneceOrigenes(*g, elem)) {
        insertarOrigen(g, elem);
    }
    tGrafo aux = *g;
    if (!perteneceDestinos(*g, elem)) {
        while (!comparar(aux->info, elem)) {
            aux = aux->sig;
        }
        introducirAdyacencia(aux, elem);
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

int perteneceDestinos(tGrafo g, tElemento elem) {
    while (!comparar(g->info, elem)) {
        g = g->sig;
    }
    listaAdy aux = g->ady;
    if (aux == NULL) return 0;
    if (compararCompleto(aux->info, elem)) {
        return 1;
    } else {
        return perteneceAdy(aux->sig, elem);
    }
}

int perteneceAdy(listaAdy listaAdy, tElemento destino) {
    if (listaAdy == NULL) {
        return 0;
    }
    if (compararCompleto(listaAdy->info, destino)) {
        return 1;
    } else {
        return perteneceAdy(listaAdy->sig, destino);
    }
}

void introducirAdyacencia(tGrafo aux, tElemento elem) {
    listaAdy listaaux = aux->ady;
    while (listaaux != NULL && listaaux->sig != NULL) {
        listaaux = listaaux->sig;
    }
    nodoAdy* nuevoNodo = (nodoAdy*)malloc(sizeof(nodoAdy));
    asignar(&nuevoNodo->info, elem);
    nuevoNodo->sig = NULL;
    if (listaaux != NULL) {
        listaaux->sig = nuevoNodo;
    } else {
        aux->ady = nuevoNodo;
    }
}

// Esta funcion nos otorga la lista de ciudades de destino desde un origen dado
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

void mostrarListaAdy(listaAdy adyacentes) {
    while (adyacentes != NULL) {
        printf("\n");
        mostrarElem(adyacentes->info);
        adyacentes = adyacentes->sig;
    }
}
