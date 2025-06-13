//
// Created by pueblo on 6/9/25.
//

#include "tHashtag.h"

#include <string.h>

void asignarHashtag(tHashtag *destino, char *origen) {
    strcpy(*destino, origen);
}

int SonIguales(tHashtag r,tHashtag hashtag){
    return strcmp(r,hashtag) == 0;
}