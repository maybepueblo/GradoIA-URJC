## Índice del Tema

- [[#2.1 Introducción y Objetivos]]
- [[#2.2 Agentes Reactivos Simples]]
- [[#2.3 Agentes con Estado]]
- [[#2.4 Agentes de Planificación]]
- [[#2.5 Agentes Híbridos]]
- [[#2.6 Agentes BDI]]
- [[#2.7 Agentes Basados en Utilidad]]
- [[#2.8 Agentes que Aprenden]]

---

## 2.1 Introducción y Objetivos

### Recordatorio del Tema 1

En el Tema 1 se vio:

- La **arquitectura básica de un agente**: compuesta por Sensores, Actuadores, Memoria, Selección-acción, Objetivos y Acciones.
- Que existen agentes para diferentes tareas:
    - **Basados en tareas:**
        - De mantenimiento
        - Para conseguir objetivos concretos
    - **Basados en utilidad:** maximizadores de la utilidad esperada

### Objetivo del Tema 2

> Analizar diferentes **tipos de agentes según cómo implementan su comportamiento**.

### Programa básico de un agente

```
m: Memoria; O: Objetivos; A: Acciones
while vivo:
    p ← percibir()
    a ← selección_acción(p, m, O, A)
    ejecutar(a)
end
```

**Funciones básicas:**

- `percibir()`: función de percepción. Obtiene la percepción del estado actual del entorno `p ∈ P`, donde `P` es el conjunto de posibles percepciones. Un agente puede percibir más o menos información según sus capacidades.
- `ejecutar()`: ejecuta una o varias acciones en el entorno.

---

## 2.2 Agentes Reactivos Simples

### Arquitectura

Un agente reactivo simple **no mantiene ningún tipo de memoria** — ni sobre su propia historia ni sobre cómo funciona y evoluciona el entorno. Elige la siguiente acción **únicamente a partir de sus percepciones actuales**.

Se implementa mediante **reglas de condición-acción**. Los objetivos suelen ser **implícitos**, codificados directamente en las reglas.

### Programa

```
while vivo:
    p ← percibir()
    a ← elegir una acción asociada a la percepción p
    ejecutar(a)
end
```

> Los agentes reactivos simples no tienen un comportamiento inteligente propio; su comportamiento **surge de la interacción con el entorno**.

---

### Ejemplo 1: Termostato

- Tipo: **Agente de mantenimiento**
- Objetivo: mantener la temperatura en un rango de alrededor de 25 grados
- Percepciones: `P = Temperatura`
- Acciones: `A = {encender, apagar}`

```
while vivo:
    temp ← percibir()
    IF temp > 25 THEN ejecutar(apagar)
    ELSE ejecutar(encender)
end
```

---

### Ejemplo 2: Cazador de Tesoros

- Tipo: **Agente basado en meta**
- Objetivo: encontrar el tesoro en una sala con obstáculos
- Percepciones: `P = {tesoro y obstáculos adyacentes a la celda actual}`
- Acciones: `A = {coger tesoro, derecha, arriba, abajo, izquierda}`

```
while vivo:
    celda ← percibir()
    IF tesoro THEN ejecutar(coger tesoro)
    IF not muro izquierda THEN ejecutar(izquierda)
    IF not muro derecha THEN ejecutar(derecha)
    IF not muro abajo THEN ejecutar(abajo)
    IF not muro arriba THEN ejecutar(arriba)
end
```

---

### Bucles Infinitos

La definición de reglas que asocian percepciones con acciones puede llevar a **bucles infinitos**. La **selección aleatoria de acciones** puede resolver estos problemas, aunque no produce un comportamiento muy inteligente.

Versión con movimiento aleatorio:

```
while vivo:
    celda ← percibir()
    IF tesoro THEN ejecutar(coger tesoro)
    ELSE
        ejecutar(movimiento aleatorio en dirección donde no hay muro)
end
```

---

### Mejor Percepción

Mejorar la percepción puede mejorar el rendimiento:

|Tipo|Descripción|
|---|---|
|**Agente ciego**|Siempre percibe lo mismo. `\|P\| = 1`. Todos los estados del mundo son **indistinguibles** para él.|
|**Agente omnisciente**|Percibe el estado completo del mundo. `\|P\| = \|S\|`. Percibe las diferencias entre todos los estados del mundo.|

**Ejemplo: Cazador de tesoros "con visión"** — se aumenta la visión a las celdas vecinas:

```
while vivo:
    celdas ← percibir()
    IF tesoro THEN ejecutar(coger tesoro)
    IF tesoro visible THEN
        ejecutar(movimiento hacia celda con tesoro)
    ELSE
        ejecutar(movimiento aleatorio en dirección donde no hay muro)
end
```

---

### Arquitectura de Subsunción de R. Brooks (1986)

**Referencia:** Brooks, R. 1986. _"A robust layered control system for a mobile robot"_

**Idea central:** La inteligencia surge de la interacción de un agente con su entorno y a partir de comportamientos simples.

**Definición formal:**

- Un **comportamiento** es un par `(c, a)`, donde `c ⊆ P` es un conjunto de percepciones y `a ∈ A` es una acción.
- `B = {(c, a) | c ⊆ P, a ∈ A}` es el conjunto de comportamientos del agente.
- En cada estado `s ∈ S`, un comportamiento se **dispara** si y solo si `c ⊆ percibir(s)`.
- En un estado pueden dispararse **varios comportamientos** a la vez.

**Selección de la acción:**

- Los comportamientos se organizan en **capas**.
- Las **capas más bajas** representan comportamientos más primitivos (evitar obstáculos, etc.) e **inhiben ("subsumen") los comportamientos de capas superiores**.

```
percepción → [Comportamientos Nivel 3]
             [Comportamientos Nivel 2]  → selección
             [Comportamientos Nivel 1]
```

**Ejemplo de aplicación:** Mars Explorer — Steels, L. (1991). _"Cooperation between distributed agents through self-organisation"_

---

## 2.3 Agentes con Estado

Un agente con estado tiene **conocimiento propio (memoria)** que mantiene y eventualmente modifica durante su ciclo de vida.

Puede mantener información sobre:

- Su **historia de acciones y percepciones**.
- Sobre **cómo evoluciona el mundo** (el entorno).

> El conocimiento acerca de cómo evoluciona el entorno se denomina **modelo del entorno**. Un agente que utilice este modelo se llama **agente basado en modelos**.

Los modelos pueden ser más o menos parciales y de mayor o menor complejidad. Pueden permitir al agente **prever las consecuencias** de sus acciones en el entorno.

---

### Arquitectura

Los agentes con estado **actualizan su estado a partir de la percepción** y seleccionan sus acciones en base a su estado/memoria.

### Programa

```
e ← e₀; O: Objetivos; A: Acciones
while vivo:
    p ← percibir()
    e ← actualizar_estado(p, e)
    a ← selección_acción(e, O, A)
    ejecutar(a)
end
```

- `e` representa el estado interno del agente (su memoria).
- `e₀` es su estado/memoria inicial.
- Los objetivos pueden ser **implícitos o explícitos**.

---

### Tipos: Reactivos vs. Deliberativos

|Tipo|Descripción|
|---|---|
|**Reactivos**|Responden directamente a estímulos del entorno. Tienen en cuenta la historia de acciones pasadas para evitar problemas como bucles infinitos. **No suelen usar un modelo del mundo.**|
|**Deliberativos**|Eligen sus acciones mediante un proceso de deliberación sobre qué acción o secuencia de acciones puede llevarles a sus objetivos. **Mantienen un modelo del mundo** y suelen ser agentes basados en metas que planifican sus acciones.|

---

### Ejemplo: Cazador de Tesoros con Estado

- Idea: almacenar el último movimiento y no volver a la celda de donde viene.

```
(um, uc) ← (null, null)
while vivo:
    celda ← percibir()
    (um, uc) ← (um, celda)
    IF tesoro THEN ejecutar(coger tesoro)
    IF posible THEN
        ejecutar(movimiento aleatorio en dirección donde no hay muro
                 y no contrario al último movimiento)
    ELSE
        ejecutar(movimiento aleatorio en dirección donde no hay muro)
    (um, uc) ← (último movimiento, celda)
end
```

Otras formas de usar la memoria en el Cazador de Tesoros:

- Evitar movimientos ya realizados anteriormente.
- Evitar moverse a celdas ya visitadas.

---

## 2.4 Agentes de Planificación

Los **agentes de planificación** son agentes "basados en metas" que:

- Mantienen una **memoria propia**.
- Mantienen una **representación explícita de sus objetivos/metas**.
- Contienen un **modelo del mundo simbólico** explícitamente representado: **creencias** especificadas.
- Usan el modelo del mundo para **deliberar** qué acción o secuencia de acciones deben realizar para alcanzar su meta.
- Seleccionan sus acciones **dirigidas por sus metas**.
- Emplean técnicas clásicas de IA como **planificación** o **búsqueda** (por ejemplo A*).

---

### Programa Básico

```
e ← e₀; O: Objetivos; A: Acciones
while vivo:
    p ← percibir()
    e ← actualizar_estado(p, e)
    plan ← planificar(e, O, A)
    ejecutar(plan)
end
```

> Los objetivos/metas del agente se encuentran incluidos en su estado/memoria.

---

### Programa con Replanificación

Cuando el entorno o los objetivos pueden cambiar, el agente necesita replanificar:

```
e ← e₀; O: Objetivos; A: Acciones
WHILE vivo:
    p ← percibir()
    e ← actualizar_estado(p, e)
    plan ← planificar(e, O, A)
    WHILE no plan vacío:
        a ← first(plan)
        ejecutar(a)
        p ← percibir()
        e ← actualizar_estado(p, e)
        IF not válido(plan, e, O) THEN
            plan ← replanificar(plan, e, O, A)
    END
```

> **Después de cada acción:** comprobar el plan y replanificar si es necesario.

El algoritmo básico (sin replanificación) funciona bien en entornos en los que:

- Los objetivos no cambian.
- El entorno no cambia.
- El agente tiene un modelo **completo y correcto** de la evolución del entorno.

---

### Ejemplos

- **Buscar el tesoro 1:** percepción perfecta, A*, sin replanificación.
- **Buscar el tesoro 2:** el tesoro puede cambiar de posición, percepción perfecta, A*, con o sin replanificación.

> Las técnicas de planificación o búsqueda se analizan en otras asignaturas.

---

## 2.5 Agentes Híbridos

Los **agentes híbridos** combinan comportamientos reactivos con planificación.

**Construcción:** a partir de dos o más subsistemas:

- Uno **deliberativo**: contiene un modelo del mundo simbólico, desarrolla planes y toma decisiones a medio o largo plazo.
- Uno **reactivo**: capaz de reaccionar a eventos sin razonamiento complejo.

Se emplea un **mecanismo de control** para decidir en cada momento cuál de los subsistemas decide la siguiente acción. Normalmente se da **precedencia al componente reactivo** sobre el deliberativo.

Los sistemas híbridos suelen definirse mediante **arquitecturas de capas**.

---

### Ejemplo: Touring Machines

**Referencia:** Ferguson, I.A. 1992. _"Touring Machines: Autonomous Agents with Attitudes"_

Arquitectura con tres capas:

```
Sensors → [Modelling Layer (M)]
          [Planning Layer (P)]   → Action Effectors
          [Reactive Layer (R)]
          [Control Framework]
```

- **Modelling Layer:** modelar el mundo.
- **Planning Layer:** planificar.
- **Reactive Layer:** responder a eventos inmediatos.
- La **selección de la acción** se realiza mediante un sistema de control.

---

## 2.6 Agentes BDI

Los **agentes BDI** (Belief, Desire, Intention) son agentes de planificación que añaden un análisis sobre **"¿Qué hacer?"**.

**Referencia:** Bratman, M. et al, 1988. _"Plans and resource-bounded practical reasoning"_

Se basan en **razonamiento práctico**:

- Es razonamiento _dirigido por las acciones_ — el proceso de descubrir qué hacer.
- _"El razonamiento práctico es una cuestión de sopesar consideraciones conflictivas por y contra las opciones que compiten, donde las consideraciones relevantes se proveen por lo que el agente desea/valora/le importa y lo que el agente cree."_ (Bratman)

> En contraste, el **razonamiento teórico** es dirigido por las creencias.

---

### Conceptos Básicos

|Concepto|Descripción|
|---|---|
|**Creencias (Beliefs)**|Información que el agente tiene sobre el mundo; su visión del mundo.|
|**Deseos (Desires)**|Estados del mundo que el agente desea, sus valores y objetivos. Un agente puede tener varios deseos de diferente tipo simultáneamente.|
|**Intenciones (Intentions)**|Deseos concretos que el agente **se ha comprometido** a lograr.|
|**Planes de acción**|Secuencias de acciones que pueden llevar a cumplir intenciones.|

---

### Razonamiento Práctico: Dos Procesos

1. **Deliberación:** Decidir _qué_ objetivos se quieren alcanzar → resultado: **intenciones**.
2. **Planificación ("Means-ends reasoning"):** Decidir _cómo_ se pueden cumplir las intenciones → resultado: **plan de acción**.

---

### Programa BDI Básico

```
C ← C₀; (objetivos y acciones incluidos en C)
WHILE vivo:
    p ← percibir()
    B ← actualizar_estado(p, C)
    I ← deliberar(C)
    plan ← planificar(C, I)
    ejecutar(a)
END
```

> `C` son las creencias (sustituye a `e` del modelo general). Los objetivos/acciones están incluidos en `C`.

---

### Programa BDI con Deliberación Explícita

La deliberación se divide en dos subprocesos:

- `opciones(C, I)`: identifica diferentes opciones/deseos.
- `filtrar(C, D, I)`: elige una opción, la convierte en intención y se compromete con ella.

```
C ← C₀; I ← I₀;
WHILE vivo:
    p ← percibir()
    C ← actualizar_estado(p, C)
    D ← opciones(C, I)
    I ← filtrar(C, D, I)
    plan ← planificar(C, I)
    ejecutar(a)
END
```

---

### Compromiso con las Intenciones

Al elegir una intención, el agente se compromete con ella. Esto implica que:

- **Estima** que puede lograrla.
- **"Insiste"** en el intento de lograrla.

El algoritmo funciona bien si:

- El entorno no cambia, salvo por las acciones del agente.
- Los objetivos del agente no cambian.
- El agente tiene un modelo completo y correcto de la evolución del entorno y emplea un mecanismo de planificación completo.

> Estas características pueden ser **demasiado restrictivas** para determinados entornos.

---

### Cambios en el Entorno

Un plan establecido puede convertirse en **inejecutable** por cambios en el entorno. Solución: comprobar el plan y replanificar tras cada acción.

```
C ← C₀; I ← I₀;
WHILE vivo:
    p ← percibir()
    C ← actualizar_estado(p, C)
    D ← opciones(C, I)
    I ← filtrar(C, D, I)
    plan ← planificar(C, I)
    WHILE no plan vacío:
        a ← first(plan)
        ejecutar(a)
        p ← percibir()
        C ← actualizar_estado(p, C)
        IF not válido(plan, C, I) THEN
            plan ← replanificar(plan, C, I)
    END
```

Los cambios también pueden afectar a la **intención** del agente: puede haber sido lograda o puede que ya no sea alcanzable:

```
WHILE no (plan vacío o exito(I, C) o imposible(I, C)):
    ...
```

> **Después de cada acción:** comprobar si la intención ya ha sido alcanzada o ya no es posible.

---

### Tipos de Compromiso: Single-minded vs. Open-minded

|Tipo|Descripción|
|---|---|
|**Single-minded**|El agente persigue una intención hasta que la alcanza o hasta que ya no es posible. **No puede cambiar su opinión** mientras persigue una intención.|
|**Open-minded (mente abierta)**|Puede **reconsiderar sus intenciones** mientras actúa. Es más flexible, puede identificar nuevas opciones/oportunidades, y revisa su intención actual después de cada acción.|

**Programa del agente de mente abierta:**

```
C ← C₀; I ← I₀;
WHILE vivo:
    p ← percibir()
    C ← actualizar_estado(p, C)
    D ← opciones(C, I)
    I ← filtrar(C, D, I)
    plan ← planificar(C, I)
    WHILE no (plan vacío o exito(I, C) o imposible(I, C)):
        a ← first(plan)
        ejecutar(a)
        p ← percibir()
        C ← actualizar_estado(p, C)
        D ← opciones(C, I)       ← revisión tras cada acción
        I ← filtrar(C, D, I)     ← revisión tras cada acción
        IF not válido(plan, C, I) THEN
            plan ← replanificar(plan, C, I)
END
```

---

### Reconsideración de Intenciones

Reconsiderar las intenciones puede ser **costoso** según el entorno, o incluso llevar a **nunca alcanzar ninguna intención**. El agente puede controlar si es razonable reconsiderar:

```
IF reconsiderar(I, C) THEN
    D ← opciones(C, I)
    I ← filtrar(C, D, I)
IF not válido(plan, C, I) THEN
    plan ← replanificar(plan, C, I)
```

---

## 2.7 Agentes Basados en Utilidad

### Motivación

Los agentes de planificación suelen ser **guiados por metas** (la satisfacción es un predicado binario: se alcanza el estado meta o no). Sin embargo, hay entornos en los que:

- La satisfacción **no es un predicado binario**.
- Cada estado del entorno es **más o menos deseable** desde el punto de vista de los objetivos del agente.
- Existe una **relación de preferencias** sobre los diferentes estados.

En estos entornos se especifican los objetivos mediante los conceptos de **utilidad** (sobre estados) y **coste** (sobre acciones).

---

### Función de Utilidad

$$U_{ag}(s_i) = y, \quad y \in \mathbb{R}$$

Representa la utilidad del estado $s_i$ para el agente $ag$, definida tal que:

$$\forall s_i, s_k \in S: U_{ag}(s_i) > U_{ag}(s_k) \Leftrightarrow ag \text{ prefiere } s_i \text{ sobre } s_k$$

> Si un estado es "mejor", su utilidad es mayor.

---

### Función de Coste

$$C_{ag}(s_i, a_k) = y, \quad y \in \mathbb{R}$$

Representa el coste de realizar la acción $a_k$ en el estado $s_i$, tal que:

$$\forall s_i, s_j \in S,\ a_k, a_l \in A: C_{ag}(s_i, a_k) < C_{ag}(s_j, a_l) \Leftrightarrow ag \text{ prefiere realizar } a_k \text{ en } s_i \text{ sobre } a_l \text{ en } s_j$$

> El coste puede entenderse como una **utilidad inversa**.

---

### Utilidad Esperada

En agentes de utilidad, el rendimiento se mide por la utilidad: $Ren_E(r) = U(r)$.

La **utilidad esperada de un agente** $ag$ en un entorno $E$ es:

$$E[U(ag, E)] = E[Ren(ag, E)] = \sum_{r \in R(ag, E)} p(r | ag, E) \cdot U(r)$$

Donde:

- $R(ag, E)$: todos los posibles recorridos de $ag$ en $E$.
- $p(r | ag, E)$: probabilidad de que ocurra el recorrido $r$.
- $U(r)$: utilidad del recorrido $r$.

---

### Agente Óptimo

Un **agente óptimo** $ag \in AG$ en un entorno $E$ es aquel que **maximiza la utilidad esperada** de su recorrido:

$$ag_opt_E = \arg\max_{ag \in AG} \sum_{r \in R(ag, E)} p(r | ag, E) \cdot U(r)$$

---

### Cómo Elige Acciones un Agente Óptimo

Dado un recorrido actual $\check{r} = s_0, \ldots, s_p$, se define la **máxima utilidad esperada posible** a partir de ese recorrido:

$$EU_{max}(\check{r}) = \max_{ag \in AG} \sum_{r \in R(ag | \check{r})} p(r | ag) \cdot U(r)$$

Desde cada estado posterior (habiendo ejecutado $a_i$ y llegado a $s_j$):

$$EU_{max}(\check{r} a_i s_j) = \max_{ag \in AG} \sum_{r \in R(ag | \check{r} a_i s_j)} p(r | ag) \cdot U(r)$$

La **máxima utilidad esperada de cada acción** $a_i$ es:

$$EU_{max}(\check{r}, a_i) = \sum_{j=1}^{m} p(s_j | \check{r} a_i) \cdot EU_{max}(\check{r} a_i s_j)$$

El **agente óptimo elige** la acción que maximiza esta utilidad:

$$ag_{opt}(\check{r}) = a_k = \arg\max_{a_i \in A(s_p)} EU_{max}(\check{r}, a_i) = \arg\max_{a_i \in A(s_p)} \sum_{j=1}^{m} p(s_j | \check{r} a_i) \cdot EU_{max}(\check{r} a_i s_j)$$

---

### Conclusión

> Si un agente $ag$ **siempre elige su siguiente acción por el principio de maximización de la utilidad esperada**, entonces $ag$ es **óptimo**.

$$ag(\check{r}) = a_k = \arg\max_{a_i \in A(s_p)} EU_{max}(\check{r}, a_i)$$

---

### Programa del Agente Basado en Utilidad

```
e ← e₀; O: Objetivos; A: Acciones
WHILE vivo:
    p ← percibir()
    e ← actualizar_estado(p, e)
    AP ← acciones_posibles(e, A)
    FOR aᵢ ∈ AP:
        ueᵢ ← estimarUE(e, aᵢ, O)
    a ← argmax_{aᵢ ∈ AP} {ueᵢ}
    ejecutar(a)
END
```

> Este tipo de agentes mantienen **conocimiento del mundo** para estimar las utilidades. No realizan una planificación directa, aunque procesos de planificación **pueden estar incluidos** en la estimación de las utilidades esperadas.

---

### Racionalidad

- Un **agente racional** emprende aquellas acciones con mayor utilidad esperada, dado todo el conocimiento del que dispone.
- **Racionalidad ≠ omnisciencia**: la racionalidad no implica hacer siempre la mejor acción, sino la mejor acción _según el conocimiento del agente_.

**Fuentes de incertidumbre del agente:**

- **Estimación de su propia historia** $\check{r}$: el agente sabe las acciones realizadas pero no necesariamente los estados por los que ha pasado (percepción parcial).
- **Estimación de los efectos futuros** $P(r | a, \check{r})$: según el entorno, es más o menos difícil prever lo que va a ocurrir.

$$\text{Más información (correcta)} \Rightarrow \text{Puede mejorar el rendimiento de un agente racional}$$

---

## 2.8 Agentes que Aprenden

### Motivación

En muchos casos es esencial que los agentes **adapten su comportamiento** a entornos cambiantes o desconocidos. Ejemplos:

- Agentes recomendadores que adaptan sus servicios a las preferencias de los usuarios.
- Agentes que aprenden a realizar tareas nuevas o de forma más eficiente.
- Agentes que tienen que actuar en entornos desconocidos.

---

### Objetivo del Aprendizaje

El objetivo siempre es **mejorar el desempeño/rendimiento**:

- **Ser más eficiente:** mejorar el _"cómo hacer"_ las cosas.
- **Ser más efectivo:** mejorar el _"qué hacer"_.

Los agentes que aprenden:

- Mantienen un **modelo del mundo** y/o conocimiento acerca de las consecuencias de sus acciones.
- El aprendizaje consiste en:
    1. Un **análisis crítico** del conocimiento basado en las observaciones del entorno.
    2. La **revisión, actualización o modificación** del conocimiento para ajustarlo a las observaciones.

> Para identificar necesidades de ajuste, el agente necesita alguna **medida de evaluación de su desempeño**.

---

### Arquitectura de un Agente que Aprende

Cuatro módulos principales:

```
Medida de
evaluación
    ↓
[Análisis crítico] ← Sensores ← Percepción ← Entorno
    ↓
[Revisión modelo] ↔ Memoria
    ↓
[Generador descubrimiento]
    ↓
[Selección-acción] → Actuadores → Acción → Entorno
    ↑ Objetivos, Acciones
```

|Módulo|Función|
|---|---|
|**Análisis crítico**|Analiza si las previsiones sobre el mundo han sido acertadas y cómo han sido los resultados de las acciones. Evalúa estos resultados en base a la **medida de evaluación**. Junto con Revisión modelo compone el **aprendizaje** del agente.|
|**Revisión modelo**|Analiza la retroalimentación del análisis crítico y **modifica y actualiza los conocimientos** del agente.|
|**Selección-acción**|Proceso de selección de la siguiente acción. Tiene en cuenta el **modelo actualizado**, por lo que puede ajustar las acciones seleccionadas a la posiblemente nueva información.|
|**Generador de descubrimiento**|Sugiere **acciones de exploración** al proceso de selección de acciones. Gestiona el dilema entre **explotar** lo ya aprendido o **explorar** nuevas situaciones.|

---

### El Dilema Exploración vs. Explotación

El agente tiene el dilema de:

- **Explotar** lo que ya ha aprendido.
- **Explorar** nuevas situaciones que potencialmente le pueden interesar.

Ejemplos de situaciones donde se aplica la exploración:

- En un juego como el Póker, analizar cómo otro jugador reacciona ante ciertas situaciones.
- Un agente con modelo parcial del entorno puede querer ampliar su visión para descubrir estados nuevos que potencialmente le interesen.

> El **generador de descubrimiento** se encarga de sugerir acciones de exploración con el fin de proporcionar nuevas experiencias que a **largo plazo** podrían ser beneficiosas para el agente.

---

## Resumen Comparativo de Tipos de Agentes

|Tipo de Agente|Memoria|Modelo del Mundo|Planificación|Aprendizaje|Utilidad|
|---|---|---|---|---|---|
|**Reactivo simple**|No|No|No|No|No|
|**Con estado**|Sí|Opcional|No|No|No|
|**De planificación**|Sí|Sí (simbólico)|Sí|No|No|
|**Híbrido**|Sí|Sí|Sí (capa deliberativa)|No|No|
|**BDI**|Sí (Creencias)|Sí|Sí (Means-ends)|No|No|
|**Basado en utilidad**|Sí|Sí|Opcional|No|Sí|
|**Que aprende**|Sí|Sí (actualizable)|Opcional|Sí|Opcional|
