//
// Created by maybepueblo on 10/9/24.
//

#include "complejos.h"
#include <math.h>

// Constructora generadora
tComplejo CrearComplejo(double re, double im) {
    tComplejo complejo;
    complejo.real = re;
    complejo.imag = im;
    return complejo;
}

// Constructoras no generadoras
tComplejo Sumar(tComplejo a, tComplejo b) {
    return CrearComplejo(a.real + b.real, a.imag + b.imag);
}

tComplejo Restar(tComplejo a, tComplejo b) {
    return CrearComplejo(a.real - b.real, a.imag - b.imag);
}

tComplejo Multiplicar(tComplejo a, tComplejo b) {
    double re = a.real * b.real - a.imag * b.imag;
    double im = a.real * b.imag + a.imag * b.real;
    return CrearComplejo(re, im);
}

tComplejo Dividir(tComplejo a, tComplejo b) {
    double denom = b.real * b.real + b.imag * b.imag;
    if (denom == 0) {
        return CrearComplejo(0, 0);
    }
    double re = (a.real * b.real + a.imag * b.imag) / denom;
    double im = (a.real * b.imag - a.imag * b.real) / denom;
    return CrearComplejo(re, im);
}

tComplejo Conjugar(tComplejo a) {
    return CrearComplejo(a.real, -a.imag);
}

tComplejo I() {
    return CrearComplejo(0, 1);
}

// Observadoras selectoras
double ObtenerReal(tComplejo a) {
    return a.real;
}

double ObtenerImag(tComplejo a) {
    return a.imag;
}

// Observadoras no selectoras
double CalcularModulo(tComplejo a) {
    double square_root = sqrt(a.real * a.real + a.imag * a.imag);
    return square_root;
}
