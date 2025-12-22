//
// Created by pueblo on 6/10/25.
//

#ifndef TELEMENTO_H
#define TELEMENTO_H
#include <stdio.h>

typedef struct {
    char ciudadOrigen[20];
    char ciudadDestino[20];
    char compania[20];
    int tiempo;
    int precio;
} tElemento;

void crearElemento(tElemento *e, char ciudadOrigen[20], char ciudadDestino[20], char compania[20], int tiempo, int precio);
int comparar(tElemento e1, tElemento e2);
int compararCompleto(tElemento e1, tElemento e2);
void asignar(tElemento* destino, tElemento origen);
void actualizarElem(tElemento* destino, tElemento origen);
void copiar(tElemento* destino, tElemento origen);
void mostrarElem(tElemento elem);
tElemento leer(FILE *f);

#endif //TELEMENTO_H
