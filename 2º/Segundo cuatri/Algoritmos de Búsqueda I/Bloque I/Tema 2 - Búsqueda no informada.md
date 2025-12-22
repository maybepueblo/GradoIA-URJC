## Método general de búsqueda
Decimos que la búsqueda no informada es una técnica para resolver problemas de búsqueda en un espacio de estados. En este método, no tenemos conocimiento previo sobre el problema más allá de su definición.
Por ende, sólo podemos distinguir si un estado es objetivo (meta) o no, y no hay información sobre cómo de cerca de la solución estamos
### Conceptos clave
- **Árbol de búsqueda**
	- Representación gráfica de estados y transiciones
	- Nodo = estado, ramas = acciones
- **Lista de abiertos**
	- Nodos en espera a expandirse
	- El algoritmo manda sobre cómo extraemos (FIFO, LIFO, etc.)
- **Expansión de nodos**
	- Generar sucesores
- **Completitud**
	- Lo es si garantiza encontrar solución (si la hay)
- **Optimalidad**
	- Algoritmo óptimo = solución de menor coste
- **Complejidad**
	- ***Tiempo***
	- ***Espacio***

Seguimos en este método los siguientes pasos:
1. Iniciamos lista abierta con el estado inicial
2. Repetimos hasta que se vacíe la lista abierta o encontremos una solución:
	- Seleccionamos primer nodo de la lista
	- Si es meta = devolvemos la solución
	- Expandimos el nodo generando sucesores
	- Añadimos los sucesores según el orden definido por el algoritmo
## Amplitud y profundidad
### Amplitud BFS
- **Estrategia**: Exploramos por niveles, expandiendo todos los de un nivel antes del siguiente.
- **Implementación**: Cola FIFO para la lista abierta. Nuevos nodos al final de la lista
- **Ventajas**
	- **Completo** -> Solución si existe
	- **Óptimo** -> Menor número de pasos (si todos los operadores tienen el mismo coste)
- **Desventajas**
	- **Complejidad en espacio** -> Almacena todo un nivel antes de pasar al siguiente
	- **Complejidad en tiempo** -> Peor caso = explorar todos los nodos del árbol
#### Ejemplo
Suponiendo que estás en **A** y quieres ir a **B**. Este algoritmo exploraría todas las ciudades conectadas a A (nivel 1), luego las ciudades conectadas a esas (nivel 2), y así sucesivamente hasta encontrar **B**
### Profundidad DFS
- **Estrategia**: Exploramos por ramas, siguiendo hasta el final, para luego retroceder y probar otro camino
- **Implementación**: Pila LIFO para la lista abierta. Los nuevos nodos se añaden al principio de la lista
- **Ventajas**
	- **Eficiencia en espacio**: Almacena los nodos de la rama actual = menos memoria
- **Desventajas**
	- **No es completo**: En estados infinitos, se puede perder
	- **No es óptimo**: Puede haber solución, pero no tiene por qué ser la más corta
#### Ejemplo
Si estás en **A**, podríamos ir primero a **S**, luego **F** y luego a **B**, sin explorar otras rutas hasta haber agotado esta rama.
### Coste uniforme UCS
- **Estrategia**: Similar a amplitud, pero en vez de por el menos profundo, lo hacemos por el nodo con menor coste acumulado
- **Implementación**: Cola de prioridad para la lista abierta, se ordenan por coste acumulado
- **Ventajas**
	- **Completo**: si existe sol. la encuentra
	- **Óptimo**: encuentra la solución con menor coste total
- **Desventajas**
	- **Complejidad en tiempo y espacio**: Similar a amplitud, costoso en problemas grandes
#### Ejemplo
Si estás en **A** y quieres llegar a **B**, UCS eligiría la ruta con menor distancia total
### Profundidad Limitada DLS
- **Estrategia**: Variante de DFS que establece un límite de profundidad para evitar que el algoritmo se pierda en ramas infinitas
- **Implementación**: Similar a profundidad, pero nos detenemos si alcanzamos el límite de profundidad
- **Ventajas**
	- **Control sobre profundidad**: Evita que el algoritmo se pierda en ramas infinitas
- **Desventajas**
	- **No es completo**: Si está más allá del límite, no la encontrará
#### Ejemplo
Si el límite es 2, el algoritmo exploraría solo dos niveles de profundidad. Si la solución está en el nivel 3, no la encontraría
### Profundidad Iterativa IDS
- **Estrategia**: Combina DFS y DLS. Realizando múltiples búsquedas en profundidad con límites incrementales hasta encontrar la solución.
- **Implementación**: Comienza con un límite de profundidad de 0 y lo incrementa en cada iteración
- **Ventajas**
	- **Completo**: Si existe sol. la encuentra
	- **Óptimo**: Encontramos solución con menor coste (si los operadores tienen el mismo coste)
	- **Eficiencia en espacio**: Similar a DFS, pidiendo menos memoria que BFS
- **Desventajas**
	- **Repetición de trabajo**: En cada iteración, se repite el trabajo de las iteraciones anteriores
#### Ejemplo
Si está en el nivel 3 la solución, el algoritmo exploraría primero con límite 0, luego con límite 1, luego con límite 2 y finalmente con 3, donde encontraría la solución.
## Complejidad
La complejidad de estos algoritmos se evalúa en términos de tiempo y espacio. Aquí tenemos una comparación detallada:

| **Algoritmo**           | **Completitud** | **Optimalidad** | **Complejidad en tiempo** | Complejidad en espacio |
| ----------------------- | --------------- | --------------- | ------------------------- | ---------------------- |
| *Amplitud*              | Sí              | Sí (*)          | O(b^d)                    | O(b^d)                 |
| *Coste Uniforme*        | Sí              | Sí              | O(b^d)                    | O(b^d)                 |
| *Profundidad*           | No              | No              | O(b^d) o inf              | O(bd)                  |
| *Profundidad Iterativa* | Sí              | Sí (*)          | O(b^d)                    | O(bd)                  |
( * ) Solo es óptimo si todos los operadores tienen el mismo coste

Vamos a explicar brevemente:
- **Complejidad en tiempo** -> Número de nodos que el algoritmo ha de expandir antes de encontrar una solución. El peor caso es la exponencial, siendo b el factor de ramificación y d la profundidad de la solución.
- **Complejidad en espacio** -> Cantidad de memoria que el algoritmo necesita para almacenar nodos durante la búsqueda. BFS y UCS tienen una complejidad de espacio exponencial, ya que almacenan todos los nodos antes de pasar al siguiente nivel. DFS y IDS tienen una complejidad bd ya que solo almacenan los nodos de la rama actual.
## Ejemplo práctico 
Demos un ejemplo con todos los casos
#### Problema de Encontrar Rutas
Supongamos que queremos encontrar la ruta más corta entre dos ciudades. Cada ciudad es un estado, y los operadores son las rutas entre ciudades. El coste de un operador es la distancia entre las ciudades.
- **BFS**: Exploraría todas las rutas de longitud 1, luego las de longitud 2, etc., hasta encontrar la ruta más corta.
- **DFS**: Elegiría una ruta y la seguiría hasta el final antes de probar otra. Podría encontrar una ruta, pero no necesariamente la más corta.
- **UCS**: Elegiría siempre la ruta con la menor distancia total, incluso si eso significa pasar por más ciudades.
- **DLS**: Exploraría solo hasta un límite de profundidad. Si la solución está más allá del límite, no la encontraría.
- **IDS**: Exploraría con límites incrementales hasta encontrar la solución, asegurándose de encontrar la ruta más corta.