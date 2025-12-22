#include <stdio.h>

#include "tABB.h"
#include "tElemento.h"

int main(void) {
    tElemento c1;
    crearElemento(&c1, "C1", 0, 550);

    tElemento c2;
    crearElemento(&c2, "C2", 0, 130);

    tElemento c3;
    crearElemento(&c3, "C3", 0, 780);

    tElemento c4;
    crearElemento(&c4, "C4", 0, 250);

    tElemento c5;
    crearElemento(&c5, "C5", 0, 40);

    tElemento c6;
    crearElemento(&c6, "C6", 0, 860);

    tElemento c7;
    crearElemento(&c7, "C7", 0, 660);

    tABB arbol;
    crearABBVacio(&arbol);

    construir(&arbol, c1);
    construir(&arbol, c2);
    construir(&arbol, c3);
    construir(&arbol, c4);
    construir(&arbol, c5);
    construir(&arbol, c6);
    construir(&arbol, c7);
    inorden(arbol);

    printf("\n");
    printf("Elemento más bajo -> ");
    tElemento masBajo;
    premiomasbajoRECURSIVO(arbol, &masBajo);
    mostrarElemento(masBajo);

    printf("\n");

    printf("Borramos el elemento c3");
    printf("\n");

    eliminar(&arbol, c3);
    inorden(arbol);
    int bool = esEquilibrado(arbol);

    printf("\n");

    if (bool) {
        printf("Si es equilibrado");
    } else {
        printf("No es equilibrado");
    }
    printf("\n");

}
