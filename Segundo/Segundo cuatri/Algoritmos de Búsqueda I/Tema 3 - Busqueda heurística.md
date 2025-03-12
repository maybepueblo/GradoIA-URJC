## Búsqueda Primero el Mejor
Estrategia que selecciona el nodo más prometedor para expandir, basándose en una función heurística. Esta técnica utiliza información adicional (lo que conocemos como **heurística**) para guiar la búsqueda.
### Conceptos básicos
- **Heurística** -> Regla o método que ayuda a encontrar soluciones rápidamente (no garantiza la optimalidad). En búsqueda, una heurística es una función que estima el coste de llegar desde un nodo x hasta el nodo meta.
	- **Interpretación fuerte** > Facilita la resolución del problema, pero no garantiza una solución óptima.
	- **Interpretación débil** > Mejora el rendimiento promedio del método de resolución, pero no garantiza una mejora en el peor caso.
- **Función heurística** (h*(n))->  Función que estima el coste desde el nodo n hasta el meta más cercano. Una heurística es **optimista**/**admisible** si nunca sobrestima el coste real, es decir $$h*(n) < h(n) \space \forall n$$
	- *Ejemplo* -> En el problema de bloques, una heurística común es el número de bloques mal colocados. En la búsqueda de rutas, la distancia en línea recta hasta el destino es heurística optimista
### Búsqueda Avara
Variante de la vista anteriormente en este md, aquí seleccionamos el nodo con el valor heurístico más bajo, es decir, el nodo que parece estar más cerca del objetivo. Sin embargo, no es óptimo, ya que no tiene en cuenta el coste acumulado para llegar al nodo.
- *Ejemplo* -> En un espacio de estados con nodos A, B, C y D, donde h*(A) = 7, h*(B) ? 2, h*(C) 
  = 5, y h*(D) = 0, la avara elegiría primero B, luego C, y finalmente D. Sin embargo, si el coste para llegar a D es muy alto, no se garantiza la solución óptima.
#### Limitaciones
- **No es óptima**
- **Complejidad**
## Algoritmo A* 
Este algoritmo conocido como algoritmo A estrella es una de las técnicas más populares en búsqueda heurística. Combinamos el coste real para llegar a un nodo (**g(n)**) con una estimación heurística del coste restante **h*(n)** para seleccionar el nodo más prometedor

**Función de evaluación**
En A*, la función de evaluación es f(n) = g(n) + h*(n) donde:
- g(n) es el coste real desde el nodo inicial hasta n
- h*(n) es una estimación desde n hasta la meta

**Estrategia**
Expandimos el nodo con el valor f(n) más bajo en cada paso, lo que garantiza que encontremos una solución óptima si la heurística es **optimista**
- Por ejemplo, si tenemos un grafo con nodos A, B, C, D, E y F, donde g(A) = 0, h*(A) = 366