//
// Created by maybepueblo on 10/9/24.
//

#include "complejos.h"
#include <stdio.h>
#include "Bitmap.h"

int main() {
    int i, j;
    int ancho = 640;
    int alto = 480;
    Bitmap gradiente = createBitmap("mandelbrot.bmp", ancho, alto, 3);
    for (i = 0; i < ancho; i++) {
        for (j = 0; j < alto; j++) {
            int maxIteraciones = 64;
            // Definimos nuestros complejos z y c
            tComplejo z = CrearComplejo(0, 0);
            tComplejo c = CrearComplejo(((double) i / 160 - 2.5), ((double) j / 160 - 1.5));

            // Ahora, nombramos el índice que nos ayudará a saber en qué posición de la iteración estamos
            int indice = 0;
            int comprobador = 0; // Un comprobador simple para ver si ya hemos llegado al límite del conjunto
            while (comprobador == 0 && indice < maxIteraciones) {
                double limiteModulo = 2.0; // Sabemos que si |zn| > 2, c no está en el conjunto
                // índice < 64, módulo <= 2
                z = Sumar(Multiplicar(z, z), c); // Calculamos justamente el |zn|
                if (CalcularModulo(z) > limiteModulo) {
                    comprobador = 1;
                }
                indice++;
            }
            putPixel(&gradiente, i, j, (char)indice); // pintamos el resto en función de dónde estemos
        }
    }
    saveBitmap(&gradiente);
}
