En este documento nos referimos como PSO al *Particle Swarm Optimization*
# Introducción
Nos basamos en el comportamiento de bandadas de pájaros o bancos de peces donde:
- Cada animal (**partícula**) vuela por el espacio de soluciones.
- Su **velocidad** y **posición** se ajustan en función de sus propios valores y los del enjambre. 
- Las partículas **se mueven hacia posiciones mejores** según la función objetivo.
## Características principales
- Metaheurística poblacional, véase [[Tema 2 - Introducción a las heurísticas y metaheurísticas]]
- Cada **partícula** representa una **solución** al problema
	- La posición y la velocidad de la partícula son dos vectores de *n* dimensiones.
- Se suele comenzar con una **población aleatoria**
- La actualización de posición y velocidad sigue unas fórmulas definidas aquí.
- Es un algoritmo intuitivo y flexible.
- Capaz de manejar funciones objetivos de naturaleza estocástica.
- **No depende del gradiente de la función objetivo**
- Fácil de paralelizar: podemos actualizar cada partícula en paralelo.
- Requiere pocos parámetros
- En algunos casos tarda en converger
# Actualizar las partículas
## Posición
En la iteración $t+1$ se actualiza la posición de cada partícula usando la nueva velocidad para $t+1$:$$X^i(t+1)=X^i(t)+V^i(t+1)$$
Es una suma entre vectores. En un problema con dos dimensiones $x$ e $y$, se realiza de la manera:$$\begin{aligned}x^i(t+1)=x^i(t)+v^i_x(t+1)\\y^i(t+1)=y^i(t)+v^i_y(t+1)\end{aligned}$$
## Velocidad
La velocidad en la iteración $t+1$ se obtiene a partir de una ecuación más elaborada con diferentes elementos:$$V^i(t+1)=wV^i(t)+c_1r_1(p_{best}^i-X^i(t))+c_2r_2(g_{best}-X^i(t))$$
Donde:
- $p_{best}^i$ es la posición donde la partícula $i$ ha obtenido el mejor valor de función objetivo (*particle best*)
- $g_{best}$ es la posición con mejor valor de función objetivo obtenida por el enjambre (*global best*) 
- $r_1$ y $r_2$ son valores aleatorios entre 0 y 1 calculados según una distribución uniforme.
- $w$, $c_1$ y $c_2$ son valores constantes que se reciben como parámetros de entrada del algoritmo:
	- $w$ es la inercia. Su valor está entre 0 y 1. Determina el peso que se le da a la velocidad de la iteración anterior.
	- $c_1$ y $c_2$ son los coeficientes cognitivo y social, respectivamente. Permiten ajustar el peso entre los resultados de la partícula (explotación) y los del enjambre (exploración).
- Los valores $p_{best}^i$ y $g_{best}$ se actualizan en cada iteración.
# Pseudocódigo PSO
**Parámetros de entrada:** `numParticulas`, `maxIteraciones`, `w`, `c1`, `c2`

```
X = creaParticulasIniciales(numParticulas)
V = creaVelocidadesIniciales(numParticulas)
// Inicializamos los mejores valores (podemos en el primer paso)
pBest = X
gBest = obtenerMejor(X)
for t = 1 to t=maxIteraciones {
	V = actualizarVelocidades(w, c1, c2, pBest, gBest)
	// se actualizarán pBest y gBest al actualizar X
	X = actualizarPosiciones(X, V, pBest, gBest)
}
return gBest
```
# Selección de parámetros
Una configuración básica sería la siguiente:
- Número de particulas: 10
- Número de iteraciones: 100
- Inercia ($w$): 0.5
- Coeficiente cognitivo (c1): 0.5
- Coeficiente social (c2): 0.5

A partir de esos valores podemos ir modificando los parámetros:
- Si el enjambre se estanca pronto (sus partículas convergen y no mejoran más), subimos el número de partículas.
- Si la evolución muestra tendencia a mejorar en las últimas iteraciones, subimos el número de iteraciones.
- Se puede variar la inercia para explorar diferentes comportamientos del enjambre.
# Variantes
- Construcción de **enjambre inicial** con métodos alternativos
- Establecer una **velocidad máxima**: permite evitar comportamientos erráticos.
- Establecer una **posición máxima**: implementar *absorbing wall*, *reflecting wall* y *invisible wall*
- Diferente **condición de parada**:
	- max núm de iteraciones
	- cota de calidad
	- tiempo de ejecución
	- convergencia del enjambre: no hay cambios durante un tiempo determinado
- **Otros**: paralelizar, multi-enjambre....