#include <stdio.h>
#include "tArbolDioses.h"
#include "tDios.h"

int main(void) {
    tDios cronos, zeus, hera, ares, hefeso, apolo, atenea, orfeo, aristeo, dedalo;
    crearElemento(&cronos, "Cronos", "dios del tiempo");
    crearElemento(&zeus, "Zeus", "dios supremo, líder de los 12 dioses olímpicos");
    crearElemento(&hera, "Hera", "diosa del matrimonio, las mujeres, el cielo y las estrellas");
    crearElemento(&ares, "Ares", "dios de la guerra, de la brutalidad y los horrores de las batallas");
    crearElemento(&hefeso, "Hefeso", "dios de la forja y del fuego, de los herreros, de los artesanos y los escultores");
    crearElemento(&apolo, "Apolo", "dios del sol");
    crearElemento(&atenea, "Atenea", "diosa de la civilización, la sabiduría, la razón, la inteligencia y la estrategia de combate");
    crearElemento(&orfeo, "Orfeo", "músico y poeta legendario, considerado uno de los músicos más talentosos de la mitología griega");
    crearElemento(&aristeo, "Aristeo", "semidiós asociado con la agricultura, la apicultura y la cría de animales");
    crearElemento(&dedalo, "Dedalo", "arquitecto");

    tArbol arbolCronos, arbolZeus, arbolHera, arbolAres, arbolHefeso, arbolApolo, arbolAtenea;
    tArbol arbolOrfeo, arbolAristeo, arbolDedalo;

    crearArbolVacio(&arbolCronos);
    crearArbolVacio(&arbolZeus);
    crearArbolVacio(&arbolHera);
    crearArbolVacio(&arbolAres);
    crearArbolVacio(&arbolHefeso);
    crearArbolVacio(&arbolApolo);
    crearArbolVacio(&arbolAtenea);
    crearArbolVacio(&arbolOrfeo);
    crearArbolVacio(&arbolAristeo);
    crearArbolVacio(&arbolDedalo);

    construirArbolB(&arbolDedalo, NULL, dedalo, NULL);
    construirArbolB(&arbolAtenea, arbolDedalo, atenea, NULL);
    construirArbolB(&arbolOrfeo, NULL, orfeo, NULL);
    construirArbolB(&arbolAristeo, NULL, aristeo, NULL);
    construirArbolB(&arbolApolo, arbolOrfeo, apolo, arbolAristeo);
    construirArbolB(&arbolZeus, arbolAtenea, zeus, arbolApolo);

    construirArbolB(&arbolHefeso, NULL, hefeso, NULL);
    construirArbolB(&arbolAres, NULL, ares, NULL);
    construirArbolB(&arbolHera, arbolHefeso, hera, arbolAres);

    construirArbolB(&arbolCronos, arbolZeus, cronos, arbolHera);

    // Preorden
    printf("Arbol genealogico en preorden:\n");
    preordenArbol(arbolCronos);

    printf("\n");

    esPadre(arbolCronos, hefeso, dedalo);

    printf("\n");

    esPadre(arbolCronos, zeus,atenea);

    printf("\n");

    char nombre[100];
    printf("Introduzca el nombre del dios que quiere buscar: ");
    scanf("%s",nombre);
    existeDios(arbolCronos,nombre);

    return 0;
}