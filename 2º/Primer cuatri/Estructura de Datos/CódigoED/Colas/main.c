#include <stdio.h>

#include "tColaPrioridad.h"

int main() {
    tColaPrioridad cola;
    crearColaVacia(&cola);

    tElemento e1 = {5}, e2 = {10}, e3 = {3};
    insertar(&cola, e1);
    insertar(&cola, e2);
    insertar(&cola, e3);
    imprimirCola(cola); // Debe imprimir: 10 5 3

    eliminar(&cola, e1);
    imprimirCola(cola); // Debe imprimir: 10 3

    return 0;
}
