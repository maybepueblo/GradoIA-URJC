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
- Por ejemplo, si tenemos un grafo con nodos A, B, C, D, E y F, donde g(A) = 0, h*(A) = 366, g(B) = 118, h*(B) = 329, etc. El algoritmo A* calcularía f(n) para cada nodo y expandiría primero el nodo con el mejor f(n)

**Pasos del algoritmo A****
1. **Inicialización** ->Comienza desde el nodo inicial s0 en la lista abierta
2. **Selección** -> Selecciona el nodo con el menor f(n) de la lista abierta
3. **Expansión** -> Expande el nodo seleccionado y genera sus sucesores
4. **Inserción** -> Inserta los sucesores en la lista abierta, ordenados por f(n)
5. **Terminación** -> Si se alcanza un nodo meta, devolvemos solución. Si la lista abierta está vacía, devolvemos un fallo.
 
 **Ejemplo de A* en Acción**

- **Ejemplo**: Supongamos que tenemos un grafo con nodos A, B, C, D, E y F, donde:
    - g(A)=0,  h∗(A)=8
    - g(B)=4,  h∗(B)=6
    - g(C)=3,  h∗(C)=6
    - g(D)=7,  h∗(D)=5
    - g(E)=10,  h∗(E)=0
    - g(F)=11,  h∗(F)=0
    
    El algoritmo A* calcularía f(n) para cada nodo y expandiría primero el nodo con el menor f(n). En este caso, A* no encontraría el mejor nodo meta E si la heurística no es optimista.
## Análisis del Algoritmo A*
Centrado en **completitud**, **optimalidad** y **complejidad**, así como en las propiedades de la función heurística utilizada.

**Completitud**
Decimos que el algoritmo es completo, lo que significa que siempre encontrará solución si existe (espacio finito y costes positivos)
- *Prueba de completitud* -> Si no encontramos solución debe haber un camino infinito. Sin embargo, como los costes son positivos, g(n) aumenta indefinidamente, haciendo que f(n) supere cualquier límite. 
**Optimalidad**
Si la heurística lo es, A* también. Encuentra así la solución con menor coste
- *Teorema de Optimalidad* -> La prueba se basa en que A* siempre expande el nodo con el menor f(n) y si h*(n) es optimista, f(n) no sobrestima el coste real.
**Consistencia**
Si para todo nodo ni y su sucesor directo nj se cumple que h*(ni) - h*(nj) <= c(ni, nj) donde esto último es el coste de operador que lleva de ni a nj. Si h*(n) es consistente, entonces f(n) crece monótonamente a lo largo de cualquier camino.
- *Lema 1*: Si h∗(n) es consistente, entonces f(n) crece de forma débilmente monótona en todos los caminos del árbol de búsqueda.
- *Corolario 1*: Si h∗(n) es consistente, A* expande todos los nodos nini​ tal que f(ni)≤f(nm), donde nm es el mejor nodo meta.
**Complejidad**
- **Complejidad en tiempo y espacio**: En el peor caso, la complejidad del algoritmo A* es exponencial en función del coste de la solución óptima (g_gorro​) y el coste mínimo de los operadores (ε). La complejidad en tiempo y espacio es O(b^{g_gorro/ε}), donde b es el factor de ramificación del árbol de búsqueda.
### **Ejemplo de Análisis**
- **Ejemplo**: En un grafo con nodos A, B, C, D, E y F, donde h∗(n) es consistente, A* expandirá todos los nodos con f(n)≤f(nm), asegurando que se encuentre la solución óptima