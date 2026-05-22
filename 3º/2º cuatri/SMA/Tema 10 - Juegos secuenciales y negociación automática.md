## Índice

1. [[#10.1 Juegos en Forma Extensiva]]
2. [[#10.2 Conceptos Básicos de la Negociación Automática]]
3. [[#10.3 Negociación Unidimensional]]
4. [[#10.4 Negociación Multidimensional]]
5. [[#10.5 Negociación Heurística]]

---

## 10.1 Juegos en Forma Extensiva

### Motivación

- En los **juegos en forma normal**, los jugadores eligen sus estrategias **una vez** y de forma **simultánea**.
- Muchas situaciones del mundo real requieren **múltiples jugadas** que se realizan de forma **secuencial**.
- Dichas situaciones se pueden modelar mediante **juegos en forma extensiva**.

### Definición

Un **juego en forma extensiva** es un **árbol etiquetado**:

- Los **nodos** representan los **estados del juego**. La raíz del árbol es el **estado inicial**.
- Los **arcos** representan una jugada que lleva al juego del nodo padre al nodo hijo. Están etiquetados con el nombre de la **acción**.
- Los **nodos interiores** representan estados en los que el juego sigue, y están etiquetados con el **jugador** $i \in N$ al que le toca realizar una jugada.
- Los **nodos hoja** representan **estados terminales** del juego, y están etiquetados con un vector $(U_1, \ldots, U_{|N|})$, siendo $U_i$ la utilidad obtenida por cada jugador $i$.

### Ejemplo: Mercado de Renovables

- **Jugador 1:** Gran comercializadora eléctrica → decide entre entrar en el mercado de renovables (**IN**) o no (**OUT**).
- **Jugador 2:** Pequeña comercializadora ya en el mercado → si entra el Jugador 1, decide entre estrategia **cooperativa (CO)** o **agresiva con descuentos (AG)**.
- Resultados:
    - OUT → $(0, 2)$
    - IN + CO → $(0.5, 0)$
    - IN + AG → $(-0.5, -1)$

```
         Jugador 1 (e1)
           /        \
         IN          OUT
          |            |
    Jugador 2 (e2)    (e3)
       /      \       (0, 2)
      CO       AG
      |         |
    (e4)       (e5)
  (0.5, 0)  (-0.5, -1)
```

---

### Forma Normal Asociada

- Una **estrategia** de un jugador $i$ especifica, en cada estado $e_i$ en el que le toca jugar, qué acción elige.
- El conjunto de estrategias $S_i$ se puede concebir como el **producto cartesiano** de los conjuntos de acciones entre los que puede elegir el jugador cada vez que le toca jugar.
- Un **perfil estratégico** describe un conjunto de arcos del árbol que constituye un **camino completo** de la raíz a una hoja.
- La etiqueta de esa hoja es el **vector de utilidades** correspondiente al perfil, y se denota en la celda de la matriz del juego en forma normal asociado.

**Matriz del juego normal asociado al ejemplo:**

||**CO**|**AG**|
|---|---|---|
|**IN**|0.5, 0|-0.5, -1|
|**OUT**|0, 2|0, 2|

---

### Equilibrios de Nash Contraintuitivos

- El juego en forma normal asociado tiene **dos equilibrios de Nash**: **(OUT, AG)** y **(IN, CO)**.
- Sin embargo, **(OUT, AG)** **no parece realista**:
    - Con (OUT, AG), en $e_1$ el Jugador 1 elige OUT porque el Jugador 2 "amenaza" con jugar AG en $e_2$.
    - Pero esta amenaza **no es creíble**: para el Jugador 2, en $e_2$ lo racional sería jugar CO (obtiene utilidad 0 en vez de −1).
    - No sería racional para el Jugador 2 jugar AG en $e_2$ para "perjudicar" al Jugador 1, porque así se perjudicaría también a sí mismo.
- Es necesario **adaptar el concepto de equilibrio de Nash** para evitar este tipo de equilibrios contraintuitivos.

---

### Subjuegos

- Cualquier **subárbol** del juego en forma extensiva (un árbol que cuelga de cualquier nodo interior) es un **subjuego**.
    - La definición considera el propio juego en forma extensiva un subjuego de sí mismo.
- En el ejemplo hay **2 subjuegos**: uno con raíz en $e_1$ y otro con raíz en $e_2$.
- En el subjuego con raíz en $e_2$: el Jugador 2 elige entre CO y AG; el Jugador 1 no puede actuar.
    - El **equilibrio de Nash en el subjuego 2** es $(-, CO)$.
- Para aplicar un perfil estratégico a un subjuego, se eliminan todas las acciones que originan en nodos que no forman parte del subjuego.
    - Ej.: las estrategias (IN, CO) y (OUT, AG) se corresponden a $(-, CO)$ y $(-, AG)$ en el subjuego 2.

**Matriz del subjuego 2:**

||**CO**|**AG**|
|---|---|---|
|**−**|0.5, 0|-0.5, -1|

---

### Equilibrio Perfecto en Subjuegos (EPS)

> Un perfil estratégico está en **equilibrio perfecto en subjuegos** de un juego en forma extensiva con información perfecta si **constituye un equilibrio de Nash en cada subjuego**.

- **(IN, CO) sí es un EPS**: es equilibrio de Nash en el subjuego 1, y $(-, CO)$ lo es en el subjuego 2.
- **(OUT, AG) no es un EPS**: aunque (OUT, AG) sea equilibrio de Nash en el subjuego 1, $(-, AG)$ no lo es en el subjuego 2.

> **Nota:** Todo EPS es un equilibrio de Nash (el árbol completo es un subjuego de sí mismo), pero no viceversa.

_(Concepto introducido por Reinhard Selten, 1930–2016)_

---

### Cómputo del EPS: Algoritmo de Zermelo (Inducción hacia Atrás)

**Método:** Inducción hacia atrás para computar un EPS.

**Algoritmo:**

1. Sea $\Pi$ un juego en forma extensiva. Elegir un subjuego $\Pi_i$ (con raíz $r_i$) de $\Pi$, tal que **todos los sucesores de $r_i$ son hojas** (subjuego donde solo un jugador puede actuar).
2. Determinar un **equilibrio de Nash** $s^*$ de $\Pi_i$: se obtiene determinando la acción que **maximice la utilidad** del único jugador que puede actuar.
3. En $\Pi$, **sustituir** $\Pi_i$ por $r_i$, y etiquetar la nueva hoja $r_i$ con el vector de utilidades $U(s^*)$.
4. **Repetir** hasta que $\Pi$ sea solo la raíz.

_(Algoritmo de Ernst Zermelo, 1871–1953)_

**Ejemplo aplicado:**

- **Paso 1:** Se toma el subjuego $\Pi_i$ con raíz $e_2$. El Jugador 2 elige CO (maximiza su utilidad: 0 > −1). El subjuego se sustituye por el nodo $e_2$ con utilidades $(0.5, 0)$.
- **Paso 2:** Queda el subjuego con raíz $e_1$, donde el Jugador 1 elige entre IN→$(0.5, 0)$ y OUT→$(0, 2)$. El Jugador 1 elige IN (0.5 > 0).
- **Resultado:** EPS es **(IN, CO)** con $U_1 = 0.5$ y $U_2 = 0$.

---

### Análisis de Complejidad

- La representación en árbol es **más compacta** que la matriz del juego normal; el algoritmo de Zermelo es **más eficiente** que la búsqueda exhaustiva.
- Aun así, con secuencias de longitud máxima $d$ y $b$ posibles acciones por turno, la complejidad es del orden de $b^d$ en el peor caso.

> **Teorema:** Todo juego **finito** en forma extensiva con **información perfecta** tiene al menos un EPS, que puede calcularse mediante inducción hacia atrás siguiendo el algoritmo de Zermelo.

---

## 10.2 Conceptos Básicos de la Negociación Automática

### Negociación

> Todo proceso de interacción entre **dos o más participantes**, con objetivos y preferencias **conflictivas**, que facilite llegar a un **acuerdo aceptable** para todos ellos.

**La necesidad de negociación surge normalmente cuando:**

- Hay **recursos insuficientes** para todas las partes.
- Los participantes son **individualistas**.
- **No llegar a un acuerdo** es el peor escenario para todos.
- Las propias partes en conflicto deben ser las que lo resuelvan.

### Negociación Automática

> (Algunos de) los negociadores son **agentes software** que actúan representando (los intereses y preferencias de) su usuario humano.

---

### Escenario de Negociación

- **Conjunto de negociación:**
    
    - Todos los posibles acuerdos a los que se puede llegar.
    - Circunscribe el **dominio de la negociación**: todas las dimensiones relevantes y sus dominios (los valores que pueden tomar).
    - Ejemplo: calidad de un producto (bajo, media, alta) y su precio (entre 10€ y 20€).
- **Protocolo de negociación:**
    
    - Reglas que determinan el proceso de negociación:
        - ¿Cómo, cuándo, y qué ofertas se pueden hacer?
        - ¿Cuándo termina la negociación y cuál es el resultado?
    - Ejemplo: "No se puede 'empeorar' una oferta ya hecha".
- **Estrategia de negociación:**
    
    - Cómo elegir entre las diferentes acciones que permite el protocolo.
    - Ejemplo: "Mejorar mi última oferta en 10% cada 5 minutos".

---

### Dimensiones de Negociación

- **Número de negociadores:**
    
    - Uno contra uno: escenario más habitual (este Tema 10).
    - Uno contra muchos: se modelan frecuentemente con **subastas** (Tema 12).
    - Muchos contra muchos: se analizan mediante **teorías de mercados**.
- **Número de dimensiones:**
    
    - **Unidimensional:** solo hay una variable cuyo valor hay que acordar.
    - **Multidimensional:** se han de acordar simultáneamente varios valores.
- **Tipo de dimensiones:**
    
    - **Divisibles:** el recurso se puede repartir entre los negociadores (ej. una unidad de energía).
    - **Indivisibles:** la dimensión se adjudica solo a uno de los negociadores (ej. una frecuencia radioeléctrica).
- **Horizonte temporal:**
    
    - **Finito (con _deadline_):** si no hay acuerdo en un cierto tiempo, la negociación acaba en desacuerdo.
    - **Infinito (sin _deadline_):** no hay presión temporal (más allá de la que se imponen los propios negociadores).

---

### Análisis Estratégico de la Negociación

**Objetivo:** Dado un conjunto de negociación y un protocolo de negociación, determinar el **perfil estratégico en equilibrio**, es decir, las mejores estrategias para los negociadores suponiendo que todos son racionales.

**Supuestos del análisis en este tema:**

- Negociaciones **bipersonales** (uno a uno).
- Los negociadores son **individualmente racionales** (los humanos no siempre lo somos).
- **Información completa:** un negociador conoce las preferencias (la función de utilidad) del otro, además del protocolo y el conjunto de negociación.

---

## 10.3 Negociación Unidimensional

### Escenario

- Dos jugadores negocian cómo repartirse un recurso de **tamaño 1** (ej. 1 kWh de energía).
- El recurso es **divisible**.
- La utilidad de cada jugador se incrementa con una mayor parte del recurso.

**Conjunto de negociación:** $$NS = {(x, 1-x) \mid 0 \leq x \leq 1}$$

- Un reparto $(x,y)$ con $x + y < 1$ no sería **eficiente**.

**Protocolo de ofertas alternadas:**

1. Un jugador hace una **oferta** (un elemento del conjunto de negociación).
2. El otro jugador bien la **acepta** (termina la negociación), o bien la **rechaza** y hace una **contraoferta**.
3. Si no se llega a acuerdo (_ad infinitum_), la negociación acaba en **conflicto** (_conflict deal_).
    - Por definición, acabar en conflicto es **peor** que cualquier resultado $(x, 1-x) \in NS$ para ambos negociadores.

**Conjunto de estrategias $S_i$:** $$S_i = {Ofrecer(x, 1-x) \mid 0 \leq x \leq 1} \cup {Aceptar, Rechazar}$$

---

### Jugadores Pacientes

Los jugadores son **indiferentes al tiempo** que se tarda para llegar a un acuerdo.

#### Horizonte finito $n=1$ (Juego del Ultimátum)

- El juego se acaba después de **1 ronda**.
- Perfil estratégico en equilibrio: $((1,0), Aceptar)$.
    - Si el Jugador 1 propone quedarse todo, lo mejor que el Jugador 2 puede hacer es aceptarlo (rechazar llevaría al desacuerdo, que es el peor resultado).

#### Horizonte finito $n=2$

- El Jugador 2 puede rechazar la oferta de la ronda 1, convirtiendo el resto en un juego del ultimátum.
- El Jugador 2 se quedaría con todo el recurso, y el Jugador 1 no obtiene nada.

#### Horizonte finito $n>2$

- En la ronda $n$ el juego se convierte en un juego del ultimátum.
- El jugador al que le toca hacer una oferta en la **última ronda** se queda con todo el recurso.

#### Horizonte infinito

- Para cualquier acuerdo $(x, 1-x)$, existe un perfil estratégico que lo alcanza y que es un **equilibrio de Nash**.
- Si el Jugador 2 sabe que el Jugador 1 solo acepta $(x, 1-x)$ y rechaza cualquier otra oferta, lo racional es ofrecer justo eso (para no acabar en conflicto).
- Esta suposición es **factible en negociación automática**: el agente del negociador 1 podría hacer público su código.

---

### Jugadores Impacientes

El tiempo es valioso: con el paso del tiempo **el recurso pierde valor** para los jugadores.

**Factor de descuento $\delta_i$, $0 \leq \delta_i \leq 1$:**

La utilidad del jugador $i$ si obtiene la parte $x$ del recurso en la ronda $t$ es: $$U_i(x, t) = x \cdot \delta_i^{t-1}$$

- $t=1$: $U_i = x \cdot \delta_i^0 = x$
- $t=2$: $U_i = x \cdot \delta_i^1 = \delta_i x$
- $t=3$: $U_i = x \cdot \delta_i^2 = \delta_i \delta_i x$
- $t=k$: $U_i = \delta_i^{k-1} x$

> Cuanto menor sea $\delta_i$, más rápido pierde valor el recurso para el jugador $i$.

---

### Jugadores Impacientes y Horizonte Finito

_(Se asume que ambos jugadores tienen el mismo factor de descuento $\delta$)_

#### Horizonte finito $n=1$

- Juego del ultimátum. Acuerdo: $(1, 0)$.

#### Horizonte finito $n=2$

Razonamiento por inducción hacia atrás:

- En $t=1$, si el Jugador 2 rechaza, puede forzar el acuerdo $(0,1)$ en $t=2$, lo que le aporta utilidad $\delta$.
- Por tanto, el Jugador 2 **acepta** cualquier oferta $(x,y)$ con $y \geq \delta$ (ya que $U_2((x,y),1) \geq \delta$), y **rechaza** con $y < \delta$.
- Sabiendo esto, el Jugador 1 ofrece $(1-\delta, \delta)$ en $t=1$, y el Jugador 2 lo acepta.

**EPS único:** $(1-\delta, \delta)$, alcanzado en la primera ronda.

> **Efecto del primer jugador:** con $\delta \leq 0.5$ (y $n=2$), es mejor ser el primer jugador; si no, el segundo.

#### Horizonte finito $n=3$

|ronda|turno|acuerdo|$U_1$|$U_2$|
|---|---|---|---|---|
|$t=1$|Jug. 1|$(1-(\delta-\delta^2), \delta-\delta^2)$|$1-\delta+\delta^2$|$\delta - \delta^2$|
|$t=2$|Jug. 2|$(\delta, 1-\delta)$|$\delta^2$|$\delta - \delta^2$|
|$t=3$|Jug. 1|$(1, 0)$|$\delta^2$|$0$|

- En cada ronda $t$, si le toca hacer una propuesta al jugador $i$, es racional proponerle al contrario un acuerdo que le proporciona la **misma utilidad** aceptando en ronda $t$ que rechazando e yéndose a la ronda $t+1$.
- **EPS único:** $(1-\delta+\delta^2, \delta-\delta^2)$, alcanzado en la primera ronda.

#### Horizonte finito $n=4$

|ronda|turno|acuerdo|$U_1$|$U_2$|
|---|---|---|---|---|
|$t=1$|Jug. 1|$(1-(\delta-\delta^2+\delta^3), \delta-\delta^2+\delta^3)$|$1-\delta+\delta^2-\delta^3$|$\delta-\delta^2+\delta^3$|
|$t=2$|Jug. 2|$(\delta-\delta^2, 1-(\delta-\delta^2))$|$\delta^2-\delta^3$|$\delta-\delta^2+\delta^3$|
|$t=3$|Jug. 1|$(1-\delta, \delta)$|$\delta^2-\delta^3$|$\delta^3$|
|$t=4$|Jug. 2|$(0, 1)$|$0$|$\delta^3$|

**EPS único:** $(1-\delta+\delta^2-\delta^3, \delta-\delta^2+\delta^3)$, en la primera ronda.

#### Horizonte finito $n=k$ (general)

Se alcanza el siguiente **EPS único** en la primera ronda:

$$\left(\sum_{i=0}^{k-1} (-1)^i \delta^i, ; 1 - \sum_{i=0}^{k-1} (-1)^i \delta^i\right)$$

---

### Jugadores Impacientes y Horizonte Infinito

**Razonamiento ($n \to \infty$):**

- Supongamos que en la ronda $n$ el Jugador 1 puede conseguir como mucho la $M$-ésima parte del recurso.
- Eso implica que en ronda $n-1$ el Jugador 2 puede conseguir como mínimo la parte $1 - \delta M$.
- A su vez, en la ronda $n-2$ el Jugador 1 puede conseguir como mucho la parte $1 - \delta + \delta^2 M$.
- Hay dos fórmulas para la parte máxima que el Jugador 1 puede conseguir: $M$ y $1-\delta+\delta^2 M$.
- Resolviendo: $M = \dfrac{1-\delta}{1-\delta^2}$
- Por tanto el Jugador 2 recibe $1 - M = \dfrac{\delta - \delta^2}{1-\delta^2}$.

**EPS único** (se alcanza en la primera ronda): $$\left(\frac{1-\delta}{1-\delta^2}, ; \frac{\delta-\delta^2}{1-\delta^2}\right)$$

**Nótese:**

- Con el protocolo de ofertas alternadas, horizonte infinito y jugadores impacientes, el acuerdo es **instantáneo** ($t=1$), **único** y **eficiente** (las partes siempre suman 1).
- El resultado depende del **factor de descuento** $\delta$ y de **quién hace la primera oferta**.

---

## 10.4 Negociación Multidimensional

### Motivación

La mayoría de problemas de negociación del mundo real involucran **dimensiones múltiples**:

- Intercambio de bienes y servicios: precio, calidad, tiempo de entrega, método de pago, servicio de postventa, …
- Negociación entre partidos políticos: impuestos, política social, presupuesto, …
- Negociación de la parte fija y variable de tarifas (gas, eléctricas, etc.).

Los negociadores dan **pesos diferentes** a cada dimensión (ej. un partido liberal valora más los presupuestos; un partido de izquierdas da más importancia a la política social).

---

### Modelo de Negociación Multidimensional

- **Negociadores:** $N = {a, b}$
- **Número de dimensiones:** $m \geq 2$
    - En cada dimensión hay que repartir un recurso de tamaño 1 entre los dos negociadores.
    - **Dimensiones divisibles** (ej. negociación sobre precio) o **indivisibles** (ej. asignación de horarios para profesores).
- **Restricciones temporales:** Tiempo límite de $n$ instantes.
- **Jugadores impacientes:** factor de descuento $\delta$.

---

### Utilidad de los Negociadores

**Definiciones:**

- $x_{i,j}$: parte del recurso de la dimensión $j$ asignado al negociador $i$.
- $x_i$: vector con las partes de todos los recursos asignados al negociador $i$.
- $\omega_{i,j}$: peso que el negociador $i$ da al recurso de la dimensión $j$.
- $t$: ronda de negociación (inicialmente $t=1$).

**Utilidad de la dimensión $j$ en la ronda $t$:** $$U_i(x_{i,j}, t) = \omega_{i,j} \cdot x_{i,j} \cdot \delta^{t-1}$$

**Utilidad acumulada para todas las dimensiones en la ronda $t$:** $$U_i(x_i, t) = \sum_{j=1}^{m} U_i(x_{i,j}, t)$$

---

### Ejemplo: Negociar Partes Fija y Variable de una Tarifa Energética

- **Agente $a$ (comercializadora):** valora más la parte fija. $$U_a((x_1, x_2), 1) = 2 \cdot x_1 + x_2$$
- **Agente $b$ (gran industria):** da más peso al precio del consumo real. $$U_b((x_1, x_2), 1) = x_1 + 2 \cdot x_2$$

**Posibilidad de _tradeoffs_:**

- Si el negociador $a$ aumenta su parte en la dimensión 1 en $\varepsilon > 0$, su utilidad aumenta **más** que la de $b$ si su parte de la dimensión 1 se aumentara en $\varepsilon$ (y viceversa con la dimensión 2).
- Si se acuerda que $b$ cede "algo" en la dimensión 1, y "a cambio" $a$ cede "algo" en la dimensión 2, **ambos se benefician**.

**Aplicación con inducción hacia atrás** ($\delta = 0.5$, $n = 2$, empieza jugador $a$):

|ronda|turno|acuerdo|$U_1$|$U_2$|
|---|---|---|---|---|
|$t=1$|Jug. 1|$((1,0), (0.25, 0.75))$|$2·1+0.25 = \mathbf{2.25}$|$0+2·0.75 = \mathbf{1.5}$|
|$t=2$|Jug. 2|$((0,1), (0,1))$|$0$|$0.5·(1+2) = \mathbf{1.5}$|

- En $t=2$ hay un juego del ultimátum: $b$ se queda con todo y obtiene utilidad 1.5 (por el factor de descuento $\delta=0.5$).
- En $t=1$, el jugador $a$ hace una oferta que asegura utilidad 1.5 al jugador $b$, que la acepta.
- Hay más acuerdos en $t=1$ que aseguran utilidad 1.5 a $b$ (ej. $((0,1), (0.75, 0.25))$), pero $((1,0), (0.25, 0.75))$ es el que **maximiza la utilidad del negociador $a$**.

---

### Diferentes Protocolos para Negociación Multidimensional

#### Paquetes

- Se usa el protocolo de **ofertas alternadas**, con horizonte finito.
- Se negocian **todas las dimensiones a la vez** en un paquete.
- Conjunto de negociación:
    - Para recursos **indivisibles:** $NS = {0,1}^m$
    - Para recursos **divisibles:** $NS = [0,1]^m$
- El protocolo termina o bien con acuerdo para **todas** las dimensiones, o bien en desacuerdo para **todas**.

#### Simultáneo

- Se lanzan $m$ negociaciones unidimensionales **en paralelo** e independientes entre sí.
- El resultado **puede no ser eficiente** (no Pareto-óptimo).

#### Secuencial

- Se establece una **agenda** (un orden) y se realizan $m$ negociaciones unidimensionales de forma **secuencial** (se empieza la dimensión $k$ cuando haya acuerdo sobre la $k-1$).
- El resultado **puede variar** según cómo se establece la agenda.

---

### Tradeoffs: Dimensiones Divisibles

**Estrategia del negociador $a$ para la ronda $t < n$:**

Entre todos los acuerdos que, si se aceptan en ronda $t$, aseguran al negociador $b$ la misma utilidad que obtendría en la ronda $t+1$ si rechazara ($U_b(t+1)$)… elegir aquel que **maximice la utilidad del negociador $a$**.

**Formalmente:**

$$\max_{x_a} \sum_{c=1}^{m} \omega_{a,c} \cdot x_{a,c}$$

Sujeto a:

$$\delta^{t-1} \cdot \sum_{c=1}^{m} \omega_{b,c} \cdot (1 - x_{a,c}) = U_b(t+1)$$

$$0 \leq x_{a,c} \leq 1, \quad 1 \leq c \leq m$$

_(No hace falta incluir el factor de descuento en la función objetivo al ser el mismo en todas las dimensiones.)_

---

### Tradeoffs: Dimensiones Indivisibles

**Estrategia del negociador $a$ para la ronda $t < n$:**

Mismo argumento que en el caso divisible, pero con la restricción de que cada recurso se asigna **enteramente** a uno de los dos negociadores.

**Formalmente:**

$$\max_{x_a} \sum_{c=1}^{m} \omega_{a,c} \cdot x_{a,c}$$

Sujeto a:

$$\delta^{t-1} \cdot \sum_{c=1}^{m} \omega_{b,c} \cdot (1 - x_{a,c}) = U_b(t+1)$$

$$x_{a,c} \in {0, 1}, \quad 1 \leq c \leq m$$

**Complejidad:**

- Para **dimensiones divisibles:** se puede resolver con complejidad $O(m)$ (_continuous knapsack problem_).
- Para **dimensiones indivisibles:** sería un _fractional knapsack problem_, que es **NP completo**.

---

## 10.5 Negociación Heurística

### Idea General

Generar estrategias que son **"lo suficientemente buenas"**, aunque no necesariamente en equilibrio.

### ¿Por qué estudiar enfoques heurísticos?

- En escenarios **computacionalmente complejos**.
- Cuando los oponentes **no se comportan** con la racionalidad asumida en teoría de juegos.

---

### Tipos de Enfoques Heurísticos

1. **Dependientes del tiempo:** la oferta se define en base a la función de utilidad del proponente y del **tiempo restante** de negociación.
2. **Dependientes del comportamiento del oponente:** las ofertas se definen en base a la función de utilidad del proponente y de las **ofertas previas recibidas** del oponente.
3. **Dependientes de los recursos existentes:** las ofertas se definen en base a la función de utilidad del proponente y de los **recursos disponibles** en el entorno (crédito, energía, …).

---

### Heurísticas Dependientes del Tiempo

**Notación:**

- $j$: dimensión de negociación que determina el **precio** de un producto.
- $min_j^a$ ($max_j^a$): mínimo (máximo) precio con el que el negociador $a$ valora la dimensión $j$.
- Si $a$ es **vendedor**, su utilidad **crece** con el precio; si es **comprador**, **decrece**.
- $\kappa_j^a$: **oferta inicial** del negociador $a$ respecto a la dimensión $j$.
- $t_{max}^a$: _**deadline**_ de la negociación.
- $\alpha_j^a(t)$: función $0 \leq \alpha_j^a(t) \leq 1$ que determina la **"concesión"** de $a$ dependiendo del tiempo $t$, con $\alpha_j^a(0) = \kappa_j^a$ y $\alpha_j^a(t_{max}^a) = 1$.

**Oferta $x_{a \to b}^j(t)$ del negociador $a$ a $b$ en ronda $t$:**

$$x_{a \to b}^j(t) = \begin{cases} min_j^a + \alpha_j^a(t)(max_j^a - min_j^a) & \text{si la utilidad de } a \text{ decrece con el precio (comprador)} \ min_j^a + (1 - \alpha_j^a(t))(max_j^a - min_j^a) & \text{si la utilidad de } a \text{ crece con el precio (vendedor)} \end{cases}$$

**Estrategias posibles con $\alpha_j^a(t)$:**

- **Boulware:** mantener la oferta inicial hasta muy cerca del _deadline_.
- **Conceder:** acercarse rápidamente al precio reserva.

**Ejemplo de función $\alpha_j^a(t)$:**

$$\alpha_j^a(t) = \kappa_j^a + (1 - \kappa_j^a)\left(\frac{min(t, t_{max}^a)}{t_{max}^a}\right)^{1/\beta} \quad \text{con } \beta \in \mathbb{R}^+$$

- $\beta$ **pequeño:** comportamiento más _Boulware_.
- $\beta$ **grande:** comportamiento más _Conceder_.

---

### Heurísticas Dependientes de los Recursos

Determinan la oferta en ronda $t$ respecto a la dimensión $j$, en función del **nivel de consumición de algún recurso**:

- En negociaciones 1 a $n$, el recurso podría ser el **número de agentes** que en tiempo $t$ todavía negocian con $a$ sobre la dimensión $j$.
- El **tiempo** se puede ver como un recurso específico que "se consume" de forma lineal.

Se modelan de forma **similar a las dependientes del tiempo**.

**Ejemplo:** si $resource^a(t)$ mide la cantidad del recurso disponible para $a$ en tiempo $t$:

$$\alpha_j^a(t) = \kappa_j^a + (1 - \kappa_j^a) e^{-resource^a(t)}$$

---

### Heurísticas Dependientes del Comportamiento del Oponente

Determinan la oferta en ronda $t$ en función del **comportamiento del oponente**:

- **Tit-for-tat relativo:** concesión en **porcentaje idéntico** a la concesión del oponente.
    
    - Si la última oferta del oponente mejora su oferta anterior en un 10%, también mejorar la última oferta de $a$ en un 10%.
- **Tit-for-tat absoluto:** concesión en **valor absoluto idéntico** a la concesión del oponente.
    
    - Si la última oferta del oponente mejora su oferta anterior en 2€, también mejorar la última oferta de $a$ en 2€.
- **Tit-for-tat promedio:** concesión en **porcentaje idéntico al promedio** de concesiones del oponente.
    
    - Si en el pasado el oponente mejora su oferta en promedio en un 10% (en 2€), también mejorar la última oferta de $a$ en un 10% (en 2€).

---

## Resumen de Conceptos Clave

|Concepto|Descripción|
|---|---|
|**Juego en forma extensiva**|Árbol etiquetado con nodos (estados), arcos (acciones) y hojas (utilidades).|
|**Subjuego**|Cualquier subárbol del juego en forma extensiva.|
|**EPS (Equilibrio Perfecto en Subjuegos)**|Perfil estratégico que es equilibrio de Nash en cada subjuego.|
|**Algoritmo de Zermelo**|Inducción hacia atrás para calcular el EPS. Complejidad $O(b^d)$.|
|**Negociación automática**|Negociadores son agentes software que representan a usuarios humanos.|
|**Protocolo de ofertas alternadas**|Uno propone, el otro acepta o rechaza y contraoferta.|
|**Factor de descuento $\delta$**|Modela la impaciencia: $U_i(x,t) = x \cdot \delta^{t-1}$.|
|**EPS horizonte infinito**|Acuerdo único, instantáneo y eficiente: $\left(\frac{1-\delta}{1-\delta^2}, \frac{\delta-\delta^2}{1-\delta^2}\right)$.|
|**Tradeoffs multidimensionales**|Ceder en una dimensión menos valorada a cambio de ganar en otra más valorada.|
|**Knapsack problem**|Problema de optimización en negociación multidimensional. Divisible → $O(m)$; indivisible → NP completo.|
|**Heurísticas Boulware**|Mantener oferta inicial hasta cerca del _deadline_.|
|**Heurísticas Conceder**|Acercarse rápidamente al precio reserva.|
|**Tit-for-tat**|Imitar la concesión del oponente (relativo, absoluto o promedio).|