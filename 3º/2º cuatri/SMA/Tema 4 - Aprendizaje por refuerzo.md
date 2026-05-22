## Índice

1. [[#4.1. Introducción y Objetivos]]
2. [[#4.2. Algoritmo Q-learning]]
3. [[#4.3. Selección de Acciones]]
4. [[#4.4. Inicialización]]
5. [[#4.5. Entornos Deterministas y No Deterministas]]
6. [[#4.6. Resumen]]

---

## 4.1. Introducción y Objetivos

### Contexto: Diferencia con el Tema 3

En el **Tema 3** se estudiaron:

- Agentes basados en utilidad que actúan en entornos **MDP**
- Los agentes tenían **conocimiento completo** del entorno (transiciones, recompensas, etc.)
- Se usaba el **algoritmo de iteración de valores** para calcular la política óptima

En el **Tema 4**, el tipo de entorno es el mismo (decisiones secuenciales, basado en recompensas, modelable como MDP), **pero** los agentes **NO tienen conocimiento completo del entorno**. Los agentes deben **aprender su política** → esto es el **Aprendizaje por Refuerzo**.

**Ejemplos de aplicación:** laberintos, robots que se mueven en entornos desconocidos, agentes que juegan a juegos.

---

### Descripción del Entorno

|Elemento|Descripción|
|---|---|
|**S** — Estados posibles|Posiblemente no se conoce; solo se conocen los estados visitados|
|**A** — Acciones posibles|La relación de acciones por estados (s, a) puede ser solo parcialmente conocida|
|**T(s, a, s')** — Modelo de transición|`T: S × A × S → [0..1]` **desconocido**|
|**r(s, a, s')** — Modelo de recompensas|`r: S × A × S → ℝ` **desconocido**|

El agente solo percibe el **estado actual** y la **recompensa** tras cada acción. El ciclo de interacción es:

```
Entorno [T(s,a,s'), r(s,a,s')] ---(s, r)---> Agente [π(s)] ---(a)---> Entorno
```

### Objetivo

Aprender la **política óptima** `π*: S → A` que **maximiza las recompensas acumuladas esperadas**.

---

### Ejemplo Ilustrativo: El Laberinto

- Hay diferentes caminos; algunos salen del laberinto.
- En cada camino se gana o pierde una cantidad de euros (recompensas) que se desconocen a priori.
- No se conocen a priori los posibles caminos ni todos los posibles estados.
- En cada estado (cruce de caminos) se puede elegir entre varias acciones (caminos).
- **Objetivo:** aprender las acciones que permiten pasar el laberinto con la mayor ganancia posible.
- Para ello, se puede recorrer el laberinto tantas veces como se quiera.

> **Pregunta clave:** ¿Cómo podemos aprender las acciones óptimas en cada estado?

---

### Tipos de Métodos de Aprendizaje por Refuerzo

La idea básica del Aprendizaje por Refuerzo es:

- Actuar en el entorno por **prueba y error**
- Mejorar la política de control en base al **refuerzo (recompensas) recibido**

Existen dos grandes familias de métodos:

#### Métodos libres del modelo _(model-free)_

- Solo se intenta aprender la **política óptima** directamente
- Ejemplo: **Q-learning** (Watkins, 1989)

#### Métodos basados en el modelo _(model-based)_

- Se aprende también el **modelo** (transiciones y recompensas)
- Se usa esa información para actualizar la política aprendida

---

## 4.2. Algoritmo Q-learning

### Idea General

El algoritmo Q-learning busca aprender una función **Q** que aproxime la función óptima **Q***. Una vez aprendida, la política del agente se determina como:

$$\pi(s) = \arg\max_{a \in A(s)} Q(s, a)$$

**Diferencias respecto a la iteración de valores para MDP:**

- La actualización de los valores Q se realiza de forma **dinámica, paso a paso**
- El algoritmo mejora/actualiza los valores Q **mientras el agente actúa** en el entorno durante varios (posiblemente muchos) episodios
- El agente aprende a mejorar su política **repitiendo episodios** en el mismo entorno

---

### Algoritmo Q-learning para Entornos Deterministas

> _Se analiza primero el caso de un **entorno determinista** (el agente sabe que no hay acciones no deterministas)_

Los valores Q se almacenan en una **tabla `<estado, acción>`** (la memoria del agente).

```
Repite para muchos episodios (o para siempre):

01: s ← observar estado entorno
02: if s es un estado desconocido:          // inicialización de Q(s,a)
03:     for all acciones a en s: añade Q(s,a) a la memoria e inicializa su valor
04: while s != estado terminal do           // o durante toda la vida
05:     a ← seleccionar siguiente acción en s   // Política de selección de acciones
06:     ejecutar a
07:     r ← recompensa
08:     s' ← nuevo estado
09:     if s' es un estado desconocido:     // inicialización de Q(s',b)
10:         for all acciones b en s': añade Q(s',b) a la memoria e inicializa su valor
11:         Q(s, a) = r + γ · max_{b∈A(s')} Q(s', b)   // actualización de Q
12:     s ← s'
13: end while
```

**Fórmula de actualización (entorno determinista):**

$$Q(s, a) = r + \gamma \cdot \max_{b \in A(s')} Q(s', b)$$

---

### Ejemplo de Actualización (Entorno Determinista)

**Situación:** El agente está en $s_0$, con $\gamma = 0{,}9$.

- Acciones disponibles: $a$ con $Q(s_0, a) = 2$; $b$ con $Q(s_0, b) = 0$
- El agente elige $a$. El entorno transita a $s_1$ con recompensa $r = 2$
- Los valores en $s_1$ son: $Q(s_1, a) = -7$; $Q(s_1, b) = -1$

**Actualización:**

$$Q(s_0, a) := r + \gamma \cdot \max{Q(s_1, a), Q(s_1, b)} = 2 + 0{,}9 \cdot \max{-1; -7} = 1{,}1$$

---

### Traza de Ejecución del Ejemplo Determinista

**Parámetros:**

- $Q(s, a)$ inicializados en 0
- En cada estado se selecciona la acción con mayor valor $Q(s, a)$
- En caso de empate se elige aleatoriamente (en este caso, la acción "a")
- Estado inicial: $s_0$; $\gamma = 1$

**Movimientos del primer episodio:**

|Mov.|Estado|Acción|Estado nuevo|Rec.|
|---|---|---|---|---|
|inic.|$s_0$||||
|1|$s_0$|a|$s_1$|2|
|2|$s_1$|a|$s_2$|-7|
|3|$s_2$|a|$s_1$|6|
|4|$s_1$|b|$s_3$|-1|
|5|$s_3$|a|$s_1$|-3|
|6|$s_1$|b|$s_3$|-1|
|7|$s_3$|b|$s_4$|6|

**Valores finales tras el primer episodio:**

|$Q(s_0,a)$|$Q(s_0,b)$|$Q(s_1,a)$|$Q(s_1,b)$|$Q(s_2,a)$|$Q(s_2,b)$|$Q(s_3,a)$|$Q(s_3,b)$|
|---|---|---|---|---|---|---|---|
|2|0|-7|-1|6|0|-4|6|

---

### Segundo Episodio (con valores aprendidos)

Con los valores aprendidos en el primer episodio, el segundo episodio sigue un camino diferente (ya que los Q han cambiado). Tras el segundo episodio, los valores se actualizan de nuevo:

|$Q(s_0,a)$|$Q(s_0,b)$|$Q(s_1,a)$|$Q(s_1,b)$|$Q(s_2,a)$|$Q(s_2,b)$|$Q(s_3,a)$|$Q(s_3,b)$|
|---|---|---|---|---|---|---|---|
|1|0|-7|5|6|0|-4|6|

> **Pregunta:** ¿Qué ocurre si repetimos el mismo episodio de nuevo (y de nuevo)?

---

### Problema: Exploración Insuficiente

Tras muchas ejecuciones con política greedy pura, el agente aprende el siguiente camino:

- **Camino aprendido:** $s_0 \to s_1 \to s_3 \to s_4$ → recompensa acumulada = **7**
- **Camino óptimo real:** $s_0 \to s_2 \to s_1 \to s_3 \to s_4$ → recompensa acumulada = **9**

**Causa:** el agente **nunca probó la acción $b$ en $s_0$ ni en $s_2$**.

> **Problema:** el agente **no explora** lo suficientemente el entorno.

---

## 4.3. Selección de Acciones

### El Dilema: Explotación vs. Exploración

- El agente quiere **explotar lo aprendido** (ejecutar las mejores acciones conocidas)
- Pero también necesita **explorar acciones nuevas**
- Este es un **problema típico en el aprendizaje automático**
- La cuestión de fondo es saber si ya se ha aprendido "lo suficiente" o hay que seguir

---

### Estrategia 1: Política _Greedy_

En cada estado $s$, elegir **siempre** la acción $a$ con el mayor valor $Q(s, a)$:

$$\arg\max_{a \in A(s)} Q(s, a)$$

Si hay varias acciones con el mismo valor máximo, se elige aleatoriamente entre ellas.

**Problema:** hay riesgo de **explotar demasiado** acciones buenas descubiertas al principio del aprendizaje, sin considerar acciones potencialmente mejores.

---

### Estrategia 2: Política _ε-greedy_

En cada estado $s$, la acción se elige según:

- Con probabilidad **ε**: elegir **cualquier acción aleatoriamente** (exploración)
- Con probabilidad **1 - ε**: elegir la acción con el **máximo valor Q(s, a)** (explotación)

De esta forma el agente equilibra explotación y exploración.

**Representación de una posible secuencia de selección:**

```
○ ● ◉ ● ○ ◉ ○ ● ○ ● ◉ ○ ● ○ ● ◉ ○ ● ...
(● = acción de mayor valor Q;  ◉ = acción aleatoria)
```

---

### Estrategia 3: Política _Softmax_

Con _ε-greedy_, cuando se elige aleatoriamente, **todas las acciones tienen la misma probabilidad**. La estrategia _softmax_ mejora esto: las acciones se eligen según su valor Q, de modo que **una acción tiene más probabilidad si tiene mayor valor Q**.

La probabilidad de elegir la acción $a$ en el estado $s$ se calcula como:

$$P(a | s) = \frac{e^{Q(s,a)/\tau}}{\sum_{b \in A(s)} e^{Q(s,b)/\tau}}$$

Donde **τ (tau)** es un parámetro llamado **temperatura**:

- Si **τ es alto** → mayor probabilidad de elegir de forma aleatoria (más exploración)
- Si **τ tiende hacia 0** → más probabilidad a la acción (o acciones) de mayor valor Q (más explotación)

---

### Estrategia 4: _Softmax_ o _ε-greedy_ con Decadencia

**Idea:** explorar más al principio y, conforme se aprende más, explotar más y explorar menos. Se reduce ε o τ **con el tiempo**.

Esta idea refleja de alguna forma el comportamiento humano (al principio se exploran más opciones; con experiencia, se explotan las mejores conocidas).

**Ejemplo de secuencia con decadencia (más exploración al principio → menos al final):**

```
● ● ◉ ● ● ● ◉ ● ● ● ◉ ● ● ● ● ● ◉ ● ...
(● = acción de mayor valor Q;  ◉ = acción aleatoria)
```

---

## 4.4. Inicialización

La **inicialización de los valores $Q(s, a)$** también influye en la manera de explorar las diferentes opciones.

### Tipos de Inicialización

#### Inicialización Optimista

- Se inicializa con valores **altos**, por encima de los valores reales
- Genera **mayor exploración**: como todos los Q iniciales son muy altos, cualquier acción ejecutada devuelve un valor real más bajo, lo que "decepciona" y motiva al agente a probar otras acciones

#### Inicialización Pesimista

- Se inicializa con valores **bajos**, por debajo de los valores reales
- Genera **menos exploración**

#### Inicialización Neutra

- $Q(s, a) := 0$
- Supone un equilibrio entre las dos anteriores

#### Inicialización con Recompensas Conocidas

- Si se conocen las recompensas a priori, se pueden usar directamente para inicializar los valores

---

### ¿Por qué la Inicialización Optimista Favorece la Exploración?

Si todos los valores Q se inicializan en un valor muy alto (p. ej., 20), cuando el agente ejecuta una acción y recibe una recompensa real (normalmente menor), actualiza el Q hacia abajo. Como el valor de esa acción "cae" y los demás siguen altos, el agente se ve motivado a probar otras acciones (que aún tienen el valor inicial alto). Esto **fuerza la exploración de todas las acciones** antes de que el agente empiece a explotar.

---

## 4.5. Entornos Deterministas y No Deterministas

### El Problema con Entornos No Deterministas

El algoritmo presentado hasta ahora **solo sirve para entornos deterministas**.

En un **entorno no determinista**, al realizar la acción $a$ en el estado $s$ es posible transitar a $s'$ (con probabilidad $p'$) o a $s''$ (con probabilidad $p''$). Las probabilidades son desconocidas (incluso puede ser desconocido que la acción sea no determinista).

**Problema con la actualización determinista:**  
Si el agente elige $a$ y transita a $s'$, la actualización sería:

$$Q(s, a) = r + \gamma \cdot \max_{b \in A(s')} Q(s', b) = 2 + 1 \cdot \max{2; 1} = 4$$

Pero este valor **no sería correcto**, ya que dependiendo de las probabilidades, el valor esperado real es una mezcla entre el resultado por $s'$ y el resultado por $s''$.

**Solución:** hay que actualizar $Q(s, a)$ solo con **una parte de esta nueva información** recién descubierta → se introduce la **constante de aprendizaje α**.

---

### Algoritmo Genérico (Determinista y No Determinista)

```
Repite para muchos episodios (o para siempre):

01: s ← observar estado entorno
02: if s es un estado desconocido:          // inicialización de Q(s,a)
03:     for all acciones a en s: añade Q(s,a) a la memoria e inicializa su valor
04: while s != estado terminal do           // o durante toda la vida
05:     a ← seleccionar siguiente acción en s   // Política de selección de acciones
06:     ejecutar a
07:     r ← recompensa
08:     s' ← nuevo estado
09:     if s' es un estado desconocido:     // inicialización de Q(s',b)
10:         for all acciones b en s': añade Q(s',b) a la memoria e inicializa su valor
11:         Q(s, a) = (1 - α) · Q(s, a) + α · [r + γ · max_{b∈A(s')} Q(s', b)]   // actualización de Q
12:     s ← s'
13: end while
```

> **0 < α < 1**: constante de aprendizaje

**Fórmula de actualización (genérica):**

$$Q(s, a) = (1 - \alpha) \cdot Q(s, a) + \alpha \left[ r + \gamma \cdot \max_{b \in A(s')} Q(s', b) \right]$$

---

### Interpretación de la Fórmula de Actualización

Esta fórmula es muy recurrente en el aprendizaje por refuerzo. Sus componentes son:

```
Q(s,a)     =    (1 - α) · Q(s,a)   +   α · [r + γ · max Q(s',b)]
   ↑                    ↑                          ↑
estimación         estimación              nueva información /
actualizada         anterior                  observación
```

- Se ajusta el valor de $Q(s, a)$ haciendo una **media ponderada** (por α) entre:
    - el **valor estimado hasta ahora** (estimación anterior)
    - el **valor observado en la situación actual** (nueva información)
- **α** representa la porción (ponderación) de la nueva información respecto a la estimación anterior
- **0 < α ≤ 1** (típicamente α es pequeño; se da mucho más peso a la estimación anterior)

**Efecto de α:**

- Si **α es mayor** → los valores Q(s,a) cambian más rápido (aprendizaje más veloz pero menos preciso)
- Si **α es menor** → se obtiene mayor precisión de los valores Q(s,a) (aprendizaje más lento pero más estable)

---

### Ejemplo de Actualización con α

**Situación:** agente en $s_2$, elige acción $a$ con $Q(s_2, a) = 6$.  
Transita a $s_5$, recibe recompensa $r = -2$.  
Valores en $s_5$: $Q(s_5, a) = -6$; $Q(s_5, b) = -2$.  
Parámetros: $\alpha = 0{,}1$; $\gamma = 0{,}9$

**Cálculo:**

$$Q(s_2, a) = (1 - 0{,}1) \cdot 6 + 0{,}1 \cdot \left[-2 + 0{,}9 \cdot \max{-6; -2}\right]$$ $$= 0{,}9 \cdot 6 + 0{,}1 \cdot \left[-2 + 0{,}9 \cdot (-2)\right]$$ $$= 5{,}4 + 0{,}1 \cdot (-2 - 1{,}8) = 5{,}4 - 0{,}38 = 5{,}02$$

---

### Ejercicio: Ejemplo con Entorno No Determinista

**Entorno:** igual al ejemplo del grafo de estados, pero la acción $b$ en $s_2$ es no determinista:

- Con probabilidad ½ → transita a $s_3$ con recompensa 12
- Con probabilidad ½ → transita a $s_4$ con recompensa 8

**Parámetros:** $Q(s,a)$ inicializados en 0; estado inicial $s_0$; $\gamma = 1$; $\alpha = 0{,}3$

**Reglas de los 4 episodios:**

- Episodios 1 y 2: el agente elige siempre la acción de mayor valor Q (y la acción $b$ en caso de empate)
- Episodios 3 y 4: igual, salvo en $s_0$ donde el agente elige $b$ para **explorar**
- Para la acción $b$ en $s_2$: la primera vez transita a $s_3$, la segunda a $s_4$, la tercera de nuevo a $s_3$, y así sucesivamente (alternando)

**Valores tras los 4 episodios:**

|$Q(s_0,a)$|$Q(s_0,b)$|$Q(s_2,a)$|$Q(s_2,b)$|$Q(s_3,a)$|$Q(s_3,b)$|$Q(s_1,a)$|$Q(s_1,b)$|
|---|---|---|---|---|---|---|---|
|0,6|0,834|0|7,962|0|3,942|0,24|0|

---

## 4.6. Resumen

### Condiciones de Convergencia del Q-learning

El Q-learning **garantiza la convergencia** de $Q(s, a)$ a $Q^*(s, a)$ si se cumplen las siguientes condiciones:

1. **El entorno se puede modelar como un MDP**
    
2. **La constante de aprendizaje α decrece con el tiempo:**  
    En cada actualización $i$ de $Q(s,a)$, la constante de aprendizaje $\alpha_i$ debe satisfacer: $$\sum_{i=0}^{\infty} \alpha_i = \infty \quad \text{y} \quad \sum_{i=0}^{\infty} \alpha_i^2 < \infty$$ Un ejemplo válido: $\alpha = \frac{1}{n(s,a)}$, donde $n(s,a)$ es el número de veces que se ha actualizado el valor $Q(s,a)$
    
3. **Cada pareja (s, a) es visitada un número infinito de veces**
    
4. **El entorno es estacionario** (la probabilidad de transitar de $s$ a $s'$ ejecutando la acción $a$ no varía en el tiempo)
    

---

### Ejemplos Reales de Aplicación

#### Helicóptero Autónomo (Stanford)

- Aprendizaje para controlar un helicóptero acrobático autónomo
- Referencia: http://heli.stanford.edu/
- El aprendizaje puede realizarse de manera **online** o **offline**. A ser posible, se aprende la política óptima de manera **offline** y luego se aplica en el problema real

#### TD-Gammon (Tesauro, 1995)

Uno de los mejores resultados históricos en aprendizaje por refuerzo:

- **Objetivo:** aprender a jugar al Backgammon
- **Estructura de recompensas:**
    - +100 si la acción ejecutada gana la partida
    - -100 si la acción ejecutada pierde la partida
    - 0 para todas las demás acciones
- **Proceso de aprendizaje:** 1.500.000 partidas jugadas contra sí mismo

|Programa|Partidas de entrenamiento|Oponentes|Resultados|
|---|---|---|---|
|TDG 1.0|300.000|Robertie, Davis, Magriel|-13 pts/51 games (-0,25 ppg)|
|TDG 2.0|800.000|Goulding, Woolsey, Snellings, Russell, Sylvester|-7 pts/38 games (-0,18 ppg)|
|TDG 2.1|1.500.000|Robertie|-1 pt/40 games (-0,02 ppg)|

---

### Implementaciones en NetLogo

- **Versión determinista:**  
    `T4_1_MDP_q-learning_determinista_entornodeterminista.nlogo`
    
- **Versión no determinista** (aunque aplicado a un entorno determinista):  
    `T4_2_MDP_q-learning_NOdeterminista_entornodeterminista.nlogo`
    

---

### Problema Principal del Algoritmo en su Versión Simple

El algoritmo de aprendizaje por refuerzo en su versión más simple **tiene que almacenar un valor $Q(s,a)$ para cada pareja estado-acción** (por ejemplo, en una tabla). Esto es inviable para entornos muy grandes:

> El **ajedrez** tiene $10^{43}$ estados

---

### Variaciones y Extensiones del Algoritmo

- **Representación compacta de los estados** (en lugar de tablas explícitas)
- **Extensiones para espacios de estados y acciones continuos**
- **Aprendizaje basado en el modelo** (se aprende también el modelo del entorno)
- **Transferencia de aprendizaje:** reutilizar la función $Q(s,a)$ aprendida para un problema concreto y aplicarla a otro problema similar
- **Variaciones del aprendizaje** en función de la información disponible
- **Deep Q-learning** (uso de redes neuronales profundas para aproximar la función Q)

---

## Esquema Conceptual General

```
Aprendizaje por Refuerzo
│
├── Objetivo: Aprender π*(s) sin conocer T ni r
│
├── Algoritmo base: Q-learning (Watkins, 1989)
│   ├── Actualización: Q(s,a) ← (1-α)·Q(s,a) + α·[r + γ·max Q(s',b)]
│   ├── Memoria: tabla <estado, acción>
│   └── Política: π(s) = argmax Q(s,a)
│
├── Selección de acciones
│   ├── Greedy → solo explotación (problema: no explora)
│   ├── ε-greedy → equilibrio explotación/exploración
│   ├── Softmax → explotación proporcional al valor Q
│   └── Con decadencia → más exploración al inicio, más explotación al final
│
├── Inicialización de Q(s,a)
│   ├── Optimista (valores altos) → más exploración
│   ├── Pesimista (valores bajos) → menos exploración
│   └── Neutra (= 0) → equilibrio
│
├── Entornos no deterministas
│   └── Se usa α (constante de aprendizaje) para ponderar la nueva info
│
└── Convergencia garantizada si:
    1. Entorno modelable como MDP
    2. α decrece con el tiempo (Σαᵢ = ∞ y Σαᵢ² < ∞)
    3. Cada (s,a) visitada infinitas veces
    4. Entorno estacionario
```

---
