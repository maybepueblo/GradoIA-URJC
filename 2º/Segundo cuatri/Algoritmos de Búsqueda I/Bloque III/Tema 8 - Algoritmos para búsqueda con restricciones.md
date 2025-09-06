## Satisfacción de restricciones
Recordamos lo que significa un problema de CSP visto en [[Tema 7 - Restricciones]]:
- Un conjunto de **variables** $X = \{x_1,x_2,...,x_n\}$
- Un conjunto de **dominios** $D=\{D_1,D_2,...,D_n\}$ donde cada $D_i$ contiene los valores posibles para $x_i$
- Un conjunto de **restricciones** $R$ que limitan las combinaciones válidas de valores para las variables.
**Solución:** Una asignación completa de valores a las variables que cumpla todas las restricciones.
### Algoritmo: Chronological Backtracking

**Concepto**
Algoritmo de búsqueda en profundidad que explora asignaciones parciales de variables y retrocede cuando detecta inconsistencia.

**Funcionamiento**
1. **Estado**: Asignación parcial de valores a algunas variables
2. **Operador**: Asignar un valor a variable no asignada, cumpliendo las restricciones
3. **Meta**: Encontrar asignación completa que satisfaga las restricciones
4. **Retroceso**: Si una asignación parcial viola alguna restricción, se deshace la última decisión y se prueba otro valor.

**Ejemplo: Problema de las 4 Reinas**
- **Variables** $x_1,x_2,x_3,x_4$ (columnas donde colocamos las reinas en filas 1 a 4)
- **Dominios**: $D_i=\{1,2,3,4\}$ para cada $x_i$
- **Restricciones** Ninguna reina puede atacarse mutuamente (no pueden ni estar en la misma columna ni en diagonales)
**Proceso**
1. Se asigna $x_1=1$
2. Se prueba $x_2 = 1$ pero viola la restricción (misma columna) por lo que se retrocede y se prueba $x_2 = 2$
3. Se continúa hasta encontrar una asignación válida como $\{x_1=2,x_2=4,x_3=1,x_4=3\}$
**Limitaciones**
- **Thrashing:** Repite los mismos errores al no recordar causas de fallos anteriores
- **Ineficiencia:** Explora ramas del árbol de búsqueda que podrían descartarse con información adicional.
## Propagación de restricciones
Técnicas que reducen el espacio de búsqueda eliminando valores inconsistentes de los dominios de las variables antes o durante la búsqueda.
### Forward Checking
Después de asignar un valor a una variable, borramos los valores inconsistentes de las variables no asignadas relacionadas por restricciones.

**Funcionamiento**
1. **Filtrado:** Para cada variable asignada $x_i$, se revisan las restricciones binarias con variables no asignadas $x_j$
2. **Eliminación:** Se eliminan de $D_j$ los valores $v'$ que violan $R(x_i,x_j)$ con el valor actual de $x_i$
3. **Marcha atrás:** Si algún dominio se vacía, retrocedemos

**Ejemplo: 4 Reinas con Forward Checking**
1. **Asignación:** $x_1 = 1$
2. **Filtrado:** 
	- $x_2$: Elimina 1 y 2 (por restricciones de columna y diagonal) dejando $D_2 = \{3,4\}$
	- $x_3$: Elimina 1 y 3, dejando $D_3 = \{2,4\}$
	- $x_4$: Elimina 1 y 4, dejando $D_4=\{2,3\}$
3. **Continuación**: Se explora $x_2=3$ y repetimos el proceso

**Ventajas**
- Reduce dominios tempranamente, evitando explorar ramas inviables
**Limitaciones**
- No considera restricciones entre variables no asignadas (ejemplo: $x_3$ y $x_4$ en las 4 reinas)
## Consistencia de Arco y Consistencia de Dominio

**Concepto**
- **Consistencia de Arco** -> Una variable $x_i$ es arco-consistente con respecto a $x_j$ si para todo valor en $D_i$, existe al menos un valor en $D_j$ que satisface la restricción $R(x_i,x_j)$
- **CSP Arco-Consistente** -> Todas sus restricciones binarias son arco-consistentes

**Algoritmo AC-3 (Consistencia de Arco)**
1. **Inicialización**: Se colocan todas las restricciones en una cola
2. **Procesamiento**
	- Para cada restricción $R(x_i,x_j)$ se eliminan los valores de $D_i$ que no tienen soporte en $D_j$
	- Si se elimina algún valor, se vuelven a revisar las restricciones relacionadas con $x_i$
3. **Terminación**: Cuando la cola está vacía o algún dominio se vacía (CSP inconsistente)

**Ejemplo: 4 Reinas con Consistencia de Arco**
1. **Asignación:** $x_1 = 1$
2. **Dominios iniciales:** $D_2 = \{3,4\},D_3=\{2,4\},D_4=\{2,3\}$
3. **Procesamiento**: 
	- Para $x_3 =2$ no hay $v'\in D_4$ que cumpla $R_6'(x_3,x_4)$ (no pueden estar en diagonal)
	- Se elimina 2 de $D_3$, dejando $D_3 = \{4\}$
	- Para $x_3=4$ no hay $v'\in D_2$ que cumpla $R_4'(x_3,x_2)$
	- Se elimina 4 de $D_3$, dejando $D_3=\emptyset$ . **El CSP es inconsistente**
**Ventajas**
- Detecta inconsistencias tempranas sin explorar el árbol de búsqueda
- Reduce dominios de forma óptima
**Limitaciones**
- Coste computacional elevado ($O(n^2·d^3)$) 
- No garantiza detectar todas las inconsistencias (ejemplo: CSP no binarios)
#### Algoritmo MAC
Combina chronological backtracking con el AC-3:
1. Después de cada asignación, aplicamos AC-3 para mantener arco-consistencia
2. Si un dominio se vacía, retrocede inmediatamente
**Ejemplo**
- En las 4 reinas, MAC detectaría que $x_1=1$ lleva a un dominio vacío para $x_3$, evitando explorar ramas innecesarias.
