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
#### Eficiencia Algorítmica
##### Comparación de algoritmos
La eficiencia de un algoritmo mide los recursos empleados durante su ejecución, tales como ***tiempo***, ***espacio*** (memoria) y ***número de procesadores***. 

En términos de tiempo, dependemos de varios factores: datos de entrada, calidad de código generado, velocidad del procesador y complejidad del algoritmo. Podemos ver dos enfoques para estudiar el tiempo de ejecución:
- **Teórico** : Estimamos el comportamiento del algoritmo sin necesidad de ejecutarlo, independiente del ordenador.
- **Real** : Medimos el tiempo de ejecución en un caso específico y en un ordenador particular.

##### Complejidad Algorítmica

>[!NOTE] **Referencias**
>Cabe destacar que este apartado de algoritmos tiene mucho que ver con la asignatura de **[[Estructura de datos]]**, en concreto con el apartado de ejercicios de **
>[[Complejidad Algorítmica]]**

Con esto determinamos la eficiencia del algoritmo en función del tamaño de entrada **n**, expresada en términos de "pasos" o número de instrucciones.

###### Ejemplos de complejidad
1. **Suma de componentes de un vector**

```
suma = 0
for j in range(1, n+1):
	suma += c[j]
```

- **Complejidad** --> T(n) = k · n, ya que se ejecutan veces el cuerpo del bucle.

2. **Producto de dos matrices nxn**

```
for i in range(1, n+1):
	for j in range(1, n+1):
		c[i, j] = 0
		for k in range(1, n+1):
			c[i, j] += a[i, k] * b[k, j]
```

- **Complejidad** --> T(n) = k · n^3, dado que hay tres bucles anidados.

3. **Ordenación de un vector mediante comparación**

```
for i in range(1, n):
	for j in range(1, n-i):
		if c[j] > c[j+1]:
			c[j], c[j+1] = c[j+1], c[j]
```

- **Complejidad** --> T(n) = n(n-1)/2, que es aproximadamente O(n^2).

4. **Búsqueda secuencial**

```
i = 1
while i < n and c[i] != elem:
	i += 1
if i > n:
	i = 0
```

- **Complejidad** --> Varía entre T(1), T(n/2) y T(n), dependiendo de cuándo se encuentre el elemento.

###### Medidas asintóticas

- **Tmax(n)** --> Tiempo máximo para una entrada de tamaño n (caso peor)
- **Tmin(n)** --> Tiempo mínimo (caso mejor).
- **Tmed(n)** --> Tiempo medio (considerando que todas las secuencias de entrada son equiprobables).

###### Notaciones asintóticas

1. **Notación O** (Cota superior):
	1.  Se estudian funciones que crecen tan rápido como la función dada. Garantiza que el tiempo de ejecución no será mayor a esa cota.
	2. Ejemplo. Si f(n) = n^2 + 100, entonces f(n) pertenece a O(n^2).
2. **Notación Ω** (Cota inferior): 
	1. Se estudian funciones que crecen tan lento como la función dada. Garantiza un tiempo mínimo para el algoritmo.
	2. Ejemplo. 5n^2 pertenece a Ω(n^2) porque crece al menos tan rápido como n^2. 
3. **Notación Θ** (Orden exacto):
	1. Define el comportamiento exacto de una función. Si f pertenece a O(g) y f pertenece a Ω(g), entonces f pertenece a Θ(g)

###### Cálculo de eficiencia

- **Bucles** --> El número de iteraciones se multiplica por el tiempo que toma una iteración.
- **Sentencias condicionales** --> Se toma el máximo entre las ramas ***if*** y ***else***. 
- **Funciones recursivas** --> Se resuelven mediante métodos como la expansión de recurrencias o árboles de recursividad.

