//
// Created by maybepueblo on 10/9/24.
//

#ifndef COMPLEJOS_H
#define COMPLEJOS_H

typedef struct {
    double real;
    double imag;
} tComplejo;

// Constructora generadora
tComplejo CrearComplejo(double real, double imag);

// Constructoras no generadoras
tComplejo Sumar(tComplejo a, tComplejo b);
tComplejo Restar(tComplejo a, tComplejo b);
tComplejo Multiplicar(tComplejo a, tComplejo b);
tComplejo Dividir(tComplejo a, tComplejo b);
tComplejo Conjugar(tComplejo a);
tComplejo I();

// Observadoras selectoras
double ObtenerReal(tComplejo a);
double ObtenerImag(tComplejo b);

// Observadora no selectora
double CalcularModulo(tComplejo a);

#endif //COMPLEJOS_H
