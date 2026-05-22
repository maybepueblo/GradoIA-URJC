## Índice
1. [[#11.1 Diseño de Mecanismos]]
2. [[#11.2 Agregación de Preferencias]]
3. [[#11.3 Mecanismos Cuasi-lineales]]

---

## 11.1 Diseño de Mecanismos

### Gobernar Interacciones
- **Coordinar = gobernar la interacción** (Wegner)
- En informática (p.e. programación concurrente):
	- Se usan **protocolos de interacción**
	- Definen un conjunto de posibles secuencias de ejecución
- **Propiedades deseadas:**
	- Se definen respecto a características de dichas secuencias
	- **Propiedades de seguridad (safety):** evitar "siempre" que ocurra algo "malo"
	- **Propiedades de vivacidad (liveness):** asegurar que "eventualmente" la computación avanza

### Definición de Diseño de Mecanismos
- **Diseño de Mecanismos** (*mechanism design*):
	- Definir unas **reglas del juego** para la interacción entre agentes ("protocolo de coordinación")…
	- …tal que el resultado cumpla unas **propiedades deseadas** (por el diseñador del mecanismo)

### Asunciones del Diseño de Mecanismos
- Los agentes son **individualmente racionales** (actúan para que el resultado de la interacción sea el más preferido por ellos mismos)
- Los agentes tienen **información privada** que pueden no revelar de forma certera (pueden **"mentir"** acerca de sus preferencias)

### Propiedades Deseadas
- … del **resultado de la interacción**, respecto a las preferencias individuales de los agentes participantes
- … de la **información revelada** por los agentes

---

### Elementos de un Mecanismo

| Elemento | Descripción |
|---|---|
| **Resultado** | Una elección de un bien/persona/…, una asignación de bienes a agentes/precios…, un estado del mundo, … |
| **Planificador social** | Una institución (p.e. casa de subastas), un procedimiento (p.e. rifa, procedimiento electoral), … |
| **Tipo de agente** ($\theta_i$) | Define sus preferencias sobre resultados (e implícitamente, sus estrategias/acciones para realizarlas dentro del mecanismo) |
| **Utilidad del agente** ($u_i(x, \theta_i)$) | Depende del resultado y del tipo de agente (no considera lo que obtienen los demás agentes) |

### Dinámica de un Mecanismo
1. Cada agente **juega una estrategia** $s(\theta_i)$ que observa el planificador social
2. Dado el perfil estratégico $s(\theta)$ observado, el planificador social **elige un resultado** $x \in X$
3. Cada agente **computa su utilidad** $u_i(x, \theta_i)$

### Ejemplo: Votación
1. La estrategia de cada agente es **votar al candidato más preferido**
2. Dado el perfil de votos $(x_2, x_3, x_4, \ldots, x_2)$, el planificador social **elige el candidato más votado**
3. Cada agente computa su utilidad $u_i(x_2, \theta_i)$

### Retos para el Diseño de Mecanismos
El planificador social se enfrenta a **dos problemas**:

1. **Elección Social (agregación de preferencias):**
	- Dado un perfil de preferencias $\theta$, ¿qué resultado $x$ elegir?

2. **Revelación de la información (elicitación de preferencias):**
	- ¿Cómo hacer que cada agente $i$ elija su estrategia en base a su **verdadero tipo** $\theta_i$ (que forma parte de su información privada)?

---

## 11.2 Agregación de Preferencias

### Elección Social
- El mecanismo recibe como **entrada** $N$ órdenes de preferencias sobre posibles resultados $X$ (tipos $\theta_i$ de $N$ agentes)
- Produce como **salida** un resultado $x \in X$ elegido por el planificador social

#### Función de Elección Social (SCF)
$$f: \Theta_1 \times \Theta_2 \ldots \times \Theta_N \rightarrow X$$
- Dado un perfil de preferencias, devuelve **un único resultado** $x$

#### Función de Bienestar Social (SWF)
$$f: \Theta_1 \times \Theta_2 \ldots \times \Theta_N \rightarrow \Theta$$
- Dado un perfil de preferencias, devuelve **un orden de preferencia agregado** sobre los resultados

> Una SCF describe un mecanismo de forma **declarativa**.

---

### Votaciones
- Ejemplo "clásico" de elección social
- **Conjunto de posibles resultados:** candidatos
- **Entrada:** preferencias sobre candidatos
- **Salida:** candidato elegido

#### Métodos de Votación

| Método | Descripción |
|---|---|
| **Pluralidad (mayoría relativa)** | Cada agente da **un voto** a un candidato. Gana el que más votos recibe. |
| **Voto cumulativa** (*cumulative voting*) | Cada agente tiene **k votos** que puede distribuir. Puede dar varios votos al mismo candidato. |
| **Voto aprobatorio** (*approval voting*) | Cada agente puede dar **un voto a todos** los candidatos que "le gustan". |
| **Métodos basados en ranking** | Cada agente aporta un **orden de preferencia** entre candidatos. |

#### Métodos Basados en Ranking

**Regla de Borda** (Jean-Charles de Borda, 1733–1799):
- Cada agente asigna un **número** a cada uno de los $n$ candidatos
- Al candidato más preferido: $n-1$ puntos; al siguiente: $n-2$; …; al menos preferido: $0$ puntos
- Se **suman las puntuaciones** de cada agente y se elige el candidato con más puntos

> **Ejemplo** (2 agentes, 4 candidatos):
> - Agente 1: candidato A(3) > candidato B(2) > candidato C(1) > candidato D(0)
> - Agente 2: candidato C(3) > candidato A(2) > candidato B(1) > candidato D(0)
> - Resultado Borda: A(5) > C(4) > B(2) > D(1) → Gana A

**Eliminación sucesiva con orden:**
- Fijar inicialmente un orden ("**agenda**") en el que se comparan **pares** de candidatos
- Determinar el candidato más preferido por la mayoría en la **comparación bilateral**
- El perdedor se **elimina**, el ganador se compara con el tercero de la agenda, y así sucesivamente

**Pluralidad con eliminación** (*instant runoff voting*):
- Solo se contempla el **candidato más preferido** por cada agente
- Si algún candidato obtiene **mayoría absoluta**, es el ganador
- Si no, se elimina el candidato que **menos** veces aparece en primer lugar y se repite el proceso

---

### Criterio de Condorcet (Marques de Condorcet, 1743–1794)
- Si hay un candidato $x$ que una **mayoría** de agentes prefiere a **todos** los demás candidatos en comparaciones por pares, entonces $x$ debería ser elegido → se llama **ganador de Condorcet**

**Paradoja de Condorcet** (ejemplo con preferencias cíclicas):
- Agente 1: A > B > C
- Agente 2: B > C > A
- Agente 3: C > A > B
- → **No existe ganador de Condorcet**
- Para cualquier candidato existe una mayoría que prefiere a otro:
	- A: agentes 2 y 3 prefieren C sobre A
	- B: agentes 1 y 3 prefieren A sobre B
	- C: agentes 1 y 2 prefieren B sobre C

**Ejemplo numérico** (1000 agentes, 3 alternativas a, b, c):
- 499 agentes: a > b > c
- 3 agentes: b > c > a
- 498 agentes: c > b > a

| Método | Ganador | Razón |
|---|---|---|
| **Ganador de Condorcet** | b | 501 prefieren b sobre a; 502 prefieren b sobre c |
| **Pluralidad** | a | 499 votos en primer lugar (frente a 498 de c y 3 de b) |
| **Pluralidad con eliminación** | c | b es eliminado en 1ª ronda (solo 3 primeros puestos); en 2ª ronda c obtiene 501 votos vs 499 de a |

> **Conclusión:** Varios métodos de votación **NO cumplen** el criterio de Condorcet.

---

### Condiciones Deseables para una SWF

#### 1. Eficiencia de Pareto
- Una SWF $f$ es **Pareto-eficiente** si, en caso de que todos los agentes estén de acuerdo en preferir alternativa $x_i$ sobre $x_j$, entonces $x_i$ también es preferida sobre $x_j$ en el resultado $\theta$ de $f$
- No existe ningún otro resultado $\theta'$ que algún agente prefiera sobre $\theta$ en relación con la ordenación entre $x_i$ y $x_j$
- **Para una SCF $f$:** si todos los agentes están de acuerdo en preferir $x_i$ sobre $x_j$, entonces $x_j$ **NO** es el resultado de $f$

> **Ejemplo:** El método "Eliminación sucesiva por orden" **NO es Pareto-eficiente**
> - 3 agentes, 4 alternativas: a, b, c, d
> 	- Agente 1: b > d > c > a
> 	- Agente 2: a > b > d > c
> 	- Agente 3: c > a > b > d
> - La alternativa **b domina d** (todos prefieren b sobre d)
> - Con agenda a-b-c-d:
> 	- Ronda 1 (a-b): se elimina **b**
> 	- Ronda 2 (a-c): se elimina **a**
> 	- Ronda 3 (c-d): se elimina **c**
> 	- **Ganador: d** ← a pesar de que todos prefieren b sobre d

#### 2. Independencia de Alternativas Irrelevantes (IIA)
- Una SWF $f$ es **independiente de alternativas irrelevantes** si el orden de dos alternativas $x_i$ y $x_j$ en el resultado $\theta$ se determina *únicamente* a partir de las preferencias entre $x_i$ y $x_j$ de cada agente
- Si se aplica $f$ a un **subconjunto** de las alternativas iniciales dando como resultado $\theta'$, entonces la ordenación de alternativas en $\theta'$ ha de ser **compatible** con el resultado $\theta$ de aplicar $f$ al conjunto completo

> **Ejemplo:** La "Regla de Borda" **NO es IIA**
> - 7 agentes, 4 alternativas a, b, c, d:
> 	- 3 agentes: a > b > c > d → Borda: a=11, b=12, c=13, d=6 → Resultado: **c > b > a > d**
> - Si se elimina d:
> 	- Borda sin d: a=8, b=7, c=6 → Resultado: **a > b > c**
> - El orden inicial entre a, b y c **se ha invertido** al eliminar d

#### 3. Ausencia de Dictadores
- Un resultado $\theta$ de una SWF es **dictatorial** si existe un solo agente $i$ cuyas preferencias $\theta_i$ siempre determinan $\theta$
- Es deseable que **no existan** agentes que determinen la ordenación de las preferencias sociales con independencia de las preferencias del resto
- Una SWF dictatorial **"no agrega"** realmente preferencias

---

### Teorema de Arrow (1951)

> **Teorema de Arrow (1951):**  
> Cualquier SWF $f$ sobre **3 o más alternativas**, que es **Pareto-eficiente** e **independiente de alternativas irrelevantes**, es **dictatorial**.

**Demostración de que una SWF dictatorial es Pareto-eficiente e IIA:**
- Si todos los agentes prefieren $x_i$ sobre $x_j$, esto incluye al dictador, por lo que también se prefiere $x_i$ sobre $x_j$ en el resultado $\theta$ → cumple Pareto
- Las preferencias de los demás agentes no influyen en $\theta$, y si el dictador cambia sus preferencias solo respecto a alternativas $x_k$ distintas a $x_i$ y $x_j$, esto no influye en la relación entre $x_i$ y $x_j$ en $\theta$ → cumple IIA

### Consecuencias del Teorema de Arrow
- **Interpretación negativa:** Todas las SWF "buenas" son necesariamente dictatoriales
- Existe un resultado similar al Teorema de Arrow para **SCF**: **Teorema de Muller-Satterthwaite (1977)**
- **Posible salida:** Relajar los requisitos para SWF "buenas":
	- P.e. prescindir de / relajar la propiedad de **IIA**
	- Una nueva alternativa puede influir en el "grado" de preferencia entre los demás

---

## 11.3 Mecanismos Cuasi-lineales

### Motivación
Para abordar el problema de la **revelación de la información**, se trabaja con una subclase de mecanismos:
- **Directos:** hay una sola ronda de interacciones
- **Cuasilineales:** el resultado se divide en una **parte monetaria** y otra **no-monetaria**

---

### Elementos de un Mecanismo Directo Cuasilineal

| Elemento | Descripción |
|---|---|
| **Conjunto de resultados no monetarios** $X$ | P.e. qué bien se asigna, a quién |
| **Agentes** | Con valoraciones $v_i$ sobre $X$ y utilidad $u_i$ basada en $X$ y los pagos $p$ |
| **Conjunto de resultados monetarios (pagos $p$)** | Transferencias monetarias entre agentes y planificador |
| **Planificador social** | Decide el resultado no-monetario y los pagos |

### Protocolo del Mecanismo Directo Cuasilineal
1. Cada agente $i$ tiene sus **valoraciones privadas** $v_i$ de los resultados no-monetarios $X$, y **declara** una valoración $\hat{v}_i$ que observa el planificador social
2. Dado el perfil de valoraciones $\hat{v}$ observado, el planificador social elige un **resultado no-monetario** $x \in X$ y un **vector de pagos** $(p_1, \ldots p_N)$
3. Cada agente computa su **utilidad** $u_i((x, p_i))$

---

### Definición Formal

Un **mecanismo directo cuasilineal** es una tupla $M = (X, V, \chi(.), \wp(.))$ tal que:
- $X$ es el conjunto de **resultados no monetarios**
- $V = \{V_1, \ldots, V_N\}$, donde $V_i$ describe las **valoraciones** del agente $i$ sobre resultados no monetarios
- $\chi: V \rightarrow X$ es la **regla de elección** del resultado no-monetario
- $\wp: V \rightarrow \mathbb{R}^N$ es la **regla de pago**

**Notas importantes:**
- El conjunto de resultados completo es $O = X \times \mathbb{R}^N$ (combina parte monetaria y no-monetaria)
- Las valoraciones $v_k \in V_i$ suelen ser funciones de valor $v_k: X \rightarrow \mathfrak{R}$ que expresan **cuánto valora** el agente $i$ los resultados no-monetarios $x$
- La **utilidad** de un agente $i$ de un resultado $o = (x, (p_1, \ldots p_N))$ viene dada por:
$$u_i(o) = v_i(x) - p_i$$
- Si $p_i > 0$: el agente **paga** dinero
- Si $p_i < 0$: el agente **recibe** dinero

---

### Ejemplo: Comercio Bilateral Justo

**Contexto:**
- Agente 1 (vendedor) tiene un bien $x$ que valora en $v_1$
- Agente 2 (comprador) desea adquirir el bien y lo valora en $v_2$
- Cada agente puede declarar un precio diferente al real: $\hat{v}_1$ (precio de venta), $\hat{v}_2$ (precio de compra)
- El mecanismo determina el resultado $(x, p)$: si hay transacción y, en su caso, a qué precio

**Definición del mecanismo:**

$$\chi((\hat{v}_1, \hat{v}_2)) = (x_1, x_2) \quad \text{con} \quad (x_1, x_2) = \begin{cases} (0,1) & \text{si } \hat{v}_1 < \hat{v}_2 \\ (1,0) & \text{de lo contrario} \end{cases}$$

→ Hay transacción si el **precio de compra ofertado es superior al precio de venta**

$$\wp((\hat{v}_1, \hat{v}_2)) = (p_1, p_2) \quad \text{con} \quad p_1 = -\frac{1}{2}(\hat{v}_1 + \hat{v}_2) \cdot x_2 \quad \text{y} \quad p_2 = \frac{1}{2}(\hat{v}_1 + \hat{v}_2) \cdot x_2$$

→ Si hay transacción, el precio es el **promedio** entre los precios de compra y de venta ofertados (si no hay transacción, no hay pagos)

$$u_i((x_1, x_2), (p_1, p_2)) = x_i \cdot v_i - p_i$$

---

### Juego Inducido por un Mecanismo

**¿Cómo elige un agente racional su estrategia?**
- La valoración $\hat{v}_i$ que declara el agente $i$ depende de las valoraciones $\hat{v}_{-i}$ declaradas por los demás agentes
- Para el agente $i$, participar en el mecanismo $M$ equivale a participar en un **juego de N jugadores**, siendo $V_i$ el conjunto de sus posibles jugadas

**Definición:**

> El **juego inducido** por un mecanismo directo cuasilineal $M = (X, V, \chi(.), \wp(.))$ es un juego $\Gamma$ de $N$ jugadores con conjuntos de estrategias $V_1, \ldots, V_N$, donde la utilidad $u_i^{\Gamma}$ del agente $i$ para el perfil estratégico $(v_i, v_{-i})$ está dada por:
> $$u_i^{\Gamma}((v_i, v_{-i})) = u_i\left(\chi((v_i, v_{-i})), \wp((v_i, v_{-i}))\right)$$

**Nota:** Si el resultado del perfil de valoraciones $(v_i, v_{-i})$ bajo el mecanismo $M$ es $o = (x, p)$, entonces la utilidad que el jugador $i$ obtiene del perfil estratégico $(v_i, v_{-i})$ en el juego inducido $\Gamma$ es:
$$u_i^{\Gamma}((v_i, v_{-i})) = v_i(x) - p_i$$

#### Juego Inducido en el Comercio Bilateral Justo
- Ejemplo con vendedor $v_1 = 1$ y comprador $v_2 = 4$
- El análisis de la matriz de pagos revela:
	- Existen **múltiples equilibrios de Nash**
	- **No existe estrategia dominante**
	- Hay regiones "sin transacción" (cuando $\hat{v}_1 \geq \hat{v}_2$)
	- Los precios de transacción son el promedio de las ofertas: 1.5, 2, 2.5, 3, 3.5

---

### Resultado de un Mecanismo

**¿Cómo modelar el resultado de un mecanismo M?**
1. Una vez que los agentes hayan declarado $\hat{v}_1, \ldots, \hat{v}_N$, podemos determinar el resultado $(x, p)$ elegido por el planificador: $x = \chi(\hat{v}_1, \ldots, \hat{v}_N)$ y $p = \wp(\hat{v}_1, \ldots, \hat{v}_N)$
2. Los agentes son individualmente racionales y, por tanto, juegan un perfil estratégico $\hat{v}^*$ que es un **equilibrio del juego inducido** por M
3. A partir de las **valoraciones reales** $v_1, \ldots, v_N$ podemos determinar qué perfil $\hat{v}^*$ es racional declarar y, por tanto, el resultado $o = (x, p)$ del mecanismo M: $x = \chi(\hat{v}^*)$ y $p = \wp(\hat{v}^*)$

---

### Compatibilidad de Incentivos

**"Veracidad" de mecanismos:**
- Un mecanismo directo cuasilineal es **compatible con los incentivos** si lo mejor que puede hacer un agente es **"decir la verdad"**
- En un mecanismo compatible con los incentivos, es individualmente racional para los agentes **declarar verazmente su valoración real** $v_i$

**Definición:**

> Un mecanismo directo cuasilineal $M = (X, V, \chi(.), \wp(.))$ es **compatible con los incentivos** si el juego inducido por él tiene un equilibrio $\hat{v}^* = (\hat{v}_1^*, \ldots, \hat{v}_N^*)$ en estrategias puras, tal que $\hat{v}_i^* = v_i$ para todo agente $i$

**Nota:** La definición deja abierta de forma deliberada la noción concreta de equilibrio; en general, pueden utilizarse equilibrios en **estrategias dominantes**, **Nash**, …

#### Comercio Bilateral Justo: No-Compatibilidad con los Incentivos
- El ejemplo del comercio bilateral justo **no es compatible con los incentivos** bajo ninguna noción de equilibrio
- No tiene sentido analizarlo en base a equilibrios en estrategias dominantes, porque **no hay estrategia dominante**
- Análisis de los equilibrios de Nash (vendedor $v_1 = 1$, comprador $v_2 = 4$):

| Equilibrio $\hat{v}^*$ | ¿Coincide con valores reales? |
|---|---|
| $(1, 2)$ | $\hat{v}_2^* = 2 \neq v_2 = 4$ → **No** |
| $(3, 4)$ | $\hat{v}_1^* = 3 \neq v_1 = 1$ → **No** |
| $(2, 3)$ | $\hat{v}_1^* = 2 \neq v_1 = 1$ y $\hat{v}_2^* = 3 \neq v_2 = 4$ → **No** |

→ **Ningún equilibrio de Nash coincide con las valoraciones reales.**

---

## Resumen de Conceptos Clave

| Concepto | Definición |
|---|---|
| **Diseño de mecanismos** | Definir reglas del juego para que el resultado de la interacción entre agentes racionales cumpla propiedades deseadas |
| **SCF** | Función de elección social: $f: \Theta_1 \times \ldots \times \Theta_N \rightarrow X$ |
| **SWF** | Función de bienestar social: $f: \Theta_1 \times \ldots \times \Theta_N \rightarrow \Theta$ |
| **Ganador de Condorcet** | Candidato preferido por mayoría sobre todos los demás en comparaciones par a par |
| **Paradoja de Condorcet** | Situación con preferencias cíclicas donde no existe ganador de Condorcet |
| **Pareto-eficiencia** | Si todos prefieren $x_i$ sobre $x_j$, la SWF también debe preferir $x_i$ sobre $x_j$ |
| **IIA** | La ordenación de $x_i$ y $x_j$ solo depende de las preferencias entre $x_i$ y $x_j$ |
| **Teorema de Arrow** | Toda SWF Pareto-eficiente e IIA sobre ≥3 alternativas es dictatorial |
| **Teorema de Muller-Satterthwaite** | Resultado análogo al de Arrow para SCF (1977) |
| **Mecanismo directo cuasilineal** | $M = (X, V, \chi(.), \wp(.))$; resultado = parte no-monetaria + pagos; utilidad = $v_i(x) - p_i$ |
| **Juego inducido** | Juego de N jugadores derivado de un mecanismo, con utilidad $u_i^{\Gamma}(v_i, v_{-i}) = v_i(x) - p_i$ |
| **Compatibilidad con los incentivos** | El mecanismo tiene un equilibrio en el que cada agente declara su verdadera valoración |

---
