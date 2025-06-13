//
// Created by pueblo on 6/9/25.
//

#ifndef TARBOLTWEETS_H
#define TARBOLTWEETS_H
#include "tElemento.h"

typedef struct nodo {
    tElemento info;
    struct nodo *izq, *der;
} tNodo;

typedef tNodo* tArbol;

void crearABVacio(tArbol* arbol);
void construirAB(tArbol* arbol, tElemento elem);
void inorden(tArbol arbol);
void analizarTweets(tArbol arbol, tTweet tweet);
void imprimirHashtag(tArbol arbol, tHashtag buscado);
void eliminarHashtag(tArbol *arbol, tHashtag eliminado);
int esABVacio(tArbol arbol);

#endif //TARBOLTWEETS_H
