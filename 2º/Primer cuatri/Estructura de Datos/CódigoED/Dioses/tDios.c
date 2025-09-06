//
// Created by pueblo on 6/9/25.
//

#include "tDios.h"

#include <stdio.h>
#include <string.h>

void crearElemento(tDios *dios, char *n, char *d) {
    strcpy(dios->name, n);
    strcpy(dios->desc, d);
}

void asignarElemento(tDios *destino, tDios origen) {
    strcpy(destino->name, origen.name);
    strcpy(destino->desc, origen.desc);
}

int compararDios(tDios d1, char* n) {
    return strcmp(d1.name, n) == 0;
}

int compararNombres(tDios d1, tDios d2) {
    return strcmp(d1.name, d2.name) == 0;
}

void imprimirDios(tDios d) {
    printf("%s:", d.name);
    printf(" %s\n", d.desc);
}
