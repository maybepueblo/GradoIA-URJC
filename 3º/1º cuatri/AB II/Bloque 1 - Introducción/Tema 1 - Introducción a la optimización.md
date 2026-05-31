## ¿Qué es?
- Disciplina fundamental en campos de ciencia como la informática, inteligencia artificial o la investigación operativa.
- Es el proceso de intentar encontrar la **mejor solución posible** a un problema (tiempo limitado de normal).
- La búsqueda de la **solución óptima** a un problema de optimización.

Por ende, consiste en el proceso para encontrar el valor de unas variables de decisión (en base a restricciones) para los que una función matemática (objetivo) alcance su min o max.

**Formalismo**
- **Representación:** Encargada de codificar las soluciones factibles para su manipulación. Determina el tamaño (cardinalidad) del espacio de búsqueda (SS) de cada problema
- **Objetivo:** Describe el propósito que se debe alcanzar para una repre dada. Mates que expresan la tarea a hacer.
- **Función de evaluación**: Asociamos a cada solución factible un valor que da calidad. Es una correspondencia f entre puntos del espacio de sols y R

Dominio X y función objetivo $f(x):x\in X \rightarrow R$ tenemos que encontrar un x* que verifique:$$x*\in X:f(x*)\geq f(x), \forall x\in X$$
La optimización combinatoria es un problema donde tenemos que encontrar un objeto entre un conjunto finito o al menos contable de posibilidades.

**Solución a un problema de optimización**
- Viene dada por los valores que toman las variables de decisión del problema.
- Un conjunto de valores particular asociado a las variables de decisión se llama "solución factible" cuando cumple las restricciones del problema de optimización.
- Las soluciones infactibles pueden ser útiles en ocasiones durante el proceso de búsqueda de la solución óptima.

## Problema de optimización

**Óptimos**
- **Global**: Con problema de optimización ($f$, SS, F) decimos que una sol. factible $x\in F⊆ SS$ es un óptimo (máximo) global si:$$y\in F\rightarrow f(x)\geq f(y)$$
- **Local**: Dado el problema de optimización de antes y una vecindad N decimos que la solución factible $x\in F⊆ SS$ es un óptimo (máximo) local con respecto a N si:$$y\in F\rightarrow f(x)\geq f(y)$$
**Vecindad de una solución**
Dada una solución $x \in SS$, la vecindad $N(x)$ de esa solución es un subconjunto del espacio de soluciones que contiene soluciones que están "próximas" a la solución considerada.

**Movimiento**
En una vecindad N(x) de una solución x se encuentran todas las soluciones $y\in N(x)$ accesibles desde x a traves de un movimiento.

Dicho de otro modo, dada una solución x, cada solución de su vecindad $y\in N(x)$ puede alcanzarse u obtenerse directamente desde x mediante una operación llamada movimiento.

**Distancia entre soluciones**
- Dado SS para un problema podemos definir una función distancia $dist(x, y)$ entre cualquier par de puntos $x, y\in SS$: $$dist: SSxSS \rightarrow R$$
- Se puede definir la vecindad $N(x)\subseteq SS$ de la solución x como:$$N(x)=\{y\in SS:dist(x,y)\leq\epsilon\}$$
- Un ejemplo es la distancia euclídea

**Tipos de problemas de optimización según complejidad**
- Los fáciles
	- Lineales - método simplex
	- difíciles (NP-hard):
		- No garantizamos encontrar la mejor sol en tiempo lógico
		- Mayoría de problemas
		- Procedimientos eficientes para encontrar good sols.

![[Pasted image 20260528125244.png]]

**Complejidad algorítmica**
- Podemos resolver en tiempo polinómico cuando el tiempo de ejecución se relaciona con el tamaño de entrada con fórmula polinómica. Se denomina $P$ a estos problemas
	- Tiempo razonable pa resolverlos en equipos recientes
- Otros son difíciles de resolver, no tenemos polinómicos.
	- En algunos sabemos se puede saber en P si un valor se corresponde con la sol del problema. Estos se llaman NP.
		- Ejemplo: raíz cuadrada

Todo problema P es a su vez NP. Los NP-completos son aquellos que no tienen algoritmo polinómico que los resuelva.
- No demostrado, creemos que no existe
- Se puede verificar una solución en tiempo polinómico.

Los NP-hard son aquellos que no tienen ningún algoritmo polinómico que permita verificar una solución.

![[Pasted image 20260528125644.png]]

## Optimización combinatoria
Es un problema que consiste en **encontrar un objeto** entre un **conjunto finito** (o al menos contable) de posibilidades.
- Número natural
- Permutación
- Estructura de grafo
- Etc...

Decimos que siempre existe un algoritmo exacto para obtener la solución óptima.
- Exploramos todo el conjunto de soluciones.

Ello es **ineficiente**, el tiempo crece de forma exp. con el tamaño del problema. 

**Ejemplos:** TSP, QAP, SP, etc...

**Tipos**
- Permutaciones - ordenación
- Binarios - pertenencia
- Enteros - cardinalidad

## Cómo abordar problemas de optimización

- **Exactos**
	- Solución óptima
	- Tiempo invertido para encontrarla en un NP-hard puede llegar a ser desproporcionado
	- Son de utilidad cuando el tamaño del problema es pequeño
- **Heurísticos/Metaheurísticos**
	- Dan una buena solución del problema pero no necesariamente la solución óptima
	- El tiempo invertido puede ser muy reducido.
	- Son de utilidad cuando el tamaño del problema es grande y se requiere una solución en un corto espacio de tiempo.












