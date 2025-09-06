//
// Created by pueblo on 6/10/25.
//

#ifndef TGRAFO_H
#define TGRAFO_H
#include "tElemento.h"

typedef struct nodo {
    tElemento info;
    struct nodo *sig;
} tNodo;

typedef tNodo* listaAdy;

typedef struct nodoL {
    tElemento info;
    listaAdy ady;
    struct nodoL *sig;
} tNodoL;

typedef tNodoL* tGrafo;

void crearGrafoVacio(tGrafo* g);
void insertarOrigen(tGrafo* g, tElemento origen);
void insertarDestino(tGrafo* g, tElemento origen, tElemento destino);
int esGrafoVacio(tGrafo g);
int perteneceOrigenes(tGrafo g, tElemento origen);
int perteneceDestinos(tGrafo g, tElemento origen, tElemento destino);
void listaAdyacencia(tGrafo g, tElemento origen, listaAdy *adyacentes);
void mostrarlista(listaAdy l);

// Funciones auxiliares
int perteneceAdy(listaAdy l, tElemento destino);
void introducirAdy(tGrafo aux, tElemento elem);

#endif //TGRAFO_H
