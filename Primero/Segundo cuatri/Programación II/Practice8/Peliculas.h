//
// Created by pablo on 5/15/2024.
//

#ifndef PRACTICE8_PELICULAS_H
#define PRACTICE8_PELICULAS_H
#include "Recursos.h"

class Pelicula : public Recurso {
private:
    int minutos;

public:
    Pelicula( char *nombre, int anyo, char iden, int m) : Recurso(nombre, anyo, iden),
    minutos(m) {};
    double costePrestamo() override {
        return minutos*0.10;
    }
};

#endif //PRACTICE8_PELICULAS_H
