>[!NOTE] Propósito de la práctica
>En este caso, se busca enseñarnos cómo utilizar los polimorfismos para nuestro provecho a partir del uso de clases abstractas en herencia.
>
>Así, se nos pide crear un sistema de biblioteca que tenga un array de recursos con ciertos libros y películas disponibles para el usuario.
>
>Cabe destacar que tanto pelis como libros tienen un coste de préstamo, cada uno con su tarifa respectiva: `0.05*páginas` para los libros y `0.1*minutos` para las películas

Dividimos como siempre la práctica en secciones:

- `Recurso` -> Clase base que da lugar a todo.
- `Libro` -> Clase derivada que tiene una variable única: número de páginas.
- `Peliculas` -> Clase derivada con variable única: minutos que dura.
- `Menú principal`

#### Recurso

En este caso lo que hemos de definir es lo que comparten todas las pelis y todos los libros, un nombre, un año de publicación y un identificador único.

```
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
    }    ~Recurso() {  
        delete[] titulo;  
    }};
```

Además, como se puede observar, hemos declarado un constructor de Recurso y asimismo, un método puro que implementaremos posteriormente y que convierte a Recurso en una clase abstracta. Para más información sobre clases abstractas véase [[Tema 10 - Abstracción]].

#### Libro

```
class Libro : public Recurso {  
protected:  
    int paginas;  
public:  
    Libro(char *nombre, int anyo, int iden, int p) : Recurso(nombre, anyo, iden)  
    , paginas(p) {};  
    double costePrestamo() override {  
        return paginas*0.05;  
    }};
```

En este caso, por pura pereza, el identificador es un único número, en la realidad tiene un código mixto, lo cual pueden intentar implementar en su código, no es nada complicado. 

Por otro lado, no hay mucho más que comentar, únicamente hacemos acopio de las herramientas de herencia para poder implementar el coste de préstamo a nuestra clase.

#### Película

```
class Pelicula : public Recurso {  
private:  
    int minutos;  
  
public:  
    Pelicula( char *nombre, int anyo, char iden, int m) : Recurso(nombre, anyo, iden),  
    minutos(m) {};  
    double costePrestamo() override {  
        return minutos*0.10;  
    }};
```

Aquí volvemos a lo mismo, es usar las herramientas con el mismo fin.

#### Menú principal

```
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
```

Ya finalmente, lo cohesionamos todo bien en nuestro main.cpp y listo, tenemos un programa funcional.

Gracias por leer!