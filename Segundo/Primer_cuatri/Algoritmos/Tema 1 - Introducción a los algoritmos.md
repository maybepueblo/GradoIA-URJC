#### Problemas

Al resolver problemas en un ordenador tenemos que tener en cuenta las siguientes implicaciones:
- Diseñar un algoritmo para el problema
- Expresarlo como un programa
- Ejecutar dicho programa

##### Clasificación de problemas

Se han clasificado según su complejidad:

- **Años 30** --> Distinción entre problemas computables y no computables.
- **Años 50** --> Complejidad git de problemas computables.
- **Años 70** --> Clasificación formal de problemas computables en clases P (tiempo polinómico) y NP (tiempo polinómico en una máquina de Turing no determinista).

##### Reducción y complejidad de problemas

Esta reducción es un concepto importante en la complejidad computacional. Si se puede reducir un problema A a otro problema B, entonces una solución para B puede ser transformada en una solución para A. Si se encuentra un algoritmo en P para un problema NP-completo, entonces todos los problemas NP serían resolubles en tiempo polinómico.

#### Algorítmica

Estudio de los algoritmos de tres formas:

- **Diseño** --> Conocimiento de las técnicas para crear algoritmos eficientes, exactos y heurísticos.
- **Validación** --> Comprobar formalmente que el algoritmo produce resultados correctos para todas las entradas posibles.
- **Análisis** --> Medir el uso de recursos tales como tiempo y espacio.

##### Análisis de eficiencia

Analizar el rendimiento de un algoritmo es posible desde varios enfoques:

- **Empírico** --> A partir de experimentos y pruebas prácticas
- **Teórico** --> Análisis matemático.
- **Híbridos** --> Combinamos las anteriores (poco usado).

##### Técnicas de diseño de algoritmos

Algunas son:
- Divide y Vencerás (Divide and Conquer) 
- Algoritmos Voraces (Greedy)
- Programación Dinámica (Dinamic Programming)
- Vuelta Atrás (Backtracking)
- Ramificación y Poda (Branch and Bound)
- Algoritmos Probabilísticos (Probabilistic Algorithms)
- Metaheurísticas (Metaheuristics)

#### Problema del viajante de comercio (extra)

Problema clásico que consiste en encontrar la ruta más corta que pasa por N ciudades exactamente una vez y regresa al punto de origen. Se presenta como un ejemplo de problema que crece en complejidad de manera exponencial con el número de ciudades.

**Enlaces de interés**
[Traveling Salesman Problem Visualization (youtube.com)](https://www.youtube.com/watch?v=SC5CX8drAtU)
[The Traveling Salesman Problem (tum.de)](https://algorithms.discrete.ma.tum.de/graph-games/tsp-game/index_en.html)

