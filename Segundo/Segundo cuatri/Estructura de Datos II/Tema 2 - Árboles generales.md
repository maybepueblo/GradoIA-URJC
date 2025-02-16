### Implementaciones de árboles en Cpp
#### LCRSTree
El nodo contiene un elemento, una referencia al padre, referencia al primer hijo y luego al siguiente hermano. Por ejemplo la raíz tendría a NULL el puntero a un padre, pero tendría o no llenos los punteros a hijos. 

Te mueves entre hijos para poder acceder de uno a otro, teniendo una relación los hijos entre sí gracias al puntero que llamábamos a siguiente hermano.
## Motículo
Arbol binario construido en orden y es casi completo. El padre es mayor que sus hijos. Lo que no quiere decir que sea parecido a un AVL como vimos en ED, sino que tiene que ser simplemente el padre siempre mayor que sus hijos, sin importar en qué orden se introducen.

Si introducimos un elemento que sea mayor que se padre, habremos de hacer un intercambio para poder poner el nuevamente mayor toca cambiarle a la posición donde estaba el anterior padre. Esto se hace de forma sucesiva hasta que no sea mayor que su próximo padre o sea directamente raíz. 

- Para borrar tenemos que eliminar la raíz y la sustituimos por el último nodo, sustituyendo el hijo más grande hasta cumplir la condición de inserción. 