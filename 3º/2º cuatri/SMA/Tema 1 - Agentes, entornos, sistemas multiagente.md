## Índice del Tema

1. [[#1.1 Introducción y Objetivos]]
2. [[#1.2 ¿Qué es un Agente?]]
3. [[#1.3 Características. Agentes Inteligentes]]
4. [[#1.4 Arquitectura Abstracta de un Agente]]
5. [[#1.5 El Entorno de un Agente]]
6. [[#1.6 ¿Cómo Especificar los Objetivos de un Agente?]]
7. [[#1.7 Sistemas Multiagente]]
8. [[#1.8 Retos en Agentes y Sistemas Multiagente]]
9. [[#1.9 Netlogo]]

---

## Bloque I: Agentes Autónomos — Contexto General

El Bloque I presenta las **nociones básicas** de la asignatura (agente, entorno, etc.), analiza las arquitecturas y tipos de agentes más importantes, y estudia la toma de decisión de agentes autónomos en sus entornos **sin considerar posibles interacciones con otros agentes**.

### Temas del Bloque I

- **Tema 1:** Agentes, Entornos, Sistemas Multiagente
- **Tema 2:** Tipos de Agentes
- **Tema 3:** Agentes basados en Procesos de Decisión de Markov
- **Tema 4:** Agentes que aprenden: Aprendizaje por refuerzo

### Bibliografía

- **Michael Wooldridge (2009):** _An Introduction to MultiAgent Systems_ (2ª ed.). John Wiley & Sons. Capítulos 1, 2, 3, 4, 5 (temas 1 y 2).
- **Stuart Russell y Peter Norvig (2021):** _Artificial Intelligence – A Modern Approach_ (4ª ed.). Pearson. Capítulo 2 (temas 1 y 2), 17, 22 (temas 3 y 4).
- **H.M. Schwartz (2014):** _Multi-Agent Machine Learning: A Reinforcement Approach_. John Wiley & Sons. Capítulo 2 (temas 3 y 4).

---

## 1.1 Introducción y Objetivos

### Objetivos del Tema 1

- Desarrollar y definir el **concepto de agente** como un ente que actúa en un entorno.
- Presentar las posibles **características** tanto de agentes como de entornos y la interacción entre ambos.
- Dar una **introducción** a los sistemas multiagente y a los retos, problemas y dificultades que se estudian en el área.
- Presentar la aplicación **NETLOGO**, un entorno para programar y ejecutar sistemas multiagente.

### Tendencias en los Sistemas Informáticos

Los sistemas modernos evolucionan hacia:

|Tendencia|Descripción|
|---|---|
|**Ubicuidad**|Presencia en (casi) todos los ámbitos y lugares: teléfonos, neveras, coches, semáforos…|
|**Interconexión**|Internet y redes de proximidad facilitan la conexión entre los sistemas.|
|**Adaptabilidad**|Los sistemas aprenden y se adaptan a nuestras preferencias y hábitos.|
|**Delegación**|Delegamos cada vez más tareas: sistemas de trading en bolsa, coches autónomos…|
|**Inteligencia**|Los sistemas se comportan con eficiencia en los entornos.|
|**Orientación humana**|Interacción directa, fluida y fácil entre los sistemas y los humanos.|

- Interactuamos cada vez más con sistemas **como si interactuásemos con personas** (asistentes de voz, chatbots…).
- Los sistemas realizan cada vez más **tareas y servicios** que antes realizaban personas (búsqueda de alojamiento, coches autónomos, robots aspiradores, drones…).

### El Paradigma del Agente

Surge un **nuevo paradigma** para concebir y entender los sistemas informáticos como **Agentes**.

**Definición de la RAE:**

- Persona que obra con poder de otra para gestionar algo en su nombre.
- Persona que tiene a su cargo una agencia para gestionar asuntos ajenos o prestar determinados servicios.
- Ejemplos: agente artístico, agente literario, agente de negocios, agente de seguros…

---

## 1.2 ¿Qué es un Agente?

### Una Nueva Forma de Concebir un Sistema Informático

El concepto de **AGENTE** percibe la computación como:

- Una **actividad social**
- De un ente **autónomo e independiente** que
- **Interactúa** en un entorno
- En **representación** o nombre de su propietario o diseñador
- Y persiguiendo unos **objetivos** que se le han asignado

### Definiciones Formales

**Wooldridge:**

> Un agente es un sistema informático capaz de realizar **acciones** de forma **autónoma** en un **entorno** y con el fin de cumplir sus **objetivos** de diseño.

**Russell & Norvig:**

> Un agente es cualquier entidad que puede ser vista como que **percibe su entorno** a través de **sensores** y **actúa** en este entorno a través de **actuadores**.

```
         percepciones
sensores ←————————————— entorno
         ——————————————→
actuadores    acciones
```

### Ejemplos de Agentes

|Agente|Percepción|Actuación|
|---|---|---|
|**Termostato**|Temperatura del entorno|Enciende o apaga la calefacción; actúa de forma autónoma|
|**Humano**|El mundo a través de sus sentidos|Actúa en su entorno de forma autónoma|
|**Robot**|El mundo a través de cámaras|Motores que mueven su brazo|
|**Softbot**|Cadenas de strings (entradas)|Produce cadenas de strings (salidas)|

---

## 1.3 Características. Agentes Inteligentes

### De Agentes a Agentes Inteligentes

**Wooldridge:**

> Un agente inteligente es un sistema informático capaz de realizar acciones de forma **autónoma** y **flexible** en un entorno.  
> "Flexible" se refiere a: **reactivo**, **pro-activo** y **capacidad social**.

**Russell & Norvig:**

> Un agente inteligente es una entidad que percibe su entorno y actúa en este entorno de forma **racional**.

### Autonomía

- Un sistema que **sólo ejecuta las instrucciones** que de forma directa le indica un humano es un **mero ejecutor**.
- Un sistema **autónomo** es capaz de:
    - Determinar su comportamiento por sí solo.
    - Actuar **sin una intervención humana directa** (al menos en algunas situaciones).
    - Decidir y determinar las acciones a realizar por sí mismo y ejecutarlas en el entorno.
- En un nivel más alto de autonomía, un sistema podría tener la capacidad de **adaptar y modificar su comportamiento** a partir de su propia experiencia → capacidad de **aprender**.

### Reactividad

- Si el entorno fuese **fijo, estático** y toda la información relevante fuese conocida, el programa (bien diseñado) no tendría fallos: simplemente ejecutaría sus instrucciones.
- Los **entornos reales** no suelen ser fijos y estáticos; la mayoría son **dinámicos e inciertos** y pueden ocurrir situaciones imprevistas o desconocidas a priori.
- Un sistema **reactivo** es aquel que:
    - Mantiene una **interacción continua** con su entorno.
    - Es capaz de **detectar cambios** y **responder** a ellos de forma conforme con sus objetivos de diseño.

### Proactividad

- Los sistemas no solo deben responder a estímulos del entorno de forma reactiva.
- Los agentes inteligentes actúan en nombre de su propietario y se crean con unos **objetivos específicos**.
- Los agentes deben **reconocer oportunidades** y perseguir estos objetivos con **iniciativa propia** y de forma proactiva.
- Un sistema **proactivo** es aquel que:
    - **Genera sus propias metas** (basado en sus objetivos de diseño).
    - **Intenta alcanzarlos**, guiando sus acciones hacia la consecución de sus objetivos.
- Un agente inteligente debe **combinar reactividad** (para responder a cambios del entorno) **con proactividad** para alcanzar sus objetivos a largo plazo.

### Capacidad Social

- El mundo real es un entorno en el que **no estamos solos**; actúan e interactúan varios agentes.
- Un agente inteligente puede requerir la **interacción con otros agentes** para poder alcanzar sus objetivos.
- La capacidad social de un agente radica en su **habilidad de comunicarse** con otros agentes y posiblemente con humanos a través de algún lenguaje de comunicación, y de **interactuar** con ellos.
- La interacción puede estar limitada a un **mero intercambio de información** o podría incluir actividades de mayor nivel como la **cooperación, coordinación, negociación o argumentación**.

### Racionalidad

- La racionalidad es la capacidad de pensar, evaluar, entender y actuar de acuerdo a ciertos **principios de optimalidad y consistencia**, para satisfacer algún **objetivo o finalidad**.
- Actuar de forma racional consiste esencialmente en determinar y realizar las acciones **"mejores"**, con respecto a los objetivos, y dado el conocimiento de un agente (sus percepciones y su conocimiento a priori sobre el entorno).
- Racionalidad puede incluir el **descubrimiento de nueva información** para mejorar el desempeño.
- **Racionalidad ≠ omnisciencia:**
    - Un agente "no sabe todo" y sólo puede estimar la mejor acción a partir de su información disponible.
    - Más información puede mejorar el desempeño del agente.
    - El agente opera bajo **incertidumbre**.

### Otras Características Posibles (quizás deseables)

|Característica|Descripción|
|---|---|
|**Veracidad**|Un agente no debe comunicar información falsa de forma intencionada.|
|**Benevolencia**|Un agente debe siempre perseguir los objetivos que le han encomendado.|
|**Movilidad**|Un agente puede tener la capacidad de moverse físicamente o en una red de comunicación.|
|**Adaptabilidad**|Un agente puede tener la capacidad de adaptar su comportamiento y mejorarlo con el tiempo (capacidad de aprender).|

---

## 1.4 Arquitectura Abstracta de un Agente

### Una Nueva Forma de Construir Sistemas Informáticos

El concepto de agente no sólo es una forma distinta de concebir un sistema informático sino también corresponde a una **nueva forma de construir sistemas informáticos**.

### El Diseño de un Agente

El diseño de un agente consiste en definir:

1. Las **capacidades** del agente → las acciones que puede realizar.
2. Las **percepciones** que puede obtener del entorno.
3. Un **mecanismo de selección de acciones** en cada momento (más o menos inteligente o racional).
4. Los **objetivos** del agente.

> Mientras un sistema "clásico" ejecuta las instrucciones dadas en tiempo de diseño, **un agente elige por sí mismo las acciones a realizar**.

### Diagrama de Arquitectura

```
┌─────────────────────────────────────────┐
│                 AGENTE                  │
│                                         │
│  ┌─────────┐   ┌──────────┐             │
│  │ Memoria │←──│ Sensores │←── Percepción ──→ ENTORNO
│  └────┬────┘   └──────────┘             │
│       │                                 │
│  [Objetivos] ──→ ┌─────────────────┐    │
│  [Acciones]  ──→ │ Selección-acción│    │
│                  └────────┬────────┘    │
│                           │             │
│                  ┌────────▼────────┐    │
│                  │   Actuadores    │────────→ Acción ──→ ENTORNO
│                  └─────────────────┘    │
└─────────────────────────────────────────┘
```

### Componentes del Agente

**Sensores:**

- Permiten al agente **detectar el estado del mundo** y lo que ocurre en el entorno.
- Se deben diseñar las capacidades sensoriales que necesita el agente para conseguir sus objetivos.

**Objetivos:**

- Representan el **propósito del agente**; aquello para lo que ha sido creado.
- El agente persigue conseguir sus objetivos; los objetivos **guían su comportamiento**.

**Actuadores y Acciones:**

- Los actuadores representan las **herramientas del agente** que permiten influir en su entorno y especifican las acciones que puede realizar.
- El agente elige sus acciones y las ejecuta a través de los actuadores.
- Se debe dotar al agente de capacidades de actuación (acciones) de tal forma que pueda conseguir sus objetivos.

**Memoria:**

- Un agente puede tener **memoria propia** en la que puede almacenar información sobre el mundo o su propia historia.
- Representa su **conocimiento sobre el mundo**.
- El agente puede modificarla, actualizarla y usarla para determinar sus acciones.

**Selección-acción:**

- Representa la **"mente del agente"**.
- Relaciona el conocimiento del agente (su memoria), las percepciones, sus objetivos y acciones disponibles para **determinar en cualquier momento la acción que se debe realizar**.
- El grado de complejidad de esta función determina el **grado de racionalidad o inteligencia** del agente.

### Comparación: Sistema Clásico vs. Agente (Ejemplo Termostato)

|Sistema Clásico|Agente|
|---|---|
|`Controlar_temperatura`|Instrucción al diseñador: **"Búscate la vida"**|
|`While TRUE:`|Puedes **percibir** la temperatura (percepción).|
|`t := temperatura`|Debes **mantener** la temperatura alrededor de 25 grados (objetivo).|
|`IF t > 25 → apaga calefacción`|Puedes hacer dos **acciones** (actuadores):|
|`ELSE → enciende calefacción`|• Encender la calefacción|
|`End While`|• Apagar la calefacción|

### Programa Básico de un Agente

```
m: Memoria; O: Objetivos; A: Acciones
while vivo:
    p ← percibir()
    a ← selección_acción(p, m, O, A)
    ejecutar(a)
end
```

- `percibir()`: función que proporciona una percepción del estado actual del mundo.
- `selección-acción`: determina el comportamiento del agente; puede tener diferente grado de complejidad; se modela como una función **no necesariamente determinista** (permitiendo que el agente pueda elegir diferentes acciones en una misma situación).
- Un agente **determina su propio comportamiento**; realiza las acciones que considera adecuadas.
- Mientras un programa tradicional responde a peticiones externas, **un agente decide si le conviene responder y cómo**.

---

## 1.5 El Entorno de un Agente

### Definición de Entorno

El **entorno** de un agente es todo aquello que le rodea en el contexto en el que el agente se ejecuta, y:

- Que puede **influir en el comportamiento** del agente, o
- En lo que el agente puede **influir**.

> Ejemplo Ajedrez: El tablero con la posición de las fichas; pero no los espectadores.

- El agente puede **percibir la situación actual** del entorno (o parte de ella) y sus acciones pueden **modificar** la situación del entorno.
- El agente **no tiene control** sobre su entorno, sólo puede influir en él a través de sus acciones.
- Las acciones pueden tener el efecto deseado, o pueden **"fallar"**.

### Propiedades del Entorno

#### Accesible vs. Inaccesible

- Depende de las **capacidades de percepción** del agente en cuestión.
- **Totalmente accesible:** el agente puede obtener información completa del estado/situación actual → puede determinar de forma inequívoca el estado.
- **Inaccesible (parcialmente accesible):** sólo puede percibir parte del estado actual → aumenta la complejidad de toma de decisión.
- En casos reales e interesantes el entorno suele ser **inaccesible**.
- Ejemplos:
    - _Accesible:_ Ajedrez, "tres en raya"
    - _Inaccesible:_ Póker, laberinto, juego de vídeo

#### Determinista vs. No Determinista

- **Determinista:** las acciones del agente determinan completamente el resultado → **no existe incertidumbre** sobre los efectos de las acciones. En entornos multiagente, es determinista si el siguiente estado es completamente determinado por las acciones de **todos** los agentes en un momento dado.
- **No determinista:** la complejidad de diseñar agentes es mayor, ya que tienen que lidiar con la incertidumbre.
- Ejemplos:
    - _Determinista:_ Ajedrez, laberinto, robot aspirador
    - _No determinista:_ gestión de tráfico, robot en sala real, el Parchís

#### Estático vs. Dinámico

- **Totalmente estático:** sólo se producen cambios en el entorno como consecuencia de las acciones de un agente.
- **Dinámico:** hay otros procesos que producen cambios y que están fuera del control del agente.
- **Semi-dinámico:** existen acciones previsibles de otros agentes.
- La complejidad de diseñar agentes es mayor en entornos dinámicos.
- Ejemplos:
    - _Estático:_ agente software en un laberinto simulado
    - _Semi-dinámico:_ ajedrez (cambios previsibles, realizados por otro agente)
    - _Dinámico:_ gestión de tráfico (cambios imprevisibles)

#### Discreto vs. Continuo

- **Discreto:** hay un **número finito** de percepciones y posibles acciones → la complejidad de diseñar agentes es generalmente menor.
- **Continuo:** percepciones y acciones en un espacio continuo.
- Ejemplos:
    - _Discreto:_ juego de las damas, agente software en un laberinto simulado
    - _Continuo:_ conducción de un taxi, robot navegando en una sala real

### Modelización del Entorno como Espacio de Estados

- El entorno se encuentra en cada momento en un **estado** $s_i \in S$ del conjunto de todos los posibles estados $S = {s_1, s_2, s_3, \ldots}$.
- Un estado representa una **situación concreta** en la que se puede encontrar el entorno.
- En cada estado, un agente puede realizar una acción de un conjunto posible de acciones $A = {a_1, a_2, a_3, \ldots}$.
- Como consecuencia de una acción, el entorno puede cambiar del estado actual $s_i$ a un nuevo estado $s_j$ (incluso al mismo estado $s_i$).
- $A$ podría incluir la **acción "vacía"**: $a_i = \emptyset$ (cambios del entorno por causas ajenas al agente).
- No todas las acciones se pueden realizar en todos los estados.
- Pueden existir estados en los que un agente **no puede realizar ninguna acción**.
- Las acciones que se pueden realizar en un estado $s_i$ se denotan por $A(s_i)$.

### Espacio de Estados como Grafo

- Los **nodos** representan los estados.
- Los **arcos** representan las acciones y sus consecuencias.
- Los entornos pueden ser **no deterministas** (u otros agentes podrían actuar):
    - Como consecuencia de realizar la acción $a_1$ en $s_i$, el entorno puede transitar a uno de **varios posibles estados** resultantes.
    - Puede haber otras causas que influyen en el resultado de una acción (ajenas al agente).
- Una acción podría llevar al **mismo estado**.
- Puede haber estados **sin acciones disponibles**.

En entornos más complejos pueden existir **transiciones sin la acción explícita del agente** (otros factores/agentes modifican el estado). Se modela con la acción vacía: $\emptyset \in A(s_i)$.

En entornos aún más complejos, las transiciones pueden **depender de la historia** → ya no es posible representar la dinámica mediante un grafo simple.

### Recorrido de un Agente

El **recorrido** de un agente en un entorno representa la interacción entre ambos durante un determinado intervalo de tiempo.

Secuencia de estados del entorno y acciones del agente intercalados:

$$s_0 \xrightarrow{a_0} s_1 \xrightarrow{a_1} s_2 \xrightarrow{a_2} s_3 \ldots s_{n-1} \xrightarrow{a_{n-1}} s_n$$

- $a_i$ podría ser la acción "vacía" ($a_i = \emptyset$), representando una transición sin acción del agente.
- Todos los recorridos empiezan en el **estado inicial** del agente.
- $s(r)$: conjunto de estados en el recorrido $r$.
- $a(r)$: conjunto de acciones en el recorrido $r$.
- $R(ag, E)$: conjunto de posibles recorridos de un agente $ag$ en un entorno $E$.

### Modelización del Entorno

Un entorno $E$ se modela como una tupla:

$$E = \langle S, A, T \rangle$$

Donde:

- $S$: conjunto de estados.
- $A$: conjunto de posibles acciones que un agente puede realizar.
- $T: R(ag, E) \times A \rightarrow \mathcal{P}(S)$: **función de transición**.

La función $T$ representa los efectos que las acciones de un agente tienen sobre el entorno. El hecho de que $T(r, a)$ devuelva posiblemente un conjunto de varios estados representa que el entorno puede ser **no determinista**. Si $a = \emptyset$, el entorno transita sin la intervención del agente.

> Esta definición **sí permite** que las transiciones dependan del recorrido de un agente (ya que el dominio de $T$ incluye el recorrido completo $r$).

### Modelización de la Actuación del Agente

Un agente $ag$ en un entorno $E = \langle S, A, T \rangle$ se modela como una función (política o estrategia):

$$ag: R(ag, E) \times A \rightarrow [0,1]$$

$$\text{donde } \forall r \in R(ag, E): \sum_{a \in A} ag(r, a) = 1 \vee \sum_{a \in A} ag(r, a) = 0$$

- $ag(r, a)$: probabilidad de que el agente elija la acción $a$ dado el recorrido $r$.
- La condición implica que hay estados en los que el agente no puede realizar ninguna acción (todas las probabilidades son 0) y otros en los que debe elegir una (la suma es 1).
- El comportamiento del agente puede ser **no determinista** (puede elegir acciones diferentes en una misma situación). En algunos contextos esto es necesario (ej: "piedra, papel y tijera").
- Si el agente actúa de forma **determinista**: $ag: R(ag, E) \rightarrow A$.

### Dinámica Agente–Entorno: Un Sistema

```
[El agente ejecuta acción a] ──→ ENTORNO (T) ──→ s' ∈ T(r, a)
                                                       │
                                              [El entorno transita
                                               a nuevo estado s']
                                                       │
                                              [Recorrido r actualizado]
                                                       │
                                              percepción(s') ──→ AGENTE (ag)
                                                       │
                                          a ← ag(r, a) [El agente determina
                                                        siguiente acción]
```

### Complejidad del Agente

La complejidad de un agente (y su capacidad para conseguir sus objetivos) está relacionada con:

- Su **conocimiento sobre cómo evoluciona el entorno** (la dinámica del entorno y las consecuencias de sus acciones).
- Sus **capacidades de percepción** (capacidad de determinar con mayor o menor certeza el estado actual).
- Sus **capacidades de razonar** con esta información para encontrar las acciones más adecuadas (el algoritmo de "selección-acción").

---

## 1.6 ¿Cómo Especificar los Objetivos de un Agente?

### Medida de Rendimiento

Creamos agentes con un **propósito**, para que realicen determinadas tareas, pero **sin decirles cómo realizarlas**.

Se define una **medida de rendimiento** $Ren_E(r) \in \mathbb{R}$: función que asigna un valor de rendimiento a un recorrido $r$ de un agente en el entorno $E$. Mayores valores implican **mayor rendimiento**.

Dos formas de especificar los objetivos de un agente:

1. **Basado en tareas**
2. **Basado en utilidad**

---

### Agentes Basados en Tareas

Son agentes más simples que deben realizar **una tarea concreta**.

#### Agentes de Mantenimiento

- Persiguen **mantener** el entorno en un determinado estado o conjunto de estados (evitar estados "negativos").
- Se especifica el objetivo a través de un conjunto $B \subseteq S$ (estados a evitar).
- Posible medida de rendimiento:

$$Ren_E(r) = \begin{cases} 0 & \text{si } \exists s_i: s_i \in s(r) \wedge s_i \in B \ 1 & \text{en otro caso} \end{cases}$$

- Alternativa (proporción de estados "buenos"):

$$Ren_E(r) = \begin{cases} 1 & \text{si } r \text{ es vacío} \ \frac{|{s \mid s \in s(r) \wedge s \notin B}|}{|{s \mid s \in s(r)}|} & \text{en otro caso} \end{cases}$$

- Ejemplo: **Termostato**.

#### Agentes Basados en Metas

- Persiguen **alcanzar** un determinado estado.
- Se especifica la meta a través de un conjunto $M \subseteq S$ de **estados meta**.
- Puede haber varios estados meta posibles; da igual cuál de ellos se alcanza.
- Los estados meta pueden especificarse a través de **características**.
- Ejemplos: agentes que planifican, agentes jugando al ajedrez u otros juegos de suma nula.
- Posible medida de rendimiento:

$$Ren_E(r) = \begin{cases} 1 & \text{si } \exists s_i: s_i \in s(r) \wedge s_i \in M \ 0 & \text{en otro caso} \end{cases}$$

- Alternativa (eficiencia del camino):

$$Ren_E(r) = \begin{cases} \dfrac{\text{mínimo número de acciones para alcanzar nodo meta}}{|a(r)|} & \text{si } \exists s_i: s_i \in s(r) \wedge s_i \in M \ 0 & \text{en otro caso} \end{cases}$$

---

### Agentes Basados en Utilidad

Los objetivos se representan implícitamente mediante la especificación de **preferencias sobre estados y/o acciones**.

#### Función de Utilidad

$$U_{ag}(s_i) = y, \quad y \in \mathbb{R}$$ $$\forall s_i, s_k \in S: U_{ag}(s_i) > U_{ag}(s_k) \Leftrightarrow ag \text{ prefiere } s_i \text{ sobre } s_k$$

- Si un estado es más preferido, su utilidad es mayor.
- La utilidad de estados "malos" puede ser negativa.

#### Función de Coste

$$C_{ag}(s_i, a_k) = y, \quad y \in \mathbb{R}$$ $$\forall s_i, s_j, a_k, a_l \in S: C_{ag}(s_i, a_k) < C_{ag}(s_j, a_l) \Leftrightarrow ag \text{ prefiere realizar } a_k \text{ en } s_i \text{ en vez de } a_l \text{ en } s_j$$

- El coste puede entenderse como una **utilidad inversa**.

#### Utilidad de un Recorrido

Se especifica el rendimiento como: $Ren_E(r) = U(r)$

¿Cuál es la utilidad de un recorrido? Dependiendo del problema:

|Opción|Fórmula|
|---|---|
|Máxima utilidad de estados en $r$|$U(r) = \max_{s_i \in s(r)} U(s_i)$|
|Mínima utilidad de estados en $r$|$U(r) = \min_{s_i \in s(r)} U(s_i)$|
|Suma o media de utilidades de estados en $r$|$U(r) = \sum_{s_i \in s(r)} U(s_i)$|
|Negativo de la suma de costes de acciones en $r$|$U(r) = -\sum_{s_i a_i \in sa(r)} C(s_i, a_i)$|

En muchos casos se emplea la **combinación de utilidades y costes**:

$$U(r) = \sum_{s_i \in s(r)} U(s_i) - \sum_{s_i a_i \in sa(r)} C(s_i, a_i)$$

#### Ejemplos de Funciones de Utilidad

**Agente en almacén buscando un producto:**

- $U(s) = 100$ si el agente se encuentra en el punto del producto buscado; $U(s) = 0$ para el resto.
- $C(a) = -1$ para todos los movimientos.

**Agente que juega al póker:**

- $U(s)$ = dinero ganado/perdido en los estados finales de cada ronda; $U(s) = 0$ para el resto.
- $C(a) = 0$ para todas las acciones.

**Robot aspirador:**

- $U(s) = 100$ si encuentra polvo en la posición $s$; $U(s) = 0$ para el resto.
- $C(a) = -1$ para cada movimiento.

#### Rendimiento Esperado

En general: **no podemos saber el rendimiento** que un agente va a tener (por la incertidumbre del entorno/agente). Pero podemos determinar el **rendimiento esperado**:

Sea $p(r \mid ag, E, s_i)$ la probabilidad de que ocurra el recorrido $r$ si el agente $ag$ está puesto en el entorno $E$ en el estado $s_i$. Se cumple: $$\sum_{r \in R(ag, E)} p(r \mid ag, E, s_i) = 1$$

El **rendimiento esperado** de un agente: $$E[Ren(ag, E, s_i)] = \sum_{r \in R(ag, E)} p(r \mid ag, E, s_i) \cdot Ren_E(r)$$

Extendido a cualquier estado inicial: $$E[Ren(ag, E)] = \sum_{r \in R(ag, E)} p(r \mid ag, E) \cdot Ren_E(r)$$

> Para rendimientos binarios, $Ren_E$ representa la **probabilidad de éxito**.

#### Teoría de la Utilidad Esperada y Agentes Óptimos

- En economía y filosofía, la elección racional en un entorno con incertidumbre es elegir la acción con la **mayor utilidad esperada**.
- **Agente óptimo = agente racional = agente que maximiza su rendimiento esperado**.

$$ag_opt_E = \arg\max_{ag \in AG} E[Ren(ag, E)] = \arg\max_{ag \in AG} \sum_{r \in R(ag, E)} P(r \mid ag, E) \cdot Ren_E(r)$$

#### La Utilidad del Dinero

- El dinero puede proporcionar una función de utilidad en determinados entornos (agentes de bolsa, juegos…).
- Ejemplo: un agente puede aceptar 1.000.000€ o jugarse el premio a cara o cruz (0€ o 3.000.000€ con probabilidad 0,5).
    - Utilidad si "no se lo juega": 1.000.000€
    - Utilidad esperada si "se lo juega": $0,5 \times 0 + 0,5 \times 3.000.000 = 1.500.000€$
    - Por utilidad esperada, el agente óptimo debería "jugárselo"… pero para los humanos la utilidad del dinero **no es proporcional a la cantidad** (función de utilidad cóncava).

---

## 1.7 Sistemas Multiagente

### De Uno a Múltiples Agentes

- En muchos entornos interesantes no existe sólo un agente que actúa, sino **varios**.
- Las acciones de **todos los agentes** influyen en el cambio del estado del entorno.
- Para un agente, la consecución de sus objetivos ya **no sólo depende de él** (sino también de lo que hacen los demás).

### Propiedades de los Agentes en un SMA

|Propiedad|Implicación en SMA|
|---|---|
|**Autonomía**|Un agente **NO puede controlar** las acciones de los demás.|
|**Racionalidad**|Un agente **SÍ puede predecir** las acciones de los demás.|
|**Sociabilidad**|Un agente **SÍ puede coordinarse** con los demás.|

### Ejemplos de Sistemas Multiagente

- La **sociedad humana**: somos inteligentes, autónomos, independientes; tenemos nuestros propios objetivos; vivimos y actuamos en un mismo entorno; interactuamos entre nosotros.
- **Entornos de negocio electrónico**.
- **Juegos multijugador**.
- **El tráfico en una ciudad**.

### Características de los Agentes en un SMA

En el caso más general, los agentes de un SMA:

- Actuarán en representación de usuarios que pueden tener **diferentes objetivos y motivaciones**.
- Tendrán **diferentes capacidades y comportamientos** (quizás desconocidos para los demás).

### Del Nivel Micro al Macro

- Ya no sólo nos interesa cómo un agente puede tomar sus decisiones para realizar con éxito sus tareas.
- Sino **cómo puede hacerlo en un entorno con otros agentes**.
- Interactuar con otros agentes **puede ser necesario** para conseguir los objetivos.

---

## 1.8 Retos en Agentes y Sistemas Multiagente

### Retos en Agentes (Nivel Individual)

**Metodologías y arquitecturas:**

- ¿Cómo crear agentes en diferentes entornos?
- ¿Cómo debe ser la estructura general de un agente en un tipo de entorno y/o tipo de tareas concreto?

**Toma de decisión:**

- Algoritmos para la función "selección-acción" que implementen estrategias de comportamientos eficientes en:
    - Diferentes tipos de entornos.
    - Para diferentes tipos de objetivos.
    - En problemas concretos.

**Ética:**

- Asegurar que las decisiones de agentes se alinean con nuestros valores, normas y leyes.
- Explicabilidad de las decisiones.

### Retos en Sistemas Multiagente

**Comunicación:**

- Lenguajes de comunicación.
- Semántica: ontologías, directorio de servicios…

**Búsqueda de comportamientos globales:**

- ¿Cómo regular un entorno para conseguir un comportamiento deseado a nivel global?
- Organizaciones, coordinación, cooperación, confianza, reputación…
- Diseño de mecanismos.

**Toma de decisiones a nivel individual en entornos con dos o más agentes:**

- En situaciones "one-shot".
- En situaciones o interacciones repetidas o continuas.

**Toma de decisiones colectivas:**

- Negociación.
- Argumentación.
- Creación de coaliciones.

---

## 1.9 Netlogo

### ¿Qué es Netlogo?

- **Netlogo** es un entorno programable para **modelar y simular** sistemas single y multiagente.
- Permite definir el entorno y los agentes.
- Existen muchos **modelos ya implementados** por otros usuarios que se pueden ejecutar y analizar.
- Se usará durante el curso para mostrar algunos **ejemplos de agentes y sistemas**.

### Acceso

- Se puede **descargar** (Windows, Mac, Linux) o **ejecutar en la web**.
- URL: [https://ccl.northwestern.edu/netlogo/](https://ccl.northwestern.edu/netlogo/)
- **Recomendación:** descargar e instalar Netlogo para poder ejecutar modelos de ejemplos durante el curso.

### Modos Principales de Netlogo

|Modo|Descripción|
|---|---|
|**Interface**|Entorno para ejecutar los modelos (interfaz gráfica, botones setup/go, parámetros, resultados).|
|**Info**|Da explicaciones sobre el modelo.|
|**Code**|Código fuente del modelo.|

### Controles de la Interfaz

- **setup:** configura todo el modelo.
- **go:** ejecuta (ejecución continua).
- **Velocidad de la ejecución:** control deslizante de velocidad.
- **Especificación de parámetros:** sliders y controles de entrada.
- **Resultados:** gráficas y visualización del mundo.

### Ejemplo: Wolf Sheep Simple 5

- Modelo de simulación de dinámica de poblaciones (ovejas, lobos, hierba).
- Modelo de depredador-presa.
- Disponible en la biblioteca de modelos de Netlogo (IABM Textbook folder).

---

## Resumen de Conceptos Clave

|Concepto|Definición|
|---|---|
|**Agente**|Entidad autónoma que percibe su entorno a través de sensores y actúa en él a través de actuadores para cumplir sus objetivos.|
|**Agente inteligente**|Agente que actúa de forma autónoma, flexible (reactivo + proactivo + social) y racional.|
|**Entorno**|Todo aquello que rodea al agente y que puede influir en él o en lo que él puede influir.|
|**Estado**|Situación concreta en la que se puede encontrar el entorno en un momento dado.|
|**Recorrido**|Secuencia de estados y acciones del agente desde el inicio de su actividad.|
|**Función de transición $T$**|Función que modela los efectos de las acciones del agente sobre el entorno.|
|**Política/Estrategia $ag$**|Función que determina la distribución de probabilidades sobre las acciones del agente dado su recorrido.|
|**Medida de rendimiento**|Función que asigna un valor numérico al recorrido de un agente para evaluar el éxito.|
|**Agente óptimo/racional**|Agente que maximiza el rendimiento esperado de su recorrido.|
|**Sistema Multiagente (SMA)**|Conjunto de agentes autónomos que actúan e interactúan en un entorno compartido.|
|**Netlogo**|Entorno de programación y simulación de sistemas multi-agente.|

---