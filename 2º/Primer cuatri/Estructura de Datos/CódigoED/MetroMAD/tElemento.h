//
// Created by pueblo on 6/10/25.
//

#ifndef TELEMENTO_H
#define TELEMENTO_H

typedef struct {
    char nombre[30];
} tElemento;

void crearElemento(tElemento *elemento, char* nombre);
int comparar(tElemento e1, tElemento e2);
void asignar(tElemento* destino, tElemento origen);
void copiarElem(tElemento* destino, tElemento origen);
void mostrar(tElemento e);

#endif //TELEMENTO_H
