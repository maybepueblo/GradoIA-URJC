>[!NOTE] Propósito de la práctica
>En esta práctica llamada ArrayPlusTAD tenemos que buscar implementar funciones avanzadas a los arrays de C, ya que no tienen funciones avanzadas. En este primer ejemplo trataremos de manejar arrays de enteros.
>
>Para ello, será necesario implementar el tipo de datos ArrayPlusTAD con las siguientes funciones: creaArrayPlus, anyadeElemento, anyadeArray, imprimeArray, vaciaArray y liberaArray.

Vemos que tenemos un gran número de funciones que implementar a nuestro código, comentemos un poco lo que buscamos con cada una de ellas:

- `creaArrayPlus` -> Recibe el tamaño del nuevo ArrayPlus y crea en memoria dinámica la estructura necesaria para almacenarlo.
- `anyadeElemento` -> Añade un nuevo elemento al Array que pasamos como argumento. Si no caben más elementos, no se añade y se muestra un mensaje de error, devolviendo -1. Si no hay fallos, se devuelve un 0.
- `anyadeArray` -> Añade los elementos nuevos de otro array al nuestro. En caso de que no quepan todos, nos detenemos en cuanto no se puedan añadir más. A lo mejor una opción para seguir es usar la función anterior.
- `imprimeArrayPlus` -> Imprime todos los elementos que contiene *miArrayPlus*.
- `vaciaArray` -> Pues sí, vacía el contenido del array.
- `liberaArray` -> Liberamos la memoria ocupada por miArrayPlus. 

Lo iremos haciendo poco a poco, para entender de manera más fácil cómo implementar todo. Esta práctica se dividirá en tres pasos:

- **Declaración** -> Declararemos todo lo necesario para llevar a cabo la siguiente fase.
- **Implementación** -> Haremos funcionar todo lo que hemos mencionado arriba.
- **Programa final** -> Unimos todo para un programa funcional de prueba, con un menú interesante para que sea más bonito de ver.

#### Declaración

Primero que todo, teniendo creado nuestro proyecto, hemos de crear en él nuestro fichero .h, que llamaremos *ArrayPlusTAD.h*. Una vez lo tengamos creado, hemos de implementar todo lo necesario en él:

```
// Definimos el tipo de dato de nuestro ArrayPlus
typedef struct {  
    int *array;  
    int size;  
    int count;  
} ArrayPlusTAD;  

ArrayPlusTAD *createArrayPlus(int size);  
  
// Añade un elemento  
int addElement(ArrayPlusTAD *myArrayPlus, int element);  
  
// Añade elementos a partir de un array  
void addArray(ArrayPlusTAD *myArrayPlus, int *arrayElements, int numNewElements);  
  
// Imprime nuestro array
void printArrayPlus(ArrayPlusTAD *myArrayPlus);  
  
// Vacía nuestro array  
void emptyArrayPlus(ArrayPlusTAD *myArrayPlus);  
  
// Libera la memoria  
void freeArrayPlus(ArrayPlusTAD *myArrayPlus);
```

Como podemos ver, simplemente hemos declarado todo lo necesario además de que hemos definido el tipo de dato *ArrayPlusTAD* que nos permitirá obrar con él luego.

#### Implementación

Ahora sí, veamos cómo implementar cada función por sí sola:

##### createArrayPlus

Esta no tiene gran dificultad, vamos a echarle un vistazo:

```
ArrayPlusTAD *createArrayPlus(int size) {  
    ArrayPlusTAD *myArrayPlus = malloc(sizeof(ArrayPlusTAD));  
    myArrayPlus->array = malloc(size * sizeof(int));  
    myArrayPlus->size = size;  
    myArrayPlus->count = 0;  
    return myArrayPlus;  
}
```

Lo único que buscamos es iniciar miArrayPlus con memoria dinámica para posteriormente iniciar de igual forma el array que contiene este tipo de datos. Luego ya iniciamos el tamaño de nuestro array mejorado con el tamaño dado a la par que ponemos el número de elementos a 0.

##### addElement

```
int addElement(ArrayPlusTAD *myArrayPlus, int element) {  
    if (myArrayPlus->count < myArrayPlus->size) {  
        myArrayPlus->array[myArrayPlus->count++] = element;  
        return 0;  
    } else {  
        printf("No room for more elements\n");  
        return -1;  
    }}
```

En este caso, verificamos que count (el número de elementos) sea menor que el tamaño total de nuestro array, si lo es, añadimos el elemento, si no, damos un mensaje de error y luego un código de error, en este caso -1. 
##### addArray

```
void addArray(ArrayPlusTAD *myArrayPlus, int *arrayElements, int numNewElements) {  
    for (int i = 0; i < numNewElements; ++i) {  
        if (addElement(myArrayPlus, arrayElements[i]) == -1) {  
            break;  
        }    
    }    
}
```

Para añadir un array tenemos que simplemente añadir desde el principio hasta el número de elementos que queremos añadir, en caso de que si usamos addElement y nos da igual a -1, pues tenemos que salirnos del bucle for, si no, seguimos añadiendo elementos o bien hasta llegar al máximo o hasta que de error.

##### printArrayPlus

```
void printArrayPlus(ArrayPlusTAD *myArrayPlus) {  
    for (int i = 0; i < myArrayPlus->count; ++i) {  
        printf("Element %i -> %i\n", i+1, myArrayPlus->array[i]);  
    }
}
```

Este caso no tiene ciencia, buscamos simplemente enseñar todos los elementos que tiene nuestro array.

##### Vaciar el array o liberar la memoria

En este caso, vamos a unir estos dos en un sólo apartado, ya verán por qué:

```
void emptyArrayPlus(ArrayPlusTAD *myArrayPlus) {  
    myArrayPlus->count = 0;  
    printf("Array successfully emptied\n");  
}
```

Y ya está, esto es vaciar el array, una bobería, pero eficiente, ya que directamente nos cargamos todos los datos anteriores y reseteamos nuevamente. Veamos cómo de fácil es liberar la memoria ahora:

```
void freeArrayPlus(ArrayPlusTAD *myArrayPlus) {  
    free(myArrayPlus->array);  
    free(myArrayPlus);  
    printf("Array successfully freed\n");  
}
```

Y así de fácil es, buscamos solamente liberar el array primero para luego liberar el puntero general y ya está, programa terminado. 

#### Programa final

Y finalmente, este será un test que podemos llevar a cabo en nuestro main:

```
#include "ArrayPlusTAD.h"  
#include <stdio.h>  
  
#define SIZE 5  
  
int main() {  

    // Test general  
    // Creamos un array vacío  
    ArrayPlusTAD *myArrayPlus = createArrayPlus(SIZE * 2);  
  
    // Rellenamos el array  
    for (int i = 0; i < SIZE; i++) {  
        addElement(myArrayPlus, i);  
    }  
    // Enseñamos el contenido  
    printArrayPlus(myArrayPlus);  
  
    // Vaciamos el array  
    emptyArrayPlus(myArrayPlus);  
  
    // Varios elementos
    int arrayAux[] = {15, 64, 27, 99};  
    addArray(myArrayPlus, arrayAux, 4);  
  
    // Añade un único elemento  
    addElement(myArrayPlus, 8);  
  
    // Enseña el contenido
    printArrayPlus(myArrayPlus);  
  
    // Libera la memoria 
    freeArrayPlus(myArrayPlus);  
  
    return 0;  
}
```

Y listo, esto ya está perfectamente implementado. 

Para hacerlo más fácil de ver y de montar, adjunto de igual forma la carpeta donde tengo toda la práctica. Únicamente tened en cuenta que programo en inglés ya por costumbre, lo que significa que el código que hay dentro del archivo que subiré no está en español.

¡Muchas gracias por leerme! :)
