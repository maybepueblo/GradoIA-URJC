//
// Created by pueblo on 6/9/25.
//

#ifndef TELEMENTO_H
#define TELEMENTO_H
#include "tHashtag.h"
#include "tListaTweets.h"

typedef struct {
    tHashtag hashtag;
    tLista listaTweets;
} tElemento;

void crearElemento(tElemento *elemento, char *hashtag);
void asignar(tElemento* destino, tElemento origen);
int esMenor(tElemento e1, tHashtag e2);

#endif //TELEMENTO_H
