//
// Created by pueblo on 10/29/24.
//

#include "tListaEnlazadaSimple.h"

#include <stdio.h>
#include <stdlib.h>

void crearListaESvacia(tListaES*l) {
    *l = NULL;
}

// Para este caso, nos haremos un insertar por final a partir de un insertar por cabecera auxiliar
void insertarElemento(tElemento elem, tListaES*l) {
    if (*l == NULL) {
        insertarCabeceraAux(elem, l);
    } else {
        tNodoES* nuevoNodo = (tNodoES*)malloc(sizeof(tNodoES));
        asignarElemento(&(nuevoNodo->info), elem);
        nuevoNodo->siguiente = NULL; // Lo ponemos apuntando a nada porque está al final de la lista
        tNodoES* aux = *l; // Nodo que está en el principio de la lista
        while (aux->siguiente != NULL) {
            aux = aux->siguiente; // Si no hemos llegado al final de la lista, seguimos avanzando
        }
        aux->siguiente = nuevoNodo; // Hacemos que nuestro nodo una vez en su final, corriga a dónde apunta
    }
}

void insertarCabeceraAux(tElemento elem, tListaES*l) {
    tNodoES* nuevoNodo = (tNodoES*)malloc(sizeof(tNodoES));
    asignarElemento(&(nuevoNodo->info), elem);
    if (nuevoNodo == NULL) {perror("Error en memoria\n");}
    nuevoNodo->siguiente = *l; // Asignamos como el siguiente, al nodo que ya apuntaba la lista
    *l = nuevoNodo; // Hacemos que la lista apunte a nuestro nuevo nodo
}

void borrarElemento(tElemento elem, tListaES*l) {
    if (l == NULL) {
        perror("No hay elemento que borrar");
    } else {
        tNodoES* aux = NULL; // Un nodo que siempre sea el anterior a aux
        tNodoES* actual = *l;
        while (actual != NULL && !compararElemento(actual->info, elem)) {
            aux = actual;
            actual = actual->siguiente;
        }
        aux->siguiente = actual->siguiente;
        free(actual);
    }
}

tElemento obtenerPrimero(tListaES*l) {
    tNodoES* primero = *l;
    return primero->info;
}

int esVacia(tListaES*l) {
    if (*l == NULL) {
        return 1;
    } else {
        return 0;
    }
}


