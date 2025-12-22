//
// Created by pueblo on 6/3/25.
//

#include "tElemento.h"

#include <stdio.h>
#include <string.h>

tElemento crearElemento(char *nombre, char *apellido, int edad) {
    tElemento elem;
    strcpy(elem.nombre, nombre);
    strcpy(elem.apellido, apellido);
    elem.edad = edad;
    return elem;
}

void imprimirElemento(tElemento *elemento) {
    printf("%s;%s;%i\n", elemento->nombre, elemento->apellido, elemento->edad);
}

void asignarElemento(tElemento *destino, tElemento *origen) {
    strcpy(destino->nombre, origen->nombre);
    strcpy(destino->apellido, origen->apellido);
    destino->edad = origen->edad;
}

int compararElemento(tElemento *e2, tElemento *e1) {
    return strcmp(e1->nombre, e2->nombre) == 0 && strcmp(e1->apellido, e2->apellido) == 0 && e1->edad == e2->edad;
}

int obtenerPrioridad(tElemento elemento) {
    return elemento.edad;
}
