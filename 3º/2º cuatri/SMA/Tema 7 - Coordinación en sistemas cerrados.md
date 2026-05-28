## Índice

1. [[#7.1 Introducción]]
2. [[#7.2 Resolución Cooperativa y Distribuida de Problemas (CDPS)]]
    - [[#Fases generales del CDPS]]
    - [[#Compartición de Tareas]]
    - [[#Protocolo Contract Net]]
    - [[#FIPA Contract Net]]
    - [[#Decidir cómo pujar (Sandholm 1999)]]
    - [[#Compartición de Resultados]]
3. [[#7.3 Ejemplo — Coordinación de Ambulancias en Emergencias]]
4. [[#7.4 Coordinación Descentralizada — Subasta de Bertsekas]]
    - [[#Problema de Asignación]]
    - [[#Idea del algoritmo]]
    - [[#Algoritmo (versión matriz de valores)]]
    - [[#Algoritmo (versión matriz de costes)]]
    - [[#Ejemplo paso a paso]]
    - [[#Propiedades y complejidad]]
5. [[#7.5 Ejemplo — Gestión de Tráfico]]
    - [[#Descripción del problema]]
    - [[#Arquitectura del sistema multiagente]]
    - [[#Agentes de Detección de Problemas (PDA)]]
    - [[#Agentes de Control (CA)]]
    - [[#Ejemplo de escenario con tres problemas simultáneos]]
    - [[#Gestión de Tráfico como CDPS]]
6. [[#7.6 Ejemplo — Gestión de Flotas de Autobuses]]
    - [[#Arquitectura del sistema]]
    - [[#Detección de Incidentes]]
    - [[#Propuesta de Acciones de Control]]
    - [[#Coordinación para mover un autobús entre líneas]]

---

## 7.1 Introducción

### Posición de los Sistemas Cerrados en el espectro multiagente

Los sistemas multiagente se sitúan en un espectro que va desde sistemas **abiertos** (sin control global, objetivos individuales) hasta sistemas **cerrados** (control global total, objetivos globales):

| Tipo de sistema                                     | Control                        | Objetivos    |
| --------------------------------------------------- | ------------------------------ | ------------ |
| Sociedades de agentes (tráfico, P2P…)               | Sin control global             | Individuales |
| Equipos de agentes (fútbol, supply chains…)         | Intermedio                     | Mixtos       |
| Organizaciones de agentes (sistemas empresariales…) | Existencia de autoridad global | Mixtos       |
| **Sistemas de componentes (gestión, flotas…)**      | **Control global total**       | **Globales** |

> _"The integration and harmonious adjustment of individual work efforts towards the accomplishment of a larger goal"_ — B. Singh

### Características de la Coordinación en Sistemas Cerrados

- **TODOS** los agentes trabajan en colaboración para conseguir un **objetivo global común**.
- La pregunta central es: ¿cómo organizar de forma efectiva las acciones de los agentes?
- Se diseñan **protocolos y planes de actuación conjunta** (optimización).
- Se aplican **métodos top-down**.

---

## 7.2 Resolución Cooperativa y Distribuida de Problemas (CDPS)

**CDPS** = _Cooperative Distributed Problem Solving_

- La mayoría de estos sistemas asumen **agentes benevolentes**.
- **Agentes benevolentes:**
    - Implícitamente comparten un objetivo común.
    - Suele asumirse cuando los agentes son diseñados por o son propiedad de una misma organización.
    - La asunción de benevolencia **simplifica el diseño**.
- **Agentes con propios intereses:**
    - Tienen intereses propios, potencialmente en conflicto con otros agentes.
    - En este caso se usa **Teoría de Juegos** → Temas 9–12.

---

### Fases generales del CDPS

El proceso de resolución de un problema por un grupo de agentes con CDPS sigue tres fases:

#### 1. Descomposición del Problema

- El problema se divide en problemas más pequeños, típicamente de forma **jerárquica**.
- La división la puede hacer un agente individual que tenga la experiencia para ello (p. ej., que conozca la estructura de tareas).
- También es importante conocer los agentes que van a resolver los subproblemas.

#### 2. Solución de cada Sub-Problema

- Los subproblemas son resueltos **individualmente** por agentes.
- Puede requerir **intercambio de información** entre agentes.

#### 3. Composición de la Solución

- Las soluciones de cada subproblema se **integran** en la solución global.
- Puede realizarse de forma **jerárquica**.

---

### Compartición de Tareas

Dos actividades principales en CDPS:

#### Compartición de Tareas

- Consiste en **repartir los subproblemas** entre los agentes.
- ¿Cómo decidir cómo asignar tareas a agentes?
    - Si todos los agentes son **homogéneos** en cuanto a capacidades: es simple, cualquier tarea se puede asignar a cualquier agente.
    - Si son **autónomos (no benevolentes)**: puede requerir alcanzar acuerdos entre varios.

#### Compartición de Resultados

- Los agentes comparten información sobre sus subproblemas (tareas).
- Puede realizarse:
    - **Proactivamente**: el agente envía información a otro agente porque piensa que puede ser relevante.
    - **Reactivamente**: el agente responde a una petición de otro agente.

---

### Protocolo Contract Net

- Protocolo para **cooperación eficiente** mediante la compartición de tareas en redes de resolutores de problemas.
- Inspirado en los **procesos de ofertar contratos a licitación**.

#### Etapas

| #   | Etapa         | Descripción                                                                                                                                                                                                                                |
| --- | ------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| 1   | **Anuncio**   | El agente gestor (que tiene una tarea que no puede realizar) hace un anuncio a otros agentes con una especificación de la tarea y un tiempo para responder. El anuncio se distribuye a todos los agentes o a los candidatos si se conocen. |
| 2   | **Puja**      | Los agentes evalúan si tienen las capacidades relevantes para la tarea anunciada. Si encajan, pujan (indicando sus capacidades).                                                                                                           |
| 3   | **Concesión** | El gestor decide entre las propuestas recibidas el agente más apropiado y comunica su decisión a todos los que pujaron.                                                                                                                    |
| 4   | **Ejecución** | Una vez ejecutada la tarea, se informa al gestor.                                                                                                                                                                                          |

---

### FIPA Contract Net

Versión estandarizada por FIPA del protocolo Contract Net. Introduce roles y mensajes específicos:

#### Roles

- **Initiator** (Gestor): el agente que tiene la tarea que no puede realizar.
- **Participant** (Participante): los agentes a quienes se dirige el anuncio.

#### Mensajes del protocolo

**Fase 1 — Anuncio:**

- El _Initiator_ envía un mensaje **cfp** (_call for proposals_) a _m_ agentes con la especificación de la tarea y un plazo para responder.

**Fase 2 — Puja:**

- Los agentes evalúan si tienen las capacidades relevantes.
- Si encajan: envían **propose** (indicando sus capacidades).
- Si no encajan: envían **refuse**.
- Sólo _n_ agentes (n ≤ m) pueden responder dentro del plazo dado.

**Fase 3 — Concesión:**

- El gestor decide entre las _j_ propuestas recibidas los agentes más apropiados.
- Envía **accept-proposal** a los _l = j - k_ seleccionados.
- Envía **reject-proposal** a los _k_ no seleccionados.

**Fase 4 — Ejecución:**

- Los agentes seleccionados ejecutan la tarea e informan al gestor con:
    - **inform-done**: la tarea se ha terminado.
    - **inform-result**: explicación de los resultados.
    - **failure**: si no pudo completarse la tarea.

---

### Decidir cómo pujar (Sandholm, 1999)

Formalización de la decisión de puja en Contract Net:

- Un agente _i_ con recursos _r_ (el coste y beneficio se definen a través de una única unidad) debe decidir si pujar o no por una tarea especificada por _s_.

#### Notación

|Símbolo|Definición|
|---|---|
|τᵢᵗ|Conjunto de tareas que el agente _i_ tiene que realizar en el instante _t_|
|s|Especificación de tarea|
|τ(s)|Tareas especificadas por _s_|
|cᵢᵗ(τ)|Coste para el agente _i_ de ejecutar las tareas τ en el instante _t_|

#### Coste Marginal

El **coste marginal** para _i_ de ejecutar las tareas τ(s) en el instante _t_ (el coste de las nuevas tareas) es:

$$\mu_i(\tau(s) \mid \tau_i^t) = c_i(\tau_i^t \cup \tau(s)) - c_i(\tau_i^t)$$

#### Regla de Puja

- **Pujar si** $\mu_i(\tau(s) \mid \tau_i^t) < r$ (tiene suficientes recursos).
- De lo contrario, **no pujar**.

#### Observaciones importantes

- Debido a las **sinergias**, el coste marginal a menudo no es simplemente $c_i(\tau(s))$. De hecho, puede ser **cero** (las tareas adicionales pueden realizarse gratis).
    - Ejemplo: el coste de llevar a otra persona al trabajo en coche.
- Mientras el coste marginal sea menor que los recursos disponibles, es **racional** para el agente pujar por el trabajo.

---

### Compartición de Resultados

Los agentes intercambian información de forma cooperativa hasta componer la solución.

La compartición de resultados mejora el sistema en cuatro dimensiones:

|Dimensión|Descripción|
|---|---|
|**Confianza**|Las soluciones generadas de forma independiente pueden ser comprobadas por otros agentes.|
|**Completitud**|Los agentes pueden compartir su visión local para alcanzar una mejor visión global.|
|**Precisión**|La compartición de resultados puede mejorar la precisión de la solución global.|
|**Puntualidad**|Una solución creada de forma compartida se puede obtener más rápido (por paralelismo).|

---

## 7.3 Ejemplo — Coordinación de Ambulancias en Emergencias

### Factor clave de calidad del servicio

> El factor principal de calidad en los servicios de emergencia es el **tiempo de respuesta**, especialmente para pacientes críticos (nivel 0).
> 
> Tiempo de respuesta = desde la **movilización de un recurso** hasta la **llegada al paciente**.

**¿Cómo reducir el tiempo de respuesta?** → Optimizando la gestión de la flota de ambulancias.

---

### Procedimiento habitual vs. Propuesta

#### Procedimiento habitual (asignación secuencial)

1. El primer paciente es asignado a la unidad libre más cercana en ese momento.
2. El segundo paciente es asignado a la siguiente unidad libre más cercana.
3. Y así sucesivamente…

#### Propuesta: Reasignación dinámica de pacientes

- **Siempre que** aparece un nuevo paciente o queda una ambulancia libre:
    - Se **reasignan todos los pacientes** (incluidos los ya asignados) tal que se **minimiza la suma de los tiempos de respuesta** a todos los pacientes.

### Comparación de resultados (ejemplo con 5 pacientes y 5 UVIs)

La asignación secuencial puede generar cruces y asignaciones subóptimas, mientras que la asignación óptima minimiza la suma total de distancias/tiempos recorridos. La diferencia visual es clara en el ejemplo de Madrid con UV1–UVI5 y 5 pacientes aparecidos en orden.

### Solución técnica

> ¿Cómo encontrar la asignación óptima de un conjunto de pacientes a las ambulancias disponibles?

→ **Subastas combinatorias**, en concreto: el **Algoritmo de Subasta de Bertsekas**.

---

## 7.4 Coordinación Descentralizada — Subasta de Bertsekas

> Referencia: Bertsekas, Dimitri P. _"The auction algorithm: A distributed relaxation method for the assignment problem."_ Annals of Operations Research 14.1 (1988): 105–123.

---

### Problema de Asignación

- _n_ agentes y _m_ tareas (_m_ ≥ _n_).
- Cada tarea _t_ puede ser asignada a cualquier agente _a_ con un coste: **c(t, a)**.
- Cada tarea sólo puede ser asignada a **un agente** y cada agente recibe **exactamente una tarea** → problema de asignación clásico.
- **Objetivo:** Minimizar el coste total de la asignación global.

#### Ejemplo de matriz de costes

| C(t,a) | t₁  | t₂  | t₃  | t₄  |
| ------ | --- | --- | --- | --- |
| a₁     | 2   | 1   | 4   | 1   |
| a₂     | 4   | 7   | 2   | 8   |
| a₃     | 6   | 2   | 1   | 9   |

En este ejemplo, la asignación óptima tiene un **coste total = 5**; donde esto se consigue haciendo:
- $a_1\rightarrow t_4 ; a_2\rightarrow t_3 ; a_3\rightarrow t_2$ 

---

### Idea del algoritmo

- Los **agentes pujan** por tareas (la menos costosa).
- Las **tareas tienen un precio** (inicialmente 0).
- Cada agente emite una puja para la **tarea preferida** (la más valiosa/barata para él).
- El **importe de la puja** es el ***precio de la tarea** **más la diferencia entre el segundo mejor coste y el mejor coste***.
- Si hay varios agentes que quieren la misma tarea, ésta **aumenta su precio**.

#### Ejemplo de cálculo de puja

Dados precio $(t₁) = 4$ y precio $(t₂) = 1$:

- $cost_{a₁}(t₁) = c(a₁, t₁) + precio(t₁) = 2 + 4 = **6**$
- $cost_{a₁}(t₂) = c(a₁, t₂) + precio(t₂) = 3 + 1 = **4**$

→ a₁ puja por t₂ (menor coste) con $puja_{a₁} = cost_{a₁}(t₁) − cost_{a₁}(t₂) = 6 − 4 = 2$

> El valor de la puja representa la **ventaja** de la tarea t₂ respecto a la siguiente mejor (t₁). Si alguien pagara más por t₂, el agente cambiaría su opinión, pujando por t₁.

---

### Algoritmo (versión matriz de valores)

> Asunción: el número de agentes ≥ número de tareas.

**1. Inicialización:**

- Asignar a cada tarea un precio inicial de 0.
- Todos los agentes están inicialmente sin asignar.

**2. Mientras existan agentes sin asignar:**

_2.1 Para cada agente sin asignar:_

a. Calcular el valor más alto y el segundo valor más alto que el agente podría obtener de las tareas no asignadas:

```
valor_max         = max(valor[t] - precio[t])
segundo_valor_max = max(valor[t] - precio[t]), excluyendo la tarea con valor_max
```

b. Determinar la tarea con el valor_max:

```
tarea_optima = tarea t con (valor[t] - precio[t] == valor_max)
```

c. Calcular la oferta:

```
oferta = precio[tarea_optima] + (valor_max - segundo_valor_max) + ε
```

d. Hacer una oferta por `tarea_optima` con la cantidad `oferta`.

_2.2 Actualizar las asignaciones y precios:_

Para cada tarea que ha recibido ofertas:

- i. Si la tarea está actualmente asignada a algún agente, **liberar ese agente**.
- ii. **Asignar** la tarea al agente que hizo la oferta más alta.
- iii. **Establecer el precio** de la tarea al valor de la oferta más alta.

**3. Terminar cuando todos los agentes estén asignados.**

---

### Algoritmo (versión matriz de costes)

**Inicialización:**

- AS := {}; ∀tᵢ: precio(tᵢ) := 0 // AS = Asignación

**Repetir** (proceso iterativo):

_Fase de apuestas:_

- Para cada agente aᵢ **no asignado**:
    - Calcula el coste para cada tarea: cost_{aᵢ}(tⱼ) = c(aᵢ, tⱼ) + precio(tⱼ)
    - Sean t_k y t_s las tareas con el **menor** y el **segundo menor** coste de todas.
    - Emite una puja a la tarea de menor coste (t_k) con valor: $$puja_{a_i} = cost_{a_i}(t_s) - cost_{a_i}(t_k)$$

_Fase de asignación:_

- Para cada tarea tⱼ que ha recibido al menos una puja:
    - Sea a_u el agente con la puja más alta (puja_{aᵤ}) para tⱼ.
    - AS := (AS \ {<_, tⱼ>}) ∪ {<a_u, tⱼ>} // asigna tⱼ a a_u eliminando la asignación anterior.
    - precio(tⱼ) := precio(tⱼ) + puja_{aᵤ}

**Hasta que** todas las tareas estén asignadas.

---

### Ejemplo paso a paso

Usando la matriz de costes:

| C(t,a) | t₁  | t₂  | t₃  | t₄  |
| ------ | --- | --- | --- | --- |
| a₁     | 2   | 1   | 4   | 1   |
| a₂     | 4   | 7   | 2   | 8   |
| a₃     | 6   | 2   | 1   | 9   |

#### Iteración 0 — Inicialización

Precios: p(t₁)=0, p(t₂)=0, p(t₃)=0, p(t₄)=0

Matriz p(t) + c(a,t) (coincide con C(t,a)):

| p+c | t₁  | t₂  | t₃  | t₄  |
| --- | --- | --- | --- | --- |
| a₁  | 2   | 1   | 4   | 1   |
| a₂  | 4   | 7   | 2   | 8   |
| a₃  | 6   | 2   | 1   | 9   |

#### Iteración 1 — Fase de apuestas

- **a₁**: menores costes → t₂(1) y t₄(1) empate; segundo menor → cualquier otro. En la práctica t₂ es la preferida (coste 1). Segundo menor: t₄(1) o t₁(2). Puja por **t₂** con puja = cost(t₄) − cost(t₂) = 1 − 1 = **0**.
- **a₂**: menor → t₃(2), segundo menor → t₁(4). Puja por **t₃** con puja = 4 − 2 = **2**.
- **a₃**: menor → t₃(1), segundo menor → t₂(2). Puja por **t₃** con puja = 2 − 1 = **1**.

Pujas recibidas:

- t₂: a₁(0)
- t₃: a₂(2), a₃(1)

Fase de asignación:

- t₂ → a₁ (única puja). precio(t₂) = 0 + 0 = **0**
- t₃ → a₂ (puja más alta = 2). precio(t₃) = 0 + 2 = **2**

Estado tras iteración 1:

| Iteración | Fase       | t₁    | t₂  | t₃           | t₄  |
| --------- | ---------- | ----- | --- | ------------ | --- |
| 0         | Precio     | 0     | 0   | 0            | 0   |
| 1         | Pujas      | a₁(0) | 0   | a₂(2); a₃(1) | 0   |
| 1         | Asignación | a₁    | 0   | a₂           | 0   |
| 1         | Precio     | 0     | 0   | 2            | 0   |

Matriz p(t) + c(a,t) actualizada:

| p+c | t₁  | t₂  | t₃    | t₄  |
| --- | --- | --- | ----- | --- |
| a₁  | 2   | 1   | 2+4=6 | 1   |
| a₂  | 4   | 7   | 2+2=4 | 8   |
| a₃  | 6   | 2   | 2+1=3 | 9   |

#### Iteración 2 — Solo a₃ no asignado

- **a₃**: menor → t₂(2), segundo menor → t₃(3). Puja por **t₂** con puja = 3 − 2 = **1**.

Pujas: t₂: a₃(1).

Asignación: t₂ → a₃ (desplaza a a₁). precio(t₂) = 0 + 1 = **1**. a₁ queda libre.

|            | t₁  | t₂  | t₃  | t₄  |
| ---------- | --- | --- | --- | --- |
| asignación | 0   | a₃  | a₂  | 0   |
| precio     | 0   | 1   | 2   | 0   |

Matriz actualizada:

| p+c | t₁  | t₂    | t₃    | t₄  |
| --- | --- | ----- | ----- | --- |
| a₁  | 2   | 1+1=2 | 2+4=6 | 1   |
| a₂  | 4   | 1+7=8 | 2+2=4 | 8   |
| a₃  | 6   | 1+2=3 | 2+1=3 | 9   |

#### Iteración 3 — Solo a₁ no asignado

- **a₁**: menores costes → t₁(2), t₂(2), t₄(1). Menor → t₄(1), segundo menor → t₁(2) o t₂(2). Puja por **t₄** con puja = 2 − 1 = **1**.

Pujas: t₄: a₁(1).

Asignación: t₄ → a₁. precio(t₄) = 0 + 1 = **1**.

|            | t₁  | t₂  | t₃  | t₄  |
| ---------- | --- | --- | --- | --- |
| asignación | 0   | a₃  | a₂  | a₁  |
| precio     | 0   | 1   | 2   | 1   |
|            |     |     |     |     |

**Todos los agentes asignados. Algoritmo terminado.**

Asignación final: **a₁→t₄, a₂→t₃, a₃→t₂**  
Coste total = c(a₁,t₄) + c(a₂,t₃) + c(a₃,t₂) = 1 + 2 + 2 = **5** ✓ (óptimo)

---

### Propiedades y complejidad

- Se añade **ε** a los precios para **evitar iteraciones infinitas** en algunos casos.
- El algoritmo encuentra la **solución óptima** si:
    - Los costes son **enteros**, y
    - **ε < 1/n**
- Si **m < n** (menos tareas que agentes), entonces las tareas pujan por agentes.
- **Complejidad** (peor caso): _O(n³C/ε)_, donde _C_ es el máximo coste.
- Se puede reducir la complejidad a **O(n³log(nC))** con la técnica de _ε-scaling_.

### Aplicación directa a ambulancias

|Elemento del algoritmo|Aplicación en emergencias|
|---|---|
|Agentes|Ambulancias|
|Tareas|Pacientes|
|Coste c(t,a)|Distancia o tiempo esperado de trayecto|

---

## 7.5 Ejemplo — Gestión de Tráfico

### Descripción del problema

**Contexto:** Red de vías de alta capacidad (ejemplo de Bilbao).

**Objetivos del sistema:**

1. **Detectar problemas** a partir de los datos de sensores.
2. **Asistir a los operadores** del centro de control para configurar conjuntos de mensajes en paneles de señalización variable.

**Estructura del mapa:** Las flechas indican sentidos de circulación de vehículos en tramos de carreteras. Cada tramo y sentido (flecha) se concibe como un **"área problema"**, es decir, una zona a monitorizar.

**Áreas del ejemplo de Bilbao (12 en total):**

1. A8 Santander–Bilbao
2. Avanzada sentido Entrada
3. Avanzada sentido Salida
4. Solución Sur sentido Bilbao–S. Sebastián
5. Solución Sur sentido Bilbao→Santander
6. Rontegi sentido Cruces
7. Rontegi sentido Aeropuerto/Avanzada
8. Lamiako sentido A8
9. Lamiako sentido Avanzada
10. Enlace Basauri–Erletxe
11. Eje Norte sentido Aeropuerto
12. Eje Norte sentido Bilbao

**Complejidad del problema** debida a:

- La **cantidad de datos** a procesar.
- La **complejidad de los procesos de razonamiento**.

**Solución propuesta:** Un **sistema multiagente** que distribuye entre diferentes agentes:

- El **conocimiento** para resolver determinadas tareas.
- Las **áreas de actuación** dentro del mapa de carreteras.

---

### Arquitectura del sistema multiagente

El sistema se compone de:

- **12 agentes de detección de problemas (PDA)**
- **5 agentes de control (CA)**: Briseide, Cassandra, Demetra, Elena, Atena

**Dependencias entre CAs y PDAs:**

|CA|PDAs que gestiona (principales)|PDAs de los que recibe info adicional|
|---|---|---|
|Briseide|PDA8, PDA4|PDA1|
|Cassandra|PDA10, PDA5, PDA7|PDA1|
|Demetra|PDA11|PDA7, PDA12|
|Elena|PDA12, PDA9|PDA11, PDA3|
|Atena|PDA3, PDA2, PDA6|—|

Ejemplo: el CA "Cassandra" se encarga de proponer acciones cuando alguno de los agentes PDA5, PDA7 y/o PDA10 detectan un problema. Además, requiere información del PDA1 sobre el estado del área 1.

### Ontología compartida

Los agentes usan una **ontología compartida** para la descripción de la red de tráfico:

- **Ontología Genérica:** Define conceptos generales para cualquier red de tráfico.
    - Ejemplos: carreteras, secciones, conexiones, problemas, sensores, paneles…
- **Ontología del Dominio (instancias):** Define los elementos concretos (instancias) de la red que se modela.
    - Ejemplos: M30 (carretera), salida Boadilla (sección), sensor S111, etc.

---

### Agentes de Detección de Problemas (PDA)

Cada PDA es responsable de un **área problema concreta** y realiza tres tareas:

#### 1. Abstracción de Datos

- Los datos de sensores se **agrupan y abstraen** generando valores de más alto nivel.
- Ejemplo: en una carretera, una velocidad entre 45 y 75 km/h se considera _velocidad baja_.

#### 2. Identificación de Problemas

- Se aplican **patrones típicos de problemas** que relacionan el estado de ciertas secciones de la carretera con determinado tipo de problema.
- Ejemplo: una _"retención por rampa de incorporación"_ se detecta si:
    - En una sección de la carretera la **saturación es alta**.
    - En la sección inmediatamente anterior la **velocidad es baja** o la **ocupación alta**.
    - En medio hay una **rampa de incorporación** cuya **ocupación es media o alta**.

#### 3. Cálculo de Gravedad y Estado General del Área Problema

- Se calcula el **exceso de vehículos** en una sección como la diferencia entre la **demanda** y la **capacidad** de esa sección.
- La **gravedad** de un área se obtiene a partir del exceso, en un proceso de abstracción en categorías: **baja, media o alta**.

---

### Agentes de Control (CA)

Cada CA se encarga de problemas detectados en **varias áreas problema** (con continuidad en el sentido de la circulación).

Realizan las siguientes funciones:

#### Escenarios de Distribución de Tráfico

- Representan el **impacto esperado** de realizar ciertas propuestas de señalización en paneles para determinados problemas.

#### Propuestas de Señalización

- A partir de esos patrones y los problemas detectados, se **proponen mensajes** a poner en los paneles.

#### Detección de Conflictos

- Existe conocimiento sobre los **paneles compartidos** por varios agentes de control.
- Un conflicto ocurre cuando dos CAs quieren poner mensajes distintos en el mismo panel.

#### Resolución de Conflictos

- Se tiene en cuenta la **gravedad del problema**.
- Si tienen la misma gravedad, se hace uso de **prioridades entre las áreas problema**.
    - Ejemplo: por las mañanas, los **accesos a Bilbao tienen prioridad** sobre las salidas.
- La resolución se realiza de manera:
    - **Local:** el mismo agente resuelve sus propios conflictos.
    - **Distribuida:** los agentes de control (CA) se intercambian las propuestas locales.

---

### Ejemplo de escenario con tres problemas simultáneos

**Problemas detectados:**

- Área 2: _Avanzada sentido Entrada_
- Área 6: _Rontegi sentido Cruces_
- Área 11: _Eje Norte sentido Aeropuerto_

**Secuencia de eventos/mensajes:**

|#|Evento|
|---|---|
|1|PDA6 detecta problema en Área 6|
|2|PDA6 informa a CA Atena|
|3|CA Atena pide información a PDA12 y PDA2|
|4|PDA2 detecta un problema en Área 2|
|5|PDA2 informa a CA Atena|
|6|PDA11 detecta un problema en Área 11|
|7|PDA11 informa a CA Demetra|
|8|CA Demetra pide información a PDA7|
|9|CAs Atena y Demetra se intercambian sus propuestas locales|

---

### Gestión de Tráfico como CDPS

Aplicación del framework CDPS al problema de gestión de tráfico:

|Fase CDPS|Aplicación en Gestión de Tráfico|
|---|---|
|**Descomposición**|Se divide por tipo de problema (detección y propuesta de acción) y zona de la ciudad.|
|**Solución de cada subproblema**|Proceso continuo. PDAs detectan los problemas e informan a los CAs correspondientes. CAs proponen soluciones parciales a sus problemas.|
|**Composición de la solución**|Los CAs intercambian propuestas locales y resuelven conflictos si los hay. Informan a los paneles correspondientes; la solución global es la situación de todos los paneles.|

---

## 7.6 Ejemplo — Gestión de Flotas de Autobuses

**Caso de aplicación:** Empresa Municipal de Transportes (EMT) de Málaga.

**Flujo general del sistema:**

1. Los autobuses en circulación por la ciudad de Málaga transmiten su **localización en tiempo real** vía GPS.
2. Un **Sistema de Ayuda a la Explotación (SAE) + Ayuda a la decisión** procesa los datos.
3. Se muestra a los **gestores de línea** el estado de la flota, incidentes y recomendaciones de control.
4. Los gestores aprueban **acciones de control** que se envían por radio a los conductores.

**Funciones principales del centro de control:**

1. Control de horarios y frecuencias.
2. Comunicación con los conductores.
3. Gestión de incidencias.

---

### Arquitectura del sistema

Ejemplo para líneas 4, 12 y 17:

|Agente|Nombre completo|Rol|
|---|---|---|
|**DA**|Data Agent|Realiza la comunicación con la infraestructura (autobuses).|
|**AIA**|Action Implementation Agent|Envía mensajes a los conductores.|
|**UIA**|User Interface Agent|Comunicación con los operadores del centro de control.|
|**LMA**|Line Management Agent|Detección de problemas y generación de propuestas de acciones de control. Existe un LMA por línea (LMA4, LMA12, LMA17).|
|**CF**|Coordinator Facilitator|Agente de soporte a la coordinación cuando el problema es grave y requiere intercambio de autobuses entre líneas.|

**Flujo de información:**

- DA → LMAs (datos de flota)
- LMAs ↔ CF (coordinación)
- LMAs ↔ UIAs (información a operadores)
- AIA ← LMAs (acciones a ejecutar)

---

### Detección de Incidentes

Los **incidentes** son modificaciones de la calidad del servicio por algún motivo no previsto.

**Tipos de incidentes:**

- Retraso/adelanto individual (1 autobús).
- Retraso intralínea (varios autobuses de una línea).
- Retraso multilínea (retrasos simultáneos en varias líneas).
- Saturación de capacidad.
- Autobuses demasiado juntos (agrupamiento, _bunching_).
- Tráfico u obras.
- Averías.
- Etc.

---

### Propuesta de Acciones de Control

Las acciones de control **tratan de minimizar los efectos de los incidentes** y consisten en modificaciones del comportamiento de los autobuses.

**Tipos de acciones:**

- Saltar paradas (salvo para dejar pasajeros).
- Cambio de regulación por horario o frecuencia de paso.
- Adelantar al autobús siguiente.
- Adelantar la salida del autobús de cabecera.
- Esperar en la cabecera de línea.
- Introducir un autobús de refuerzo (se saca de la cochera).
- Mover un autobús de una línea a otra.
- Etc.

---

### Coordinación para mover un autobús entre líneas

Esta coordinación se activa en **problemas graves**, cuando se hace necesario intercambiar coches entre líneas.

**Modelo:**

- El decremento de la calidad de servicio se modela como un **coste**.
- **Objetivo:** Acordar intercambios entre los LMAs que reduzcan la suma de coste y cuyas cabeceras estén cercanas.

**Realización:** Varias rondas de negociación entre los LMAs facilitado por el **CF (Coordinator Facilitator)**, usando el protocolo **Contract Net**.

#### Protocolo de negociación

1. El **LMA solicitante** proporciona al CF una estimación del **coste reducido** si incorporara un autobús adicional.
2. El **CF** envía un _cfp (call for proposals)_ a los LMAs que comparten cabecera con el solicitante (distancia d1).
3. Los **LMAs receptores** estiman el **coste de perder un autobús**. Si el coste es **menor** del coste reducido propuesto, **aceptan** la propuesta.
4. Si **ningún LMA acepta**, se inicia **otra ronda** incrementando la distancia entre las cabeceras (d2, d3, …).

#### Ejemplo de ejecución (LMA1 solicita refuerzo)

**Ronda 1 (distancia d1):**

- CF envía cfp a los LMAs que comparten cabecera con LMA1 → solo **LMA2**.
- LMA2 **no acepta** (su coste de ceder un bus es mayor que el beneficio estimado por LMA1).

**Ronda 2 (distancia d2):**

- CF envía cfp a los LMAs a distancia d2 → **LMA3 y LMA4**.
- LMA3 y LMA4 **rechazan** la propuesta.

**Ronda 3 (distancia d3):**

- CF envía cfp a los LMAs a distancia d3 → **LMA5, LMA6 y LMA7**.
- LMA5 y LMA6 **rechazan** la propuesta.
- **LMA7 acepta** la propuesta.
- Finalmente, CF decide que sea la **línea 7 la que ceda el autobús** a la línea 1.

---

## Resumen de Conceptos Clave

|Concepto|Definición breve|
|---|---|
|**Sistema Cerrado**|Sistema multiagente con control global total y objetivos globales compartidos por todos los agentes.|
|**CDPS**|Cooperative Distributed Problem Solving. Marco para resolver problemas mediante descomposición, solución distribuida y composición de resultados.|
|**Agente Benevolente**|Agente que implícitamente comparte el objetivo global; simplifica el diseño del sistema.|
|**Contract Net**|Protocolo de compartición de tareas basado en licitación: anuncio → puja → concesión → ejecución.|
|**Coste Marginal**|Coste adicional de asumir nuevas tareas dadas las ya existentes: μᵢ(τ(s)\|τᵢᵗ) = cᵢ(τᵢᵗ ∪ τ(s)) − cᵢ(τᵢᵗ).|
|**Subasta de Bertsekas**|Algoritmo distribuido de relajación para el problema de asignación. Converge a la solución óptima si los costes son enteros y ε < 1/n.|
|**PDA**|Problem Detection Agent. Monitoriza un área y detecta problemas de tráfico.|
|**CA**|Control Agent. Propone señalizaciones y resuelve conflictos entre propuestas.|
|**LMA**|Line Management Agent. Gestiona una línea de autobuses: detecta incidentes y propone acciones.|
|**CF**|Coordinator Facilitator. Media en la coordinación entre LMAs cuando se requiere intercambio de recursos entre líneas.|

---
