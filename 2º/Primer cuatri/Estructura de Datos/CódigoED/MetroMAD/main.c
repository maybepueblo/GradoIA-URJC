#include <stdio.h>
#include <string.h>

#include "tGrafo.h"

int main(void) {
    tGrafo grafo;
    crearGrafoVacio(&grafo);

    char ruta[50];


    for (int linea = 1; linea <= 12 ; ++linea) {

        sprintf(ruta, "estaciones/L%d.txt", linea);

        FILE *f = fopen(ruta, "r");
        if(f != NULL) {

            tElemento origen, destino;

            char nombre[30];
            if (fgets(nombre, 30, f) != NULL) {
                nombre[strcspn(nombre, "\n")] = '\0';
            }
            crearElemento(&origen, nombre);
            insertarOrigen(&grafo, origen);

            while (!feof(f)) {
                copiarElem(&destino, origen);
                char nombre2[30];
                if (fgets(nombre2, 30, f) != NULL) {
                    nombre2[strcspn(nombre2, "\n")] = '\0';
                }
                crearElemento(&origen, nombre2);
                insertarDestino(&grafo, origen, destino);

            }
            fclose(f);
        }
    }

    char nombreEstacion[30];
    printf("Introduce el nombre de la estación: \n");

    fgets(nombreEstacion, sizeof(nombreEstacion), stdin);
    nombreEstacion[strcspn(nombreEstacion, "\n")] = '\0'; // Limpia el salto de línea

    tElemento estacion;
    crearElemento(&estacion, nombreEstacion);
    mostrar(estacion);

    listaAdy adyacentes;
    listaAdyacencia(grafo, estacion, &adyacentes);
    mostrarlista(adyacentes);

    return 0;
}
