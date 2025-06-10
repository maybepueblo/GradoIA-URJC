//
// Created by pueblo on 6/9/25.
//

#ifndef TLISTATWEETS_H
#define TLISTATWEETS_H
#include "tTweet.h"

typedef struct nodoL {
    tTweet info;
    struct nodoL *sig, *ant;
} tNodoL;

typedef struct {
    tNodoL *inicio, *fin;
} tLista;

void crearVacia(tLista* lista);
void construirLista(tLista* lista, tTweet t);
void imprimirLista(tLista lista);
int esVacia(tLista lista);

#endif //TLISTATWEETS_H
