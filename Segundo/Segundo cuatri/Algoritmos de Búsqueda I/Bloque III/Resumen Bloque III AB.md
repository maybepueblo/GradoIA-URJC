## Problemas de satisfacción de restricciones
Para problemas donde tenemos una gran complejidad de representación del conocimiento como por ejemplo en su expansión además de conseguir mantener el mismo, intentamos tomar en cuenta la "estructura" de los estados y además definir un estado no por su nombre sino por el conjunto de sus propiedades.

**Estructura de estados**
- Está compuesto por un conjunto **n variables** con posibles distintos valores.
- Un estado es meta si los valores que tienen sus variables cumplen *x* **restricciones**
- **Dominios reales** que lo usan -> juegos unipersonales, horarios, producción, etc.

**Definición**
- Un **problema de satisfacción de restricciones o CSP** es una tripleta $(X, D, R)$
	- $X = \{x_1, ..., x_n \}$ es un conjunto finito de variables
	- $\textbf{D}: X \rightarrow V$ es una función total que asigna un **dominio** a cada variable, es decir, el conjunto de valores posibles que puede tomar $x_i$
	- $\textbf{R} = \{ R_1,..., R_k\}$ es un conjunto finito de **restricciones** tal que cada una es un predicado sobre un subconjunto de las variables de X

Veamos esta definición aplicada a dos posibles ejemplos, el problema de las **n-reinas** o el del **sudoku**. 

**n-reinas**
- Trata de colocar *n* reinas en un tablero *nxn* tal que ninguna amenace a otra.

Veamos cómo se vería para un caso de 4-reinas: 
- $X=\{x_1,...,x_4\}$ (número de las filas)
- $D=\{D_1,...,D_4\}$ siendo $D_i = \{1, 2, 3, 4 \}$ (número de las columnas)
- $R=\{R_1\}$ siendo $R_1(x_1,x_2,x_3,x_4) = \{(2,4,1,3),(3,1,4,2)\}$

>[!NOTE]
>- R se suele modelar como un conjunto de restricciones más locales
>- En el ejemplo cada iteración de R es una amenaza entre filas
>- En un CSP binario todas las restricciones involucran como mucho dos variables

**sudoku**
Hemos de implementarlo, veamos las ideas principales:
- Cada una de las 81 casillas de un tablero de sudoku las modelamos con una variable
- Los **dominios** que representan casillas vacías van de 1 a 9
- Los **dominios** de las variables con casillas ocupadas tienen su dígito como único valor
- Las **restricciones** son del tipo "todos diferentes" 
- $R_{\neq}(x_1,..,x_9)=\{(x_1,...,x_9)\in \{1,...,9\}⁹|x_1\neq x_2 \neq ... \neq x_9\}$  
- Hay **27 restricciones** (9 para líneas horizontales, 9 verticales y 9 para subcuadrículas)
![[modelado sudoku vacío.png]]
### CSP binario como grafo
Los **CSP de restricciones binarios** son representados como grafos normalmente:
- Cada **variable** del CSP es un nodo
- Cada **restricción binaria** se representa por un arco entre los nodos $x_j$ y $x_k$
- Ejemplo: grafo correspondiente al 4-reinas
![[grafo 4-reinas.png]]
### CSP no binario como hipergrafo
Los **CSPs con restricciones k-arias (k>2)** se representan como **hipergrafos**:
- Cada **variable** es nuevamente representada como un nodo
- Cada restricción k-área se representa por un **hiperarco** que conecta *k* nodos
- Ejemplo: criptoaritmética
![[hipergrafo criptoaritmética.png]]
Cualquier CSP con restricciones k-áreas se puede representar mediante un CSP que contiene únicamente restricciones binarias
### Solución a un CSP
- Una **asignación** es una función **parcial** $\sigma$. $X \rightarrow D(X)$
	- Habitualmente se escribe "$x_1=v_a$" por "$\sigma(x_1)=v_a$" y se describe una asignación de forma extensiva tal que $\sigma = \{x_1=v_a,x_3=v_b,x_7=v_c,...\}$
	- Una asignación es **completa** si está definida para todas las variables X del CSP
	- Una asignación $\sigma$ cumple con una restricción $R_i$ si y sólo si:$$(\sigma(x_1),...,\sigma(x_l)) \in R_i(x_1, ..., x_l)$$
- Una **asignación completa** $\sigma$ es **solución** si cumple todas las restricciones en $R_i\in R$
- Ejemplos para 4-reinas
	- $\sigma = \{x_1=2,x_2=4,x_3=3\}$ es una **asignación parcial** que cumple $R'_2$
	- $\sigma = \{x_1=2,x_2=2,x_3=3, x_4=4\}$ es una **asignación total** que no cumple $R'_2$
	- $\sigma = \{x_1=2,x_2=4,x_3=1, x_4=3\}$ es una **solución completa** al problema de las 4 reinas
### Búsqueda con asignaciones completas
- *Estado*: asignación completa (valores para todas las variables)
- *Operador*: modificar el valor de una variable en la asignación
- *¿Meta?*: asignación que cumple todas las restricciones
- *Coste*: cero (la longitud de un camino hasta un nodo meta es irrelevante)
- *Heurística del conflicto mínimo*
	- Preferir sucesores que violen el mínimo número de restricciones
	- 4-reinas: nº de amenazas entre pares de reinas
## Algoritmos para búsqueda con restricciones
### Métodos de búsqueda para encontrar una solución al CSP
#### Búsqueda con asignaciones completas
- *Estado*: asignación completa (valores para todas las variables)
- *Operador*: modificar el valor de una variable en la asignación
- *¿Meta?*: asignación que cumple todas las restricciones
- *Coste*: cero (la longitud de un camino hasta un nodo meta es irrelevante)
- *Heurística del conflicto mínimo*
	- Preferir sucesores que violen el mínimo número de restricciones
	- 4-reinas: nº de amenazas entre pares de reinas
#### Búsqueda con asignaciones parciales
- *Estado*: asignación parcial (valores asignados a algunas variables)
- *Operador*: elegir un valor para una variable *no asignada* (el posible estado sucesor ha de cumplir R)
- *¿Meta?*: solución (asignación completa que cumple todas las restricciones)
- *Coste*: cero (la longitud de un camino hasta un nodo meta es irrelevante)
### Satisfacción de restricciones con vuelta atrás cronológica
Veamos el pseudocódigo para llevar a cabo esta acción
```
Función vuelta-atrás-cronológica (CSP, σ) devuelve σ'/fallo
	Si |σ| = n entonces % la asignación es completa (i.e una solución )
		devolver
	xi <- elegir-variable-no-asignada(X,σ) % orden de elección no afecta completitud
	dominio <- Dxi
	Mientras dominio /= {} hacer % en el dominio quedan valores por probar
		v <- elegir-valor(dominio)
		σ' <- σ ∪ {xi = v}       % generar nueva asignación parcial
		Si σ' ∈ R entonces       % la nueva asignación parcial es consistente
			resultado <- vuelta-atrás-cronológica(CSP, σ')
			Si resultado /= fallo entonces
				devolver(resultado)
		dominio <- dominio \ {v}
	Fin{Mientras}
	devolver(fallo)
Fin{vuelta-atrás-cronológica}
```

Hemos de hacer notar que la selección de variables y de valores no afecta a la completitud pues el espacio de búsqueda es finito. Sin embargo, sí afecta a la complejidad del algoritmo (el tamaño del árbol de búsqueda)

**Heurísticas para elección de variables**
- Hay que asignar todas las variables del CSP
- Preferir las difíciles: detectar posibles callejones sin salida (*fail first*)
	- Preferir la variable de **mínimos valores restantes** (*MRV*)
	- Preferir la variable con **mayor número de restricciones** (*grado heurístico*)

**Heurísticas para elección de valores**
- Es suficiente con asignar *uno* de los valores en el dominio de una variable
- Preferir valores "prometedores": generar una solución cuanto antes (*fail last*)
	- Preferir el valor menos limitante (respecto a variables no asignadas)
### Thrashing
Problema del algoritmo de vuelta atrás cronológica:
- No se toma en cuenta la "**causa**" de haber llegado a un callejón sin salida
- "**Thrashing**" se genera el mismo error de asignación (subárbol) varias veces
- Ejemplo
	- $x_i=a$ **es incompatible con cualquier valor del dominio de $x_k$**
	- Sin embargo, se irían probando los valores para $x_k$ (en combinación con $x_i=a$) un número exponencial de veces.

Entonces, aplicamos las siguientes mejoras a nuestro algoritmo BT para intentar mejorarlo.
### Mejoras a cronological BT

**Satisfacción de restricciones con salto atrás (*backjumping*)**
- No se retrocede a la variable más recientemente instanciada que todavía tiene alternativas posibles
- En vez, se continúa la búsqueda en la primera variable que causó el fallo
- Ejemplo: 8-reinas
	- No hay valor posible para $x_6$
	- Revisar el valor de $x_5$ no resuelve el problema
	- Retrocedemos directamente a $x_4$ saltándonos $x_5$

- **Nogoods** 
	- Recordar las asignaciones parciales que han dado fallo para que no se vuelvan a generar
	- *Ej* transparencia anterior: evitar que se vuelva a generar una asignación con $x_i=a$

### Propagación de restricciones
Queremos usar el conjunto de restricciones para reducir el espacio de búsqueda

Nuestro método será:
- "Propagar" valores a través de las restricciones que afectan a sus variables
- Intentando eliminar de los dominios los valores que no podrán formar parte de una solución

**Aplicación**
	a. *Antes* de la búsqueda, para reducir cardinalidad de los dominios
	b. *Intercalado* con la búsqueda, filtrar dominios sobre la base de una asignación parcial

### forward-checking
- **Filtrar dominios después de cada ampliación de la asignación parcial σ**
	- Para todas las restricciones binarias R que involucran una variable $x_i$ asignada en σ y otra $x_j$ no asignada en σ
	- Para todo valor v' de $D_j$: Si (σ($X_i$), v') viola $R(x_i, x_j)$ entonces eliminamos v' de Dj
- Marcha atrás si algún dominio se queda sin valores
### Consistencia de arco

**Definición**
Una variable $x_i$ es **arco consistente** con respecto a una restricción binaria $R(x_i, x_j)$ si:
$$\forall v \in D_i \space \exists v' \space D_j | (v, v') cumple R(x_i, x_j)$$
**Extensión del concepto**
- Una variable es arco-consistente si lo es con respecto a todas las restricciones binarias en las que está involucrada
- Una restricción binaria es arco-consistente si tanto $x_i$ como $x_j$ son arco-consistentes con respecto a ella
- Un CSP es arco-consistente si todas sus restricciones lo son

>[!NOTE] 
>- **Si una variable $x_i$ NO es arco consistente** con respecto a una restricción binaria entonces existe al menos un valor v perteneciente al dominio que es incompatible con todos los valores v' con respecto a dicha restricción
>- **Eliminando estos valores v NO modifica el conjunto de soluciones de un CSP**

**Método** para alcanzar arco-consistencia en un CSP:
- Para todas las variables $x$ y restricciones $R(x,\_)$ en las que $x$ está involucrada
	- Hacer $x$ arco-consistente con respecto a $R(x, \_)$
	- Al eliminar un valor del dominio $D_i$ de una variable $x_i$ involucrada en la restricción $R_y(x_i,x_j)$ se puede "estropear" la arco-consistencia de otra variable $x_k$ con respecto a la restricción $R_z(x_i, x_k)$
	- Es decir, aunque ya se haya alcanzado arco-consistencia para $x_k$ con respecto a la restricción  $R_z(x_i, x_k)$ es posible que haya que volver a hacerlo (puede ser necesario propagar valores varias veces por la misma restricción)

### Algoritmo de arco-consistencia
**Resultado**
- Este reduce un CSP en un CSP' *equivalente* (con las mismas soluciones)
- Si al aplicar el algoritmo el dominio de una variable se queda vacío, el CSP es inconsistente (no tiene solución)
**Complejidad**
- Un grafo que representa el CSP binario tiene como mucho n(n-1) o O(n²) arcos (dirigidos)
- Cada arco puede insertarse en abierta a lo sumo d veces 
- El borrado de valores que no son arco-consistentes se realiza en O(d²) pasos
- Por tanto, la complejidad en tiempo en el peor caso es O(n² d³)
**Pero**
- La reducción en el tamaño de los dominios (y el ahorro correspondiente en el tiempo de
ejecución del algoritmo de satisfacción de restricciones) suele compensar el coste adicional
de aplicar el algoritmo de propagación de restricciones para alcanzar arco-consistencia

**Análisis**
- No podemos garantizar que este detecte cualquier CSP inconsistente
- ***k-consistencia*** para cualquier asignación consistente $\sigma_{k-1}$ a k-1 variables y para cualquier variable restante, existe un valor en el dominio de esta k-ésima variable que es consistente con $\sigma_{k-1}$
- se conoce también como 2-consistencia
- se puede asegurar que un CSP con n variables tiene solución si es fuertemente n-consistente
### Algoritmo MAC
Mantenimiento de consistencia de arcos o Full Look Ahead
- Intercala satisfacción y propagación de restricciones
	- Realiza búsqueda con bt cronológica
	- Después de aumentar una asignación, construir un CSP equivalente que sea arco-consistente
- De los más básicos para CSPs
### CSPs avanzados
Temas avanzados:
• Algoritmos de satisfacción y propagación más sofisticados.
• Heurísticas de selección de variables y/o valores más sofisticados.
• CSPs con dominios infinitos y continuos.
• Estructuración (jerárquica) de CSPs.
• Preferencias sobre soluciones (optimización de restricciones, COPs).
• Satisfacción /optimización distribuida de restricciones (DCSP/DCOP).
• Relajación de restricciones.
• . . .