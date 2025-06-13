#include <stdio.h>
#include "tElemento.h"
#include "tListaOrdenada.h"

int main(void) {
    tListaO listaOrd;
    crearVaciaOrd(&listaOrd);
    int choice;
    printf("Quieres añadir un elemento: ");
    scanf("%d", &choice);
    while (choice != 0) {
        char nombre[40], apellido[40], dni[10];
        int edad;
        printf("N: ");
        scanf("%s", nombre);
        printf("A: ");
        scanf("%s", apellido);
        printf("D: ");
        scanf("%s", dni);
        printf("E: ");
        scanf("%d", &edad);
        tElemento elem = crearElemento(nombre, apellido, dni, edad);
        insertarOrd(elem, &listaOrd);
        printf("Quieres añadir un elemento: ");
        scanf("%d", &choice);
    }
    leerOrdenada(&listaMezclada);
    return 0;
}

int main9(void) {
    tListaO listaOrd1, listaOrd2;

    crearVaciaOrd(&listaOrd1);
    crearVaciaOrd(&listaOrd2);

    // Elementos de prueba
    tElemento elem1 = {"Pablo", "Apellido", "Pepe", 25};
    tElemento elem2 = {"Ana", "Apellido", "Pepe", 20};
    tElemento elem3 = {"Juan", "Apellido", "Pepe", 30};
    tElemento elem4 = {"Maria", "Apellido", "Pepe", 27};

    // Insertar elementos en ambas listas
    insertarOrd(elem1, &listaOrd1);
    insertarOrd(elem2, &listaOrd1);
    insertarOrd(elem3, &listaOrd2);
    insertarOrd(elem4, &listaOrd2);

    tListaO listaMezclada = mezclar(&listaOrd1, &listaOrd2);

    printf("Lista mezclada: \n");
    leerOrdenada(&listaMezclada);
}
