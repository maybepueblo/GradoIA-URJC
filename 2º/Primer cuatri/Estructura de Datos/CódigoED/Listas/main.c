#include <stdio.h>

#include "tElemento.h"
#include "tListaEnlazadaInsertFinal.h"
#include "tListaEnlazadaSimple.h"

int main(void) {
    tLista lista;
    tListaIF listaIF;
    crearListaVacia(&lista);
    crearVaciaIF(&listaIF);
    tElemento elem1 = crearElemento("Pablo", "Garcia", 19);
    tElemento elem2 = crearElemento("Pablo", "Garcia", 20);
    tElemento elem3 = crearElemento("Pablo", "Garcia", 21);
    tElemento elem4 = crearElemento("Pablo", "Garcia", 22);
    tElemento elem5 = crearElemento("Pablo", "Garcia", 23);
    tElemento elem6 = crearElemento("Pablo", "Garcia", 24);
    insertarCabecera(&lista, elem1);
    insertarFinal(&listaIF, elem1);
    insertarFinal(&listaIF, elem2);
    insertarCabecera(&lista, elem2);
    insertarFinal(&listaIF, elem3);
    insertarCabecera(&lista, elem3);
    insertarFinal(&listaIF, elem4);
    insertarCabecera(&lista, elem4);
    insertarFinal(&listaIF, elem5);
    insertarCabecera(&lista, elem5);
    insertarFinal(&listaIF, elem6);
    insertarCabecera(&lista, elem6);
    printf("----- Lista IC -------\n");
    imprimirLista(lista);
    printf("----- Lista IF -------\n");
    imprimirListaIF(listaIF);
    return 0;
}
