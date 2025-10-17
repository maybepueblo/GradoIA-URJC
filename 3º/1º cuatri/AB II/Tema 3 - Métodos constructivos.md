## Greedy Randomized Adaptive Search Procedure (GRASP)
Se trata de un **algoritmo constructivo multiarranque**, véase [[Tema 2 - Introducción a las heurísticas y metaheurísticas]]

Se conforma por dos fases:
1. **Fase constructiva** - Construimos una nueva solución en cada iteración
	- hacemos una lista de candidatos (CL)
	- usamos criterio de selección voraz para crear una lista restringida de candidatos (RCL)
	- pillamos un vértice de la RCL de forma aleatoria
	- actualizamos el conjunto de candidatos nuevamente
2. **Fase de búsqueda local**
	- aplicada a cada solución construida en cada iteración, de forma independiente.
	- el método finaliza en un óptimo local
	- puede ser sustituido por otro procedimiento de búsqueda más avanzado como por ejemplo otra metaheurística

**Consideraciones de la fase constructiva**
La variante más común de GRASP añade a la RCL los mejores candidatos de acuerdo con un **criterio voraz** de selección.

Existen variantes que añaden en función de un umbral de calidad, dada la función $$\mu = mejor +\alpha(mejor-peor)$$
Siendo $\alpha\in[0, 1]$ un parámetro de búsqueda:
- Si $\alpha=0$ solo entran los mejores elementos en la RCL, siendo el algoritmo completamente voraz.
- Si $\alpha=1$ entra cualquier elemento en la RCL, siendo el algoritmo completamente aleatorio.
- Permite que la RCL sea adaptativa y tenga un tamaño variable en cada iteración.

### Extensiones
- Funciones de desplazamiento -> asignamos diferentes probabilidades de ser escogidos a los elementos que formarán parte de la RCL. 
- GRASP reactivo -> Implica una modificación del parámetro $\alpha$ en función del problema a lo largo de la ejecución. 
- Randomized-Greedy -> invierte las etapas de la RCL. Primero seleccionamos un conjunto de forma aleatoria y después de entre los seleccionados, elegimos el mejor de ellos.
## Iterated Greedy
Procedimiento voraz basado en construcción de soluciones, Tiene dos etapas, una constructiva y otra "destructiva". 

Se considera un procedimiento rápido y eficaz.

Construimos de forma iterativa, centrándonos en pillar la mejor opción en un momento concreto, teniendo un conjunto de candidatos que nos llevan a una solución y una función de selección que busca el mejor candidato para la siguiente iteración.

Esto nos limita, pues tomar la decisión en un punto determinado no asegura ser lo mejor para la solución final. En ocasiones tomar una decisión muy buena en un punto determinado puede obligar a tomar decisiones muy malas posteriormente. 

**Fases del algoritmo**
- *Algunas fases del algoritmo*
	- Construimos una solución inicial como punto de partida
	- Construida la solución, la destruye parcialmente y vuelve a construir.
	- Si es aceptada puede, de manera opcional, someterse a una fase de búsqueda local
- *Condiciones de parada*
	- iteraciones
	- tiempo
	- que no haya mejora