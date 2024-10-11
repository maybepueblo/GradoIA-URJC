En este resumen se busca dar un poco más de orientación de cara a usar C++ para los fines de esta materia de [[Programación II - Índice]]. 

#### Origen de C++

Vamos a ver un poco de historia por curiosidad:

- Fue desarrollado en Bell Labs en 1979.
- **Evolución** del lenguaje C para incluir características de programación orientada a objetos (**POO**).
	- **Lenguaje híbrido** ya que permite combinar POO y programación imperativa.
	- Todos los códigos en C funcionan en un proyecto C++.

#### Características de C++

C++ está gestionado por un comité de ISO responsable de las nuevas versiones. Es además uno de los lenguajes más utilizados del mundo.

##### Funcionalidades destacadas de C++

1. **Programación Orientada a Objetos (POO)** 
	1. *Clases y objetos*
	2. *Herencia*
	3. *Polimorfismo*
2. **Soporte de diferentes paradigmas de programación**
	1. *Programación genérica*
	2. *Programación funcional*
3. **Compatibilidad con C**
	1. *C++ es compatible con C*
4. **Gestión de memoria**
	1. *Adición de operadores **new** y **delete** para gestión de mem. dinámica*
	2. *Soporte para punteros inteligentes*
5. **Biblioteca Estándar**
	1. *C++ Standard Library proporciona un conjunto de clases y funciones extenso*
	2. *Contenedores como vectores, listas, mapas, etc. y algoritmos genéricos como sort, find, etc.*

#### Diferencias con C en E/S

- Hay diferentes librerías como *iostream* dedicada a entrada/salida.
- Se utilizan **espacios de nombres**
	- ***std*** es un espacio de nombres que contiene entre otros ***cout*** para enviar contenidos al terminal (salida) o ***endl*** que se corresponde con el salto de línea.
	- ***cin*** sirve para recibir datos del terminal (entrada).

NOTA -> Hay que tener cuidado con los símbolos << y >> 

#### Espacios con nombre

Un namespace permite agrupar diferentes elementos bajo un mismo identificador. Por ejemplo *std* es un namespace creado en *iostream*. 

Para omitir el prefijo *std::* es posible utilizar la construcción *using namespace*, pero al usarla se pierde semántica y se reduce el rendimiento considerablemente.

Los espacios con nombre se crean con la siguiente sintaxis:

```
namespace nombreDelEspacio {...}
```

#### Tipos de datos básicos

C++ soporta exactamente los mismos tipos básicos que C:
- `Enteros` *int*, *short*, *long*
- `Punto flotante` *float*, *double*, *long double*
- `Caracteres` *char*, *signed char*, *unsigned char*

Además, se añade un tipo de dato para los valores booleanos: ***bool***, cuyos valores posibles son *true* y *false*. 
	Como en C, cualquier valor diferente de 0 es verdadero y el valor 0 es falso.

#### Módulos en C++

La creación de estos módulos en C++ es similar a C, solo que los ficheros tienen diferente extensión:
- Ficheros cabecera (.h) contienen declaraciones de funciones y clases.
- Ficheros fuente (.cpp) contienen las implementaciones real de las declaraciones

#### Memoria dinámica en C++

C++ dispone de dos operadores para gestionar la memoria dinámica `new` y `delete`. 

- `new` asigna un bloque de memoria del tamaño que necesitemos.

```
int *p = new int;           // Variable entera dinámica
int *array = new int[10];   // Array de enteros dinámico
```

- `delete` libera la memoria del puntero usado.

```
delete p;            // Libera la memoria de la variable dinámica
delete [] array;     // Libera la memoria del array dinámico
```

En C++ también existe los smart pointers donde la gestión de memoria es automática.