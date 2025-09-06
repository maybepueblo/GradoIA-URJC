//
// Created by pueblo on 6/3/25.
//

#include "tListaEnlazadaSimple.h"
#include <stdio.h>
#include <stdlib.h>

tLista* crearListaVacia(tLista *lista) {
    *lista = NULL;
}

void insertarCabecera(tLista *lista, tElemento elemento) {
    tNodo* nodo = (tNodo*)malloc(sizeof(tNodo));
    asignarElemento(&(nodo->elemento), &elemento); // Asignamos elemento
    nodo->siguiente = *lista; // Apuntamos desde nuestro nodo al anterior primero
    *lista = nodo; // Hacemos al nuevo nodo el primero
}

void borrarElemento(tLista* lista, tElemento elemento) {
    tNodo* previo = NULL;
    tNodo* aux = *lista;
    while (!compararElemento(&(aux->elemento), &elemento)) {
        aux = aux->siguiente;
        previo = aux;
    }
    if (aux->siguiente == NULL) {
        previo->siguiente = NULL;
    } else {
        previo->siguiente = aux->siguiente;
    }
    free(aux);
}

void imprimirLista(tLista lista) {
    tNodo* aux = lista;
    while (aux != NULL) {
        imprimirElemento(&(aux->elemento));
        aux = aux->siguiente;
    }
}

int esVacia(tLista*lista) {
    return (*lista == NULL);
}

