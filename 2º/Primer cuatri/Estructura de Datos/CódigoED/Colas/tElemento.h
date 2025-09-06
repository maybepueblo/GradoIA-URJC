//
// Created by pueblo on 6/5/25.
//

#ifndef TELEMENTO_H
#define TELEMENTO_H

typedef struct {
    int n;
} tElemento;

void asignarElemento(tElemento* destino, tElemento* origen);
int obtenerPrioridad(tElemento* elemento);
int mayor(int a, int b);
int igual(int a, int b);

#endif //TELEMENTO_H
