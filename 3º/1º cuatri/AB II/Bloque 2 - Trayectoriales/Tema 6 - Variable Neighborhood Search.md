A lo largo de este documento se verá como VNS
# Introducción
El procedimiento de Búsqueda de Vecindad Variable (VNS) vino dado por Nenad Mladenovic y Pierre Hansen en 1995 pero sus bases se asentaron en 1997.

Se basa en el principio del **cambio sistemático de estructura de vecindad** dentro de la búsqueda para **escapar de óptimos locales**. Si la búsqueda se queda atrapada, cambiamos a un entorno más amplio.

Es sencillo y ha permitido numerosas extensiones.

**Principios**
Está basado en tres hechos simples:
- Un mínimo local en una estructura de vecindad no lo es necesariamente con otra
- Un mínimo global es mínimo local con respecto a todas las posibles estructuras de vecindad.
- Para muchos problemas, los mínimos locales con la misma o distinta estructura de vecindad están relativamente cerca.

Estos hechos justifican el uso de múltiples estructuras de vecinos para abordar un problema de optimización.
## Visualización

![[Pasted image 20260531203447.png]]

**Hechos**
- Lo cerca que están los óptimos locales entre sí respecto a diferentes estructuras de vecindad es empírico. Esto nos dice que los óptimos locales nos dan información acerca del óptimo global.
- Puede ser por ejemplo, que ambas soluciones tengan características comunes.
	- Sin embargo, de forma generar no conocemos dichas características.
		- Por ello, hemos de realizar un estudio organizado en las proximidades de este óptimo local hasta encontrar uno mejor.
## Implementaciones

- Principales esquemas VNS:
	- VNS Reducida -> RVNS
	- VNS Descendente -> VND (Variable Descent Search)
	- VNS Básico -> BVNS
	- VNS General -> GVNS

- Otras extensiones VNS:
	- VNS de Descomposición (VNDS)
	- VNS Sesgada (SVNS, Skewed VNS)
	- VNS Paralelo (PVNS, Parallel VNS)
	- ...
# Reduced Variable Neighborhood Search
En la RVNS seleccionamos soluciones aleatorias de $x$ en su vecindad $N_k(x)$ a través de una función llamada `Shake` 

>[!NOTE] Nota
> No se usa procedimiento de búsqueda local

Aplicamos cambios sucesivos de vecindad mientras la solución no mejore a través de la función `NeighbourhoodChange`.

Como **criterios de parada** podemos considerar:
- Horizonte de tiempo
- Número máximo de iteraciones
- Número máximo de iteraciones SIN MEJORA
## Esquema algorítmico

![[Pasted image 20260531204336.png]]

1. Partimos de una solución inicial S y nos fijamos en el primer vecindario.

2. `Shake` 
	- **Perturbación aleatoria**. Generamos una solución S' escogiendo un punto al azar dentro del **vecindario k** de S.
		*NO es una búsqueda exhaustiva, sirve para alejarse de la solución actual y explorar otra zona del espacio*

>[!NOTE]
Importante aclarar por qué está difuminada la parte de mejora. nuestro VNS completo aplicaríamos una búsqueda local sobre S', aquí no. Al eliminarla, ganamos en rapidez, pero perdemos algo de precisión

3. `CambioVecindad(S, S')`
	- Comparamos S' con S y decidimos si movernos:
		- S' mejora a S -> actualizamos S = S' y reseteamos k = 1 (volvemos al primer vecindario con nueva solución)
		- S' no mejora -> pasamos al siguiente vecindario `k = k + 1`

4. Decisión -> $k \leq k_{max}$ 
	- No (k supera k_max) -> el algoritmo termina, devolvemos S
	- Sí (quedan vecindarios por explorar) -> volvemos a Shake con nuevo k
## Pseudocódigo
1. **procedimiento** RVNS ($f$ , $k_{max}$​ , $t_{max}$​)
2.     **repetir** 
3.            $k←1$; 
4.            **repetir** 
5.                  $f′←Shake(f,k)$; 
6.                   $NeighbourhoodChange(f,f′,k)$; 
7.            **hasta** $k=kmax​$; 
8.             $t←CPUTime()$;
9.     **hasta** $t > tmax$​;
10. **fin RVNS**;

**Función `Shake`**:
- Aplica un movimiento aleatorio a la solución que recibe como parámetro dentro de la vecindad k-ésima.

**Procedimiento Auxiliar: NeighbourhoodChange**
1. **procedimiento** $NeighbourhoodChange(x,x′,k)$
2.         **si** $(f(x′)<f(x))$ **entonces** 
3.              $x←x′$; 
4.              $k←1$;
5.         **si no** ($k←k+1$);
6. **fin $NeighbourhoodChange$**;
# Variable Neighborhood Descent
La VNDS está basada en el uso de múltiples estructuras de vecindad durante el proceso de mejora (descenso).

Los cambios de vecindad se hacen de manera determinista. Partimos de una solución previamente construida
## Esquema algorítmico

![[Pasted image 20260531213401.png]]

Ahora, expliquemos esto un pizco:
- **Inicio** $k \leftarrow 1$
	- Partimos de una solución inicial S y comenzamos con el primer vecindario. NO tenemos perturbación previa.
- **Mejora(S)**
	- Núcleo. Aplicamos una búsqueda local completa sobre S usando el vecindario k hasta encontrar el óptimo local en ese vecindario.
	*A diferencia del `Shake` aleatorio, aquí exploramos el vecindario de forma exhaustiva o sistemática hasta que no haya movimiento que de mejora*
	- El resultado es S', el óptimo local encontrado en vecindario k.
- **CambioVecindad(S, S')**
	- Comparamos S' con S:
		- S' mejora S -> `S = S'` y reseteamos k = 1, volviendo a explotar desde el primer vecindario con la solución mejorada.
		- S' no mejora S -> ya estamos en un óptimo local para este vecindario, probamos el siguiente k = k+1
- **Decisión** $k \leq k_{max}$
	- Sí -> quedan vecindarios, volvemos a Mejora con el nuevo k
	- No -> se agotaron todos los vecindarios sin mejora -> S es óptimo local en todos los vecindarios -> el algoritmo termina
## Pseudocódigo
1. procedimiento $VND (f,k_{max} )$
2.        repetir
3.             $k ← 1$;
4.             repetir
5.                    $f ′ ← ChooseBestNeighbour(f ,k )$;
6.                    $NeighbourhoodChange(f ,f ′, k )$;
7.             hasta $k = kmax$;
8.         hasta que no haya mejora;
9. fin $VND$;
# Basic Variable Neighborhood Search
El BVNS combina pasos aleatorios y pasos deterministas en las estructuras de vecindad.

Al igual que RVNS, partimos de una solución previamente construida. Asimismo, añadimos al esquema de este anterior, una búsqueda local.
## Esquema algorítmico

![[Pasted image 20260531214350.png]]
 
-  **Inicio — `k ← 1`**
	- Se parte de una solución inicial **S** con el primer vecindario k = 1.
-  **Shake(S, k) → S'**
	- Se **perturba aleatoriamente** S dentro del vecindario k, obteniendo S'. El objetivo es alejarse de la solución actual para explorar una zona diferente del espacio de búsqueda.
	*S' es una solución nueva, pero en bruto: probablemente no sea óptima localmente todavía.* 
-  **Mejora(S') → S''**
	- Sobre la solución perturbada S' se aplica una **búsqueda local completa**, obteniendo S''. Se desciende hasta el óptimo local más cercano a S'.
	*S'' es el óptimo local del "valle" en el que cayó el Shake. Ahora sí tiene sentido compararlo con S.* 
-  **CambioVecindad(S, S'')**
	- Se compara el óptimo local S'' con la solución actual S:
		- **S'' mejora S** → `S = S''` y `k = 1`: se acepta el nuevo óptimo y se reinicia desde el primer vecindario
		- **S'' no mejora S** → `k = k + 1`: ese vecindario no produjo mejora, se prueba el siguiente 
-  **Decisión — `k ≤ k_max`**
	- **Sí** → quedan vecindarios, volver a Shake con el nuevo k
	- **No** → se han agotado todos sin mejora → el algoritmo **termina** y devuelve S
## Pseudocódigo
1. procedimiento $BVNS (f ,k_{max} ,t_{max} )$
2.      repetir
3.           $k ← 1$;
4.           repetir
5.                   $f ′ ← Shake(f ,k )$;
6.                   $f ′′ ← LocalSearch(f ′, k )$;
7.                   $NeighbourhoodChange(f ,f ′′, k )$;
8.           hasta $k = k_{max}$ ;
9.           $t ← CPUTime()$;
10.    hasta $t > t_{max}$;
11. fin $BVNS$;
# General Variable Neighborhood Search
En el GVNS se combinan algunas ideas de las anteriores:
- Se emplea un esquema similar al BVNS
- Se sustituye la búsqueda local por un VND
## Esquema algorítmico

![[Pasted image 20260531215150.png]]
#### Inicio — `k ← 1`
Se parte de una solución inicial S con el índice de vecindario k = 1. Este k controla la intensidad del Shake en el bucle externo.
#### Shake(S, k) → S'
Se perturba aleatoriamente S dentro del vecindario k, obteniendo S'. El objetivo es salir de la cuenca de atracción del óptimo local actual y explorar una zona diferente del espacio.

A mayor k, mayor es la perturbación, más lejos se lanza S'.
#### VND(S') → S''
Aquí está la diferencia fundamental con BVNS. En lugar de una búsqueda local simple, se aplica un **VND completo** sobre S', que a su vez:

- Aplica búsqueda local exhaustiva con vecindario 1 hasta su óptimo local
- Si no mejora, cambia al vecindario 2 y repite
- Continúa hasta k_max del VND interno
- Devuelve S'', el mejor óptimo local encontrado en toda esa exploración multi-vecindario

S'' es por tanto un óptimo local **mucho más refinado** que el que produciría una mejora simple.
#### CambioVecindad(S, S'')
Se compara el óptimo S'' con la solución actual S:
- **S'' mejora S** → `S = S''` y `k = 1`: se acepta y se reinicia desde el primer vecindario
- **S'' no mejora S** → `k = k + 1`: se incrementa la perturbación para el siguiente intento
#### Decisión — `k ≤ k_max`
- **Si** → quedan vecindarios de Shake, volver a perturbar con mayor intensidad
- **No** → se agotaron todas las perturbaciones sin mejora, el algoritmo termina y devuelve S
## Pseudocódigo
1. procedimiento $GVNS (f, k'_{max}, k_{max}, t_{max})$
2. repetir
3.     $k ← 1$;
4.     repetir
5.         $f′ ← Shake(f, k)$;
6.         $f′′ ← VND(f′, k'_{max})$;
7.         $NeighbourhoodChange(f, f′′, k)$;
8.     hasta $k = k_{max}$;
9.     $t ← CPUTime()$;
10. hasta $t > t_{max}$;
11. fin $GVNS$;