//
// Created by pablo on 4/19/2024.
//

#include "Persona.h"
#include <cstring>

char * Persona::toString() {

    char *buf = new char[3*MAX_CHAR];

    strcpy(buf, name);
    strcat(buf, ";");
    strcat(buf, surname);

    return buf;
}

Persona::Persona(char *nom, char *sur_nom) {
    strcpy(name, nom);
    strcpy(surname, sur_nom);

}


