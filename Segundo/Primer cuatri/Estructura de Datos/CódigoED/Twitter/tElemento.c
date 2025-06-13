//
// Created by pueblo on 6/9/25.
//

#include "tElemento.h"

#include <stdlib.h>
#include <string.h>

void crearElemento(tElemento *elemento, char *hashtag) {
    int i;
    int longitud = strlen(hashtag);
    for (i = 0; i < longitud; i++) {
        if (hashtag[i] == '\n') {
            hashtag[i] = '\0';
        }
    }
    asignarHashtag(&(elemento->hashtag), hashtag);
    crearVacia(&(elemento->listaTweets));
}

void asignar(tElemento *destino, tElemento origen) {
    asignarHashtag(&(destino->hashtag), origen.hashtag);
    destino->listaTweets = origen.listaTweets;
}

int esMenor(tElemento e1, tHashtag hijo) {
    return strcmp(e1.hashtag, hijo) < 0;
}
