//
// Created by pueblo on 6/3/25.
//

#ifndef TELEMENTO_H
#define TELEMENTO_H

typedef struct {
    char nombre[20];
    char apellido[20];
    int edad;
} tElemento;

tElemento crearElemento(char* nombre, char* apellido, int edad);
void imprimirElemento(tElemento* elemento);
void asignarElemento(tElemento* destino, tElemento* origen);
int compararElemento(tElemento* e2, tElemento* e1);
int obtenerPrioridad(tElemento elemento);

#endif //TELEMENTO_H
