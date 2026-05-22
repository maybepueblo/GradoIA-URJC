## Índice del Tema

1. [[#6.1 Introducción]]
2. [[#6.2 Lenguajes de Comunicación entre Agentes]]
3. [[#6.3 Compartición de tareas y compartición de resultados]]
4. [[#6.4 Construcción de vocabularios (ontologías)]]
5. [[#6.5 Aplicaciones de Comunicación entre agentes]]

---

## 6.1 Introducción

### Habilidad social, comunicación y cooperación

La **habilidad social** en los agentes es la capacidad de interactuar con otros agentes (y posiblemente humanos) a través de algún tipo de lenguaje de comunicación de agentes, y quizás cooperar con otros.

### ¿Por qué es importante la comunicación?

- La comunicación es un **requisito para la cooperación**.
- Las sociedades pueden hacer cosas que ningún individuo puede hacer solo. Algunos objetivos requieren cooperación.
- La **diversidad** introduce heterogeneidad.
- La **autonomía** fomenta el desinterés por la estructura interna de otros agentes.

### Lenguaje común

Los agentes que se comunican necesitan entender un "lenguaje común":

- Comprensión de su vocabulario.
- Saber cómo usar efectivamente el vocabulario para realizar tareas y alcanzar objetivos.

### Analogía práctica

Los agentes de IA dependen de lenguajes y protocolos específicos para interactuar. Sin estas estructuras precisas, los agentes de IA serían como turistas perdidos en un país extranjero sin traductor.

Si dos agentes necesitan comunicarse, deben estar de acuerdo en la terminología que utilizan para describir el dominio de aplicación. Por ejemplo: qué es una farola, qué es un consumo, qué unidades de medida se usarán para comunicar el consumo, qué es Madrid, qué significa "hay"...

### Por qué la comunicación es clave para la colaboración

Lo que hace poderosos a los agentes de IA no es solo su capacidad para tomar decisiones, sino cómo comunican esas decisiones a otros. El protocolo adecuado significa que las tareas se ejecutan sin contratiempos, mientras que un error puede desbaratarlo todo.

Sin protocolos de comunicación adecuados, estos agentes operarían en burbujas aisladas, perdiendo completamente el punto de los sistemas inteligentes. Necesitan coordinarse, colaborar y transmitir datos complejos con rapidez y precisión.

Las **ontologías** proporcionan especificaciones de un conjunto de términos (conceptos) y relaciones entre ellos (propiedades).

### Formas de comunicación

- La forma más habitual es mediante **envío de mensajes**: un agente envía un mensaje a uno o varios agentes.
- **No es lo mismo** que invocar un método en Orientación a Objetos o solicitar una página web a un servidor. Los agentes son autónomos y, por tanto, son libres de usar el contenido del mensaje como deseen.
- También existe la forma de comunicación basada en **estructuras compartidas** (p.e. pizarras).

---

## 6.2 Lenguajes de Comunicación entre Agentes

### Importancia de un Lenguaje Común en Sistemas Multi-Agente

Un lenguaje común facilita la integración, mejora la flexibilidad y elimina dependencias rígidas, permitiendo sistemas distribuidos más eficientes y escalables.

#### Modularidad y Escalabilidad

- Permite añadir nuevos agentes sin modificar la arquitectura del sistema.
- Facilita la expansión del sistema sin reconfiguración compleja.

#### Elimina Enlaces Explícitos

- No requiere que los agentes conozcan a otros previamente.
- Comunicación dinámica basada en anuncios y descubrimiento.

#### Independencia de OOP (programación orientada a objetos)

- No necesita referencias directas a otros agentes.
- Basado en protocolos estándar en lugar de dependencias rígidas, promoviendo interoperabilidad.

#### Interoperabilidad y Estándares de Comunicación

- Compatible con múltiples plataformas y tecnologías.
- Uso de lenguajes como **JSON** y **XML** (estructuración de datos), **FIPA ACL** (Agent Communication Language, definido por la Foundation for Intelligent Physical Agents), **KQML** (Knowledge Query and Manipulation Language, para el intercambio de conocimiento).
- **Ejemplo IoT:** Dispositivos nuevos modelados como agentes se integran automáticamente mediante **MQTT/CoAP**.
    - MQTT (Message Queuing Telemetry Transport): protocolo de mensajería ligero y abierto, basado en un modelo de publicación/suscripción, ideal para conectar dispositivos con recursos limitados (IoT) o de máquina a máquina (M2M).

---

### Componentes de un Mensaje en un Lenguaje de Comunicación entre Agentes

Los lenguajes de comunicación entre agentes definen la estructura y semántica de los mensajes intercambiados, permitiendo la interacción efectiva en sistemas multi-agente.

|Componente|Descripción|
|---|---|
|**Emisor**|Agente que genera y envía el mensaje|
|**Receptor**|Agente destinatario del mensaje|
|**Contenido del mensaje**|Información o acción que el mensaje transmite|
|**Formato**|Forma en que se representa el contenido (ej. JSON, XML, RDF)|
|**Ontologías**|Conjunto de términos y relaciones para estructurar y dar significado al contenido|
|**Protocolo de interacción**|Conjunto de reglas que definen cómo los agentes intercambian mensajes (ej. solicitud-respuesta, negociación, subasta)|
|**Otros metadatos**|Información adicional como identificadores de conversación o niveles de prioridad|

> Los lenguajes más destacados son **KQML** y **FIPA ACL**.

---

### Lenguajes concretos

- **KQML (Knowledge Query and Manipulation Language):** Facilita la compartición de conocimiento entre agentes. Diseñado para el intercambio de información estructurada, ideal para la colaboración entre agentes que manejan tareas complejas.
- **FIPA ACL (Foundation for Intelligent Physical Agents - Agent Communication Language):** Estándar de la industria para la comunicación de agentes. Define una gama de tipos de mensajes y protocolos para asegurar que agentes de diferentes sistemas puedan comunicarse sin problemas de compatibilidad.
- **OWL (Web Ontology Language):** Permite a los agentes razonar sobre la información compartida, utilizando estructuras semánticas. Perfecto para agentes que necesitan compartir, procesar y entender modelos de conocimiento complejos.
- **JSON-RPC / XML-RPC:** Protocolos de comunicación ligeros que utilizan JSON o XML para habilitar llamadas a procedimientos remotos, útiles para interacciones simples y rápidas entre agentes y sistemas externos.

---

### FIPA ACL (Agent Communication Language)

Un mensaje en FIPA ACL es una unidad de comunicación que sigue una estructura bien definida, compuesta por un conjunto de parámetros (muchos opcionales). Estos parámetros permiten que los agentes comprendan el propósito, contenido y contexto de la comunicación.

#### Parámetros de un mensaje FIPA ACL

|Parámetro|Descripción|
|---|---|
|`performative`|Acto comunicativo (ej. Inform, request, query-if). Define la intención del mensaje|
|`sender`|Emisor|
|`receiver`|Receptor|
|`content`|Contenido del mensaje (ej. hechos, consultas, acciones, etc.)|
|`language`|Lenguaje en el que se expresa el contenido (p.e. RDF, prolog)|
|`encoding`|Codificación del contenido (p.e. XML, JSON)|
|`ontology`|Ontología(s) utilizadas en el contenido|
|`protocol`|Protocolo de interacción en el que se usa el mensaje (ej. Negociación, subasta, solicitud-respuesta)|
|`conversation-id`|Identificador único que permite rastrear el hilo de la conversación|
|`reply-with`|Valor que el receptor puede usar en la respuesta para referirse al mensaje específico|

**Ejemplo de mensaje FIPA ACL:**

```
(inform
  :sender Agente1
  :receiver Agente2
  :content "iluminacion(plazaMayor,on)"
  :language prolog
)
```

---

### FIPA ACL – Actos de habla (performative)

#### Fundamento teórico

La **teoría de los actos de habla** [Austin, 1962; Searle, 1969] estudia cómo los humanos usan el lenguaje para expresar sus intenciones y lograr objetivos.

- La comunicación se modela como **acciones que modifican el estado mental** de los participantes.
- Ciertas expresiones (actos de habla) no solo transmiten información sino que tienen características de acciones que cambian el estado del mundo de forma análoga a las acciones físicas.
- Ejemplo: Un agente que envía un mensaje de "información" está modificando el conocimiento del agente receptor. Un mensaje de "petición" no solo transmite palabras, sino que genera una acción en el agente destinatario.

#### Componentes de un acto comunicativo

1. Un **verbo performativo (Performative)** que indica la intención. Ejemplos: `inform`, `request`, `confirm`, `query-if`, `agree`, `refuse` — informar, pedir, confirmar, preguntar...
2. El **contenido proposicional del acto (Propositional Content)**: representa la información transmitida o la acción deseada. P.e. "La iluminación de la Plaza mayor está encendida".

#### Catálogo de actos comunicativos FIPA ACL

FIPA ACL define un catálogo con especificación formal de semántica:

|Acto Comunicativo|Notación Formal|Descripción|
|---|---|---|
|`inform`|`<i, inform (j, h)>`|El agente i informa al agente j que h es cierto. Intención: i intenta que j crea que h es cierto (aunque j decidirá si lo acepta o no)|
|`request`|`<i, request (j, a)>`|El agente i solicita al agente j que realice la acción a|
|`query-if`|`<i, query-if (j, h)>`|El agente i pregunta al agente j si h es cierto|
|`agree`|`<i, agree (j, a)>`|El agente i comunica al agente j que acepta realizar la acción a|
|`confirm`|`<i, confirm (j, h)>`|El agente i confirma a j que h es cierto, asumiendo que j ya tenía dudas al respecto|
|`cfp` (Call for Proposal)|`<i, cfp (j, a)>`|El agente i solicita propuestas a j para una posible acción o acuerdo|
|`not-understood`|`<i, not-understood (j, h)>`|El agente i comunica al agente j que no ha entendido el mensaje h|
|`reject`|`<i, reject (j, a)>`|El agente i comunica al agente j que rechaza realizar la acción a|
|`request-when`|`<i, request-when (j, a, h)>`|El agente i solicita a j que realice a cuando h se cumpla|
|`subscribe`|`<i, subscribe (j, h)>`|El agente i solicita a j que le informe cada vez que cambie el valor de h|

**Ejemplo aplicado** con `h = iluminacion(plazaMayor, on)`:

- `Inform`: "La iluminación de la Plaza Mayor está encendida."
- `Request`: "Enciende la iluminación de la Plaza Mayor!"
- `Query-if`: "¿Está encendida la iluminación de la Plaza Mayor?"

---

### FIPA ACL – Protocolos (protocol)

La comunicación entre agentes normalmente está estructurada en **patrones de interacción (protocolos)**. Los protocolos dictan cómo se utilizan los lenguajes.

#### Control de la conversación en FIPA ACL

Se realiza mediante parámetros clave: `protocol`, `conversation-id`, `reply-with`, `in-reply-to`, `reply-by`.

#### Protocolos definidos por FIPA

|Protocolo|Descripción|
|---|---|
|**Request**|Un agente solicita a otro la ejecución de una acción específica|
|**Query**|Un agente consulta información a otro (ej. query-if, query-ref)|
|**Request When**|Un agente solicita a otro que realice una acción cuando se cumpla una condición|
|**Contract Net**|Un agente busca colaboradores enviando solicitudes de propuestas y selecciona la mejor respuesta|
|**Iterative Contract Net**|Variante del Contract Net que permite negociaciones iterativas antes de aceptar una propuesta|
|**English Auction**|Subasta en la que los participantes realizan ofertas cada vez más altas hasta que no haya nuevas pujas|
|**Dutch Auction**|Subasta donde el precio comienza alto y disminuye progresivamente hasta que alguien acepta la oferta|
|**Brokering**|Un agente intermedio actúa como mediador, asignando tareas a otros agentes|
|**Recruiting**|Similar al brokering, pero el agente mediador busca activamente colaboradores adecuados|
|**Subscribe**|Un agente solicita ser notificado cuando cierta información cambie en el sistema|
|**Propose**|Un agente propone una acción a otro, quien puede aceptarla o rechazarla|

#### Ejemplo: Protocolo FIPA Request (`fipa-request`)

- El agente **iniciador** solicita al agente **participante** la realización de una acción.
- La solicitud es **aceptada** (`agree`) o **rechazada** (`refuse`) por el participante.
- Si es aceptada, el participante comunicará al iniciador:
    - `failure`: si hay un problema al ejecutar la acción.
    - `inform-done`: si la acción se completó correctamente.
    - `inform-result`: si desea notificar que la acción se ejecutó y los resultados de la ejecución.

#### Ejemplo de intercambio completo (protocolo Query)

```
( query-if
  :sender Agente1
  :receiver Agente2
  :content "(estado Sensor1)"
  :language Prolog
  :ontology Sensores
  :protocol Query
  :conversation-id "conv123"
  :reply-with "msg456"
)
```

```
( inform
  :sender Agente2
  :receiver Agente1
  :content "(estado Sensor1 activo)"
  :language Prolog
  :ontology Sensores
  :protocol Query
  :conversation-id "conv123"
  :in-reply-to "msg456"
)
```

---

## 6.3 Compartición de tareas y compartición de resultados

### Colaboración y cooperación

**¿Por qué y cómo trabajan juntos los agentes?** Es importante hacer una distinción entre:

- **Agentes benevolentes:** Diseñados para actuar en interés de los usuarios o del sistema en general, sin buscar beneficios personales. Su objetivo principal es contribuir al bien común y facilitar la cooperación y coordinación entre otros agentes para alcanzar metas compartidas.
- **Agentes con intereses propios o estratégicos:** Programados para maximizar sus propios beneficios o cumplir objetivos específicos que pueden no alinearse necesariamente con los intereses de otros agentes o del sistema en general. A menudo, requieren mecanismos de negociación y acuerdos para cooperar con otros.

### Agentes benévolos

- Si "poseemos" todo el sistema, podemos diseñar agentes para que se ayuden mutuamente cuando se les solicite.
- En este caso, podemos asumir que los agentes son benevolentes: **nuestro mejor interés es su mejor interés**.
- La resolución de problemas en sistemas benevolentes se denomina **Resolución de Problemas Distribuidos Cooperativos (CDPS**, por sus siglas en inglés).
- ¡La benevolencia **simplifica enormemente** la tarea de diseño del sistema!

### Agentes con intereses propios

- Si los agentes representan a individuos u organizaciones (el caso más general), entonces **no podemos hacer la suposición de benevolencia**.
- Se asumirá que los agentes actuarán para promover sus propios intereses, posiblemente a expensas de otros.
- Esto genera un **potencial para conflictos**.
- Puede **complicar enormemente** la tarea de diseño.

### Dos modos principales de resolución cooperativa de problemas

1. **Compartir tareas:** Los componentes de una tarea se distribuyen entre los agentes componentes.
2. **Compartir resultados:** La información (resultados parciales, etc.) se distribuye.

---

### Resolución de Problemas Distribuidos Cooperativos (CDPS)

- No hay ni control global ni almacenamiento global de datos.
- Ningún agente tiene información suficiente para resolver el problema entero.
- El control y los datos están **distribuidos**.

#### Características del Sistema y Consecuencias

- La comunicación es **más lenta que la computación**.
- Acoplamiento débil.
- Protocolo eficiente.
- Problemas modulares.
- Problemas con tamaño de grano grande.
- **Cualquier nodo único es un cuello de botella potencial** → necesidad de distribuir datos y control.
- Es difícil garantizar un comportamiento organizado (ya que ningún nodo tiene una visión completa).

---

### Las 4 fases de la compartición de tareas (Contract Net)

El Contract Net protocolo se ocupa de la **fase 2**:

1. **Descomposición del Problema**
2. **Distribución del Subproblema** ← _Contract Net_
3. **Solución del Subproblema**
4. **Síntesis de la Respuesta**

---

### Contract Net

Un enfoque para la **resolución de problemas distribuidos, enfocado en la distribución de tareas**.

- La distribución de tareas se ve como una especie de **negociación de contratos**.
- El "protocolo" especifica el **contenido** de la comunicación, no solo la forma.
- La transferencia **bidireccional** de información es una extensión natural de los mecanismos de transferencia de control.

#### Funcionamiento de la red de contratos

- Cada nodo en la red puede, en diferentes momentos o para diferentes tareas, ser un **gestor** o un **contratista**.
- Cuando un nodo recibe una tarea compuesta (o por cualquier razón no puede resolver su tarea actual), la **descompone** en subtareas (si es posible) y las anuncia (actuando como gestor), recibe ofertas de contratistas potenciales, y luego adjudica el trabajo.

---

### Etapas del Contract Net

#### Etapa 1: Reconocimiento

Un agente reconoce que tiene un problema con el que desea ayuda. El agente tiene un objetivo y ya sea:

- Se da cuenta de que **no puede** alcanzar el objetivo por sí solo (no tiene la capacidad).
- Se da cuenta de que **preferiría no** alcanzar el objetivo por sí solo (típicamente debido a la calidad de la solución, plazos, etc.).

#### Etapa 2: Anuncio

El agente con la tarea envía un **anuncio de la tarea** que incluye una especificación de la tarea a realizar. La especificación debe codificar:

- Descripción de la tarea en sí (posiblemente ejecutable).
- Cualquier restricción (por ejemplo, plazos, restricciones de calidad).
- Información meta-tarea (por ejemplo, "las ofertas deben presentarse antes del…").
- El anuncio se **transmite** entonces.

#### Etapa 3: Pujas – envío de ofertas

Los agentes que reciben el anuncio **deciden por sí mismos** si desean pujar por la tarea. Factores:

- El agente debe decidir si es capaz de agilizar la tarea.
- El agente debe determinar las restricciones de calidad e información sobre precios (si es relevante).
- Si deciden pujar, presentan una oferta.

#### Etapa 4 y 5: Adjudicación y Agilización

El agente que envió el anuncio de la tarea debe **elegir entre las ofertas** y decidir a quién "adjudicar el contrato":

- El resultado de este proceso se comunica a los agentes que presentaron una oferta.
- El contratista exitoso entonces **agiliza** la tarea.
- Puede involucrar la generación de relaciones adicionales de gerente-contratista: **subcontratación**.

---

### Contract Net – Desafíos de implementación

- **¿Cómo especificar tareas?** Define claramente el objetivo, los pasos necesarios para completar la tarea, cualquier requisito técnico específico y las expectativas de tiempo.
- **¿Cómo especificar la calidad del servicio?** Establece estándares medibles como tiempos de respuesta, precisión de los resultados, y nivel de soporte al cliente.
- **¿Cómo seleccionar entre ofertas competidoras?** Evalúa cada oferta según su cumplimiento con los requisitos especificados, el coste, la experiencia previa del oferente y la calidad del servicio propuesta.
- **¿Cómo diferenciar entre ofertas basadas en múltiples criterios?** Utiliza un sistema de puntuación o una matriz de decisión para asignar valores a diferentes aspectos de cada oferta (precio, tiempo de entrega, experiencia y calidad).

---

### Tipos de mensajes en Contract Net

- **Anuncio de tarea**
- **Oferta**
- **Adjudicación**
- **Informe provisional** (sobre el progreso)
- **Informe final** (incluida la descripción del resultado)
- **Mensaje de rescisión** (si el gestor desea rescindir el contrato)

---

### Contract Net – Formato del mensaje de Anuncio de Tarea

Estructura del **Espacio de Anuncio de Tarea**:

- Especificación de Elegibilidad
- Abstracción de la Tarea
- Especificación de la Oferta
- Tiempo de Expiración

**Ejemplo de Anuncio de Tarea (Fourier Transform):**

```
To:                    *
From:                  25
Type:                  Task Announcement
Contract:              43–6
Eligibility Specification: Must-Have FFTBOX
Task Abstraction:
    Task Type          Fourier Transform
    Number-Points      1024
    Node Name          25
    Position           LAT 64N LONG 10W
Bid Specification:     Completion-Time
Expiration Time:       29 1645Z NOV 2025
```

**Ejemplo de Anuncio de Tarea de Señal:**

```
To:                    *
From:                  25
Type:                  Task Announcement
Contract:              22–3–1
Eligibility Specification:
    Must-Have SENSOR
    Must-Have Position Area A
Task Abstraction:
    Task Type          Signal
    Position           LAT 47N LONG 17E
    Area Name A        Specification (…)
Bid Specification:     Position Lat Long
                       Every Sensor Name Type
Expiration Time:       29 1730Z NOV 1925
```

**Ejemplo de Oferta/puja de Señal:**

```
To:                    25
From:                  42
Type:                  BID
Contract:              22–3–1
Node Abstraction:
    LAT 47N LONG 17E
    Sensor Name S1 Type S
    Sensor Name S2 Type S
    Sensor Name T1 Type T
```

**Ejemplo de Adjudicación de Señal:**

```
To:                    42
From:                  25
Type:                  AWARD
Contract:              22–3–1
Task Specification:
    Sensor Name S1 Type S
    Sensor Name S2 Type S
```

---

### Contract Net – Modificaciones por eficiencia

- **Direccionamiento enfocado:** Cuando no se requiere una transmisión general.
- **Contratos dirigidos:** Cuando el gestor ya sabe qué nodo es el adecuado.
- **Mecanismo de solicitud-respuesta:** Para la transferencia simple de información sin la carga administrativa de la contratación.
- **Mensaje de nodo disponible:** Invierte la iniciativa del proceso de negociación.

---

### Contract Net – Características del Protocolo

- **Transferencia bidireccional** de información.
- **Evaluación local**.
- **Selección mutua:** Los contratistas potenciales eligen entre anuncios de tareas; los gestores eligen entre ofertas.
- Ejemplo: Los contratistas potenciales seleccionan a los gestores más cercanos; los gestores utilizan el número de sensores y la distribución de tipos de sensores para elegir un conjunto de contratistas que cubran cada área con una variedad de sensores.

---

### Contract Net – Relación con otros mecanismos de transferencia de control

- La red de contratos considera la transferencia de control como un proceso en tiempo de ejecución, **simétrico**, que implica el intercambio de información compleja para ser efectivo.
- Otros mecanismos (Invocación de procedimientos, Reglas de producción, Invocación dirigida por patrones, Pizarras/Blackboards) son **unidireccionales**, tienen sensibilidad mínima al tiempo de ejecución y una comunicación restringida.

---

### Contract Net – Características de las aplicaciones

- Jerarquía de Tareas.
- Niveles de Abstracción de Datos.
- La selección cuidadosa de las fuentes de conocimiento es clave.
- Los subprocesos son grandes (vale la pena el esfuerzo de distribuirlos sabiamente).
- **Principales preocupaciones:** Control distribuido, lograr confiabilidad, evitar cuellos de botella.

---

### Contract Net – Limitaciones

Otras etapas de la formulación del problema no son sencillas:

- Descomposición del Problema.
- Síntesis de la Solución.
- Sobrecarga.

Métodos alternativos para:

- Difusión de anuncios de tareas.
- Evaluación de tareas.
- Evaluación de ofertas.

---

### Compartición de resultados

Dos arquitecturas principales:

1. **Arquitectura de Pizarra Unificada**
2. **Arquitectura de Pizarra Distribuida**

#### Sistemas de Pizarra (Blackboard Systems)

- El primer esquema para la resolución cooperativa de problemas.
- Los resultados se comparten a través de una **estructura de datos compartida (BB, Blackboard)**.
- Múltiples agentes (fuentes de conocimiento (KS)/KAs) pueden leer y escribir en la BB.
- Los agentes escriben **soluciones parciales** en la BB.
- La BB puede estructurarse en una **jerarquía**.
- Se requiere **exclusión mutua** en la BB → posible cuello de botella.
- **No permite actividad concurrente**.
- Comparación: Espacios de tuplas LINDA, JavaSpaces.

#### Patrón Subscribe/Notify

- Los agentes (suscriptores) se registran para recibir actualizaciones sobre datos específicos.
- Cuando un agente (publicador) genera un nuevo resultado, notifica a los suscriptores interesados.
- Un objeto se suscribe a otro, indicando: "Avísame cuando ocurra el evento e".
- Permite una comunicación **eficiente** sin necesidad de sondeo constante.
- Reduce la carga en los sistemas distribuidos al enviar solo información relevante.
- Los objetos deben conocer los intereses de otros objetos → notifican cuando surge información relevante.
- Ejemplos: eventos en sistemas de mensajería, arquitecturas basadas en eventos como **MQTT** o **ROS**.

---

### Interpretación distribuida

#### Suposición N°1

Las técnicas de interpretación que buscan una solución mediante la **agregación incremental de soluciones parciales** son ideales para sistemas distribuidos. Los errores e incertidumbres derivados de datos de entrada, conocimiento incompleto o incorrecto se manejan dentro del proceso de interpretación.

#### Suposición N°2

Los sistemas de IA basados en conocimiento pueden manejar la **incertidumbre adicional** introducida por la descomposición distribuida **sin modificaciones extensas**.

#### Opciones para la Distribución

1. **Distribuir la Información:** La pizarra (Blackboard) es multidimensional → cada agente - fuente de conocimiento (KS) accede solo a una pequeña subárea. Reducción de redundancia y optimización del almacenamiento.
2. **Distribuir el Procesamiento:** Los módulos de fuentes de conocimiento (KS) son independientes, anónimos y asíncronos. Facilita escalabilidad y mejora la eficiencia computacional.
3. **Distribuir el Control:** Enviar hipótesis entre nodos independientes. Activar las fuentes de conocimiento (KS) según la necesidad. Permite un procesamiento más dinámico y adaptable.

---

## 6.4 Construcción de vocabularios (ontologías)

Las ontologías permiten definir **modelos formales (basados en lógica)** para representar conocimiento mediante:

- **Conceptos (clases)**
- **Individuos (instancias)**
- **Relaciones entre ellos**

### Lenguajes estándares W3C para representar ontologías

|Lenguaje|Descripción|
|---|---|
|**RDF** (Resource Description Framework)|Es el modelo de datos|
|**RDF Schema**|Extiende RDF con una semántica básica|
|**OWL** (Web Ontology Language)|Extiende RDF Schema dotando de mayor expresividad|

---

### Grafos de Conocimiento (redes semánticas)

- **Grafo dirigido etiquetado**
- **Nodos:** Conceptos o individuos concretos
- **Arcos:** Relaciones entre conceptos o individuos

Ejemplo de grafo de conocimiento (dominio farolas/iluminación):

- `Farola1` → `rdf:type` → `Farola`
- `Farola1` → `estado` → `"on"`
- `Farola1` → `tecnología` → `LED`
- `Farola1` → `potencia` → `60W`
- `Farola1` → `instaladaEn` → `Plaza Mayor`
- `Plaza Mayor` → `tipo` → `LugarPúblico`
- `Plaza Mayor` → `localidad` → `Madrid`
- `Madrid` ← `capital` — `España`
- `Farola` → `subclase` → `Consumidor Energía`
- `Farola` → `subclase` → `Dispositivo`

---

### RDF (Resource Description Framework)

- Especificación: http://www.w3.org/TR/rdf11-primer/
- Modelo de datos basado en redes semánticas (Grafos de Conocimiento).
- Los elementos (conceptos, individuos, relaciones) se representan mediante **IRIs** ("International Resource Identifier").
    - Ej: `https://w3id.org/seas/LEDLamp`
- Se asume que todos los agentes interpretan de la misma manera una determinada IRI.
- Aunque varias IRIs pueden representar la misma "cosa", p.e. Madrid:
    - `http://dbpedia.org/resource/Madrid`
    - `https://es.wikipedia.org/wiki/Madrid`
    - `https://madrid.es/`

#### Estructura de un grafo RDF

- Un grafo RDF es un conjunto de **Sentencias** (arcos).
- **Sentencia = tripla (Sujeto, Predicado, Objeto)**
    - **Sujeto:** recurso (IRI) o "blank node"
    - **Predicado/Propiedad:** relación binaria (IRI)
    - **Objeto:** IRI, literal o "blank node"
- **Blank nodes:** nodos "anónimos", no tienen identificador.
- **Literales:** constantes.

#### Serialización

RDF se puede representar en diferentes formatos (XML, Turtle, JSON-LD, etc.). El formato **Turtle** es bastante legible para los humanos.

Cada arco (tripla) se representa mediante una línea: `<sujeto> <predicado> <objeto> .`

**Ejemplo en Turtle (versión larga):**

```turtle
<http://www.example.org/Farola1> <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://dbpedia.org/resource/Lamppost> .
<http://www.example.org/Farola1> <http://www.example.org/tecnologia> <https://w3id.org/seas/LEDLamp> .
<http://www.example.org/Farola1> <http://www.example.org/estado> "on" .
```

**Versión compacta con prefijos:**

```turtle
@prefix ex: <http://www.example.org/>.
@prefix dbr: <http://dbpedia.org/resource/>.
@prefix seas: <https://w3id.org/seas/>.
@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>

ex:Farola1 rdf:type dbr:Lamppost .
ex:Farola1 ex:tecnologia seas:LEDLamp .
ex:Farola1 ex:estado "on" .
```

**O aún más compacto (compartiendo sujeto con `;`):**

```turtle
ex:Farola1 rdf:type dbr:Lamppost ;
           ex:tecnologia seas:LEDLamp ;
           ex:estado "on" .
```

**Abreviaciones Turtle:**

- `@prefix` — declarar prefijos
- `;` — compartir sujeto
- `,` — compartir sujeto y predicado
- `a` — equivale a `rdf:type`
- `[]` — blank nodes
- `()` — listas

---

### RDF Schema

- Recomendación del W3C: http://www.w3.org/TR/rdf-schema/
- RDFS **extiende RDF** con nuevas primitivas (IRIs) con semántica definida.
- Define un lenguaje básico para describir ontologías:
    - Introduce las nociones de **clase**, **instancia** y **propiedades**.
    - Fija la semántica de "subclase de" y "subpropiedad de".
    - Restricciones de dominio y rango de las propiedades.
    - Permite especificar jerarquías/taxonomías de clases y propiedades.
- Permite realizar **inferencias automáticas sencillas** con esas especificaciones.

```turtle
@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#>
```

#### Clases e Instancias

```turtle
# Definición de Clase
ex:Farola rdf:type rdfs:Class.

# Instancia
ex:Farola1 rdf:type ex:Farola.
```

#### Jerarquías de clases (`rdfs:subClassOf`)

```turtle
ex:Farola rdfs:subClassOf ex:FuenteIluminacionElectrica.
```

#### Propiedades (`rdf:Property`)

```turtle
ex:instaladaEn rdf:type rdf:Property .
```

#### Restricciones de propiedades (`rdfs:domain`, `rdfs:range`)

```turtle
ex:instaladaEn rdfs:domain ex:Dispositivo;
               rdfs:range ex:Lugar.
```

#### Jerarquías de propiedades (`rdfs:subPropertyOf`)

```turtle
ex:instaladaEn rdfs:domain ex:Dispositivo;
               rdfs:range ex:Lugar;
               rdfs:subPropertyOf ex:afecta.
```

#### Otras propiedades RDFS

- `rdfs:comment` — descripción legible (por humanos) del recurso.
- `rdfs:label` — versión legible del nombre del recurso.
- `rdfs:seeAlso` — para indicar un recurso con información adicional.

```turtle
dbpedia:Spain rdfs:comment "España es un país...";
              rdfs:label "España";
              rdfs:seeAlso <http://www.spain.info/>
```

#### Ejemplo de inferencia con RDFS

Dado que `ex:Farola1 rdf:type ex:Farola` y `ex:Farola rdfs:subClassOf ex:FuenteIluminacionElectrica`, se deduce que:

- `Farola1` es una `Farola`
- También una `Fuente de Iluminación Eléctrica`
- Un `Dispositivo`
- Y una `Cosa`

---

### Web Ontology Language (OWL)

- Recomendación del W3C:
    - http://www.w3.org/OWL/
    - http://www.w3.org/TR/2012/REC-owl2-primer-20121211/
- Se construye **sobre (extiende) RDFS**, añadiendo primitivas (IRIs) que permiten aumentar la expresividad de la representación del conocimiento.
- Por tanto, se pueden realizar **inferencias automáticas más complejas**.

```turtle
@prefix owl: <http://www.w3.org/2002/07/owl#>
```

#### Capacidades de OWL (no exhaustivo)

- **Cardinalidad** de las propiedades así como mínima y máxima.
- Restricciones **existenciales y universales**.
- **Características de propiedades** (transitiva, simétrica, funcional, inversa, etc.).
- **Clases como combinación de otras:** intersección, unión, complementario.
- **Clases disjuntas o equivalentes**.
- **Individuos que son el mismo o diferentes**.

**Ejemplos:**

```turtle
ex:familiarDe rdf:type owl:SymmetricProperty.
ex:Pais owl:equivalentClass <http://schema.org/Country>.
ex:Spain owl:sameAs <http://sws.geonames.org/2510769/>.
```

---

### Vocabularios Genéricos

|Vocabulario|Descripción|URL|
|---|---|---|
|**FOAF** (Friend-of-a-Friend)|Personas, sus actividades y sus relaciones con otras personas y objetos|—|
|**Dublin Core Metadata Initiative (DCMI)**|Atributos para metadatos como título, creador, fecha, tema, etc.|https://www.dublincore.org/specifications/dublin-core/dcmi-terms/|
|**Dbpedia Ontology**|Base de datos en RDF generada automáticamente a partir de Wikipedia|https://www.dbpedia.org/|
|**Schema.org**|Iniciativa fundada por Google, Microsoft, Yahoo and Yandex|https://schema.org/|

### Ejemplos de Ontologías en dominio de la Energía

- **Smart Energy Aware Systems (SEAS):** https://w3id.org/seas/
- **SEMANCO (Urban Energy Ontology):** http://semanco-tools.eu/urban-enery-ontology
- **Open Energy Ontology:** https://openenergy-platform.org/ontology/

#### Smart Energy Aware Systems (SEAS) – Módulos centrales

- **Características de interés y sus propiedades:** Fenómenos reales (p.e. lámpara) y propiedades observables u operables (p.e. estado encendida/apagada) de esos fenómenos.
- **Procedimientos y sus ejecuciones:** Ejecutores de procedimientos (p.e. sensores, actuadores) que implementan métodos/procedimientos (p.e. medir, actuar) y realizan actividades (p.e. observaciones, actuaciones).
- **Sistemas y sus conexiones**.
- **Evaluación de propiedades:** Representación de evaluaciones, que puede incluir el tipo (p.e. temperatura máxima), contexto (p.e. espacio y rango de tiempo), origen de la información, etc.
- **Varios módulos para diferentes dominios:** Sistemas de energía eléctrica, zonas físicas, mercados, vehículos eléctricos, alumbrado, edificios inteligentes, etc.

Ejemplo: SEAS Electric Light Source Ontology presenta una jerarquía de clases que incluye: `Device`, `LightSource`, `ElectricPowerSystem` → `ElectricLightSource` → `IncandescenceLight`, `GasDischargeLamp`, `LEDLamp` → (subclases adicionales como `IncandescentsLamp`, `HalogenLamp`, `HighPressureDischargeLamp`, `LowPressureDischargeLamp`, `LowPressureMercuryLamp`, `FluorescentTube`, `CompactFluorescentLamp`, `InductionLamp`, `LowPressureSodiumLamp`, `HighPressureSodiumLamp`, `MetalHalideLamp`, `CeramicMetalHalideLamp`, `HighPressureMercuryLamp`...).

---

### Vocabulario no compartido – Alineamiento semántico

#### ¿Qué hacemos si dos agentes no "entienden" el mismo vocabulario?

**Factores que contribuyen a la heterogeneidad entre agentes:**

1. **Diferentes lenguajes de representación:** Algunos agentes pueden usar Prolog para representar conocimiento basado en reglas, mientras que otros emplean RDF para modelado semántico.
2. **Diferencias terminológicas:** Dos agentes pueden referirse al mismo concepto con términos distintos (ejemplo: "usuario" vs "cliente").
3. **Modelos de datos distintos:** Un agente puede estructurar la información en forma de tripletas semánticas (RDF), mientras que otro utiliza un modelo relacional o basado en lógica.

---

#### Definiciones clave

- **Matching:** Es el proceso de **encontrar relaciones** entre diferentes ontologías.
- **Alineamiento:** Es el **resultado** del proceso de matching, es decir, un conjunto de correspondencias entre pares de entidades de las dos ontologías.

Una **correspondencia** entre las ontologías o1 y o2 es una **tripla `<e1, e2, r>`**:

- `e1` y `e2` son entidades (p.e. clases, propiedades) de las ontologías o1 y o2, respectivamente.
- `r` es una relación como **equivalencia** (≡), **subclase** (⊑), **disjunta** (?), entre e1 y e2.
- Por ejemplo: `<o1:Farola, o2:Alumbrado, ⊑>` (o1:Farola es subclase de o2:Alumbrado)

---

#### Ejemplo completo de Alineamiento

**Ontología O1:**

- Dispositivo → Sensor (idSensor) → Farola (idFarola, potencia, tecnología) → Foco (idFoco)
- Lugar

**Ontología O2:**

- ElementoEntrada → Sensor (idSensor)
- ElementoSalida → Visual → PanelLuminoso → Alumbrado; Sonido → Altavoz; idSalida

**Tabla de Alineamiento resultante:**

|O1|O2|r|
|---|---|---|
|o1:Sensor|o2:Sensor|≡|
|o1:idSensor|o2:idSensor|≡|
|o1:Farola|o2:Alumbrado|⊑|
|o1:idFarola|o2:idSalida|⊑|
|o1:idFoco|o2:idSalida|⊑|
|o1:Farola1|o2:F1|≡|

**Axiomas OWL correspondientes:**

```turtle
o1:Sensor owl:equivalentClass o2:Sensor .
o1:idSensor owl:equivalentProperty o2:idSensor .
o1:Farola rdfs:subClassOf o2:Alumbrado .
o1:idFarola rdfs:subPropertyOf o2:idSalida .
o1:idFoco rdfs:subPropertyOf o2:idSalida .
o1:Farola1 owl:sameAs o2:F1 .
```

Incluyendo esos axiomas junto con las ontologías se infiere que, por ejemplo:

- Todas las instancias de `o1:Farola` son instancia de `o2:Alumbrado` y, por tanto, de `o2:ElementoSalida`.

---

#### Propiedades OWL para alineamientos como axiomas

|Propiedad OWL|Significado|
|---|---|
|`rdfs:subClassOf` (⊑)|Subclase de|
|`owl:equivalentClass` (≡)|Clases equivalentes|
|`owl:disjointWith`|Clases disjuntas|
|`owl:equivalentProperty`|Propiedades equivalentes|
|`rdfs:subPropertyOf`|Subpropiedad de|
|`owl:sameAs`|Dos IRIs representan el mismo individuo|
|`owl:differentFrom`|Dos IRIs no representan el mismo individuo|

---

#### Usos de los alineamientos

**Uso 1 – Con traductor:** Los alineamientos pueden ser usados por un **traductor** para transformar un mensaje que usa una ontología (O1) en otro con ontología (O2): `mensaje(con O1)` → **Traductor** → `mensaje(con O2)`.

El proceso: Ontología O1 + Ontología O2 → **Matching** → **Alineamientos O1 ↔ O2** → **Traductor** → transforma mensajes.

**Uso 2 – Como axiomas (sin traductor):** Los alineamientos pueden ser **incorporados a las ontologías** de los agentes como axiomas, sin necesidad de traductor. En este caso los agentes pueden usar `mensaje(con O1 u O2)` directamente.

#### Observaciones

- Puede que los mensajes usen términos definidos en **varias ontologías**.
- En ese caso son necesarios alineamientos **entre pares de ellas**.

#### Referencia bibliográfica de Ontology Matching

J. Euzenat, P. Shvaiko: _Ontology matching_, Springer, 2nd edition, 2013.

---

## 6.5 Aplicaciones de Comunicación entre agentes

Ejemplos reales donde la comunicación de agentes de IA destaca:

- **Centros de Llamadas Automatizados:** Los agentes de IA coordinan respuestas recopilando datos de múltiples fuentes para proporcionar soporte al cliente de manera precisa.
- **Logística y Cadena de Suministro:** Los agentes se comunican para optimizar las rutas de entrega, gestionar inventarios y manejar cambios en tiempo real en la demanda.
- **IoT y Dispositivos Inteligentes:** Los agentes se comunican en tiempo real utilizando protocolos ligeros como MQTT, permitiendo que los dispositivos compartan datos críticos de manera eficiente.

---

## Literatura recomendada

- M. Wooldridge: _An Introduction to MultiAgent Systems_, **Capítulo 8**.

---

## Conceptos clave (resumen)

|Concepto|Definición breve|
|---|---|
|**Habilidad social**|Capacidad de interactuar con otros agentes mediante un lenguaje de comunicación|
|**FIPA ACL**|Estándar industrial de lenguaje de comunicación entre agentes|
|**Performative**|Verbo del acto comunicativo que define la intención del mensaje|
|**KQML**|Lenguaje para compartición de conocimiento entre agentes|
|**OWL**|Lenguaje de ontología web con alta expresividad semántica|
|**RDF**|Modelo de datos para grafos de conocimiento basado en triplas|
|**RDFS**|Extensión de RDF con semántica básica de clases y propiedades|
|**Contract Net**|Protocolo distribuido de distribución de tareas mediante negociación|
|**CDPS**|Resolución de Problemas Distribuidos Cooperativos (para agentes benevolentes)|
|**Blackboard**|Estructura de datos compartida para la compartición de resultados parciales|
|**Ontología**|Especificación formal de un dominio mediante conceptos, instancias y relaciones|
|**Alineamiento semántico**|Conjunto de correspondencias entre entidades de dos ontologías distintas|
|**Matching**|Proceso de encontrar relaciones entre diferentes ontologías|
|**IRI**|International Resource Identifier; identificador único de entidades en RDF/OWL|
|**MQTT**|Protocolo de mensajería ligero basado en publicación/suscripción, ideal para IoT|