//
// Created by pueblo on 6/4/25.
//

#ifndef TLISTACABECERAYFINAL_H
#define TLISTACABECERAYFINAL_H
#include "tElemento.h"

typedef struct tNodoCyF {
    tElemento e;
    struct tNodoCyF *p;
} tNodoCyF;

typedef struct Lista {
    tNodoCyF *inicio;
    tNodoCyF *final;
} tListaCyF;

tListaCyF* crearVaciaCyF(tListaCyF* lista);
void insertarCyFcabecera(tListaCyF* lista, tElemento e);
void insertarCyFfinal(tListaCyF* lista, tElemento e);
void imprimirListaCyF(tListaCyF* lista);

#endif //TLISTACABECERAYFINAL_H
