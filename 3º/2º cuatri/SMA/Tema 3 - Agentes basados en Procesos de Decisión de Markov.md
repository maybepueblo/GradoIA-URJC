
## Índice

1. [[#3.1 Introducción y Objetivos]]
2. [[#3.2 Procesos de Decisión de Markov (MDP)]]
3. [[#3.3 Funciones Valor de Estados y Acciones]]
4. [[#3.4 Algoritmo de Iteración de Valores]]
5. [[#3.5 Resumen]]

---

## 3.1 Introducción y Objetivos

### Contexto previo (Tema 2)
- Se estudiaron **agentes basados en utilidad** que intentan realizar acciones que maximicen la utilidad de su recorrido en un entorno.

### Objetivo del Tema 3
- Se aborda en más detalle un caso concreto de agentes basados en utilidad:
  - Agentes que toman decisiones y actúan en **entornos modelables mediante Procesos de Decisión de Markov**.

### Situación general
- Un **agente autónomo** actúa en un entorno: realiza acciones que producen cambios en el entorno (**transiciones a otros estados**).
- Las acciones tienen consecuencias que pueden ser más o menos positivas desde el punto de vista del agente.
  - Estas consecuencias se reflejan a través de **recompensas inmediatas** (positivas o negativas).

### Problema central

> **¿Qué acciones debe realizar el agente en cada estado para obtener las máximas recompensas acumuladas durante su ciclo de vida en el entorno?**  
> **¿Cuál es la mejor política de control del agente?**

### Ciclo de interacción agente–entorno

```
Agente → acción a → Entorno → estado s, recompensa r → Agente → selecciona siguiente acción a → ...
```

- El **entorno** transita a un nuevo estado y devuelve una **recompensa** (que define cómo de buena fue la última acción).
- El **agente** emplea su **política** para determinar la siguiente acción a ejecutar.

### Asunciones y simplificaciones
- Las **transiciones** en el entorno **sólo dependen del estado actual y de la acción** que realiza el agente, pero **no de la historia** (del recorrido del agente hasta este momento).
- El entorno es:
  - **Accesible y discreto**: el agente tiene una percepción absoluta de un estado y puede distinguir todos los estados.
  - **Estacionario**: el entorno puede ser no determinista, pero las probabilidades de transición entre estados **no cambian con el tiempo**.
- El agente es un **agente basado en utilidad**:
  - Elige sus acciones de forma **determinista**.
  - Sean **S** el conjunto de estados y **A** el conjunto de posibles acciones que un agente puede realizar.
  - Sea *r* un recorrido del agente en el entorno, el objetivo del agente es **maximizar la suma de utilidades de estados menos el coste de las acciones**:

$$U(r) = \sum_{s_i \in s(r)} U(s_i) - \sum_{s_i, a_i \in sa(r)} C(s_i, a_i)$$

- Este tipo de escenarios se puede modelizar mediante **Procesos de Decisión de Markov**.

### Ejemplos de entornos aplicables
- Navegación de robots móviles (en un entorno controlado).
- Jugar al ajedrez.
- Decidir acciones en la agricultura en base a condiciones del tiempo.
- Decidir trasvase de agua en base a posibilidades de lluvia y consumo.
- Decidir la cantidad de generación de un determinado tipo de energía eléctrica en base a demanda, disponibilidad de recursos, generación por otros medios.

---

## 3.2 Procesos de Decisión de Markov (MDP)

### Definición
- Un **Proceso de Decisión de Markov (MDP)** es un marco para modelar la toma de decisiones de un agente en **entornos secuenciales** cuya evolución depende parcialmente de estas decisiones.

### Tupla definitoria
Un MDP está definido por una tupla **< S, A, T, R >**:

| Componente | Descripción |
|---|---|
| **S** | Conjunto de **estados** |
| **A** | Conjunto de posibles **acciones** |
| **T** | **Modelo de transición**: $T: S \times A \times S \to [0..1]$ |
| **r** | **Modelo de recompensas**: $r: S \times A \times S \to \mathbb{R}$ |

#### Modelo de transición T
- Es una **distribución de probabilidades** sobre el conjunto S.
- $T(s, a, s') = \Pr(s' \mid a, s)$ denota la **probabilidad de llegar al estado s'** si se realiza la acción *a* en el estado *s*.

#### Modelo de recompensas r
- $r(s, a, s')$ denota la **recompensa que el agente recibe** si realiza la acción *a* en el estado *s* y el entorno transita como consecuencia al estado *s'*.

### Propiedad de Markov
$$\Pr(s_{t+1}, r_{t+1} \mid a_t, s_t, a_{t-1}, s_{t-1}, \ldots, a_0, s_0) = \Pr(s_{t+1}, r_{t+1} \mid a_t, s_t)$$

- La probabilidad de llegar a un determinado estado y la recompensa recibida **SÓLO depende del estado anterior y de la acción realizada** (NO del historial de los estados y acciones anteriores; recorrido).
- Son **procesos sin memoria**.

### Ejemplo: MDP determinista
- **Estados:** s₀, s₁, s₂, s₃, s₄
- **Acciones:** a, b
- Transiciones y recompensas totalmente determinadas (probabilidad 1 en cada transición).
- Ejemplo de transición: $T(s_0, b, s_2) = 1$, con recompensa $r(s_0, b, s_2) = -2$.
- **Nota:** Es posible que no todas las acciones sean posibles en todos los estados (s₄ no tiene acciones disponibles).

### Ejemplo: MDP NO determinista
- Igual estructura que el anterior salvo que la acción *b* en s₂ puede llevar a s₃ o s₄ con probabilidad ½ cada uno.
  - $T(s_2, b, s_3) = 0.5$, $r(s_2, b, s_3) = 12$
  - $T(s_2, b, s_4) = 0.5$, $r(s_2, b, s_4) = 8$

### Política
- Una **política** $\pi: S \to A$ es una función que elige para cada estado la acción a realizar. Representa una posible función de decisión / política de control del agente.
- **Nota:** π corresponde al comportamiento *ag* del agente (definido en el Tema 1), ya que el agente elige sus acciones de forma determinista y, por la propiedad de Markov, sólo en base al estado actual, independientemente del recorrido hasta este momento.

#### Ejemplo: Política πₐᵥ (política avara — siempre la acción de mayor recompensa)
- $\pi_{av}(s_0) = a$
- $\pi_{av}(s_1) = b$
- $\pi_{av}(s_2) = b$
- $\pi_{av}(s_3) = b$
- $\pi_{av}(s_4) =$ no definido

### Objetivo del agente: Maximizar recompensas acumuladas
- Las recompensas acumuladas dependen del recorrido del agente, es decir, del **estado de arranque** y de la **política** que emplea.
- Dada una secuencia a partir de $s_t$ que resulta al aplicar una política π:

$$s_t \xrightarrow{r_t} s_{t+1} \xrightarrow{r_{t+1}} s_{t+2} \xrightarrow{r_{t+2}} s_{t+3} \xrightarrow{r_{t+3}} \ldots$$

- El agente quiere maximizar:

$$r_t + \gamma r_{t+1} + \gamma^2 r_{t+2} + \gamma^3 r_{t+3} + \cdots$$

### Factor de descuento γ
- **γ** es una constante de descuento ($0 \leq \gamma < 1$) que determina la importancia relativa de las recompensas inmediatas respecto a las recompensas futuras.
  - Si **γ = 0**: el agente es "miope" y solo considera recompensas inmediatas.
  - Si **γ → 1**: el agente es más precavido.

#### ¿Por qué usar un factor de descuento?
- **Inseguridad** sobre futuras recompensas en comparación con recompensas inmediatas.
  - Ejemplo ilustrativo: ¿Prefieres 20€ ahora o 25€ dentro de 1 año?
- El comportamiento de humanos y animales señala **preferencias sobre recompensas inmediatas**.
- Desde el punto de vista matemático: con un factor de descuento, la **suma de las recompensas descontadas es finita**.

### Política óptima
- El agente quiere conocer (y aplicar) la **política óptima π\***: la política que maximiza la recompensa acumulada esperada del recorrido.
- Un agente óptimo debe elegir sus acciones según el **principio de maximización de la utilidad esperada**:

$$ag(\check{r}) = a_k = \arg\max_{a_i \in A(s_p)} EU_{max}(\check{r}, a_i)$$

- Donde $\check{r} = s_0, a_0, \ldots, a_{p-1}, s_p$ es el recorrido del agente desde su comienzo hasta el estado actual $s_p$.
- $EU_{max}(\check{r}, a_i)$ es la utilidad esperada máxima del recorrido (completo) si el agente realiza la acción $a_i$ dado que hasta el momento ha hecho el recorrido $\check{r}$.

#### Simplificación gracias a la propiedad de Markov
- Dado que las recompensas futuras **no dependen del recorrido actual** (sólo del estado actual):

$$EU_{max}(\check{r}, a_i) = U(\check{r}) + EU_{max}(s_p, a_i)$$

- Por tanto, $U(\check{r})$ es constante para todas las acciones disponibles, y el agente óptimo elige:

$$\pi^*(s) = \arg\max_{a \in A(s)} EU_{max}(s, a)$$

- Donde $EU_{max}(s, a)$ es la **máxima utilidad esperada (recompensa acumulada) del recorrido futuro** a partir del estado *s* si se elige la acción *a*.

---

## 3.3 Funciones Valor de Estados y Acciones

Para calcular la política óptima, habitualmente se definen **3 funciones**:

### V*(s) — Función valor estado
- Representa la **máxima recompensa acumulada esperada** que se pueda obtener a partir de un estado *s* (con la política óptima).

$$V^*(s_t) = r_t + \gamma r_{t+1} + \gamma^2 r_{t+2} + \cdots = \mathbb{E}\left\{\sum_{i=0}^{\infty} \gamma^i r_{t+i} \;\Big|\; s_t\right\}$$

### Q*(s, a) — Función valor estado-acción
- Representa la **máxima recompensa acumulada esperada** que se pueda obtener al ejecutar la acción *a* en el estado *s* (y luego seguir con la política óptima).
- Corresponde a $EU_{max}(s, a)$.

### π*(s) — Política óptima
- Dado un estado *s*, π*(s) nos da la **"mejor" acción**: la acción con la que se puede conseguir la máxima recompensa acumulada esperada a partir de *s*.

### ¿Por qué hablamos de valores esperados?
- Porque pueden existir **acciones no deterministas**.
- La ganancia (recompensa) **esperada** de una acción con varios posibles resultados es la suma de cada resultado multiplicado por su probabilidad de ocurrir:

$$\mathbb{E}[X] = \sum_{x_i \in X} x_i \cdot p(x_i)$$

- Para una acción no determinista con dos posibles continuaciones (probabilidades 1/3 y 2/3):

$$V^*(s_t) = \frac{1}{3}\sum_{i=0}^{\infty} \gamma^i r_{t+i} + \frac{2}{3}\sum_{i=0}^{\infty} \gamma^i r'_{t+i}$$

- Es el valor que se obtendría **en promedio** al realizar esta secuencia de acciones muchas veces.

### Cómo calcular Q*(s, a)
- El "valor" de una acción es la **recompensa inmediata más el valor del estado siguiente**:

$$\boxed{Q^*(s, a) = \sum_{s' \in S} T(s, a, s') \cdot \left[r(s, a, s') + \gamma \cdot V^*(s')\right]}$$

#### Ejemplo de cálculo
Dados $V^*(s_2) = -1$, $V^*(s_1) = 9$, $V^*(s_3) = 2$ (con γ = 1):

- $Q^*(s_0, a) = \frac{1}{2}(5 + \gamma(-1)) + \frac{1}{2}(3 + \gamma(2)) = 4.5$
- $Q^*(s_0, b) = 1 \cdot (7 + \gamma(9)) = 16$

### Cómo calcular V*(s)
- El "valor" de un estado es igual al valor de la **"mejor" acción** en ese estado:

$$\boxed{V^*(s) = \begin{cases} \max_{a \in A(s)} Q^*(s, a) \\ 0, \text{ si no hay acciones disponibles en } s \end{cases}}$$

#### Ejemplo:
$$V^*(s_0) = \max_{a \in A(s_0)} Q^*(s_0, a) = \max(Q^*(s_0, a),\, Q^*(s_0, b)) = \max(4.5;\; 16) = 16$$

### Cómo calcular π*(s)
- La mejor acción (de la política óptima) es aquella que tiene el **mayor "valor"**:

$$\boxed{\pi^*(s) = \arg\max_{a \in A(s)} Q^*(s, a)}$$

#### Ejemplo:
$$\pi^*(s_0) = \arg\max_{a \in A(s_0)} Q^*(s_0, a) = \arg\max(Q^*(s_0, a),\, Q^*(s_0, b)) = b$$

### Ecuación de Bellmann para Q*
Sustituyendo la expresión de V* en la de Q*:

$$\boxed{Q^*(s, a) = \sum_{s' \in S} T(s, a, s') \cdot \left[r(s, a, s') + \gamma \cdot \max_{b \in A(s')} Q^*(s', b)\right]}$$

- Es la **ecuación de optimalidad de Bellmann para la función valor estado-acción**.
- Representa un **sistema de ecuaciones** que tiene **solución única** y se puede resolver de forma iterativa.
- Con ello se pueden calcular los valores de Q*, y a partir de Q* obtener V* y π*.

### Relación entre las tres funciones

| Función | Fórmula |
|---|---|
| $Q^*(s, a)$ | $\sum_{s'} T(s,a,s') \cdot [r(s,a,s') + \gamma \cdot V^*(s')]$ |
| $V^*(s)$ | $\max_{b \in A(s)} Q^*(s, b)$ (o 0 si no hay acciones) |
| $\pi^*(s)$ | $\arg\max_{a \in A(s)} Q^*(s, a)$ |

> Si tenemos **Q\*** podemos calcular directamente **V\*** y **π\***.

---

## 3.4 Algoritmo de Iteración de Valores

### Objetivo
- **Resolver un MDP** consiste en calcular π*.
- Se basa en resolver el sistema de ecuaciones dado por la **ecuación de Bellmann**.
- Algoritmo de programación dinámica: **"Algoritmo de iteración de valores"**.

### Pseudocódigo

```
Algoritmo de iteración de valores (para V*, Q* y π*)

1  Para todo s y todas las acciones a aplicables en s:
2      Q*(s, a) := 0          // inicializar los valores de Q*

3  Repetir
4      seguir := false
5      Para todo s y todas las acciones a aplicables en s:
6          old := Q*(s, a)
7          Q*(s, a) := Σ_{s'∈S} T(s,a,s') · [r(s,a,s') + γ ·               max_{b∈A(s')} Q*(s',b)]
8          Si |old - Q*(s,a)| > σ  Entonces  seguir := true
9  Hasta que not(seguir)          // σ positivo define el                                            criterio de terminación

10 Devuelve Q*
11 Devuelve V*(s) = max_{a∈A(s)} Q*(s, a)
12 Devuelve π*(s) = argmax_{a∈A(s)} Q*(s, a)
```

- **σ (sigma):** parámetro positivo que define el criterio de terminación. El algoritmo para cuando ningún valor de Q* cambia más de σ en una iteración completa.

### Traza del ejemplo (γ = 1, orden: estados s₀ a s₄, acciones a y b)

Partiendo del MDP no determinista con s₂ → {s₃ con ½; s₄ con ½}:

| It. | Q*(s₀,a) | Q*(s₀,b) | Q*(s₁,a) | Q*(s₁,b) | Q*(s₂,a) | Q*(s₂,b) | Q*(s₃,a) | Q*(s₃,b) |
|-----|----------|----------|----------|----------|----------|----------|----------|----------|
| 0   | 0        | 0        | 0        | 0        | 0        | 0        | 0        | 0        |
| 1   | 2        | -2       | -7       | -1       | **5**    | 10       | -4       | 6        |
| 2   | 1        | 8        | 3        | 5        | 11       | 13       | 2        | 6        |
| 3   | 7        | 11       | 6        | 5        | 12       | 13       | 3        | 6        |
| 4   | 8        | 11       | 6        | 5        | 12       | 13       | 3        | 6        |
| 5   | 8        | 11       | 6        | 5        | 12       | 13       | 3        | 6        |

**Resultados finales:**

| Estado | s₀  | s₁  | s₂  | s₃  | s₄  |
| ------ | --- | --- | --- | --- | --- |
| **V*** | 11  | 6   | 13  | 6   | 0   |
| **π*** | b   | a   | b   | b   | —   |

---

## 3.5 Resumen

### Aplicación a agentes basados en metas
- El cálculo de la política óptima también puede usarse para **agentes basados en metas**:
  - Hay que definir las utilidades de estados y costes de acciones (y con ello las recompensas) para que **reflejen el hecho de lograr o no una meta**.
  - Ejemplo: Encontrar la salida en una sala con barreras.
    - **Estados** = cuadrados del mapa.
    - **Transiciones** = flechas (con recompensas).
    - **Estado meta** = estado azul a alcanzar.
  - Codificación de objetivos con recompensas:
    - Recompensa alta (**+100**) para cualquier acción que lleva directamente a un estado meta.
    - Recompensa negativa (**-1**) para cualquier otra acción.

### Resultados del ejemplo de la sala con barreras (γ = 0.9)
- Los valores de V*(s) decaen con la distancia al estado meta siguiendo el factor de descuento (100 → 89 → 79.1 → 70.2 → 62.2 → 55 → 48.5 → 42.6 → 37.3 → 32.6 → 28.3...).
- La política óptima π* en cada estado dirige siempre hacia la meta por el camino más corto viable.

### Condiciones de optimalidad del agente basado en MDP

Un agente basado en utilidad que:
- Tiene una **percepción completa** de los estados.
- Tiene un **modelo del entorno completo y correcto**.
- Calcula la **política óptima** en función de sus funciones de utilidad y coste.
- Aplica la política óptima para decidir sus acciones.

**Es óptimo** en un entorno:
- **Accesible, discreto y estacionario**.
- En el que las consecuencias de las acciones NO dependen de la secuencia de acciones hasta este momento, sino sólo del **estado actual** y de las acciones que el agente elige.

### Convergencia del algoritmo
- Si **γ < 1** y **σ** es lo suficientemente pequeño (o se itera indefinidamente), el algoritmo **converge hacia los valores correctos de Q\***, es decir, hacia la política óptima.

### Problemas y limitaciones
- Las restricciones del modelo son **bastante fuertes**:
  - En muchos casos no se tiene un **modelo completo y correcto del mundo** o el entorno es dinámico.
  - No hay una **percepción perfecta** del entorno.
- En entornos interesantes el número de estados y acciones suele ser **muy elevado** → problemas de memoria.

### Extensiones
- **POMDP (Partially Observable Markov Decision Process)**:
  - La percepción del estado no es perfecta.
  - No se sabe con exactitud el estado al que se ha llegado después de una acción; se observa el estado con una **cierta probabilidad**.
  - Ejemplo de aplicación: **Póker**.

---

## Fórmulas Clave (Resumen)

| Nombre | Fórmula |
|---|---|
| **Recompensa acumulada descontada** | $r_t + \gamma r_{t+1} + \gamma^2 r_{t+2} + \cdots$ |
| **Modelo de transición** | $T(s,a,s') = \Pr(s' \mid a, s)$ |
| **Recompensa** | $R(s,a,s') = U(s') - C(s,a)$ |
| **V\*(s)** | $\mathbb{E}\left\{\sum_{i=0}^{\infty} \gamma^i r_{t+i} \mid s_t\right\}$ |
| **Q\*(s,a)** | $\sum_{s'} T(s,a,s') \cdot [r(s,a,s') + \gamma \cdot V^*(s')]$ |
| **π\*(s)** | $\arg\max_{a \in A(s)} Q^*(s,a)$ |
| **V\*(s) desde Q\*** | $\max_{a \in A(s)} Q^*(s,a)$ |
| **Bellmann Q\*** | $\sum_{s'} T(s,a,s') \cdot [r(s,a,s') + \gamma \cdot \max_{b \in A(s')} Q^*(s',b)]$ |

---