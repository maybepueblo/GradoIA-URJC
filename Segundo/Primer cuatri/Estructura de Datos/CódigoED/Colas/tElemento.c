//
// Created by pueblo on 6/5/25.
//

#include "tElemento.h"

void asignarElemento(tElemento *destino, tElemento *origen) {
    destino->n = origen->n;
}

int obtenerPrioridad(tElemento *elemento) {
    return elemento->n;
}

int mayor(int a, int b) {
    return a > b;
}

int igual(int a, int b) {
    return a == b;
}
