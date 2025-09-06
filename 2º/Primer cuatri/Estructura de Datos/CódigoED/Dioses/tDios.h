//
// Created by pueblo on 6/9/25.
//

#ifndef TDIOS_H
#define TDIOS_H

typedef struct {
    char name[20];
    char desc[500];
} tDios;

void crearElemento(tDios* dios, char* n, char* d);
void asignarElemento(tDios* destino, tDios origen);
int compararDios(tDios d1, char* d2);
int compararNombres(tDios d1, tDios d2);
void imprimirDios(tDios d);

#endif //TDIOS_H
