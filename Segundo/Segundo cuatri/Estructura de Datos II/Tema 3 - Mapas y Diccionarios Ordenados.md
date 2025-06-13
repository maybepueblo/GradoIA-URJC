## Árboles binarios de búsqueda (ABB)
### Definición y propiedades
Un **ABB** es una estructura de datos en forma de árbol donde cada nodo tiene un valor y dos subárboles: izquierdo y derecho. La propiedad clave de un ABB es que:
- Todos los valores en el subárbol **izquierdo** de un nodo son **menores** que el valor del nodo
- Todos los valores en el subárbol **derecho** son **mayores**

```
    5
   / \
  3   8
 / \   \
1   4   9
```
Si recorriésemos los nodos de este árbol en inorden (izquierda, raíz, derecha), véase [[Tema 2 - Árboles generales]], obtenemos los valores en orden ascendente: 1, 3, 4, 5 , 8, 9
### Operaciones en ABB
- **Búsqueda**: Comenzamos en la raíz y comparamos el valor buscado con el nodo actual. Si es menor, buscamos por el subárbol izquierdo, pero si es mayor, en el derecho. La complejidad es **O(h)** siendo **h** la altura del árbol
- **Inserción**: Para insertar un valor, seguimos un proceso similar a la búsqueda. Cuando llegamos a un nodo nulo, insertamos el nuevo valor allí. La complejidad también es **O(h)**
- **Borrado**: Tres casos:
	1. **Nodo hoja**: Eliminamos directamente
	2. **Nodo con un hijo**: Reemplaza el nodo por su hijo
	3. **Nodo con dos hijos**: Reemplazamos el nodo por su sucesor (menor valor en el subárbol derecho), y luego borramos el sucesor

***Ejemplo de borrado***
En el árbol anterior, queriendo borrar 5, tenemos como sucesor al 8, se quedaría así:
```
    8
   / \
  3   9
 / \
1   4
```
### Importancia del equilibrado
Para mantener la eficiencia de las operaciones, han de mantenerse los árboles equilibrados. Un árbol desequilibrado puede degenerar en una lista, aumentando altura **h** y por tanto, complejidad en operandos. Esto lo veremos mejor después
## Mapas y diccionarios ordenados
### Definición y características
Son estructuras de datos que almacenan pares **clave-valor**, donde cada clave está asociada a un valor. Nos permiten buscar de forma eficiente por clave, haciéndolas útiles en situaciones donde hemos de acceder rápidamente a información asociada a cierta clave
- **Mapas**: no permiten claves duplicadas. Clave única y asociada a un solo valor
- **Diccionarios ordenados**: Similar a mapas, pero elementos ordenados según un criterio específico (e.j. orden alfabético o numérico)
En C++, implementamos esto como `set`, `map`, `multiset` y `multimap`. No debemos confundirlo con "unordered", que no tienen orden específico
### Operaciones básicas
- **Búsqueda**: La búsqueda de un elemento en un mapa o diccionario ordenado tiene complejidad de **O(log N)**, siendo **N** el número de elementos. Esto porque se construyen sobre ABBs o similares
- **Inserción y Borrado**: Misma complejidad que antes, requieren mantener el orden y la estructura del árbol.
- **Búsqueda por rango**: En diccionarios ordenados se nos permite realizar búsquedas por rango. Por ejemplo, teniendo un diccionario ordenado de números, puedes buscar entre valores 10 y 20 de forma eficiente.
### Comparación entre mapas ordenados y no ordenados
- **Mapas ordenados** (`map`, `set`): Mantienen elementos ordenados según criterio. Ideales para recorrer elementos en cierto orden o para búsquedas por rango 
- **Mapas no ordenados** (`unordered_map`, `unordered_set`): No hay orden específico pero dan acceso rápido a elementos individuales (**O(1)** como promedio)
Si tienes un diccionario de palabras y sus definiciones, y necesitas acceder a las palabras en orden alfabético, usarías un `map`. Si solo necesitas buscar definiciones rápidamente sin importar el orden, un `unordered_map` sería más eficiente.
## Equilibrado de árboles
### Importancia
Lo dijimos antes, es necesario para que no se degenere un árbol sin equilibrar en una lista, que aumenta la complejidad innecesariamente.
### Árboles AVL
Los vimos en [[Tema 7 - Árboles]], son árboles binarios de búsqueda equilibrados, para cada nodo, la altura de los subárboles izquierdo y derecho difiere en máximo 1. Si se desequilibra, hacemos **rotaciones** para re equilibrarlo.
- **Rotaciones**:
	1. **Simple**: Cuando el desequilibrio ocurre en un solo lado (izq-izq o der-der)
	2. **Doble**: Cuando ocurre en lados opuestos (izq-der o der-izq)

***Ejemplo de simple***
Si está desequilibrado hacia la izquierda, haces una rotación simple a la derecha para equilibrarlo. Igualmente, en el tema 7 de ED I hay ejemplos hechos.
### Árboles Rojo-Negro
Otra forma donde cada nodo tiene un color. Las propiedades de estos árboles aseguran que ningún camino desde la raíz a una hoja sea más del doble de largo que otro.
- **Propiedades**
	1. Raíz siempre negra
	2. Hojas (nodos nulos) son negras
	3. Hijos de un nodo rojo son negros
	4. Todos los caminos desde un nodo hasta sus hojas tienen el mismo número de nodos negros (profundidad negra)
#### Doble rojo
Para remediarlo, se pueden cumplir 2 casos:
1. El tío del nodo insertado es negro
2. El tío del nodo insertado es rojo
##### Caso 1
Se lleva uno de los nodos del doble rojo a la posición del abuelo. Repartimos los rojos eliminando el problema del doble rojo. Para ello:
- Aplicamos reestructuración trinodo
	- Dado z (insertado), su padre v, y su abuelo u son reestructurados
- Coloreamos el nodo medio como negro y sus hijos de rojo

![[Configuraciones Caso 1.png]]
##### Caso 2
Un recoloreado a negro en ambas ramas y un recoloreado a rojo en un ascendiente para no modificar la altura negra. Para ello:
- Aplicamos recolor
- El padre y el tío se colorean a negro
- El abuelo se colorea de rojo (salvo que sea raíz)

*Ejemplo*
```
Árbol a cambiar
    \
   4 (n)
  /    \
 2 (r)  7 (r)
        /
      6 (r)
      
Cambio
   \
  4 (r)
 /     \
2 (n)  7 (n)
       /
     6 (r)  
```
### Comparación entre AVL y Rojo-Negro
- **AVL**: Estrictos en equilibrio, siendo más eficientes para búsqueda, pero requieren más rotaciones para inserciones y borrados
- **Rojo-Negro**: Menos estrictos, reduciendo rotaciones, pero pueden tener más altura que los AVL
