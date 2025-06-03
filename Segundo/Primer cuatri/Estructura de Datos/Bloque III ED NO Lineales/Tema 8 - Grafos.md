#### Introducción
Usamos los grafos para modelar sistemas posiblemente menos jerárquicos o relaciones arbitrarias. Por ejemplo, caminos entre ciudades, redes de ordenadores, redes sociales, etc.

##### Concepto
- Grafo: G = (V, A)
- V = conjunto de vértices pertenecientes al grafo G {v1, v2, v3, ...}
- A = conjunto de pares (v1, v2) donde v1 y v2 pertenecen a V. Representan los arcos (aristas) de G.

- Densidad: relación entre número de arcos y número de vértices:
	- Diferenciamos grafos densos o dispersos. (cambia nuestra implementación)
	- A menos vértices, más aristas y entonces más disperso.

- Grafo dirigido / Digrafo: cuando los arcos son ordenados (v1, v2) != (v2, v1)
- Arcos con sentido -> hay flechas
- Puede haber 2 arcos entre 2 nodos.

Adyacencia: dos vértices son adyacentes si existe un arco que los una (para grafos dirigidos: "adyacentes a")

- Grafo valorado o ponderado --> grafo que tiene asociado un valor a la arista (peso o coste de forma general)

##### Definiciones
- Grado: número de arcos que contiene un nodo
- Si el grafo es dirigido hay que diferenciar entre:
	- Grado de entrada
	- Grado de salida
- Nodos fuente/sumidero: nodos que sólo tienen aristas de salida (fuente) o sólo de entrada (sumidero)
- Camino: secuencia para llegar de un punto a otro.
- Longitud de camino: número de arcos que recorremos.
- Ciclos: camino de un nodo a sí mismo (pasando por otros nodos)
- Bucle: arista que conecta un nodo consigo mismo.

- Grafo fuertemente conexo --> para un grafo dirigido, si existe un camino desde un vértice a cualquier otro nodo. 
- Un grafo dirigida puede ser conexo (si lo es sin considerarlo dirigido) o fuertemente conexo.
#### Implementaciones 

- Implementación estática 
	- Conjunto de nodos y matriz de adyacencia.

- Implementación dinámica
	- Lista de adyacencia que incluye conjunto de nodos




