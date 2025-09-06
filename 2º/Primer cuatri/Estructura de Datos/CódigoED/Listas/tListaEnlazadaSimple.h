//
// Created by pueblo on 6/3/25.
//

#ifndef TLISTAENLAZADASIMPLE_H
#define TLISTAENLAZADASIMPLE_H
#include "tElemento.h"

typedef struct Nodo {
    tElemento elemento;
    struct Nodo *siguiente;
} tNodo;

typedef tNodo* tLista;

tLista* crearListaVacia(tLista* lista);
void insertarCabecera(tLista *lista, tElemento elemento);
void borrarElemento(tLista* lista, tElemento elemento);
void imprimirLista(tLista lista);
int esVacia(tLista * lista);

#endif //TLISTAENLAZADASIMPLE_H
