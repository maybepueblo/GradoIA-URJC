## Diseño y calidad de funciones heurísticas
El algoritmo A* ([[Tema 3 - Busqueda heurística]]) es uno de los métodos más conocidos en heurísticas. Usa una función de evaluación f(n) = g(n) + h(n) siendo g(n) el coste real desde el estado inicial hasta el nodo n, y h(n) una estimación heurística del coste desde n hasta el estado meta
**Preguntas clave**
¿Cómo encontrar funciones heurísticas optimistas?
¿Cómo distinguir entre heurísticas buenas y malas?
¿Cúal es la complejidad de A* y cómo optimizarlo?

Una función heurística es **optimista** si siempre subestima el coste real de llegar al estado meta. Por ejemplo, en el problema del 8-puzzle, la heurística de "número de piezas descolocadas" es optimista porque nunca sobreestima el número de movimientos necesarios para resolver el puzzle.

La **distancia de Manhattan** es más informada que el número de piezas descolocadas, ya que siempre es mayor o igual que h_a*.

**Calidad de las funciones heurísticas**
Una heurística es mejor cuanta más información tenga, es decir, entre dos posibles interpretaciones de una heurísticas, si se cumple que h1*(n) >= h2*(n) entonces h1 es más informada que h2.
**Teorema**: Si h1∗​ es más informada que h2∗​, entonces A* con h1∗​ expandirá menos nodos que A* con h2∗​.

**Complejidad**
Si h(n) = h*(n) A* tiene complejidad lineal. Pero si h(n) = 0, A* degenera en búsqueda de coste uniforme.

En la práctica, el error heurístico tiende a crecer linealmente con la distancia al estado meta, pero A* sigue siendo más eficiente que los métodos no informados.
## Búsqueda online
Enfoque que combina búsqueda y ejecución de acciones en tiempo real. A diferencia de los métodos **offline** (plan completo generado antes de ejecutar), los métodos en línea **intercalan la búsqueda con la acción**

**Ciclo de búsqueda en línea**
1. Percibir el estado actual s
2. Aplicar un método de búsqueda para decidir la siguiente acción a
3. Ejecutar la acción y observar el nuevo estado s'

**Indicaciones**
- El espacio de búsqueda es demasiado grande para explorarlo completamente
- No se dispone de un modelo determinista del entorno (que no haya "mapa" del mundo)

**Medida de eficiencia**: El **índice competitivo**, que compara el coste del camino real del agente con  el coste del camino óptimo. Puede ser infinito si hay acciones irreversibles
## Búsqueda con horizonte
Técnica usada en la búsqueda en línea para limitar la profundidad de la búsqueda. En lugar de buscar hasta el meta, el agente busca k acciones hacia adelante y luego decide la siguiente acción a ejecutar.

**Proceso**
1. Generar el conjunto Hk de estados alcanzables en k acciones
2. Elegir el estado s* en Hk con el menor valor de f*
3. Ejecutar la primera acción en el camino hacia s*
4. Repetir el proceso desde el nuevo estado

**Optimización**: Si la heurística es consistente, se pueden podar ramas del árbol de búsqueda que no prometen mejorar la solución actual.

**Ejemplo**
- **Estado actual**: s = *A*, horizonte k = 2
- Se generan todos los estados alcanzables en 2 acciones y se elige el camino con el menor f*
- Se ejecuta la primera acción de ese camino y se repite el proceso desde el nuevo estado