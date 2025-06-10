#include <stdio.h>

#include "tGrafo.h"

int main(void) {
    FILE *f = fopen("vuelos.txt", "r");
    tGrafo g;
    crearGrafoVacio(&g);

    tElemento e;
    while (!feof(f)){
        e = leer(f);
        insertarDestino(&g, e);

    }

    tGrafo aux = g;
    while (aux != NULL){
        printf("%s\n", aux->info.ciudadOrigen);
        mostrarListaAdy(aux->ady);
        printf("\n");
        printf("\n");
        aux = aux->sig;
    }

    return 0;


}
