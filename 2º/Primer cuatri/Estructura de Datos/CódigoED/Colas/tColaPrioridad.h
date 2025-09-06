//
// Created by pueblo on 6/5/25.
//

#ifndef TCOLAPRIORIDAD_H
#define TCOLAPRIORIDAD_H
#include "tElemento.h"

typedef struct tNodo {
    tElemento e;
    struct tNodo *prox;
} tNodoC;

typedef struct {
    tNodoC *inicio;
    tNodoC *final;
} tColaPrioridad;

void crearColaVacia(tColaPrioridad *c);
void insertar(tColaPrioridad* c, tElemento e);
void eliminar(tColaPrioridad* c, tElemento e);
void imprimirCola(tColaPrioridad c);
int esColaVacia(tColaPrioridad c);

#endif //TCOLAPRIORIDAD_H