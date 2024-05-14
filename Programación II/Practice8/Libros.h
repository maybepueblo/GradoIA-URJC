//
// Created by pablo on 5/15/2024.
//

#ifndef PRACTICE8_LIBROS_H
#define PRACTICE8_LIBROS_H
#include "Recursos.h"

class Libro : public Recurso {
protected:
    int paginas;
public:
    Libro(char *nombre, int anyo, int iden, int p) : Recurso(nombre, anyo, iden)
    , paginas(p) {};
    double costePrestamo() override {
        return paginas*0.05;
    }
};


#endif //PRACTICE8_LIBROS_H
