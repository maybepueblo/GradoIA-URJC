//
// Created by pueblo on 6/10/25.
//

#include "tElemento.h"

#include <stdio.h>
#include <string.h>

void crearElemento(tElemento *elemento, char *nombre) {
    strcpy(elemento->nombre, nombre);
}

int comparar(tElemento e1, tElemento e2) {
    // Borrar el salto de línea del final por si acaso
    e1.nombre[strcspn(e1.nombre, "\n")] = '\0';
    e2.nombre[strcspn(e2.nombre, "\n")] = '\0';
    return strcmp(e1.nombre, e2.nombre) == 0;
}

void asignar(tElemento *destino, tElemento origen) {
    strcpy(destino->nombre, origen.nombre);
}

void copiarElem(tElemento *destino, tElemento origen) {
    strcpy(destino->nombre, origen.nombre);
}

void mostrar(tElemento e) {
    printf("%s\n", e.nombre);
}

