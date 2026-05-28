## Índice

1. [[#8.1 Introducción]]
2. [[#8.2 Sociedades de Agentes]]
3. [[#8.3 Confianza y Reputación]]
4. [[#8.4 Un Modelo de Confianza y Reputación]]

---

## 8.1 Introducción

### Espectro de sistemas multiagente

Los sistemas multiagente se distribuyen en un espectro que va desde sistemas **completamente abiertos** hasta sistemas **completamente cerrados**, en función de dos dimensiones clave:

- **Eje de control:** desde _sin control global_ hasta _control global total_
- **Eje de objetivos:** desde _objetivos individuales_ hasta _objetivos globales_

|Tipo de sistema|Características|
|---|---|
|**Sociedades de agentes** (tráfico, P2P…)|Sin control global, objetivos individuales|
|**Equipos de agentes** (fútbol, supply chains…)|Control parcial, mezcla de objetivos|
|**Organizaciones de agentes** (sistemas empresariales…)|Autoridad global, objetivos compartidos|
|**Sistemas de componentes** (gestión, flotas…)|Control global total, objetivos globales|

> _"Co-ordination is a way of Adapting to the environment"_ — von Martial

### Conceptos clave de la coordinación en sistemas abiertos

- **Objetivos individuales de los agentes:** Cada agente está programado para perseguir sus propias metas en un entorno que puede ser cooperativo o competitivo.
- **Adaptación en entornos dinámicos:** Estrategias para que los agentes mejoren su desempeño y toma de decisiones en contextos que son parcialmente desconocidos y constantemente cambiantes.

---

## 8.2 Sociedades de Agentes

### Características de las sociedades de agentes

1. **Autonomía de los agentes:** No hay control global sobre los agentes. Cada agente opera de manera independiente dentro de la sociedad.
2. **Dinamismo del sistema:** Los agentes pueden entrar y salir libremente, lo que resulta en un número fluctuante de participantes en cualquier momento.
3. **Conocimiento social emergente:** El conocimiento social surge a través de las interacciones entre los agentes, por lo que cada agente tiene un conocimiento/entendimiento (alcance) parcial y propio de la sociedad.
4. **Estructuras sociales emergentes:** Las estructuras sociales emergen de manera descentralizada a partir de las interacciones locales (**enfoque bottom-up**).

### ¿Cómo puede un agente mejorar en un entorno cambiante y parcialmente desconocido?

- **Emergencia de estructuras organizativas que ayuden a (casi) todos:** Desarrollo de estructuras organizativas que emergen naturalmente y facilitan la consecución de objetivos colectivos, beneficiando a la mayoría de los agentes.
- **Estrategias de coordinación Bottom-Up:** Exploración de métodos para la auto-organización y adaptabilidad mediante la utilización de enfoques bottom-up, enfatizando la importancia de las interacciones locales entre agentes.
- **Formación de sociedades:** Los agentes forman una sociedad en la que no solo persiguen sus objetivos individuales, sino que también pueden interaccionar con otros agentes para mejorar su adaptabilidad y eficiencia.

### Gestión de la robustez y seguridad del sistema

- **Necesidad de control de robustez:** Es crucial monitorear y asegurar la robustez del sistema para prevenir fallos y asegurar la continuidad operativa.
- **Retos con agentes ineficientes:** Identificación y mejora de agentes que no cumplen con los estándares de eficiencia requeridos para mantener la funcionalidad óptima del sistema.
- **Manejo de agentes malignos:** Detección y mitigación de agentes con comportamientos perjudiciales o malintencionados que pueden comprometer la integridad y la seguridad del sistema.
- **Decisión y colaboración basada en confianza:** En ausencia de un control global, los agentes pueden elegir con quiénes interactuar basándose en la **confianza** y la **reputación** dentro de la sociedad, lo cual facilita la creación de un entorno más seguro y cooperativo.

---

## 8.3 Confianza y Reputación

### Motivación

En una sociedad de agentes, un agente A puede tener un objetivo que no puede lograr por sí mismo. Se enfrenta a una sociedad de agentes que ofrecen servicios y debe decidir: **¿Con quién hago la transacción?**

Los factores que entran en juego son: confianza + coste + riesgo + …

**Ejemplo (comercio electrónico):** Un agente cliente C1 quiere comprar un coche. Hay varios proveedores (P1, P2, P3, P4). C1 debe evaluar a cada proveedor según confianza, coste y riesgo, y tomar la decisión (e.g., comprar a P2).

### Proceso típico de interacción en sociedades de agentes

```
Planificación / Determinación de solicitar servicio a otros
        ↓
Búsqueda de posibles ofertas
        ↓
Selección de oferta  ← (¿Cómo elegimos la "mejor" oferta?)
        ↓
Negociación / Ejecución
```

Las interacciones en una sociedad de agentes son **intrínsecamente inseguras** porque:

- Falta de conocimiento sobre el comportamiento de otros agentes
- Otros agentes no necesariamente son benévolos
- Fiabilidad de las ofertas es incierta

Los conceptos de **confianza y reputación** permiten a un agente:

- Elegir el "mejor" agente con el que puede interactuar para una determinada interacción
- Ayudan a **predecir el comportamiento** de otros agentes en situaciones determinadas
- Permiten **estimar la satisfacción** que un agente recibirá si actúa con otros agentes

### Definiciones de Confianza y Reputación

#### Definición de Gambetta (1990)

> _"La confianza es la probabilidad subjetiva por la que un individuo A espera que otro individuo B realice una determinada acción de la que el bienestar de A depende."_

#### Definición de la RAE

- **Confianza:** 1. Esperanza firme que se tiene de alguien o algo. 2. Seguridad que alguien tiene en sí mismo.
- **Reputación:** 1. Opinión o consideración en que se tiene a alguien o algo. 2. Prestigio o estima en que son tenidos alguien o algo.

#### Distinción operativa (Confianza ≠ Reputación)

|Concepto|Definición|
|---|---|
|**Confianza**|Expectativa subjetiva de que un agente actuará de manera beneficiosa o al menos no perjudicial. Profundamente arraigada en las **experiencias directas** e información específica del contexto entre los agentes.|
|**Reputación**|Se forma a partir de las **percepciones compartidas** o el consenso general sobre las acciones pasadas de un agente, extendiéndose más allá de las interacciones personales para incluir información compartida por otros.|

#### Definición operativa general

- **Confianza:**
    
    - Es la **opinión subjetiva** que **un agente** tiene sobre la calidad de otro
    - Facilita a un agente determinar si otro actuará de forma correcta
    - Es un concepto amplio que puede incluir: la reputación, la satisfacción propia experimentada en experiencias pasadas, etc.
- **Reputación:**
    
    - Es la **opinión de la sociedad** en su conjunto respecto a la calidad de una cosa
    - Puede entenderse como la agrupación de las confianzas de los agentes
    - Es un factor que los agentes pueden usar para determinar la confianza

### Ambigüedad terminológica y sus consecuencias

**Diversidad de términos:** Trust, Reputation, Confidence, Reliability, Willingness…

**Consecuencias de la ambigüedad:**

- **Interpretaciones erróneas:** Agentes pueden confundir "reputación" con "confiabilidad", lo que puede no reflejar la alineación de intenciones entre agentes.
- **Decisiones basadas en supuestos incorrectos:** La confusión terminológica puede conducir a decisiones mal informadas, poniendo en riesgo la eficacia y seguridad del sistema.
- **Ejemplo concreto:** Un agente con "alta reputación" en transacciones financieras podría ser erróneamente considerado confiable para el intercambio de información sensible, llevando a vulnerabilidades inadvertidas.

**Soluciones:**

- Desarrollo de normativas y protocolos con definiciones claras
- Implementación en algoritmos de los sistemas multi-agente
- Capacitación y educación continua en precisión semántica
- Herramientas de validación semántica

### Ejemplos comerciales de sistemas de confianza

- **eBay:** Valoraciones numéricas (+1, 0, -1), comentarios textuales, visión global de la reputación (% votos positivos, puntuaciones por categorías como descripción, comunicación, envío, gastos).
- **TripAdvisor:** Opiniones, votaciones, rankings con valoraciones positivas y negativas segmentadas por perfil de viajero (familias, parejas, solitarios, negocios).

### Tipos de modelos de confianza

#### 1. Modelos Cualitativos y Cuantitativos

- **Cualitativos:** Utilizan descripciones basadas en atributos o categorías (bajo, medio, alto). Útiles donde la precisión matemática es menos crítica; permite evaluación más intuitiva y adaptable.
- **Cuantitativos:** Emplean métricas numéricas para definir y calcular la confianza, incluyendo algoritmos estadísticos o de aprendizaje automático para evaluar la probabilidad de comportamientos confiables basados en evidencias pasadas.

#### 2. Modelos Basados en Relaciones Sociales o Dependencias

- **Relaciones Sociales:** Evalúan la confianza basada en la dinámica de las interacciones y la historia de relaciones entre agentes. Importantes en redes donde la estructura social influye en la toma de decisiones.
- **Dependencias:** Consideran cómo la confianza en un agente depende de sus roles y responsabilidades dentro de un sistema, evaluando cómo estos roles afectan la percepción de confiabilidad.
#### 3. Modelos Basados en Reputación y/o Experiencia Propia
- **Reputación:** Incorporan evaluaciones basadas en las percepciones colectivas de las acciones pasadas de un agente, compiladas de múltiples fuentes dentro del sistema.
- **Experiencia Propia:** Se basan en las interacciones directas e individuales con otros agentes, proporcionando una medida de confianza ajustada a experiencias específicas del evaluador.
#### 4. Modelos de Nivel Físico
- **Seguridad de Infraestructura:** Mecanismos como autenticación y autorización, uso de certificados y credenciales para asegurar las transacciones y las comunicaciones entre agentes.
- Fundamental en contextos donde la verificación de la identidad y la autoridad del agente son cruciales para la seguridad y el cumplimiento normativo.

---

## 8.4 Un Modelo de Confianza y Reputación

> Modelo cuantitativo desarrollado por **Billhardt et al. (2007)**, inspirado en **Ramchurn et al. (2003)**.

### Idea general del modelo

**Notación base:**
- Sociedad de agentes: **A = {a₁, …, aₙ}**
- Interacciones posibles: **I = {i₁, …, iₘ}** (actividades/tareas realizadas entre varios agentes)
- Roles posibles: **R = {r₁, …, rₖ}** (papel que un agente asume en una interacción)

**Ejemplos:**
- Interacción: "Un vendedor vende un coche a un cliente", "Dos alumnos realizan una práctica"
- Roles: Vendedor, cliente, defensa, delantero, administrativo, profesor, cocinero…

Los agentes quieren encontrar **"agentes fiables"** para realizar interacciones con ellos.
### Concepto de Fiabilidad
**Fiabilidad:** Capacidad y previsibilidad con la que un agente cumple sus roles y responsabilidades dentro de una interacción específica.

**Características de un agente fiable:**
- **Consistencia:** Actúa de manera uniforme y predecible, cumpliendo con las expectativas basadas en interacciones previas.
- **Competencia:** Posee las habilidades y conocimientos necesarios para realizar el rol asignado eficazmente.
- **Honestidad:** Actúa de acuerdo con los principios éticos y no engaña ni manipula a otros agentes para beneficio propio.
- **Responsabilidad:** Asume la responsabilidad de sus acciones y sus resultados, y está dispuesto a rectificar en caso de errores o fallos.
**Importancia de la fiabilidad:**
- **Confianza Interpersonal:** La fiabilidad fortalece la confianza entre los participantes y es crucial para la formación de relaciones duraderas y efectivas.
- **Eficiencia del Sistema:** Agentes fiables mejoran la eficiencia de las operaciones y reducen los costos asociados con supervisión y corrección de errores.
- **Seguridad del Sistema:** Incrementa la seguridad al asegurar que cada agente cumpla con sus deberes, reduciendo el riesgo de fallas y vulnerabilidades.

### Contexto y combinación de confianza

**La confianza depende de la situación/contexto:**

- `cₓ(<aᵢ, rⱼ, iₚ>)` representa la estimación de la satisfacción del agente _x_ respecto a la **situación** `<aᵢ, rⱼ, iₚ>`: la "calidad" del agente _aᵢ_ jugando el rol _rⱼ_ en la interacción _iₚ_.

**La confianza combina experiencias individuales y reputación:**

$$\text{Confianza} = \text{Experiencia} \otimes \text{Reputación}$$

- **Experiencia:** `eₓ(<aᵢ, rⱼ, iₚ>)` — experiencia acumulada de _x_ con respecto al comportamiento de _aᵢ_ en situaciones pasadas del tipo `<aᵢ, rⱼ, iₚ>`.
- **Reputación:** `r_RA(<aᵢ, rⱼ, iₚ>)` — agregación de la opinión de otros agentes (su experiencia) con respecto al comportamiento de _aᵢ_ en situaciones pasadas del tipo `<aᵢ, rⱼ, iₚ>`.

### Proceso de decisión: Uso de la confianza

_"Agente **a** busca otro agente que debe jugar un rol **rⱼ** en una interacción **iₚ**"_

**Pasos del proceso:**

1. Buscar posibles candidatos `{x₁, …, xₙ} ⊆ A` de agentes que puedan jugar el rol _rᵢ_ en interacción _iₚ_
2. Para cada agente _xᵢ_ calcular la confianza `cₐ(<xᵢ, rⱼ, iₚ>)`
3. Negociar y realizar la interacción con el agente _xᵢ_ con **mayor valor de confianza**
4. Evaluar la satisfacción de la interacción respecto al agente elegido: `gₐ(<xᵢ, rⱼ, iₚ>)`
5. Actualizar la experiencia propia respecto a la situación `<xᵢ, rⱼ, iₚ>`

---

### Tabla Local de Interacciones (LIT)

Cada agente _a_ mantiene una **tabla local de interacciones (LIT)** que:

- Recopila su experiencia respecto al comportamiento de otros agentes en interacciones pasadas
- Está indexada por claves del tipo **agente/rol/interacción** (`<X, Y, Z>`): agente X jugando el papel Y en la interacción Z

|Agente/Rol/Interacción|Experiencia `eₐ(<X,Y,Z>)`|Fiabilidad `fₐ(<X,Y,Z>)`|
|---|---|---|
|`<x₁, r₃, i₂>`|0.5|0.3|
|…|…|…|
|`<x₉, r₂, i₅>`|0.8|0.7|

Cada registro tiene un **valor de experiencia** y uno de **fiabilidad**.

#### Experiencia `eₐ(<xᵢ, rⱼ, iₚ>)`

- Valor en el intervalo **[0..1]**
- Mide la **satisfacción acumulada** que el agente _a_ ha experimentado respecto a la situación `<xᵢ, rⱼ, iₚ>` (agente _xᵢ_ realizando el rol _rⱼ_ en la interacción _iₚ_)
- Valor **acumulado** de la satisfacción sobre todas las instancias (experiencias) pasadas
- Valores altos → mayor satisfacción

#### Fiabilidad `fₐ(<xᵢ, rⱼ, iₚ>)`

- Valor en el intervalo **[0..1]**
- Mide **cómo de seguro** está el agente _a_ acerca de su propio valor de experiencia
- Valores altos → mayor fiabilidad

#### Ejemplo de LIT (Práctica de IA)

_"Un estudiante **a** necesita encontrar un compañero (Estudiante-Rol) para realizar una práctica de IA (Interacción)"_

| Agente/Rol/Interacción            | Experiencia | Fiabilidad |
| --------------------------------- | ----------- | ---------- |
| `<Pepe, estudiante, practica IA>` | 0.6         | 0.7        |
| `<Juan, estudiante, practica IA>` | 0.9         | 0.1        |
| `<Rosa, estudiante, practica IA>` | 0.8         | 0.8        |
| `<Pepe, delantero, partido>`      | 0.5         | 0.3        |

→ _a_ elegiría a Juan (mayor experiencia = 0.9), pero su fiabilidad es muy baja (0.1), lo que plantea el problema de cómo tratar la fiabilidad reducida.

**Problemas identificados:**

1. ¿Cómo tratar una **fiabilidad reducida** de las propias estimaciones? (Juan tiene experiencia 0.9 pero fiabilidad 0.1)
2. ¿Cómo decidir si el agente **no tiene experiencias pasadas** sobre una determinada situación? → Idea: **combinar experiencia local con reputación**

---

### Cálculo de la Reputación

**Reputación:** valoración de una situación por "la sociedad".

$$r_{a_RA}(<x_i, r_j, i_p>) = \frac{\sum_{b \in RA} e_b(<x_i, r_j, i_p>) \cdot f_b(<x_i, r_j, i_p>)}{\sum_{b \in RA} f_b(<x_i, r_j, i_p>)}$$

Donde **RA** es el **conjunto de agentes de recomendación**, que puede ser:

- Todos los agentes que conoce _a_
- Un grupo de agentes en los que _a_ "confía" como "recomendador" en la interacción "recomendar valores de satisfacción"
- El agente puede usar su propia LIT para saber a quién preguntar por sus opiniones

---

### Cálculo de la Confianza (combinando experiencia y reputación)

**Proceso completo para calcular `cₐ(<xᵢ, rⱼ, iₚ>)`:**

1. Determinar experiencia `eₐ(<xᵢ, rⱼ, iₚ>)` y fiabilidad `fₐ(<xᵢ, rⱼ, iₚ>)`
2. Determinar un conjunto de agentes recomendadores **RA**
3. Pedir a los recomendadores sus estimaciones y calcular la reputación:

$$r_{a_RA}(<x_i, r_j, i_p>) = \frac{\sum_{b \in RA} e_b(<x_i, r_j, i_p>) \cdot f_b(<x_i, r_j, i_p>)}{\sum_{b \in RA} f_b(<x_i, r_j, i_p>)}$$

4. Calcular la confianza:

$$c_a(<x_i, r_j, i_p>) = f_a(<x_i, r_j, i_p>) \cdot e_a(<x_i, r_j, i_p>) + (1 - f_a(<x_i, r_j, i_p>)) \cdot r_{a_RA}(<x_i, r_j, i_p>)$$

> **Interpretación:** La confianza se basa en **primer lugar** en la experiencia propia y, como **complemento**, en la reputación (ponderada por la fiabilidad).

> _Hay otras posibles formas de combinar experiencia local y reputación._

#### Ejemplo numérico de cálculo de confianza

Dados los siguientes datos (agente **a** y conjunto de recomendadores RA = {b₁, b₂, b₃, b₄}):

|                              | Agente a        | b₁  | b₂  | b₃  | b₄  |
| ---------------------------- | --------------- | --- | --- | --- | --- |
| Experiencia `eₓ(<xᵢ,rⱼ,iₚ>)` | 0.8             | 0.1 | 0.3 | 0.1 | 0.2 |
| Fiabilidad `fₓ(<xᵢ,rⱼ,iₚ>)`  | 0.9 / 0.5 / 0.1 | 0.2 | 0.1 | 0.3 | 0.8 |

**Reputación:** $$r_{a_RA} = \frac{(0.1 \cdot 0.2) + (0.3 \cdot 0.1) + (0.1 \cdot 0.3) + (0.2 \cdot 0.8)}{0.2 + 0.1 + 0.3 + 0.8} = 0.17$$

**Confianza** (según la fiabilidad del agente a = 0.9 / 0.5 / 0.1):

- Fiabilidad **alta** (0.9): `cₐ = 0.9 * 0.8 + 0.1 * 0.17 = 0.74`
- Fiabilidad **media** (0.5): `cₐ = 0.5 * 0.8 + 0.5 * 0.17 = 0.48`
- Fiabilidad **baja** (0.1): `cₐ = 0.1 * 0.8 + 0.9 * 0.17 = 0.23`

---

### Actualización de la Experiencia Propia (LIT)

Cada vez que el agente _a_ experimenta la situación `<xᵢ, rⱼ, iₚ>`, actualiza los valores de experiencia y fiabilidad.

#### Actualización de la Experiencia `eₐ(<xᵢ, rⱼ, iₚ>)`

Después de realizar la interacción, el agente evalúa la **satisfacción percibida** `gₐ(<xᵢ, rⱼ, iₚ>)` y actualiza:

$$e_a(<x_i, r_j, i_p>) := (1 - \alpha) \cdot e_a(<x_i, r_j, i_p>) + \alpha \cdot g_a(<x_i, r_j, i_p>)$$

Donde:

- **α** es una constante que determina la importancia de la experiencia de instancias pasadas respecto a la nueva instancia
- **Si es la primera experiencia:** `eₐ(<xᵢ, rⱼ, iₚ>) := gₐ(<xᵢ, rⱼ, iₚ>)`
- **No es una media:** Esta fórmula permite **"olvidar" valores antiguos** → permite adaptarse mejor si la calidad del agente evoluciona

**Comportamiento según el valor de α:**

- **α pequeño (0.1):** Reacciona lentamente a los cambios (más estable)
- **α grande (0.5):** Reacciona rápidamente a los cambios (más sensible a variaciones recientes)

#### Actualización de la Fiabilidad `fₐ(<xᵢ, rⱼ, iₚ>)`

La fiabilidad depende de **dos factores principales:**

**1. Número de experiencias (fₙ):**

$$f_n = \begin{cases} 1 & \text{si } N > \phi \ \frac{N}{\phi} & \text{en otro caso} \end{cases}$$

- **φ** — umbral que determina cuándo se considera que hay suficientes experiencias para asegurar fiabilidad
- **N** — número de experiencias en las que se basa el valor `eₐ(<xᵢ, rⱼ, iₚ>)`

**2. Desviación/Variabilidad de los valores de experiencia (fₐ):**

$$f_d = 1 - \frac{1}{N} \sum_{k=1}^{N} \left| g_a^k(<x_i, r_j, i_p>) - e_a^k(<x_i, r_j, i_p>) \right|$$

Donde:

- `gₐᵏ(<xᵢ, rⱼ, iₚ>)` — evaluación real de la satisfacción del agente en la instancia _k_
- `eₐᵏ(<xᵢ, rⱼ, iₚ>)` — estimación previa de la satisfacción del agente en la instancia _k_

Cuando el comportamiento del agente es **consistente**, `fₐ` tiende a 1 (alta fiabilidad). Cuando hay cambios bruscos, `fₐ` baja inicialmente y sube gradualmente a medida que la nueva conducta se estabiliza.

**Combinación de ambos factores:**

$$f_a(<x_i, r_j, i_p>) = f_n \cdot f_d$$

---

### Ejemplo completo del modelo

_"Un agente **a** busca otro agente que le puede vender un coche (rol V = Vendedor; interacción c = vender coche)"_

**Datos del agente a (LIT):**

|Situación|Experiencia|Fiabilidad|
|---|---|---|
|`<p₁, V, c>`|0.8|0.5|
|`<p₂, V, c>`|0.3|0.8|
|`<p₁, D, f>`|…|…|

**Recomendadores r₁ y r₂:**

|Situación|`eᵣ₁`|`fᵣ₁`|
|---|---|---|
|`<p₁, V, c>`|0.6|0.9|
|`<p₂, V, c>`|0.8|0.6|
|`<p₃, V, c>`|0.8|0.7|

|Situación|`eᵣ₂`|`fᵣ₂`|
|---|---|---|
|`<p₂, V, c>`|0.9|0.8|
|`<p₃, V, c>`|0.9|0.6|

**Cálculo de confianzas:**

- `cₐ(<p₁, V, c>) = 0.5 * 0.8 + 0.5 * (0.6*0.9)/0.9 = 0.70`
- `cₐ(<p₂, V, c>) = 0.8 * 0.3 + 0.2 * (0.8*0.6 + 0.9*0.8)/(0.6+0.8) = 0.8*0.3 + 0.2*0.857 = 0.41`
- `cₐ(<p₃, V, c>) = 0 * … + 1 * (0.8*0.7 + 0.9*0.6)/(0.7+0.6) = 0 + 1*0.846 = 0.85`

→ El agente **a** elige a **p₃** (mayor confianza = 0.85) y realiza la interacción.

**Evaluación y actualización de la LIT** (suponiendo α = 0.2, φ = 10):

- `gₐ(<p₃, V, c>) = 0.9` (satisfacción obtenida)
- `fn = 1/10 = 0.1` (primera experiencia, N=1)
- `fd = 1 – (1/1) * |0.9 – 0.85| = 0.95`
- `eₐ(<p₃, V, c>) = 0.9` (experiencia nueva, primera vez)
- `fₐ(<p₃, V, c>) = fn * fd = 0.1 * 0.95 = 0.095`

LIT actualizada:

|Situación|Experiencia|Fiabilidad|
|---|---|---|
|`<p₁, V, c>`|0.8|0.5|
|`<p₂, V, c>`|0.3|0.8|
|`<p₁, D, f>`|…|…|
|**`<p₃, V, c>`**|**0.9**|**0.095**|

---

### Inferencia de la Confianza

#### Problema

¿Cómo seleccionar un agente si no tengo ninguna experiencia previa con él?

**Situaciones donde ocurre:**

- Para nuevos agentes
- En entornos abiertos muy grandes o con interacciones poco frecuentes

**Posible solución: usar solo la reputación.** Pero surgen nuevos problemas:

- ¿Si no conozco otros agentes?
- ¿Si otros agentes no me dicen la verdad?

**Solución propuesta:** → **Inferir el comportamiento esperado a partir de experiencias con situaciones similares**

#### Hipótesis e Idea

- **Hipótesis:** Los agentes se comportan de forma similar en interacciones similares
- **Idea:** Estimar la confianza en base a experiencias pasadas en interacciones similares con los mismos agentes

**Efectos:**

- Es posible evaluar pares `<agente, rol, interacción>` incluso si no se dispone de experiencias pasadas
- **Modelo de inferencia vs. "modelo básico":** Mejor rendimiento al principio del ciclo de vida de los agentes
- **Modelo de inferencia vs. "reputación":** No dependencia de otros (posiblemente maliciosos) agentes

#### Fórmula de inferencia de confianza

El agente _x_ quiere estimar la confianza en la situación `<aᵢ, rⱼ, iₚ>`:

$$c_x(<a_i, r_j, i_p>) = \frac{\sum_{<a,r,i> \in LIT_x} e_x(<a,r,i>) \cdot f_x(<a,r,i>) \cdot sim(<a,r,i>, <a_i, r_j, i_p>)}{\sum_{<a,r,i> \in LIT_x} f_x(<a,r,i>) \cdot sim(<a,r,i>, <a_i, r_j, i_p>)}$$

Es decir: **media ponderada de la experiencia para todas las situaciones**, ponderada por la fiabilidad y similitud.

#### Cálculo de la similitud

$$sim(<a, r, i>, <a_i, r_j, i_p>) = \begin{cases} sim(i, i_p) & \text{si } a = a_i \text{ y } r = r_j \ 0 & \text{en otro caso} \end{cases}$$

**En este caso:** La similitud solo existe para los mismos agentes jugando el mismo rol en interacciones diferentes. Se podrían considerar también similitudes entre roles y/o agentes.

#### Similitud de interacciones mediante taxonomías

Muchas actividades/interacciones tienen similitudes "naturales":

- Jugar fútbol / jugar baloncesto
- Cocinar / hornear
- etc.

Esas relaciones se pueden definir mediante **taxonomías**. La similitud entre interacciones se calcula basándose en la taxonomía:

$$sim(i, i_p) = \frac{h(i, i_p)}{h_{max}}$$

Donde:

- `h(i, iₚ)` — número de saltos entre conceptos de la taxonomía
- `h_max` — máximo número de saltos entre dos conceptos

**Ejemplo de taxonomía:**

```
Travel service
├── Hotel service
│   ├── Hotel search
│   └── Hotel res.
└── Car service
    └── Car rental
```

`Sim(Hotel search, Hotel reservation) = 0.5`

#### Resultados de simulación

**Escenario de simulación de turismo:**

- 20 agentes en rol de proveedor (12 servicios de transporte)
- 20 agentes en rol de cliente
- 40.000 peticiones de servicio (generadas y asignadas aleatoriamente)

**Proceso:**

- Un cliente C recibe un objetivo (solicitar un servicio particular S)
- C usa confianza para seleccionar un agente A que actúe como proveedor (P) del servicio S
- La ejecución es simulada y `g<A,P,S>` se envía a C

**Generación del comportamiento de los proveedores:**

- Distribución de probabilidad normal con parámetros μ ∈ [0..1] y varianza σ² ∈ [0..0.25] asignada a cada par `<A, P, S>`
- Pares `<A, P, S>` similares tienen distribuciones de probabilidad similares

**Modelos comparados:**

- **Modelo básico:** Confianza solo basada en la experiencia (sin reputación)
- **Modelo de inferencia:** Confianza basada en experiencia con cálculo de similitud

**Resultado:** El modelo de inferencia obtiene mayor satisfacción media percibida, especialmente en las primeras interacciones (arranque más alto), convergiendo a valores similares al modelo básico a largo plazo.

#### Comentarios adicionales sobre inferencia

- **Explotación vs. exploración:** ¿Cómo descubrir nuevos mejores agentes? Diferentes posibles políticas de selección: _greedy_, _ε-greedy_, ruleta…
- El modelo de inferencia **se puede extender** con información de reputación
- El modelo de inferencia permite diferentes estimaciones de similitud:
    - Agentes jugando **diferentes roles** en las mismas interacciones
    - **Agentes similares** jugando el mismo rol en las mismas interacciones

#### Generalización de la confianza desde la LIT

La estructura de los valores de experiencia `eₓ(<aᵢ, rⱼ, iₚ>)` puede usarse para estimar la confianza de diferentes elementos (calculando la media sobre los diferentes valores de la LIT):

- **Confianza en un agente:** `cₓ(<a, _, _>)` — confianza del agente _x_ en el agente _a_ en general
- **Confianza en un rol:** `cₓ(<_, r, _>)` — confianza de _x_ en el rol _r_ (sobre todos los que juegan ese rol)
- **Confianza en un grupo de agentes:** `cₓ(<{a,…}, _, _>)` — confianza general de _x_ en el grupo de agentes `{a,…}`

---

## Referencias bibliográficas

- **[Billhardt et al., 2007]** Billhardt, H., Hermoso, R., Ossowski, S., and Centeno, R. _"Trust-based service provider selection in open environments."_ In Proceedings of the 2007 ACM Symposium on Applied Computing, pp. 1375-1380.
- **[Ramchurn et al., 2003]** Ramchurn, S., Sierra, C., Godó, L., & Jennings, N. R. _"A computational trust model for multi-agent interactions based on confidence and reputation."_ In Proceedings of 6th International Workshop of Deception, Fraud and Trust in Agent Societies, pp. 69–75.
- **[Braga et al., 2018]** Braga, D. D. S., Niemann, M., Hellingrath, B., & Neto, F. B. D. L. _"Survey on computational trust and reputation models."_ ACM Computing Surveys (CSUR), 51(5), 1-40.
- **[Gambetta, 1990]** Gambetta, D. _Trust: Making and Breaking Cooperative Relations_, Chapter "Can We Trust Trust?", pp. 213–237. Basil Blackwell, Oxford.

---
