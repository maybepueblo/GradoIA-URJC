## Problemas de satisfacción de restricciones CSP
### Conceptos Básicos
Es un modelo matemático usado para representar problemas donde se deben encontrar valores para un conjunto de variables que cumplan con ciertas restricciones. Se suele definir como una tripleta (*X*, *D*, *R*):
- $X = \{{x_1, ..., x_n}\}$: Conjunto finito de **variables** que necesitan ser asignadas
- $D$: Función que asigna a cada variable $x_i$ un **dominio** $D_i$, es decir, el conjunto de valores posibles que puede tomar $x_i$.
- $R = \{{R_1, ..., R_k}\}$: Conjunto de **restricciones**, donde cada $R_i$ es un predicado que limita los valores que pueden tomar las variables involucradas. Por ejemplo $R_i(x_1,x_2)$ podría indicar que $x_1 \neq x_2$.
*Ejemplo*: Problema de las *n*-Reinas
- **Variables**: $X = \{{x_1, ..., x_n}\}$, donde representa la columna en la que se coloca la reina de la fila $i$
- **Dominios:** $D_i=\{1,2,...,n\}$ para cada variable $x_i$
- **Restricciones**
	- Ninguna reina puede estar en la misma columna: $x_i \neq x_j$ para todo $i \neq j$.
	- Ninguna reina puede estar en la misma diagonal: $|x_i-x_j| \neq |i-j|$ para todo $i \neq j$ 
En el caso de las **4-reinas** una solución sería $\sigma = \{x_1=2,x_2 = 4, x_3=1, x_4 =3\}$ donde ninguna reina amenaza a otro.

*Ejemplo*: Sudoku
- **Variables**: Cada casilla vacía del tablero, denotadas por $A1, A2, ..., I9$
- **Dominios**:
	- Casillas vacías: $D_{ij}=\{1,2,...,9\}$
	- Casillas con vacías iniciales $D_{ij}=\{k\}$ donde $k$ es el valor predefinido
- **Restricciones**
	- **Líneas horizontales y verticales**: Todos los dígitos en una fila o columna deben ser diferentes.
	- **Subcuadrículas 3x3**: Todos los dígitos en una subcuadrícula deben ser diferentes
Por ejemplo, en la fila $A$, las variables $A1, A2, ..., A9$ deben tener valores distintos entre sí

*Ejemplo*: Criptoaritmética
- **Problema**: Asignar dígitos a letras en una operación aritmética para que la ecuación sea válida. Por ejemplo:

```
  TWO
+ TWO
-----
 FOUR
```
- **Variables**: Letras, $T, W, O, F, U, R$ y variables de acarreo $C_1, C_2, C_3$
- **Dominios:**
	- Letras: $D = \{1,...,0\}$ (excepto $F$, que puede ser 0 o 1 si hay acarreo)
	- Acarreos: $D_{C_i} = \{0,1\}$ 
- **Restricciones**:
	- $O+O=R+10·C_1$ (unidades)
	- $W+W+C_1=U+10·C_2$ (decenas)
	- $T + T + C_2 = O + 10 · C_3$ (centenas)
	- $F = C_3$ (millares)
	- Todas las letras deben tener valores distintos

### **Representación de CSPs**
- **CSP Binario:** Restricciones involucran como máximo dos variables. Se representa como un **grafo**, donde los nodos son variables y los arcos restricciones.
	- *Ejemplo* -> Grafo de las 4-reinas donde cada arco conecta variables que no pueden tener el mismo valor o estar en la misma diagonal.
- **CSP No Binario**: Restricciones involucran más de dos variables. Se representa como un **hipergrafo**, donde los hiperarcos conectan múltiples nodos.
	- *Ejemplo* -> Problema de criptoaritmética, donde las restricciones como $R_1(O,R,C_1)$ conectan tres variables.
### Solución a un CSP
Es una **asignación completa** $\sigma$ que asigna un valor a cada variable de $X$ y cumple todas las restricciones en $R$. Por ejemplo:
- En las 4-reinas, $\sigma = \{x_1 = 2, x_2 = 4, x_3 = 1, x_4 = 3\}$ es una solución
- En Sudoku, una solución es una asignación que llena todas las casillas cumpliendo las restricciones.
## Búsqueda con estados completos
### Enfoque de búsqueda
Para resolver un CSP, se pueden usar métodos de búsqueda que exploran el espacio de posibles asignaciones. Hay dos enfoques principales:
1. **Búsqueda con Asignaciones Completas**
	- **Estado**: Todas las variables tienen un valor asignado aunque pueda violar restricciones
	- **Operador**: Modificar el valor de una variable en la asignación
	- **Meta**: Encontrar una asignación que cumpla todas las restricciones
	- **Coste**: No se considera el coste del camino, solo si se alcanza una solución
	- **Heurística**: Se utiliza el **conflicto mínimo**, que prioriza asignaciones que violen el menor número de asignaciones.
		- Por ejemplo, en las 4-reinas, se cuentan las amenazas entre reinas y se elige el movimiento que reduzca esto.
	- ***Ejemplo de aplicación***
		- En las 4-reinas, comenzamos con una asignación aleatoria, como $\sigma = \{x_1 = 1, x_2 = 1, x_3 = 1, x_4 = 1\}$, que viola todas las restricciones. 
		- Aplicamos la heurística de conflicto mínimo para modificar una variable a la vez, reduciendo el número de amenazas hasta llegar a una solución válida.
2. **Búsqueda con Asignaciones Parciales**
	- **Estado**: Sólo algunas variables tienen valores asignados, pero cumplen las restricciones relevantes.
	- **Operador**: Asignar valor a variable no asignada, asegurando que no se violen restricciones
	- **Meta**: Asignación completa que cumpla todas las restricciones
	- **Coste**: No se considera el coste del camino.
	- **Ventajas**
		- Evita generar estados inválidos, ya que cada paso asegura que las restricciones se cumplan
		- Reduce el espacio de búsqueda al no explorar asignaciones incompatibles
	- ***Ejemplo de aplicación***
		- En Sudoku, comenzamos con una casilla vacía y probamos valores que no violen las restricciones de fila, columna y subcuadrícula. 
		- Si no hay valores válidos, se retrocede (backtracking) y se prueban alternativas
### Comparación de enfoques
- **Asignaciones completas**: Son útiles para cuando sea fácil generarlas y luego refinarlas (ejemplo de las reinas)
- **Asignaciones parciales**: Más eficiente en problemas como el sudoku, donde las restricciones son estrictas y el espacio de búsqueda es grande.
### Notas adicionales
- **Conmutatividad**: Orden en el que se asignan variables no afecta al resultado final. Esto permite optimizar la búsqueda evitando redudancias.
- **Complejidad:** El número de posibles asignaciones es $d^n$ (siendo $d$ el tamaño del dominio y $n$ el número de variables), pero con restricciones, este espacio se reduce significativamente.
