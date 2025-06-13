//
// Created by pueblo on 10/29/24.
//

#include "tListaOrdenada.h"
#include <stdio.h>
#include <stdlib.h>
#include "tElemento.h"

void crearVaciaOrd(tListaO* l) {
    *l = NULL;
}

tListaO mezclar(tListaO* l1, tListaO* l2) {
    if (*l1 == NULL) { return *l2; }
    if (*l2 == NULL) { return *l1; }

    tListaO resultado;
    crearVaciaOrd(&resultado);

    tNodoO* actual_l1 = *l1;
    tNodoO* actual_l2 = *l2;
    if (obtenerPrioridad(actual_l1->info) <= obtenerPrioridad(actual_l2->info)){
        insertarOrd(actual_l1->info, &resultado);
        *l1 = actual_l1->siguiente;
        resultado->siguiente = mezclar(l1, l2);
    } else {
        insertarOrd(actual_l2->info, &resultado);
        *l2 = actual_l2->siguiente;
        resultado->siguiente = mezclar(l1, l2);
    }
    return resultado;
}

void insertarOrd(tElemento elem, tListaO* l) {

    if (l == NULL) {
        perror("NO");
        return;
    }

    tNodoO* nuevoNodo = (tNodoO*)malloc(sizeof(tNodoO));
    if (nuevoNodo==NULL) {perror("Error en memoria\n");}
    asignarElemento(&(nuevoNodo->info), elem);
    if (*l == NULL) {
        *l = nuevoNodo;
    } else {
        tNodoO* anterior = NULL;
        tNodoO* actual = *l;
        while (actual != NULL && obtenerPrioridad(nuevoNodo->info) >= obtenerPrioridad(actual->info)) {
            anterior = actual;
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual;
        if (anterior == NULL) {
            *l = nuevoNodo;
            nuevoNodo->siguiente = NULL;
        } else {
            anterior->siguiente = nuevoNodo;
        }
    }
}

void leerOrdenada(tListaO*lista) {
    tNodoO* temp = *lista;
    while (temp != NULL) {
        printf("Nombre: %s, Apellido: %s, DNI: %s, Edad: %d\n",
               temp->info.nombre, temp->info.apellido,
               temp->info.dni, temp->info.edad);
        temp = temp->siguiente;
    }
}

