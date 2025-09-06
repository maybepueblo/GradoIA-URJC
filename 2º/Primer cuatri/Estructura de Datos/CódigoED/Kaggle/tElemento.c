//
// Created by pueblo on 6/9/25.
//

#include "tElemento.h"

#include <stdio.h>
#include <string.h>

void crearElemento(tElemento *elemento, char *titulo, int tiempo, int premio) {
    elemento->premio = premio;
    elemento->tiempo = tiempo;
    strcpy(elemento->titulo, titulo);
}

void asignarElemento(tElemento *destino, tElemento origen) {
    destino->premio = origen.premio;
    destino->tiempo = origen.tiempo;
    strcpy(destino->titulo, origen.titulo);
}

void mostrarElemento(tElemento elem) {
    printf("%s: %i\n", elem.titulo, elem.premio);
}
