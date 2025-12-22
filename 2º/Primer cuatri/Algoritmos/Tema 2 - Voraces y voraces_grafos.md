### Voraces
Los algoritmos voraces son una técnica que construye soluciones paso a paso tomando decisiones óptimas de forma local, sin reconsiderar decisiones anteriores. Es decir, tomamos decisiones en base a lo que tenemos que decidir ahora, no nos importa lo anterior.

**Características principales**
- Solución de forma iterativa
- Decisión óptima en cada paso
- Decisiones tomadas se consideran definitivas y no se reconsideran
- Buscan optimizar un objetivo
#### Componentes esenciales
1. **Conjunto de candidatos**
2. **Función de selección** (mejor candidato en cada paso)
3. **Función de factibilidad** (verifica si la selección es válida)
4. **Función solución** (determinamos si hemos alcanzado una solución)
5. **Función objetivo** (evaluamos lo óptima que es la solución)
#### Ventajas y desventajas
**Ventajas**
- Sencillo de implementar
- Eficiencia computacional (complejidad polinómica), véase [[Complejidad Algorítmica]]
- Encuentran la solución óptima en varios problemas
**Desventajas**
- No siempre hay solución óptima
- La no reconsideración de decisiones puede llevar a óptimos locales
- Es dificil encontrar la función de selección adecuada
- Compleja demostración formal de optimalidad
#### Aplicaciones
1. **Problema del cambio de monedas**
	- **Objetivo** --> Devolver cantidad M usando el mínimo número de monedas
	- **Estrategia** --> Seleccionar siempre la moneda de mayor valor posible
2. **Minimización del tiempo de espera en sistema**
	- **Objetivo** --> Minimizar el tiempo medio de espera de n clientes
	- **Estrategia** --> Ordenar los clientes por tiempo de servicio creciente
3. **Problema de la mochila fraccionaria**
	- **Objetivo** --> Maximizar el valor de objetos en una mochila con capacidad limitada
	- **Estrategia** --> Seleccionar objetos por mayor ratio valor/peso
	- Se permiten fracciones de objetos
4. **Planificación con plazo fijo**
	- **Objetivo** --> Maximizar beneficio realizando tareas antes de su fecha límite.
	- **Estrategia** --> Ordenar tareas por beneficio decreciente.
	- Cada tarea tiene un beneficio tope.
#### Estructura general

```python
función voraz(C: conjunto): conjunto
    S ← ∅
    mientras C ≠ ∅ y no solución(S) hacer
        x ← seleccionar(C)
        C ← C \ {x}
        si factible(S ∪ {x}) entonces
            S ← S ∪ {x}
        fin_si
    fin_mientras
    si solución(S) entonces
        devolver S
    si_no
        devolver ∅
    fin_si
fin_función
```
### Voraces aplicado a grafos

#### Introducción a los Algoritmos Voraces
Los algoritmos voraces son estrategias de resolución de problemas que toman decisiones localmente óptimas en cada paso, con la esperanza de encontrar una solución global óptima. En el contexto de grafos, estos algoritmos se aplican a diversos problemas de optimización.
#### Árboles de Recubrimiento Mínimo
##### Definición del Problema
El objetivo es encontrar un subgrafo conexo T de un grafo no dirigido y ponderado G = (V,E), que conecte todos los vértices de G y cuya suma de pesos de aristas sea mínima.

- Si el grafo es conexo, la solución será necesariamente un árbol.
##### Aplicaciones
- Diseño de redes (telefónicas, eléctricas, hidráulicas, de ordenadores, carreteras)
- Construcción de redes de mínimo coste
- Identificación de cuellos de botella
- Enrutamiento para evitar ciclos
- Algoritmos de agrupamiento (clustering)
##### Algoritmo de Kruskal
**Funcionamiento:**
1. Ordena las aristas de menor a mayor peso
2. Construye el árbol a partir de varias componentes conexas
3. Incluye una arista solo si une dos componentes conexas diferentes
4. Termina cuando solo hay una componente conexa
**Implementación:**
- Complejidad: O(|E| log |V|) con una implementación eficiente
- Utiliza la estructura de datos union-find para la fusión de componentes conexas
##### Algoritmo de Prim
**Funcionamiento:**
1. Comienza con un vértice arbitrario como raíz
2. En cada iteración, añade la arista de menor peso que conecta el árbol parcial con un nuevo vértice
3. Continúa hasta que todos los vértices están incluidos
**Implementación:**
- Complejidad: O(|E| log |V|) con una implementación eficiente usando una cola de prioridad

>[!WARNING]
> Kruskal > Prim (todo lo de prim se puede hacer con kruskal pero no al revés)
#### Caminos Mínimos: Algoritmo de Dijkstra
##### Definición del Problema
Dado un grafo dirigido y ponderado G = (V,E) con pesos positivos y un vértice de origen v, el objetivo es determinar la longitud mínima del camino desde v hasta todos los demás vértices.
##### Funcionamiento del Algoritmo
1. Mantiene dos conjuntos de nodos: S (seleccionados) y C (candidatos)
2. Inicializa las distancias desde el origen a todos los nodos
3. En cada iteración, selecciona el nodo de C con menor distancia y lo añade a S
4. Actualiza las distancias de los nodos adyacentes al seleccionado
5. Repite hasta que todos los nodos estén en S
**Implementación:**
- Complejidad: O(|V|^2) con implementación básica, O(|E| log |V|) con cola de prioridad (heap de Fibonacci)
#### Heurísticas Voraces
##### Coloreado de Grafos
**Problema:** Asignar colores a los vértices de un grafo de manera que vértices adyacentes tengan colores diferentes, minimizando el número de colores utilizados. **Heurística:**
1. Elige un color
2. Colorea todos los vértices posibles con ese color
3. Repite con un nuevo color hasta colorear todo el grafo
##### Problema del Viajante de Comercio
Encontrar un circuito hamiltoniano de coste mínimo en un grafo. 
**Heurísticas:**
1. Vecino más cercano: En cada paso, elige el vértice no visitado más cercano.
2. Basada en Kruskal: Selecciona aristas de menor coste, asegurando la formación de un circuito.