//
// Created by pueblo on 6/10/25.
//

#ifndef TGRAFO_H
#define TGRAFO_H
#include "tElemento.h"

typedef struct nodo {
    tElemento info;
    struct nodo *sig;
} nodoAdy;

typedef nodoAdy* listaAdy;

typedef struct nodoL {
    tElemento info;
    listaAdy ady;
    struct nodoL *sig;
} tNodoL;

typedef tNodoL* tGrafo;

void crearGrafoVacio(tGrafo* g);
void insertarOrigen(tGrafo* g, tElemento origen);
void insertarDestino(tGrafo* g, tElemento elem);
int esGrafoVacio(tGrafo g);
int perteneceOrigenes(tGrafo g, tElemento origen);
int perteneceDestinos(tGrafo g, tElemento elem);
void listaAdyacencia(tGrafo g, tElemento origen, listaAdy* adyacentes);
void mostrarListaAdy(listaAdy adyacentes);

#endif //TGRAFO_H
