//
// Created by pueblo on 6/10/25.
//

#include "tElemento.h"

#include <string.h>

void crearElemento(tElemento *e, char ciudadOrigen[20], char ciudadDestino[20], char compania[20], int tiempo,
                   int precio) {
    strcpy(e->ciudadOrigen, ciudadOrigen);
    strcpy(e->ciudadDestino, ciudadDestino);
    strcpy(e->compania, compania);
    e->tiempo = tiempo;
    e->precio = precio;
}

int comparar(tElemento elem1, tElemento elem2){ //Devuelve 1  si son iguales y 0 si son distintos
    elem1.ciudadOrigen[strcspn(elem1.ciudadOrigen, "\n")] = '\0';
    elem2.ciudadOrigen[strcspn(elem2.ciudadOrigen, "\n")] = '\0';

    return !strcmp(elem1.ciudadOrigen, elem2.ciudadOrigen);
}

int compararCompleto(tElemento elem1, tElemento elem2){ //Devuelve 1  si son iguales y 0 si son distintos
    elem1.ciudadOrigen[strcspn(elem1.ciudadOrigen, "\n")] = '\0';
    elem1.ciudadDestino[strcspn(elem1.ciudadDestino, "\n")] = '\0';
    elem1.compania[strcspn(elem1.compania, "\n")] = '\0';

    elem2.ciudadOrigen[strcspn(elem2.ciudadOrigen, "\n")] = '\0';
    elem2.ciudadDestino[strcspn(elem2.ciudadDestino, "\n")] = '\0';
    elem2.compania[strcspn(elem2.compania, "\n")] = '\0';

    return !strcmp(elem1.ciudadOrigen, elem2.ciudadOrigen) && !strcmp(elem1.ciudadDestino, elem2.ciudadDestino) &&
           !strcmp(elem1.compania, elem2.compania) && elem1.precio == elem2.precio && elem1.tiempo == elem2. tiempo;
}

void asignar(tElemento *destino, tElemento origen) {
    strcpy(destino->ciudadOrigen, origen.ciudadOrigen);
    strcpy(destino->ciudadDestino, origen.ciudadDestino);
    strcpy(destino->compania, origen.compania);
    destino->tiempo = origen.tiempo;
    destino->precio = origen.precio;
}

void mostrarElem(tElemento elem) {
    printf("%s;%s;%s;%i;%i", elem.ciudadOrigen, elem.ciudadDestino, elem.compania, elem.tiempo, elem.precio);
}

tElemento leer(FILE *f) {
    tElemento elem;
    fscanf(f, "%s", elem.ciudadOrigen);
    fscanf(f, "%s", elem.ciudadDestino);
    fscanf(f, "%s", elem.compania);
    fscanf(f, "%d", &elem.tiempo);
    fscanf(f, "%d", &elem.precio);
    return elem;
}
