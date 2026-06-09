# Algoritmos Genéticos (GAs)

## 1. Simple GA (SGA)

La primera propuesta surge en **1975** por John Holland (*Adaptation in Natural and Artificial Systems*) y se le conoce como **Simple GA (SGA)**. Sus características son:

- **Representación:** cadenas binarias
- **Selección de progenitores:** proporcional al fitness
- **Recombinación:**
	- *N-point:* se eligen N puntos en el cromosoma y se intercambian los segmentos
	- *Uniforme:* cada bit se elige de un padre con igual probabilidad bajo distribución uniforme
- **Mutación:** inversión de bits bit a bit (*bitwise bit-flipping*) con probabilidad fija
- **Reemplazo:** todos los descendientes reemplazan a los progenitores
- Se da **más énfasis al cruce** que a la mutación

Holland propuso también el **Teorema de los Esquemas**, considerado la prueba matemática del funcionamiento de los GAs.

---

## 2. Representación en SGA

La representación es **binaria**: el espacio de fenotipos (soluciones reales al problema) se convierte al espacio de genotipos $\{0,1\}^L$ mediante una **codificación (encoding)**, y se vuelve al espacio de fenotipos mediante una **decodificación (decoding)**.

![[Pasted image 20260603160638.png]]

---

## 3. Ciclo reproductivo del SGA

1. Seleccionar el conjunto de progenitores a recombinar → **mating pool** (tamaño = tamaño de la población)
2. Mezclar el *mating pool* aleatoriamente
3. Para cada par consecutivo aplicar cruce con probabilidad $p_c$; si no, copiar los padres
4. Para cada descendiente aplicar mutación: cambio de bit con probabilidad $p_m$ de forma independiente para cada bit
5. **Reemplazar toda la población** con la descendencia → **reemplazo generacional**

---

## 4. Operadores del SGA

### 4.1 Selección de progenitores (Ruleta)

La idea es que **los mejores individuos tienen mayor probabilidad de ser seleccionados** → selección proporcional al fitness.

**Implementación – Algoritmo de la Ruleta (*roulette wheel*):**
- Se asigna a cada individuo una parte de la ruleta proporcional a su fitness
- Se gira la ruleta $n$ veces para seleccionar $n$ individuos

*Ejemplo:* fitness(A) = 3, fitness(B) = 1, fitness(C) = 2 → A ocupa el 50%, B el 17%, C el 33% de la ruleta.

![[Pasted image 20260603161031.png]]
### 4.2 Cruce de 1 punto (*1-point crossover*)

- Se elige un punto aleatorio entre dos progenitores
- Se dividen ambos cromosomas por ese punto
- Se crean los descendientes intercambiando la parte final
- $p_c$ típicamente en el rango **(0.6 – 0.9)**

![[Pasted image 20260603161146.png]]
### 4.3 Mutación

- Se altera cada gen **independientemente** con probabilidad $p_m$ (*mutation rate*)
- Típicamente $p_m \in [\frac{1}{\text{tam\_población}}, \frac{1}{\text{long\_cromosoma}}]$

![[Pasted image 20260603161349.png]]

---

## 5. Características y deficiencias del SGA

El SGA es muy utilizado como **referencia** para evaluar nuevos GAs, pero tiene importantes deficiencias:

- La representación binaria es **demasiado restrictiva**
- Las mutaciones y cruces solo son aplicables para cadenas de bits y enteros
- El mecanismo de selección es **sensible a poblaciones convergentes** (fitness parecidos → se pierde presión de selección)
- El modelo de población generacional puede mejorarse con **elitismo** (selección explícita de supervivientes)

---

## 6. Operadores de cruce alternativos

El cruce de 1 punto sufre de **sesgo posicional**: los genes cercanos tienen más probabilidad de transmitirse juntos, mientras que los genes en extremos opuestos nunca pueden mantenerse juntos. Esto limita la exploración del espacio de soluciones.

### 6.1 Cruce N puntos

- Se eligen $n$ puntos de cruce aleatorios
- Se divide el cromosoma a lo largo de esos puntos
- Se concatenan las partes alternando entre progenitores
- Es la generalización del cruce de 1 punto; **aún tiene cierto sesgo posicional**

![[Pasted image 20260603185511.png]]

### 6.2 Cruce uniforme

- Se asigna "cara" a un progenitor y "cruz" al otro
- Para cada gen del primer descendiente se lanza una moneda → si cara, toma el gen del primer progenitor; si cruz, del segundo
- El segundo descendiente recibe la **copia inversa**
- La herencia es **independiente de la posición** → elimina el sesgo posicional

![[Pasted image 20260603185528.png]]

---

## 7. ¿Son necesarios cruce y mutación?

Hay consenso en que **ambos son necesarios**, aunque su impacto depende del problema. **Un algoritmo de solo mutación es posible; uno de solo cruce, no.**

|                                      | **Cruce**                                     | **Mutación**                            |
| ------------------------------------ | --------------------------------------------- | --------------------------------------- |
| **Rol**                              | Exploratorio                                  | Explotador                              |
| **Acción**                           | Salto entre dos áreas del espacio de búsqueda | Pequeña desviación cerca del progenitor |
| **Combina info de dos progenitores** | ✅ Sí                                          | ❌ No                                    |
| **Introduce nuevos alelos**          | ❌ No                                          | ✅ Sí                                    |
| **Cambia frecuencias de alelos**     | ❌ No                                          | ✅ Sí                                    |

> El cruce **no cambia las frecuencias de los alelos** en la población (experimento mental: si el 50% de la población tiene 0 en el primer bit, tras $n$ cruces seguirá siendo el 50%). Para introducir nueva información genética, es imprescindible la mutación.

---

## 8. Otras representaciones

Hoy en día se acepta que es mejor codificar las variables numéricas **directamente** como enteros o reales, en lugar de usar cadenas de bits.

### 8.1 Gray Coding (cromosomas binarios)

En binario estándar, un pequeño cambio de valor puede requerir cambiar muchos bits (ej: 7 = 0111 → 8 = 1000). El **código Gray** garantiza que valores consecutivos difieran en **exactamente 1 bit**, haciendo la asignación genotipo-fenotipo más "suave" y beneficiosa para el GA.

![[Pasted image 20260609232357.png]]
### 8.2 Representación con enteros
- Útil para problemas con variables enteras o categóricas (ej: {azul, verde, amarillo, rosa})
- Los cruces uniformes y de punto N funcionan directamente
- La mutación *bit-flip* se modifica:
	- **Creep:** mayor probabilidad de moverse a un valor similar
	- **Elección aleatoria:** especialmente para variables categóricas
	- Para problemas ordinales se usan dos operadores de mutación en tándem
### 8.3 Representación con números reales

- Para problemas de optimización continua: $f: \mathbb{R}^n \to \mathbb{R}$
- Mapear reales a bits es complicado (mayor precisión = mayor longitud de cromosoma)
- Lo más habitual es usar **cromosomas de números reales**: $(x_1, \ldots, x_n),\; x_i \in [LB_i, UB_i]$

---

## 9. Operadores para representación real

### 9.1 Mutación con reales

**Mutación uniforme (más sencilla):** se genera un número aleatorio en $[LB_i, UB_i]$ con distribución uniforme:
$$\bar{x} = \langle x_1, \ldots, x_l \rangle \to \bar{x}' = \langle x_1', \ldots, x_l' \rangle, \quad x_i, x_i' \in [LB_i, UB_i]$$

**Mutaciones no uniformes:** la mayoría son probabilísticas y hacen pequeños cambios. El método más común es agregar una desviación tomada de una **distribución gaussiana $N(0, \sigma)$** y ajustarla al rango. La desviación estándar $\sigma$ controla la magnitud del cambio (2/3 de las mutaciones caen en el rango $(-\sigma, +\sigma)$).

### 9.2 Cruce con reales

**Cruce discreto:** cada alelo del descendiente $z$ proviene de uno de los padres $(x, y)$ con igual probabilidad: $z_i = x_i$ ó $y_i$. Se puede usar n-puntos o uniforme.

**Cruce intermedio (recombinación aritmética):** explota la idea de crear hijos "entre" los padres:
$$z_i = \alpha x_i + (1 - \alpha) y_i, \quad \alpha \in [0, 1]$$

El parámetro $\alpha$ puede ser:
- **Constante** → cruce aritmético uniforme
- **Variable** (e.j dependiendo de la edad de la población)
- **Aleatorio** en cada aplicación

Puede ser *single* (se cambia un gen), *simple* (se mezcla a partir de un punto al azar), o *completo* (todo el cromosoma).

---

## 10. Representación de permutaciones

Los **problemas de ordenamiento/secuenciación** (ej: TSP, scheduling) se expresan como una permutación: lista de $n$ enteros donde cada uno aparece exactamente una vez.

Hay dos tipos de información a preservar:
- **Orden:** qué elementos aparecen antes que otros (ej: algoritmos de ordenamiento)
- **Adyacencia:** qué elementos aparecen uno al lado del otro (ej: TSP)

### 10.1 Mutación de permutaciones

Los operadores normales (*bit-flip*) crean soluciones inválidas porque rompen la condición de permutación. Por eso **deben cambiarse al menos dos valores** simultáneamente. El parámetro $p_m$ ahora refleja la probabilidad de aplicar algún operador una vez a **toda la cadena**, no gen a gen o en otras palabras no individualmente en cada posición.

| Operador               | Descripción                                               | Preserva                                        | Imagen                                            |
| ---------------------- | --------------------------------------------------------- | ----------------------------------------------- | ------------------------------------------------- |
| **Inserción**          | Elige 2 alelos; mueve el segundo para que siga al primero | Orden y adyacencia                              | ![[Pasted image 20260609232812.png\|50000000000]] |
| **Intercambio (swap)** | Elige 2 alelos e intercambia sus posiciones               | Adyacencia (4 enlaces rotos), altera orden      | ![[Pasted image 20260609232854.png\|50000000]]    |
| **Inversión**          | Elige 2 alelos e invierte la subcadena entre ellos        | Adyacencia (solo 2 enlaces rotos), altera orden | ![[Pasted image 20260609232909.png\|5000000]]     |
| **Mezcla (scramble)**  | Selecciona un subconjunto y reorganiza aleatoriamente     | Ninguno en particular                           | ![[Pasted image 20260609232921.png\|500000]]      |

### 10.2 Cruce de permutaciones

Los cruces estándar producen soluciones inválidas en permutaciones. Se usan **operadores especializados**:

#### Cruce de Orden 1 (OX1)
Preserva el **orden relativo** en el que aparecen los elementos:
1. Copiar una parte arbitraria del primer progenitor al descendiente

![[Pasted image 20260603191629.png]]

2. Rellenar los genes restantes con los elementos que faltan, en el **orden en que aparecen en el segundo progenitor**, comenzando desde el punto de corte y dando la vuelta al final

![[Pasted image 20260603191643.png]]

3. Para el segundo descendiente, invertir los roles

#### Partially Mapped Crossover (PMX)
Preserva tanto **posición** como **adyacencia**:
1. Elegir un segmento aleatorio y copiarlo de P1 al descendiente
2. Para cada elemento en ese segmento de P2 que no fue copiado (elemento $i$): buscar qué elemento $j$ ocupa esa posición en el descendiente → colocar $i$ donde estaba $j$ en P2 (resolviendo conflictos encadenados si es necesario)
3. Rellenar el resto desde P2

![[Pasted image 20260603192132.png]]
#### Cycle Crossover (CX)
La idea es que **cada alelo proviene de un progenitor junto con su posición**:
1. Identificar ciclos: comenzar desde el primer alelo de P1, mirar el alelo en P2 en esa posición, ir a esa posición en P1, repetir hasta volver al inicio
2. Copiar los ciclos en los descendientes de forma **alternada** (ciclo 1 → del padre 1, ciclo 2 → del padre 2, etc.)

![[Pasted image 20260603192613.png]]

---

## 11. Recombinación multiprogenitor

Los AEs no están limitados por la biología, por lo que es posible usar **más de 2 progenitores**. Existe desde los años 1960 y los estudios indican que es útil. Hay tres tipos:

- **Basados en frecuencias de alelos:** ej. votación p-sexual (generaliza cruce uniforme)
- **Basados en segmentación:** ej. cruce diagonal (generaliza cruce N puntos)
- **Basados en operaciones numéricas:** ej. cruce del centro de masa (generaliza recombinación aritmética)

---

## 12. Modelos de población

### 12.1 Modelo generacional (GGA)
- Cada individuo sobrevive exactamente **una generación**
- Todo el conjunto de padres es reemplazado por la descendencia
- Para garantizar convergencia (teorema de los esquemas) **se debe mantener al mejor individuo** → elitismo
- **Brecha generacional = 1.0** (toda la población se reemplaza)

### 12.2 Modelo de estado estable (SSGA)
- Se genera **un descendiente por generación**
- Se reemplaza un miembro de la población
- **Brecha generacional = 1/pop_size**

---

## 13. Mecanismos de selección

La selección puede ocurrir en dos momentos:
1. **Selección de progenitores:** elegir quién se reproduce
2. **Selección de supervivientes:** elegir quién pasa a la siguiente generación

Los operadores de selección trabajan sobre **individuos completos** → son independientes de la representación.

### 13.1 Selección Proporcional al Fitness (FPS)

El número esperado de copias del individuo $i$ es:
$$E(n_i) = \mu \cdot \frac{f(i)}{\langle f \rangle}$$

donde $\mu$ es el tamaño de la población y $\langle f \rangle$ es el fitness promedio.

**Implementaciones:**
- **Ruleta (un brazo):** gira $n$ veces → no hay garantías sobre el número real de copias; puede haber individuos "malos" que no se representen
- **SUS (Stochastic Universal Sampling) de Baker:** $n$ brazos uniformemente espaciados, gira una vez → garantiza $\lfloor E(n_i) \rfloor \leq n_i \leq \lceil E(n_i) \rceil$; da mayor oportunidad a individuos de baja calidad

**Problemas de FPS:**
1. **Convergencia prematura:** un individuo con fitness muy alto puede dominar rápidamente si el resto tiene fitness mucho menor
2. **Pérdida de presión de selección** al final, cuando todos tienen fitness parecido
3. **Sensibilidad a la transposición:** sumar una constante al fitness cambia completamente las probabilidades de selección

**Soluciones mediante escalado:**
- *Windowing:* $f'(i) = f(i) - \beta^t$ donde $\beta$ es el peor fitness en las últimas $n$ generaciones
- *Escalado sigma:* $f'(i) = \max(f(i) - (\langle f \rangle - c \cdot \sigma_f),\; 0)$ donde $c \approx 2$ y $\sigma_f$ es la desviación típica del fitness

### 13.2 Selección basada en Ranking

- Intenta eliminar los problemas de FPS usando el **fitness relativo** en lugar del absoluto 
- Ordena la población y asigna probabilidades de selección según el **rango** (el más apto tiene ranking $\mu$, el peor ranking 1)
- Variantes: **ranking lineal** y **ranking exponencial**
- Introduce una sobrecarga por ordenación, pero es generalmente insignificante frente al coste de evaluación del fitness

### 13.3 Selección por Torneo

- No depende de estadísticas globales → ideal para implementaciones paralelas
- **Procedimiento:** seleccionar $k$ miembros al azar y elegir el mejor; repetir para seleccionar más
- La presión de selección aumenta con:
	- Mayor $k$ (tamaño del torneo)
	- Elección sin reemplazo (vs. con reemplazo)
	- Ganador determinista (vs. probabilístico con probabilidad $p$)
- Para $k=2$ determinista, el tiempo de convergencia es el mismo que el ranking lineal con $s = 2p$

---

## 14. Selección de supervivientes (Reemplazo)

Dos enfoques principales:

**Basada en la edad:**
- SSGA: el más antiguo es reemplazado (*first in, first out*)
- La eliminación aleatoria no se recomienda

**Basada en fitness:** usando cualquier mecanismo de selección anterior

**Casos especiales:**
- **Elitismo:** siempre se mantiene al menos una copia de la mejor solución encontrada hasta el momento. Ampliamente utilizado tanto en GGA como SSGA.
- **GENITOR** ("eliminar lo peor"): algoritmo original SSGA de Whitley con ranking lineal para selección de padres. Útil con poblaciones grandes o política de no duplicados.

---

# Algoritmos Meméticos (MAs)

## 1. Hibridaciones de algoritmos

Los **motivos para hibridar** un AE con otras técnicas son:
- Incorporar el AE como parte de un sistema más amplio
- Mejorar técnicas existentes sin reinventar la rueda
- Mejorar un AE para encontrar mejores soluciones

Según Michalewicz, existe una relación entre los tipos de algoritmos y el rango de problemas: los métodos a medida (*problem tailored*) son los mejores para su problema específico, pero los AEs enriquecidos con conocimiento (*EA enriched with knowledge*) son los más robustos a lo largo de un amplio rango de problemas.

---

## 2. Dónde hibridar

Se puede incorporar conocimiento en distintos puntos del ciclo del AE:

- **Población inicial:** soluciones conocidas, heurísticas constructivas, búsqueda local multi-arranque
- **Cruce:** información específica del problema en el operador
- **Mutación:** información específica del problema en el operador
- **Sobre los descendientes** (tras cruce o tras mutación): aplicar búsqueda local
- **Selección:** operadores de selección modificados

---

## 3. Inicialización de la población

**Heurísticas para inicializar:**
- **Torneo de n vías entre soluciones aleatorias** (Bramlette): NO es lo mismo que elegir los mejores de un conjunto grande; el torneo mantiene más diversidad
- **Búsqueda local multi-arranque:** se elige *popsize* puntos aleatorios y se arranca una búsqueda local desde cada uno
- **Heurísticas constructivas:** muy habituales en la práctica

**Problemas al usar soluciones conocidas:**
- Inicializar con soluciones ya conocidas puede parecer que rinde menos al principio si los óptimos locales en diferentes landscapes no coinciden
- Surry y Radcliffe (1994): el rendimiento **medio** mejora al sesgar hacia soluciones conocidas, pero el **mejor** rendimiento viene de soluciones más aleatorias

---

## 4. Operadores "inteligentes"

A veces es posible incorporar **conocimiento específico del problema** dentro de los propios operadores:

- **Cruces y mutaciones específicos para TSP** que incluyen algún tipo de heurística de vecindad
- **Operadores que garantizan la factibilidad** de la solución (evitan soluciones inválidas)
- **Mecanismos de selección** que usan características del problema para acotar el espacio de búsqueda

---

## 5. Algoritmos Meméticos

Propuestos por **Pablo Moscato en 1989** (*On Evolution, Search, Optimization, Genetic Algorithms and Martial Arts: Towards Memetic Algorithms*).

Se basan en la metáfora del **meme** (Richard Dawkins, *El gen egoísta*, 1976):
> Un meme es un elemento de una cultura o sistema de comportamiento transmitido de un individuo a otro por imitación u otros medios no genéticos.

Los MAs tratan de **imitar la evolución cultural**, no solo la biológica.

> *"Memetic Algorithms is a marriage between a population-based global search and a heuristic local search made by each of the individuals".*

**Características clave:**
- Utilizan **conocimiento específico del problema** bajo estudio (no es opcional, es fundamental)
- En general: combinación de **AE + búsqueda local** dentro del bucle del AE
- El término también se aplica a AEs que usan conocimiento específico de la instancia en los operadores
- Se ha demostrado que los MAs son más precisos que los AEs puros en muchos problemas → son el **estado del arte** en numerosas aplicaciones

**Tipos de MAs** (según la revista *Memetic Computing*):
- **Tipo 1:** Algoritmos de propósito general + heurísticas artesanales con conocimiento del dominio (el MA clásico: AE + búsqueda local específica del problema)
- **Tipo 2:** Algoritmos con capacidad de **seleccionar, adaptar y reutilizar automáticamente** la heurística más apropiada de un conjunto disponible
- **Tipo 3:** Algoritmos que **aprenden autónomamente con la experiencia**, reutilizando datos o modelos de problemas relacionados (transfer learning, multi-task optimization, etc.)

---

## 6. Búsqueda Local (recordatorio)

Se relaciona con la metáfora del *fitness landscape*:
- Se define un **vecindario $N(x)$** como el conjunto de soluciones alcanzables desde $x$ aplicando un movimiento
- La búsqueda local explora el vecindario y devuelve un **óptimo local** respecto a ese vecindario

**Variantes:**
- ***Best improvement:*** explora el vecindario completo y elige el mejor vecino → más lenta pero garantiza el óptimo local
- ***First improvement:*** cambia de solución en cuanto encuentra una mejora → más rápida pero no garantiza el óptimo local

---

## 7. Búsqueda Local en descendientes

La búsqueda local dentro del MA puede verse como un "**aprendizaje permanente**" (*lifelong learning*) en la metáfora memética.

Se usa frecuentemente para **acelerar el juego final** del AE: hacer que la búsqueda en las proximidades de buenas soluciones sea más sistemática que la mutación sola.

**Decisiones de diseño al aplicar búsqueda local en un MA:**
- ¿La búsqueda se realiza en el espacio de **representación** o en el espacio de **soluciones**?
- ¿Cuántas **iteraciones** de la búsqueda local se realizan?
- ¿Se ejecuta la búsqueda local en **todas las iteraciones** del algoritmo o solo en algunas?
- ¿A qué individuos se aplica?
	- ¿A **toda la población**?
	- ¿Solo al/los **mejor(es)**?
	- ¿Solo al/los **peor(es)**?

---

## 8. Modelos de adaptación a lo largo de la vida

Cuando la búsqueda local mejora un individuo, ¿se transmite esa mejora a la descendencia? Hay dos modelos:

### 8.1 Lamarkiano

> Los rasgos adquiridos por un individuo durante su vida **pueden** transmitirse a su descendencia.

- El individuo es **reemplazado** por el vecino con mejor fitness encontrado mediante búsqueda local
- El genotipo mejorado entra a la población y puede heredarse

### 8.2 Baldwiniano

> Los rasgos adquiridos por un individuo durante su vida **no pueden** transmitirse a su descendencia.

- El individuo recibe el **fitness** (pero no el genotipo) de un vecino con mejor fitness obtenido por búsqueda local
- El genotipo original permanece sin cambios; solo cambia su evaluación
- Este efecto de la experiencia sobre la evolución se conoce como **"efecto Baldwin"**

> El dogma central de la genética establece que los rasgos adquiridos durante la vida no pueden reescribirse en los gametos. Sin embargo, los MAs **no están restringidos por la biología real**, por lo que en la práctica se suele aplicar el **Lamarkianismo** por ser más eficiente.

---

## 9. Otras cuestiones a considerar en los MAs

- La búsqueda local **puede reducir la diversidad** de la población y provocar **convergencia prematura** → se pueden incluir mecanismos explícitos para mantener la diversidad

- Es más ventajoso utilizar una búsqueda local que use un **movimiento DIFERENTE** al utilizado por los operadores de cruce y mutación:
	- Un óptimo local en un *landscape* puede ser un punto con gradiente en otro → la búsqueda local "escapa" de trampas del AE

- La búsqueda local implica **muchas evaluaciones** y puede ser **costosa** si no se optimiza
	- Como consecuencia, la búsqueda global del AE realizará **menos evaluaciones** totales (hay que compensar el presupuesto computacional)
