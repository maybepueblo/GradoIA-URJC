//
// Created by pueblo on 6/9/25.
//

#include "tTweet.h"

#include <string.h>

void asignarTweet(tTweet *destino, tTweet origen) {
    strcpy(*destino, origen);
}
