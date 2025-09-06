//
// Created by pueblo on 6/9/25.
//

#ifndef TELEMENTO_H
#define TELEMENTO_H

typedef struct {
    int premio;
    int tiempo;
    char titulo[10];
} tElemento;

void crearElemento(tElemento *elemento, char* titulo, int tiempo, int premio);
void asignarElemento(tElemento *destino, tElemento origen);
void mostrarElemento(tElemento elem);

#endif //TELEMENTO_H
