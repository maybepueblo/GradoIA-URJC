//
// Created by pablo on 5/15/2024.
//

#ifndef PRACTICE8_RECURSOS_H
#define PRACTICE8_RECURSOS_H
#include <cstring>

#define MAX 30

class Recurso {
protected:
    char* titulo;
    int year;
    int ID;
public:
    Recurso(char *title, int y, int I) {
        titulo = new char[MAX];
        strcpy(this->titulo, title);
        year = y;
        ID = I;
    };
    virtual double costePrestamo() = 0;
    char *getTitulo() {
        return titulo;
    }
    ~Recurso() {
        delete[] titulo;
    }
};


#endif //PRACTICE8_RECURSOS_H
