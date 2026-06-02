En este documento nos referimos al concepto por ACO, *Ant Colony Optimization*
# Introducción
Nos basamos en el comportamiento de búsqueda de alimento de las colonias de hormigas:
- Son capaces de encontrar rutas más cortas hacia su objetivo (comida) gracias a los **caminos de feromonas**:
	- Al recorrer un camino, depositan feromonas
	- A mayor número de hormigas por camino, más feromonas
	- La cantidad de feromonas determina la probabilidad de seguir dicho camino, aunque podemos explorar otros
	- Se evaporan las feromonas, variando caminos cuandoo la fuente de alimento se agota.
- Cada hormiga es un organismo simple e independiente.
## Características principales
- Es una metaheurística poblacional, véase [[Tema 2 - Introducción a las heurísticas y metaheurísticas]]
- El **recorrido** de cada hormiga construye una **solución** al problema.
- La **decisión** de qué camino tomar en cada punto viene dada por una **probabilidad** definida aquí.
- La **inicialización** de una hormiga suele ser **aleatoria**:
	- Las colocamos aleatoriamente en puntos de decisión (nodos del grafo)
	- Puede haber varias hormigas en el mismo nodo.
- Comenzamos con una **distribución de feromonas constante** en los puntos de decisión (típicamente nodos de un grafo).
- Las hormigas depositan feromonas en su recorrido.
- La **concentración de feromonas** se **actualiza** cuando todas las hormigas han completado el recorrido.
	- Es decir, cuando cada hormiga ha construido una solución.
# Algoritmo
## Ciclo de la hormiga
Cada una es un **agente independiente** con las siguientes características:
- Elige el siguiente punto de decisión (nodo) con una probabilidad en función de la distancia al nuevo punto y a la cantidad de feromona presente en la conexión (arista) desde el punto actual (i) hasta el nuevo punto (j).
- NO se permite visitar puntos ya visitados en el recorrido actual.
	- No hay ciclos.
- Al completar el recorrido, se actualiza la cantidad de feromona en cada una de las aristas (i, j) recorridas por la hormiga.
## Probabilidad de transición
Para una hormiga $k$ situada en el nodo $i$ y considerando moverse hacia el nodo $j$, la probabilidad de transición $p_{ij}^k$ se define generalmente como:$$p_{ij}^k=\frac{(𝜏_{ij})^\alpha(𝜂_{ij})^\beta}{\sum_{l\in N_i^k} (𝜏_{il})^\alpha(𝜂_{il})^\beta}$$
Donde:
- $𝜏_{𝑖𝑗}$ es la **intensidad**, o cantidad de feromona en el camino que conecta el nodo $i$ con el nodo $j$. Representa la experiencia acumulada y cuán deseable es ese camino según exploraciones anteriores.
- $𝜂_{𝑖𝑗}$ es la **visibilidad** del movimiento de $i$ a $j$. Heurística típicamente definida como la inversa de la distancia $𝑑_{𝑖𝑗}$ , es decir, $𝜂_{𝑖𝑗} = \frac{1}{𝑑_{𝑖𝑗}}$ . Cuanto menor sea la distancia, más atractiva será la transición.
- $𝛼 ∈ (0,1]$ es un parámetro que controla la influencia de la feromona en la probabilidad de transición. Si $𝛼$ es grande, las hormigas preferirán rutas con mucha feromona.
- $𝛽 ∈ (0,1]$ es un parámetro que controla la influencia de la visibilidad (o heurística). Si $𝛽$ es grande, las hormigas preferirán caminos más cortos.
- $𝑁_𝑖^𝑘$ es el conjunto de nodos disponibles para ser seleccionados como el siguiente paso desde el nodo $i$, aún no visitados por la hormiga $k$.
## Actualización de feromonas
Una vez que las hormigas hayan construido una solución, la cantidad de feromonas se actualiza con la siguiente fórmula:$$\tau_{ij}=\rho·\tau_{ij}+\sum_k\Delta\tau_{ij}^k$$
Donde:
- $\rho\in(0,1]$ es un coeficiente de modo que $(1-\rho)$ representa la **evaporación** de la feromona dado que es menor que 1.
- $\Delta\tau_{ij}^k$ es la cantidad de feromona que la hormiga $k$ deja en la arista $(i, j)$. Este valor normalmente depende de la calidad de la solución obtenida. Una fórmula típica para este valor es la siguiente:$$\Delta\tau_{ij}^k=\frac{Q}{L_k}$$
	- Donde $Q$ es una constante que suele valer 1, y $L_k$ es la longitud del camino recorrido por la hormiga $k$ que se corresponde con la calidad de la solución. A menor longitud, mayor cantidad de feromona se añade.
## Pseudocódigo ACO
**Parámetros de entrada:** `numHormigas`, `maxIteraciones`, $\rho$, $\alpha$, $\beta$, $Q$, $d$, `numNodos`

```
𝜏 = inicializaFeromonas() // Init a valores rand pequeños
S* = ∞                    // Init mejor solución (minimizar)
for t=1 to t=maxIteraciones {  // Bucle principal
	for k=1 to k=numHormigas {  // Recorrido de hormigas
		Hk = nodoAleatorio()  // Init hormiga en nodo aleatorio
		while |Hk| != numNodos {  // Itera mientras no visita                                        todos los nodos
			Hk = añadeNodoSegunProbabilidad(Hk, 𝜏, 𝛼, 𝛽)
		}
		Lk = evaluar(Hk)   // Evaluar hormiga
	}
	𝜏 = actualizaFeromonas(𝜏, 𝜌, 𝑄, 𝐿)  // Actualizar feromonas
	S* = actualizaBest(S*, 𝐻)   // Actualizar mejor solución
}
return S*   // Devolver mejor solución
```
# Algoritmo de la ruleta
El seleccionar un elemento en función de una probabilidad se suele hacer con el algoritmo de la ruleta.

![[Pasted image 20260602231100.png]]

Se compone de tres pasos principales:
- Calcular la probabilidad $p_i$ asociada a cada elemento.
- Dividir el intervalo $[0, 1]$ en segmentos proporcionales a $p_i$.
- Generar un número aleatorio $r\in[0,1]$ y elegir el elemento cuyo segmento contiene $r$.

Suponiendo que las probabilidades están almacenadas en $p_i$, un ejemplo de pseudocódigo puede ser el siguiente:

```
r = numeroAleatorio()  // Numero aleatorio entre 0 y 1
acumulado = 0
for i=0 to i=n-1 {
	acumulado = acumulado + pi
	if r <= acumulado 
		return i         // Indice del individuo seleccionado
}
```
# Selección de parámetros en ACO
Una configuración básica sería:
- Número de hormigas: 10
- Número de iteraciones: 100
- $\rho=0.9$, indica una evaporación del 10%
- $\alpha=0.5$, $\beta=1$, da mayor peso a la visibilidad (caminos cortos) frente a la intensidad.
- $Q=1$

A partir de estos valores podemos modificar los parámetros:
- Si el conjunto de hormigas se estanca pronto, subimos el número.
- Si la evolución muestra tendencia a mejorar en las últimas iteraciones, subimos número de iteraciones.
- Se pueden variar los coeficientes para explorar diferentes comportamientos:
	- Subir $\alpha$ incrementa el peso de la intensidad, de manera que se beneficia al recorrido más común entre las hormigas.
	- Subir $\beta$ incrementa el peso de la heurística (visibilidad)
	- Aumentar la evaporación (bajando $\rho$) ayuda a incrementar la exploración frente a la explotación (diversificación frente a intensificación)
# Variantes del ACO
- Diferentes métodos de **actualización de feromonas**:
	- *Elitista*: la hormiga que ha encontrado la mejor solución tiene más peso en la actualización
	- *Ranking*: varias hormigas actualizan las feromonas pero se pondera la actualización en función de la calidad obtenida.
- **ACO distribuido**: varias colonias de hormigas trabajan en paralelo y comparten información a través de hormigas "emigrantes".
- Implementación binaria, continua, multiobjetivo, ....