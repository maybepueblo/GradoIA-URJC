# Introducción
El procedimiento de **Recocido Simulado/Simulated Annealing** (**SA**) fue propuesto por Kirkpatrick et al. en 1983. Este está basado en el *"el principio de empeoramiento"*. Esto es, que permitimos movimientos que empeoran la función objetivo (movimientos ascendentes) para escapar de óptimos locales.

Su nombre se basa en la analogía entre un proceso de optimización y el **proceso termodinámico del recocido**
- **Elevamos la temperatura** de un sólido cristalino con defectos hasta una temperatura determinada (alta por lo general).
- Posteriormente, **el material se enfría muy lentamente**
- Este enfriado viene dado por una **función de temperatura** conocida como cola de enfriamiento.
- Esta nueva estructura tiene un **estado de energía de la red mínimo**

Traducido a la optimización, es un **algoritmo de búsqueda local** capaz de escapar de óptimos locales permitiendo que, dadas unas circunstancias, se **admitan movimientos que empeoren** la mejor solución encontrada hasta el momento.

En **búsqueda local**, perturbamos de forma paulatina (lentamente) una solución mientras producimos una mejora, de modo que el proceso acaba en óptimo local.

Por esto, la **parametrización** es determinante en su rendimiento.
## Resumen
Para evitar quedar atrapado en un **óptimo local**, el SA permite **movimientos de escape** que deben controlarse adecuadamente para no desviar la búsqueda cuando nos dirijamos hacia una buena solución.

Por ello, usamos una **función de probabilidad** que disminuye la probabilidad de movimientos de escape cuando la búsqueda avanza.
# Pseudocódigo
Dada una solución $x$, sea $f(x)$ el coste de dicha solución y $N(x)$ su vecindad.

1. Inicializar: solución inicial $x_0$; temperatura inicial $t_0 > 0$; función de reducción de temperatura $α$; número de repeticiones $nrep$; criterio de parada $C$;
2. Repetir
3.     Repetir
4.         Seleccionar aleatoriamente una solución $x$ de $N(x_0)$;
5.         $δ = f(x) − f(x_0)$; *diff_coste entre candidato y solución actual*
6.         Si $δ < 0$ entonces /* $x$ es mejor que $x_0$ * /
7.             $x_0 = x$;
8.         Si no /* $x$ es peor que $x_0$ * /
9.             Generar aleatoriamente $u$ de $U(0,1)$; *aceptación probabilística*
10.            Si $u < e^{(-δ/t)}$ entonces
11.                $x_0 = x$;
12.            Fin si
13.        Fin si
14.    Hasta que $i = nrep$;
15.    $t = α(t)$;
16. Hasta que $C$ sea verificado;

La probabilidad de que se produzca un incremento energético (δ) a temperatura **t** es:$$P[δ]=e^{δ/kt}$$
siendo **k** la constante de Boltzmann (no la consideramos de normal en el contexto de la optimización) y **t** es un parámetro de búsqueda.

Dada una **perturbación**:
- Aceptamos siempre que disminuya la energía.
- Aceptamos con cierta probabilidad si aumenta la energía. La probabilidad viene dada por la fórmula.

Veamos la analogía entre los procesos termodinámicos y los procesos de optimización:

| **Termodinámica**   | **Optimización combinatoria** |
| ------------------- | ----------------------------- |
| Estados del sistema | Soluciones factibles          |
| Energía             | Coste                         |
| Cambio de estado    | Solución del entorno          |
| Temperatura         | Parámetro de control          |
| Estado congelado    | Solución heurística           |
# Parametrización
Lo que solemos llamar temperatura (**t**) es un parámetro que controla la probabilidad de que se produzca un movimiento de escape.
- Cuando **t** es alto, se producen **movimientos de escape** (EM a partir de ahora) muy facilmente. Sin embargo, si es lo suficientemente pequeño, no se producen EMs y la búsqueda acaba en un **óptimo local**
- **Teóricamente** está probada la convergencia al óptimo cuando la temperatura se reduce lentamente. El problema es que los tiempos de cómputo no son asumibles.
## Decisiones a tomar
- **Genéricas**
	- Cómo controlar la temperatura:
		- Temperatura inicial $t_0$
		- Función de disminución $\alpha$
	- $nrep$
	- $C$
- **Específicas del problema**
	- Espacio de soluciones
	- Estructuras de vecindad
	- Función de coste
	- Obtención de la solución inicial $x_0$

La **temperatura inicial** ($t_0$) debe ser:
- Independiente de la solución
- Suficientemente alta como para aceptar al inicio casi libremente las soluciones del entorno.

La **temperatura final** ($t_f$) debería ser 0 aunque en la práctica el proceso converge antes:
- Si es muy baja, se desaprovecha tiempo
- Si es muy alta, no se alcanza un óptimo local
## Mecanismos de enfriamiento $\alpha$
- Basado en sucesivas temperaturas descendentes **fijadas por el usuario**
- **Descenso constante** de temperatura
- **Descenso geométrico**: $t_{i+1}=\alpha · t_i, \alpha\in[0.8,0.99]$
- **Criterio de Boltzmann**: $t_i = \frac{t_0}{1+log(i)}$
- **Esquema de Cauchy**: $t_i=\frac{t_0}{1+i}$
- **Lundi y Mees**: $t_{i+1} =\frac{t_i}{1+\beta·t_i}$ con $\beta$ muy pequeño.
## Configuraciones específicas
- La **solución inicial** $x_0$ la podemos obtener con métodos diversos: aleatorio, voraz, etc...
- Cualquier solución debe ser alcanzable desde cualquier otra a través de una **cadena de movimientos válidos**
- La generación de una vecindad y la evaluación de la probabilidad de aceptación de un movimiento deben ser **rápidos**