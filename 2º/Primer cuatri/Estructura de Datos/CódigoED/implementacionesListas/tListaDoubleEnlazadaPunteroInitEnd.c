//
// Created by pueblo on 10/29/24.
//

#include "tListaDoubleEnlazadaPunteroInitEnd.h"

#include <stdio.h>
#include <stdlib.h>

void crearListaEPIEVacia(tListaEPIE *l) {
    l->principio = NULL;
    l->final = NULL;
}

void insertarElementoPE(tElemento elem, tListaEPIE *l) {
    tNodoEPIE* nuevoNodo = (tNodoEPIE*)malloc(sizeof(tNodoEPIE));
    if (nuevoNodo == NULL) {perror("Error en memoria\n");}
    asignarElemento(&(nuevoNodo->info), elem);
    nuevoNodo->siguiente = l->principio;
    l->principio = nuevoNodo;
}

void borrarElementoPE(tElemento elem, tListaEPIE *l) {
    if (l->final == NULL) {
        perror("No hay nada que borrar\n");
    } else {
        tNodoEPIE* temp = l->principio, *ultimoCoincidente = NULL, *anterior = NULL, *anteriorUltimo = NULL;
        while (temp!= NULL) {
            if (compararElemento(temp->info, elem)) {
                ultimoCoincidente = temp;
                anteriorUltimo = anterior;
            }
            anterior = temp;
            temp = temp->siguiente;
        }

        if (ultimoCoincidente != NULL) {
            if (anteriorUltimo == NULL) {
                l->principio = l->principio->siguiente;
            } else {
                anteriorUltimo->siguiente = ultimoCoincidente->siguiente;
            }
        }
        free(ultimoCoincidente);
    }
}

tElemento obtenerFinal(tListaEPIE *l) {
    return l->final->info;
}

int esVaciaEPIE(tListaEPIE *l) {
    if (l->final == NULL) {
        return 1;
    } else {
        return 0;
    }
}
