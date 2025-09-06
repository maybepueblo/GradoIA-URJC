## Introducción a los árboles
**Árbol**: Estructura jerárquica que representa parentesco entre nodos. 
- *Elementos de un árbol*
	- **Raíz** -> Nodo sin padre
	- **Hoja** -> Nodo sin hijos
	- **Nodo Interno** -> Al menos un hijo. Conectan raíz con hojas
	- **Ancestros** -> Padres, abuelos, etc.
	- **Descendientes** -> Hijos, nietos, etc.
	- **Profundidad** -> Número de ancestros de un nodo
	- **Altura** -> Nivel máximo del árbol. Longitud (rama más larga) desde raíz hasta hoja
	- **Hermanos** -> Nodos con mismo padre
	- **Grado de un nodo** -> Hijos que tiene un nodo
	- **Grado de un árbol** -> Mayor grado entre nodos del árbol
	- **Subárbol** -> Nodo y sus descendientes

Los árboles se usan para **flujos en organizaciones**, **sistemas de ficheros** y **entornos de programación** como algunos ejemplos.
## Operaciones Generales sobre Árboles
Permiten manipular y consultar la estructura de los datos. Se dividen en **construcción**, **acceso** y **consulta**

**Operaciones básicas**
- **isEmpty** -> Si árbol es vacío
- **Add** -> Añadir nodo al árbol, como raíz o como hijo
- **Cut** -> Subárbol a partir de un nodo
- **Attach** -> Añade un subárbol a un nodo

**Operaciones de acceso**
- **Root** -> Devuelve raíz
- **Parent** -> Devuelve padre 
- **Children** -> Devuelve un iterador a los hijos de cierto nodo

**Operaciones de consulta**
- **isRoot** -> Verifica si nodo es raíz
- **isLeaf** -> Verifica si nodo es hoja
- **isInternal** -> Verifica si nodo es interno (al menos un hijo)
## Árbol N-ario
Árbol en el que cada nodo puede tener hasta **N hijos**. Útiles para representar estructuras con múltiples ramas
### LinkedTree
- **Descripción**: Cada nodo contiene:
	- El elemento almacenado
	- Una referencia a su padre
	- Una colección de referencias a sus hijos
- ***Ejemplo*** -> Si `A` es padre de `B`, `C` y `D` entonces `A` tiene una lista de hijos que incluye a `B`, `C` y `D`
### LCRSTree
- **Descripción**: Cada nodo contiene:
	- El elemento almacenado
	- Referencia al padre
	- Referencia al primer hijo
	- Referencia al siguiente hermano
- ***Ejemplo*** -> Si `A` es padre de `B`, `C` y `D`, entonces `B` es el primer hijo de `A`, `C` es el hermano derecho de `B` y `D` es el hermano derecho de `C`
## Recorridos en Árboles
Formas de visitar todos los nodos de un árbol. Los más comunes son:
- **Preorden** -> Visita raíz, luego hijos de izquierda a derecha
	- *Ejemplo* -> Con raíz `A`, hijos `B` y `C`, `B` con hijos `D` y `E`, el recorrido preorden sería: `A, B, D, E, C`
- **Postorden** -> Visita hijos de izquierda a derecha, luego la raíz
	- *Ejemplo* -> Mismo árbol de antes, el recorrido siendo `D, E, B, C, A`
- **Inorden** (binarios only) -> Visita el hijo izquierdo, luego raíz, luego el hijo derecho
	- *Ejemplo* -> En árbol binario con raíz `A`, hijo izquierdo `B`, hijo derecho `C`, el recorrido inorden sería: `B, A, C`
### Iteradores personalizados
- **Descripción**: Permiten recorrer el árbol de manera eficiente, siguiendo un orden específico (preorden, postorden, inorden)
- ***Ejemplo*** -> Un preorden visitaría los nodos en el orden: raíz, hijo izquierdo, hijo derecho
## Árbol Binario
Caso especial de árbol N-ario, donde cada nodo tiene como máximo 2 hijos (izquierdo y derecho). Útiles en árboles de expresión y de decisión. Los vimos primeramente en [[Estructura de datos]] (véase [[Tema 7 - Árboles]])
### Linked Binary Tree
- **Descripción**: Cada nodo contiene:
	- El elemento almacenado
	- Una referencia a su padre
	- Una referencia a su hijo izquierdo
	- Una referencia a su hijo derecho
- ***Ejemplo*** -> Si `A` es la raíz, `B` es el hijo izquierdo, `C` el derecho, entonces `A` tiene referencias a `B` y `C`
### Array Binary Tree
- **Descripción**: La posición de cada elemento en un array establece la relación entre nodos.
	- La raíz está en posición 0
	- El hijo izquierdo de un nodo en la posición `i` está en `2*i + 1`
	- El hijo derecho está en `2*i + 2`
- ***Ejemplo*** -> Si la raíz está en 0, su hijo izquierdo está en 1 y el derecho en 2
### Montículo
- **Descripción**: Árbol binario en orden casi completo donde cada nodo es mayor que sus hijos. Se implementa comúnmente con un ArrayBinaryTree.
- **Inserción**: Añadimos un nodo en la siguiente posición libre y se intercambia con su padre si es mayor, propagándose hasta la raíz.
	- *Ejemplo*: Insertar `D` en un montículo: no intercambiamos porque es menor que su padre. Mientras que insertar `Z` intercambiamos con su padre y luego con la raíz, dejando `Z` como nueva raíz.
- **Borrado**: Eliminamos la raíz y sustituimos el último nodo, intercambiando con el hijo más grande hasta cumplir la condición de montículo.
	- *Ejemplo*: Si borramos la raíz `Z`, sustituimos por el último nodo insertado, como `J`, y se intercambia con `W` si necesario.

>[!WARNING] 
> NO quiere decir que sea parecido a un AVL como vimos en ED, sino que tiene que ser simplemente el padre siempre mayor que sus hijos, sin importar en qué orden se introducen.
