#include <iostream>
#include "Recursos.h"
#include "Libros.h"
#include "Peliculas.h"

int const MAX_RECURSOS = 5;

int main() {
    Recurso *recurso[MAX_RECURSOS];

    int numRecursos = 0;
    recurso[numRecursos] = new Libro("Harry Potter", 2010, 2024, 500);
    recurso[++numRecursos] = new Pelicula("Interstellar", 2000, 3, 150);

    for (int i = 0; i <= numRecursos; ++i) {
        std::cout << "Coste de prestamo de \"" << recurso[i]->getTitulo() << "\": " << recurso[i]->costePrestamo()
        << std::endl;
    }

    return 0;
}
