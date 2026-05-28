## Índice del Tema

1. [[#9.1 Racionalidad en entornos multiagente]]
2. [[#9.2 Juegos en forma normal]]
3. [[#9.3 Computar equilibrios de Nash]]

---
## 9.1 Racionalidad en entornos multiagente

### Situación general

- Múltiples agentes actúan en el **mismo entorno**.
- Desde el punto de vista de un agente, **los demás agentes forman parte de su entorno**.
- Este entorno **no es estático**: sin que nuestro agente actúe, los demás pueden introducir cambios.
- Las acciones de los demás agentes pueden influir en el **grado de alcance del objetivo** (o en la utilidad) de nuestro agente.
- Nuestro agente **no puede controlar** las acciones de los demás, porque son **autónomos**.

### Entorno dinámico de forma específica

- El entorno **no** cambia únicamente por procesos aleatorios desconocidos.
- Los cambios son introducidos por agentes que eligen sus acciones **guiados por sus propios objetivos** (para maximizar su propia utilidad).
- Si nuestro agente **conoce los objetivos de los demás**, puede «ponerse en su lugar» y **anticipar sus acciones**… para tomarlas en cuenta al elegir las propias.
- Un entorno multiagente que cambia **únicamente por las acciones de los agentes** se llama **semi-dinámico**.

> **Ejemplo de entorno semi-dinámico: Ajedrez**  
> El estado del entorno equivale a una posición de las fichas en el tablero. Desde el punto de vista del jugador blanco, la única forma de cambiar el estado del entorno (aparte de cuando le toca jugar a él) es cuando el jugador negro mueve ficha.

### Racionalidad en el Ajedrez

- Cuando le toca mover al jugador blanco, para evaluar una posible jugada:
  - Intenta **anticipar** con qué jugada contestaría el jugador negro.
  - Y cómo, a su vez, él respondería a esa jugada, etc.
  - La conveniencia de la posición alcanzada a través de una secuencia de movimientos caracteriza la adecuación de la jugada.
- **Condición clave:** el jugador blanco conoce los objetivos del jugador negro.
  - En el ajedrez esto se cumple: sabe que el negro tiene el objetivo de ganar, y por tanto hará lo posible para que pierda el blanco.

### Aplicaciones reales (sector energía e infraestructuras)

- **Crowdshipping:** mensajeros autónomos negocian rutas, intercambio de paquetes, etc.
- **Recarga de vehículos eléctricos:** dueños de coches eléctricos *compiten* por la energía de recarga disponible.
- **Mercado eléctrico mayorista:** se asegura el suministro mediante agentes que negocian.
- **Redes eléctricas inteligentes:** igualar oferta y demanda en una red con millones de pequeños productores de energía individualmente racionales.

### ¿Por qué analizar decisiones racionales en entornos multiagente?

#### Nivel micro (punto de vista de un agente)
- Diseñar un **agente inteligente** que se desenvuelve bien en un entorno multiagente.
- Implementar una **estrategia** para ese agente: en cada momento, ¿cuál de sus acciones posibles debe elegir?
  - *En el ajedrez:* cuando le toca jugar al agente, ¿qué jugada hacer?
  - *En una subasta de energía:* cuando toca pujar, ¿qué precio ofrecer por kWh?
- Propiedades a analizar: optimalidad, complejidad computacional, incentivos para comportamiento estratégico, etc.

#### Nivel macro (punto de vista del sistema)
- **Diseñar un entorno** para que «el sistema» (el conjunto de los agentes interactuando) tenga propiedades deseadas.
- Para ello, hay que poder **predecir** las acciones que cada agente tomará.
- Propiedades a analizar: calidad de servicio, eficiencia, compatibilidad con los incentivos, etc.

### Ejemplo: Infraestructura telefónica futura

**Escenario:** asignación dinámica de llamadas telefónicas a compañías de telecomunicación. Objetivo: evitar comportamiento estratégico entre compañías.

**Entorno (protocolo de subasta):**
- Al descolgar el auricular, un agente software comunica las características de la llamada a las compañías disponibles.
- Las compañías contestan con una oferta (precio por minuto) mediante sus propios agentes software.
- El agente usuario elige una oferta según las «reglas de juego» del entorno (las reglas de la subasta).

#### Entorno 1: Subasta de *mejor precio*
- Se asigna la llamada a la compañía de la **oferta más baja**.
- El usuario paga el precio requerido por esa compañía.
- *Ejemplo:* Telefónica ofrece 0,18 €/min, Deutsche Telekom 0,22, British Telecom 0,23 → gana Telefónica, usuario paga **0,18 €/min**.
- **Problema:** hay incentivos para **comportamiento estratégico**.
  - Si Telefónica hubiera conocido los precios de los demás, podría haber pedido 0,21 €/min y aumentado su beneficio.
  - Como diseñadores del entorno, preferimos que las compañías inviertan en mejorar su infraestructura (bajar precios), no en modelar decisiones ajenas.

#### Entorno 2: Subasta de *segundo precio* (subasta Vickrey)
- Se asigna la llamada a la compañía de la **oferta más baja**.
- El usuario paga el precio de la **segunda oferta más baja**.
- *Ejemplo:* gana Telefónica, usuario paga **0,22 €/min**.
- **Propiedad macro: Compatibilidad con los incentivos.**
  - Ya no hay motivación para ninguna compañía de adoptar comportamiento estratégico.
  - Incluso si Telefónica conociera los precios ajenos, no podría aumentar su beneficio pidiendo más que su coste real (0,18 €/min), pues arriesgaría perder la llamada si su predicción fuera errónea.
  - **Desventaja:** el precio de la llamada es ligeramente más alto para el usuario (0,22 vs. 0,18 €/min).

### Resumen del Bloque III (visión global)

| Tema | Nivel | Enfoque |
|------|-------|---------|
| **Tema 9** | Micro + Macro | Formalismo: el entorno se modela como un «juego». Se determinan las mejores estrategias (micro) y los equilibrios (macro). |
| Tema 10 | Micro | Juegos en forma extensiva (acciones secuenciales). Diseño de estrategias para negociación automática. |
| Tema 11 | Macro | Diseñar reglas de interacción con propiedades deseadas. Técnicas para agregar preferencias. |
| Tema 12 | Macro | Subastas como entornos de negociación estructurada. Diseño de mecanismos. |

---

## 9.2 Juegos en forma normal

### Definición formal

Un **juego en forma normal** tiene los siguientes elementos:

| Elemento | Descripción |
|----------|-------------|
| **Jugadores** | Conjunto $P = \{1, \ldots, |P|\}$ |
| **Estrategias** | Conjunto $S_i$ para cada jugador $i$ |
| **Función de utilidad** | $U_i: S_1 \times \ldots \times S_{|P|} \to \mathbb{R}$ para cada jugador $i$ |

### Dinámica del juego

- Las estrategias $S_i$ representan las **opciones (acciones)** del jugador $i$.
- Los jugadores eligen sus estrategias $s_i \in S_i$ de forma **simultánea**.
  - Al elegir, el jugador $i$ **no sabe** qué estrategia jugarán los demás $P \setminus \{i\}$.
- Una combinación de estrategias así elegidas se llama **perfil estratégico** $s \in S$.
- Cada agente $i$ recibe su utilidad $U_i(s)$ correspondiente al perfil estratégico $s$.
- Los jugadores **no pueden comunicar explícitamente** durante el juego.
- Cada jugador $i$ es un **maximizador de utilidad**: prefiere el perfil estratégico que maximice $\max_{s \in S} U_i(s)$, aunque dicho perfil no depende solo de él.
- Se dice que el jugador $i$ prefiere un perfil $s$ sobre $s'$ (formalmente: $s >_i s'$) si $U_i(s) > U_i(s')$.

> **Restricción del tema:** se trabaja con **juegos bipersonales** ($P = \{1,2\}$) de **información completa** (ambos jugadores conocen los conjuntos de estrategias y las funciones de utilidad propias y del contrario).

### Matriz de juego (representación visual)

Para juegos bipersonales se usa una matriz $|S_1| \times |S_2|$:
- **Filas:** estrategias del jugador 1.
- **Columnas:** estrategias del jugador 2.
- **Celdas:** cada celda representa un perfil estratégico con las utilidades $(U_1, U_2)$.

---

### Ejemplo 1: Dilema del Prisionero (DP)

**Escenario:** dos cautivos interrogados por separado, con evidencia sobre un crimen cometido conjuntamente.

**Estrategias:**
- **D** (*defect*): delatarse / confesar.
- **C** (*cooperate*): callarse / negarlo todo.

**Resultados:**
| Situación | Consecuencia |
|-----------|-------------|
| Ninguno delata | Ambos: 1 año de cárcel |
| Ambos delatan | Ambos: 5 años de cárcel |
| Uno delata, el otro se calla | Delator: libre; callado: 10 años |

**Modelado como juego en forma normal:**
- $P = \{1, 2\}$, $S_1 = S_2 = \{C, D\}$
- Funciones de utilidad (años en cárcel como valores negativos):

| | $C$ | $D$ |
|---|-----|-----|
| $C$ | $-1,\ -1$ | $-10,\ 0$ |
| $D$ | $0,\ -10$ | $-5,\ -5$ |

- Preferencias:
  - Jugador 1: $(D,C) >_1 (C,C) >_1 (D,D) >_1 (C,D)$
  - Jugador 2: $(C,D) >_2 (C,C) >_2 (D,D) >_2 (D,C)$

#### Mejor estrategia en el DP

- Si jugador 2 juega $C$ → mejor respuesta del jugador 1 ($MR_1$): jugar $D$, porque $U_1((D,C)) > U_1((C,C))$.
- Si jugador 2 juega $D$ → mejor respuesta del jugador 1: jugar $D$, porque $U_1((D,D)) > U_1((C,D))$.
- De forma simétrica: $MR_2(C) = \{D\}$ y $MR_2(D) = \{D\}$.

**Jugar $D$ es una estrategia dominante para ambos jugadores** → es la mejor opción *independientemente* de lo que haga el otro.

#### Equilibrio en estrategias dominantes

- Si ambos jugadores tienen estrategias dominantes $s_a$ y $s_b$, el perfil $(s_a, s_b)$ se llama **equilibrio en estrategias dominantes**.
- Modela el resultado del juego cuando ambos jugadores son racionales.
- En el DP: equilibrio = $(D, D)$.
- **Limitación:** un equilibrio en estrategias dominantes **no existe en todos los juegos**.

---

### Ejemplo 2: Batalla de Géneros

**Escenario:** marido (J1) prefiere fútbol (F); esposa (J2) prefiere ópera (O). Solo hay utilidad si van juntos.

| | $F$ | $O$ |
|---|-----|-----|
| $F$ | $2,\ 1$ | $0,\ 0$ |
| $O$ | $0,\ 0$ | $1,\ 2$ |

**Análisis:** $MR_1(F)=\{F\}$, $MR_1(O)=\{O\}$ → $MR_1(F) \cap MR_1(O) = \emptyset$.
Lo mismo para J2. **No existe equilibrio en estrategias dominantes.**

→ Se necesita una **noción de equilibrio más débil**.

---

### Equilibrio de Nash

> Un perfil estratégico está en **equilibrio de Nash** si **ningún jugador puede mejorar su utilidad desviándose de él de forma unilateral**.

Formalmente: el perfil $(s_a, s_b)$ es un equilibrio de Nash si $s_a \in MR_1(s_b)$ **y** $s_b \in MR_2(s_a)$.

**Análisis de la Batalla de Géneros:**
- $(F,F)$: equilibrio de Nash ✓ ($F \in MR_1(F)$ y $F \in MR_2(F)$).
- $(O,O)$: equilibrio de Nash ✓ ($O \in MR_1(O)$ y $O \in MR_2(O)$).
- $(F,O)$: **no** es equilibrio ($F \notin MR_1(O)$).
- $(O,F)$: **no** es equilibrio ($O \notin MR_1(F)$).

#### Definición formal (n jugadores)

Sea $s_i$ la estrategia (posiblemente mixta) del jugador $i$, y $s_{-i}$ las estrategias de los demás. El perfil $(s_i, s_{-i})$ es un **equilibrio de Nash** si:

$$\forall i \in N\ \forall s' \in S_i.\ U_i\bigl((s', s_{-i})\bigr) \leq U_i\bigl((s_i, s_{-i})\bigr)$$

Para todo jugador $i$, si los demás juegan $s_{-i}$, entonces $i$ **no puede ganar nada** eligiendo una estrategia diferente de $s_i$ (aunque sea mixta).

> **Teorema (Nash, 1951):** Todo juego en el que cada jugador tiene un conjunto finito de estrategias tiene **al menos un equilibrio de Nash en estrategias mixtas**.

---

### Optimalidad de Pareto

Un perfil estratégico $s$ es **Pareto-óptimo** si no existe ningún otro perfil $s'$ en el que un jugador esté estrictamente mejor y los demás no estén peor:

$$\nexists s' \in S.\ \Bigl(\exists i \in N.\ U_i(s') > U_i(s)\ \land\ \forall k \in N.\ U_k(s') \geq U_k(s)\Bigr)$$

- Son los resultados considerados como **«eficientes»**.
- Ningún *grupo de jugadores* puede desviarse de un resultado Pareto-óptimo mejorando a alguien sin empeorar a otro.
- **Diferencia clave con el Equilibrio de Nash:** en el EN ningún *jugador individual* puede desviarse unilateralmente mejorando su utilidad.
- La optimalidad de Pareto es exigible a cualquier noción de **bienestar social** (ej.: la suma de las utilidades).

**Ejemplos comparados:**

| Juego | Resultados Pareto-óptimos | Equilibrios de Nash | Relación |
|-------|--------------------------|---------------------|----------|
| Batalla de Géneros | $(F,F)$, $(O,O)$ | $(F,F)$, $(O,O)$ | Coinciden |
| Dilema del Prisionero | $(C,C)$, $(C,D)$, $(D,C)$ | $(D,D)$ | El EN **no** es Pareto-óptimo |

> En el DP, el «resultado racional» no es eficiente porque se asume (en la Teoría de Juegos **no-cooperativa**) que los jugadores **no pueden alcanzar acuerdos vinculantes** («no se fían» los unos de los otros).

---

### Estrategias puras y mixtas

#### Estrategia pura
Elegir una única estrategia del conjunto $S_i$ con probabilidad 1.

**Problema:** puede haber juegos **sin equilibrio de Nash en estrategias puras**.

> **Ejemplo: «Céntimo a juego»**  
> Cada jugador convierte en secreto su moneda en cara o cruz. Si coinciden, gana J1; si no, gana J2.
>
> | | Cara | Cruz |
> |---|------|------|
> | Cara | $+1,\ -1$ | $-1,\ +1$ |
> | Cruz | $-1,\ +1$ | $+1,\ -1$ |
>
> En cualquier perfil estratégico, uno de los jugadores preferiría desviarse → **no hay equilibrio de Nash en estrategias puras**.

#### Estrategia mixta
Un jugador puede jugar cada estrategia con una cierta probabilidad.

Una **estrategia mixta** $em_i$ del jugador $i$ es una distribución de probabilidad sobre $S_i = \{s_1, \ldots, s_m\}$:

$$em_i = [p_1:s_1,\ \ldots,\ p_m:s_m] \quad \text{con } p_k \in [0,1] \text{ y } \sum_{k=1}^{m} p_k = 1$$

- $p_k$: probabilidad con la que el jugador $i$ juega la estrategia $s_k$.
- Si el jugador juega una estrategia fija ($p_k = 1$), se dice que juega una **estrategia pura**.
- Un **perfil estratégico mixto** $pem$ es un vector de estrategias mixtas, una por jugador.
- **Utilidad esperada** al jugar un perfil estratégico mixto $pem$:

$$U_i(pem) = \sum_{(s_a, s_b) \in S} U_i\bigl((s_a, s_b)\bigr) \cdot p_a \cdot p_b$$

**Equilibrio de Nash en estrategias mixtas (céntimo a juego):**
- El perfil $([0.5:cara,\ 0.5:cruz],\ [0.5:cara,\ 0.5:cruz])$ **es** un equilibrio de Nash.
- Si un jugador elige aleatoriamente 50/50, el otro siempre obtiene utilidad esperada 0, independientemente de la estrategia que juegue → no puede beneficiarse desviándose.
- $U_1(pem) = 1 \cdot 0{,}25 - 1 \cdot 0{,}25 + 1 \cdot 0{,}25 - 1 \cdot 0{,}25 = 0$.

---

### Nociones alternativas de equilibrio y extensiones

**Variantes del EN:**
- **EN aproximado ($\varepsilon$-Nash equilibrium):** ningún jugador puede ganar *más de $\varepsilon$* desviándose del equilibrio.
- **EN robusto ($k$-resilient Nash equilibrium):** ningún *grupo de hasta $k$ jugadores* puede ganar algo desviándose del equilibrio.

**Representaciones más ricas de juegos (no-cooperativos):**
- **Juegos en forma extensiva** (Tema 10): el juego requiere múltiples jugadas de cada agente.
- **Juegos repetidos:** el mismo juego se juega repetidamente por los mismos jugadores.
- **Juegos estocásticos:** secuencia de juegos donde el juego de cada ronda depende probabilísticamente del juego y las acciones de la ronda anterior.
- **Información parcial en juegos.**

---

## 9.3 Computar equilibrios de Nash

### Resultados de complejidad

- Encontrar **un** equilibrio de Nash en juegos finitos de suma general con dos o más jugadores es **PPAD-duro** → probablemente todos los algoritmos para este problema han de ser exponenciales (similar a NP).
- Encontrar **todos** los equilibrios de Nash en juegos finitos de suma general con dos jugadores requiere, en el peor caso, **tiempo exponencial** en el número de acciones de cada jugador.

> En la práctica se trabajan subproblemas concretos más tratables.

---

### Algoritmo 1: Búsqueda exhaustiva (2 jugadores, estrategias puras)

**Entrada:** matriz de juego $n \times m$ (jugador 1 tiene $n$ estrategias, jugador 2 tiene $m$).

**Algoritmo:**
```
Paso 1: Para todas las columnas c
          Marcar las utilidades máximas del jugador 1 en c

Paso 2: Para todas las filas f
          Marcar las utilidades máximas del jugador 2 en f

Paso 3: Para todas las celdas p
          SI ambas utilidades en p están marcadas
             → incluir p en el conjunto de equilibrios de Nash
```

- **Complejidad en tiempo:** $O(n \times m)$.
- **Problema de escalado:** al extender a juegos de $k$ jugadores, la complejidad sube a $O(|S|^k)$.

**Ejemplo (matriz 3×4):**

| | $s^2_1$ | $s^2_2$ | $s^2_3$ | $s^2_4$ |
|---|---------|---------|---------|---------|
| $s^1_1$ | 5, 4 | **3**, **7** | -10, -1 | **-2**, **7** |
| $s^1_2$ | 4, 8 | 1, 6 | **6**, **10** | -4, 8 |
| $s^1_3$ | **9**, **6** | **3**, **6** | 4, 3 | -7, **6** |

**Resultado: 5 equilibrios de Nash** (celdas con ambas utilidades marcadas).

---

### Algoritmo 2: Programación lineal (2 jugadores, juegos de suma cero)

#### Definición: juego bipersonal de suma cero
$$\forall s \in S_1\ \forall s' \in S_2.\ U_1\bigl((s,s')\bigr) = -U_2\bigl((s,s')\bigr)$$

#### Conceptos clave

**Estrategia Maxmin** $\bar{s}$ del jugador 1:
- Supone que cada estrategia suya $s$ será contestada con la estrategia del J2 que *minimice* $U_1$.
- Elige la estrategia que maximiza el peor caso:
$$\bar{s} = \arg\max_{s_1} \min_{s_2} U_1\bigl((s_1, s_2)\bigr)$$

**Estrategia Minmax** $\underline{s}$ del jugador 1:
- Supone que cada estrategia suya será contestada con la estrategia del J2 que *maximice* $U_2$.
- Elige la estrategia que minimiza el beneficio del contrario:
$$\underline{s} = \arg\min_{s_1} \max_{s_2} U_2\bigl((s_1, s_2)\bigr)$$

> **Teorema (basado en von Neumann, 1921):** En juegos bipersonales de suma nula, las estrategias de los agentes en equilibrio de Nash coinciden con sus estrategias Maxmin (y también Minmax).

#### Programa lineal para la estrategia del jugador 2 (Minmax)

Encontrar $em_2 = [p_1:s'_1, \ldots, p_m:s'_m]$ que minimice la utilidad del J1 ($u_1^*$ es la utilidad Minmax):

$$\text{minimizar}\ u_1^*$$
$$\text{s.a.}\ \sum_{k=1}^{m} U_1\bigl((s_j, s'_k)\bigr) \cdot p_k \leq u_1^* \quad \forall s_j \in S_1 \quad (n \text{ desigualdades, una por fila})$$
$$\sum_{k=1}^{m} p_k = 1 \qquad p_k \geq 0 \quad \forall k \in \{1, \ldots, m\}$$

#### Programa lineal para la estrategia del jugador 1 (Maxmin)

Encontrar $em_1 = [p_1:s_1, \ldots, p_n:s_n]$ que maximice la utilidad del J1 ($u_1^*$ es la utilidad Maxmin):

$$\text{maximizar}\ u_1^*$$
$$\text{s.a.}\ \sum_{j=1}^{n} U_1\bigl((s_j, s'_k)\bigr) \cdot p_j \geq u_1^* \quad \forall s'_k \in S_2 \quad (m \text{ desigualdades, una por columna})$$
$$\sum_{j=1}^{n} p_j = 1 \qquad p_j \geq 0 \quad \forall j \in \{1, \ldots, n\}$$

> **Resultado:** $(em_1, em_2)$ es una **estrategia mixta en equilibrio de Nash**.  
> **Ventaja:** la programación lineal garantiza poder resolverse en **tiempo polinomial**.

#### Ejemplo completo (juego de suma nula 2×2)

| | $s'_1$ | $s'_2$ |
|---|--------|--------|
| $s_1$ | $4,\ -4$ | $2,\ -2$ |
| $s_2$ | $1,\ -1$ | $3,\ -3$ |

Sin equilibrios de Nash en estrategias puras. Se aplica el método de programación lineal.

**Estrategia del jugador 2** (minimizar $u_1^*$, variable $p_1 \in [0,1]$, $p_2 = 1 - p_1$):
$$4p_1 + 2(1-p_1) \leq u_1^* \iff 2p_1 + 2 \leq u_1^*$$
$$1p_1 + 3(1-p_1) \leq u_1^* \iff -2p_1 + 3 \leq u_1^*$$

La menor cota superior está en la intersección de las dos rectas:
$$2p_1 + 2 = -2p_1 + 3 \implies p_1 = \frac{1}{4}$$

$$\Rightarrow em_2 = \left(\frac{1}{4},\ \frac{3}{4}\right)$$

**Estrategia del jugador 1** (maximizar $u_1^*$, variable $p_1 \in [0,1]$, $p_2 = 1-p_1$):
$$4p_1 + 1(1-p_1) \geq u_1^* \iff 3p_1 + 1 \geq u_1^*$$
$$2p_1 + 3(1-p_1) \geq u_1^* \iff -p_1 + 3 \geq u_1^*$$

La mayor cota inferior está en la intersección:
$$3p_1 + 1 = -p_1 + 3 \implies p_1 = \frac{1}{2}$$

$$\Rightarrow em_1 = \left(\frac{1}{2},\ \frac{1}{2}\right)$$

**Equilibrio de Nash:**
$$pem = \left(\left(\frac{1}{2},\ \frac{1}{2}\right),\ \left(\frac{1}{4},\ \frac{3}{4}\right)\right)$$

---

### Algoritmo 3: Mejor respuesta iterada / heurística (k jugadores, estrategias puras)

También llamado *iterated best response* o *myopic best response*.

**Entrada:** matriz k-dimensional. La celda $[j_1, \ldots, j_k]$ contiene el vector de utilidades $(u_1, \ldots, u_k)$ del perfil estratégico en el que cada jugador $i$ juega su $j_i$-ésima estrategia.

**Algoritmo (tipo hill climbing):**
```
Elegir un perfil estratégico σ al azar
Repetir
    Elegir un jugador i al azar. Sea σ = (s_i, s_{-i})
    Computar las mejores respuestas MR_i(s_{-i}) de i a s_{-i}
    Elegir una s_i' ∈ MR_i(s_{-i})
    Actualizar σ: σ ← (s_i', s_{-i})
Hasta que s_i' = s_i para todos los jugadores i  o  "timeout"
```

- Para ciertos tipos de juegos llamados **potential games**, encuentra un equilibrio de Nash rápidamente.
- En el caso general **puede haber ciclos** (de ahí el «timeout»).

#### Ejemplo (3 jugadores): $S_1 = \{U,D\}$, $S_2 = \{L,R\}$, $S_3 = \{W,E\}$

**Si J3 juega W:**

| | L | R |
|---|---|---|
| U | 3, 4, 4 | 1, 3, 3 |
| D | **8, 1, 4** | **2, 0, 6** |

**Si J3 juega E:**

| | L | R |
|---|---|---|
| U | 4, 0, 5 | **0, 1, 6** |
| D | 5, 1, 3 | **1, 2, 5** |

**Traza del algoritmo** (partida: $(U, R, E)$, orden cíclico J1→J2→J3):

$$(U,R,E) \xrightarrow{J_1} (D,R,E) \xrightarrow{J_2} (D,R,E) \xrightarrow{J_3} (D,R,W) \xrightarrow{J_1} (D,R,W) \xrightarrow{J_2} (L,R,W) \xrightarrow{J_3} (L,R,W) \xrightarrow{J_1} (L,R,W)$$

**Resultado:** ningún jugador se desvía unilateralmente de $(L, R, W)$ → **es equilibrio de Nash**.

---

### Extensión: Juego ficticio (*fictitious play*)

En la práctica, algunas suposiciones no se cumplen:
- Los jugadores muchas veces **desconocen la matriz de juego completa**.
- Un jugador solo observa: su propia estrategia, la estrategia de los demás, y su propia utilidad obtenida.
- Además, **el mismo juego se juega de forma repetida** («juego evolutivo»).

→ En estas situaciones, los jugadores deben **ir aprendiendo su mejor estrategia sobre la marcha**.

Al generalizar la idea del algoritmo de mejor respuesta iterada a esta situación, se llega a un algoritmo de aprendizaje muy usado: el **juego ficticio** (*fictitious play*).

---

## Bibliografía del Bloque III

- Stuart Russell y Peter Norvig (2021): *Artificial Intelligence – A Modern Approach* (4ª ed.). Pearson. Cap. 18.
- Yoav Shoham y Kevin Leyton-Brown (2009): *Multiagent Systems – Algorithmic, Game-Theoretic, and Logical Foundations*. Cambridge University Press. Caps. 9 y 10.
- Michael Wooldridge (2009): *An Introduction to MultiAgent Systems* (2ª ed.). John Wiley & Sons. Caps. 11, 14 y 15.
- Shaheen Fatima, Sarit Kraus y Michal Wooldridge (2015): *Principles of Automated Negotiation*. Cambridge University Press. Caps. 2, 3, 5 y 6.
