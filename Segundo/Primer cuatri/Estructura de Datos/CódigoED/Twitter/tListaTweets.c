//
// Created by pueblo on 6/9/25.
//

#include "tListaTweets.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void crearVacia(tLista *lista) {
    lista->inicio = NULL;
    lista->fin = NULL;
}

void construirLista(tLista *lista, tTweet t) {
    tNodoL* nodo = (tNodoL*)malloc(sizeof(tNodoL));
    asignarTweet(&(nodo->info), t);
    if (esVacia(*lista)) {
        lista->inicio = nodo;
        lista->fin = nodo;
        nodo->sig = NULL;
        nodo->ant = NULL;
    } else {
        nodo->sig = lista->inicio;
        lista->inicio->ant = nodo;
        nodo->ant = NULL;
        lista->inicio = nodo;
    }
}

void imprimirLista(tLista lista) {
    if (esVacia(lista)) return;
    tNodoL* aux = lista.inicio;
    while (aux != NULL) {
        printf("%s \n", aux->info);
        aux = aux->sig;
    }
}

int esVacia(tLista lista) {
    return lista.inicio == NULL, lista.fin == NULL;
}
