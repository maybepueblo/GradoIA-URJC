//
// Created by pueblo on 10/29/24.
//

#include "tElemento.h"

#include <stdio.h>
#include <string.h>

tElemento crearElemento(char *n, char *a, char *d, int edad) {
    tElemento elemento;
    strcpy(elemento.nombre, n);
    strcpy(elemento.apellido, a);
    strcpy(elemento.dni, d);
    elemento.edad = edad;
    return elemento;
}

void mostrarElemento(tElemento elem) {
    printf("%s;%s;%s;%d", elem.nombre, elem.apellido, elem.dni, elem.edad);
}

void asignarElemento(tElemento *destino, tElemento origen) {
    strcpy(destino->nombre, origen.nombre);
    strcpy(destino->apellido, origen.apellido);
    strcpy(destino->dni, origen.dni);
    destino->edad = origen.edad;
}

int obtenerPrioridad(tElemento elem) {
    return elem.edad;
}

int compararElemento(tElemento elem1, tElemento elem2) {
    // Creamos un puntero a cada campo del primer elemento y del segundo
    char* camposE1[] = {elem1.nombre, elem1.apellido, elem1.dni};
    char* camposE2[] = {elem2.nombre, elem2.apellido, elem2.dni};

    int i = 0;
    while (i < 3) {
        if (strcmp(camposE1[i], camposE2[i]) != 0) {
            return 0;
        }
        i++;
    }

    // Comparamos edades
    if (elem1.edad != elem2.edad) {
        return 0;
    }

    // Si no, retornamos 1 al coincidir todos los campos
    return 1;
}




