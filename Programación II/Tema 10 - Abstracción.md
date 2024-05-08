> [!NOTE]  El por qué de la abstracción
> La abstracción es un proceso cognitivo que podemos usar o bien para **destacar las partes relevantes** de un elemento o fenómeno complejo, o bien para **ignorar el resto de detalles** que son prescindibles para entender el concepto o resolver un problema. 
> 
> De esta manera, la abstracción nos permite abordar problemas complejos a través de la simplificación en problemas más sencillos, reduciendo la cantidad de información necesaria por problema y permitiéndonos identificar comportamientos o características comunes a diversos elementos

#### Abstracción en programación 

Esta oculta los detalles de ciertos elementos:
- Funciones
- Módulos
- TADs (tipos abstractos de datos)
- Clases

A su vez que los oculta, se nos brinda una interfaz de comunicación con estos elementos abstraídos, reduciendo el esfuerzo al programar y por tanto, la dificultad.

Así, podemos decir que la abstracción expone la **funcionalidad**. Es decir, el usuario solo sabe qué hace el elemento, pero no cómo lo hace

#### Tipos de abstracción

En este curso trataremos los siguientes dos tipos:

- **Abstracción funcional** -> 
	- Separa el propósito de una función y su implementación
		- Se puede hacer esa función en múltiples pasos.
	- Define el qué tiene que hacer una función ocultando cómo lo ha de hacer.
- **Abstracción de datos** (TADs) ->
	- Consiste en la creación de nuevos tipos de datos.
	- Define posibles valores y operaciones para manejar estos valores nuevos.
	- Cada operación es una abstracción funcional. 

#### Módulos

Hasta el momento, no nos habíamos alejado del fichero *main.c*, lo cual hacía un código muy **poco modular**, ya que teníamos todo aglutinado en el mismo fichero.

En C tenemos la opción de modularizar nuestro código:

- Podemos dividirlo en **distintos ficheros** que contienen funciones relacionadas entre sí de alguna forma. (Por ejemplo la librería *math.h* tiene funciones matemáticas, la *stdio.h* de entrada-salida, etc...)
- Para definir esta propia librería en C, necesitamos de dos ficheros:
	- [nombre].c -> contiene el código de las funciones implementadas
	- [nombre].h -> contiene el prototipo de las funciones sin código.
- El fichero .h muestra lo público mientras que el fichero .c abstrae la implementación -> **Abstracción funcional**

##### Ejemplo

En este caso, definiremos una librería *calculadora*. Vamos a crear para ello dos ficheros:
- **calculadora.c** contendrá el código de nuestra librería.
- **calculadora.h** contendrá los prototipos de las funciones disponibles.

###### calculadora.h

Veamos cómo hemos de rellenar el fichero .h

```
//  
// Created by pueblo on 5/8/2024.  
//  

// Definiciones dadas por Clion
#ifndef CALCULADORATEST_CALCULADORA_H  
#define CALCULADORATEST_CALCULADORA_H  

// Declaramos todas las funciones que luego implementaremos
int sumar(int a, int b);  
int restar(int a, int b);  
int multiplicar(int a, int b);  
int dividir(int a, int b);  
int potencia(int a, int b);  
  
  
#endif //CALCULADORATEST_CALCULADORA_H
```

Como vemos, no tiene mucha complejidad, ya que condensa los problemas en trozos pequeños que son mucho más digeribles. En este caso, el fichero *.h* cumple la función de responder a *¿Qué funciones tiene mi programa?* que como podemos ver hemos fijado en este caso las operaciones matemáticas básicas.

###### calculadora.c

Ahora, vamos a implementar nuestras funciones, en este caso serán muy simples:

```
//  
// Created by pueblo on 5/8/2024.  

// Importante incluir la librería .h donde teníamos las declaraciones antes
#include "calculadora.h"  
  
int sumar(int a, int b) {  
    return a+b;  
}  
  
int restar(int a, int b) {  
    return a-b;  
}  
  
int dividir(int a, int b) {  
    return a/b;  
}  
  
int multiplicar(int a, int b) {  
    return a*b;  
}  
  
int potencia(int a, int b) {  
    return a^b;  
}
```

Como vemos, debido a la simplicidad de nuestra tarea, es bastante fácil llevar a la realidad nuestras funciones. Cabe denotar que no ha de ser así la sintaxis en todos los casos, habrá ocasiones donde sean funciones complejas pero que aisladas de esta manera facilitan su implementación.

###### main.c

Ahora sí que sí, veamos como todo se trae a la vida en nuestro fichero de programa:

```
#include <stdio.h>  
#include "calculadora.h"  
  
int main() {  
    int suma = sumar(3, 3);  
    int resta = restar(5, 2);  
    int division = dividir(6, 3);  
    int multiplicacion = multiplicar(3, 5);  
    int potencias = potencia(2, 6);  
  
    printf("Suma: %d\n", suma);  
    printf("Resta: %d\n", resta);  
    printf("Division: %d\n", division);  
    printf("Multiplicacion: %d\n", multiplicacion);  
    printf("Potencias: %d\n", potencias);  
  
    return 0;  
}
```

Nunca nos podemos olvidar de incluir la librería, que al ser creada por nosotros tenemos que llamar con la sintaxis `"nombre.h"`. Por lo demás, hasta aquí llegamos, esto por supuesto significa que acabamos de crear un programa mucho más modular que nunca, lo cual nos vendrá bien para futuras ocasiones.