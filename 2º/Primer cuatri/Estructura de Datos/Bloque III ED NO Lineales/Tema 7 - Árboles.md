## Definiciones
- **Camino** -> secuencia de nodos conectados dentro de un árbol
- **Longitud de camino** -> número de nodos que unen el camino
- **Grado** (aridad) de un **nodo** -> número de hijos del nodo
- **Grado** (aridad) de un **árbol** -> máximo grado de sus nodos
- **Altura** o **profundidad** -> longitud del camino desde el nodo raíz a su hoja más lejana
- **Nivel** o **profundidad** de un **nodo** -> longitud entre raíz del árbol y dicho nodo
## Conceptos de árboles binarios
- Árboles N-Arios
	- Padres tienen un número indeterminado de subárboles
- Árboles binarios
	- Padres no tienen más de 2 hijos
	- Puede degenerar en una lista
### Binarios
- Hijos de un nodo: izquierdo y derecho (no son iguales ni aunque se cambien de orden)
- Profundidad del árbol binario promedio es mucho menor que n -> árboles binarios de búsqueda
## Especificación algebraica
## Implementaciones
- Mediante vectores simulando memoria dinámica![[Implementación estática árbol.png]]
- Mediante punteros y variables dinámicas
![[Implementación dinámica árbol.png]]
### Recorridos
Dado un árbol básico A-B-C de la siguiente forma:
![[a-b-c.png]]
Decimos que existen los siguientes tipos de recorridos:
- **Preorden** -> A-B-C (raíz, izquierda, derecha)
- **Inorden** -> B-A-C (izquierda, raíz, derecha)
- **Postorden** -> B-C-A (izquierda, derecha, raíz)
## Programación con árboles binarios
- Contar número de nodos
- Contar hojas
- Decir si dos árboles son iguales
- Pertenencia de un elemento a un árbol
- Construir imagen especular
- Calcular profundidad de un árbol
- Ver si un árbol está equilibrado
- Calcular el nivel en el que aparece un nodo en un árbol
## Árboles binarios de búsqueda
### Introducción
- Particularización del binario con nodos ordenados en función de lo que contienen
- Para cada nodo, los de su subárbol izquierdo son menores que su elemento y los del derecho mayores.
- Ordenación consistente
	- Facilita la búsqueda
	- Puede degenerarse igual
### Especificación Algebraica
### Implementación
- Memoria dinámica
- Punteros y variables dinámicas nuevamente
### AVL
- Búsqueda de elementos en árbol binario de búsqueda: O(log n) y O(n) dependiendo del orden de inserción de elementos
- Surgen estos AVL para mejorar el rendimiento de operaciones, tienen así una condición de equilibrio:
	- Las alturas de los 2 subárboles para cada nodo no difieren en más de una unidad
	- Factor de equilibrio o balance de un nodo se define como altura del subárbol derecho menos altura del subárbol izquierdo para ese nodo
	- Cada nodo del AVL puede tener un balance de -1, 0 o 1.

Así, mantenemos información de la altura en cada nodo. Y para garantizar esta ordenación consistente podemos hacer rotaciones:
- Rotación simple: izq-izq o dcha-dcha
- Rotación doble: izq-dcha o dcha-izq
