//
// Created by pueblo on 6/4/25.
//

#include "tListaOrdenada.h"

#include <stddef.h>
#include <stdlib.h>

void crearVaciaO(tListaO*l) {
    *l = NULL;
}

void insertarOrd(tListaO*l, tElemento e) {
    tNodoO* nuevo = (tNodoO*)malloc(sizeof(tNodoO));
    asignarElemento(&(nuevo->e), &e);
    if (l == NULL) {
        *l = nuevo;
        nuevo->p = NULL;
    } else {
        tNodoO* anterior = NULL;
        tNodoO* actual = *l;
        while (actual != NULL && obtenerPrioridad((nuevo->e)) >= obtenerPrioridad(actual->e)) {
            anterior = actual;
            actual = actual->p;
        }
        nuevo->p = actual;
        if (anterior == NULL) {
            *l = nuevo;
        } else {
            anterior->p = nuevo;
        }
    }
}

tListaO mezclar(tListaO*l1, tListaO*l2) {
    if (*l1 == NULL) {return *l2;};
    if (*l2 == NULL) {return *l1;};
    tListaO resultado;
    crearVaciaO(&resultado);
    tNodoO* actuall1 = *l1;
    tNodoO* actuall2 = *l2;
    if (obtenerPrioridad(actuall1->e) <= obtenerPrioridad(actuall2->e)) {
        insertarOrd(&resultado, actuall1->e);
        *l1 = actuall1->p;
        resultado->p = mezclar(l1, l2);
    } else {
        insertarOrd(&resultado, actuall2->e);
        *l2 = actuall2->p;
        resultado->p = mezclar(l1, l2);
    }
    return resultado;
}
