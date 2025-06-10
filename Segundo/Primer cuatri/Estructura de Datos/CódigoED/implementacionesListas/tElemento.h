//
// Created by pueblo on 10/29/24.
//

#ifndef TELEMENTO_H
#define TELEMENTO_H

#include <string.h>

typedef struct {
    char nombre[100];
    char apellido[100];
    char dni[9];
    int edad;
} tElemento;

// Constructora generadora
tElemento crearElemento(char* n, char* a, char* d, int edad);

// Observadora selectora
void mostrarElemento(tElemento elem);
void asignarElemento(tElemento* destino, tElemento origen);
int obtenerPrioridad(tElemento elem);

// Observadora no selectora
int compararElemento(tElemento elem1, tElemento elem2);


#endif //TELEMENTO_H
