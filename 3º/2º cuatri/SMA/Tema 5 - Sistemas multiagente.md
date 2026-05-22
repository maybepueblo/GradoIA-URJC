## Índice del Tema 5

1. [[#5.1 Introducción]]
2. [[#5.2 Coordinación]]
3. [[#5.3 Tipos de Sistemas Multiagente]]
4. [[#5.4 Interacción entre Agentes]]
5. [[#5.5 Desarrollo de Sistemas Multiagente]]

---

## 5.1 Introducción

### ¿Qué es un Agente?

- **Entidad computacional autónoma** que actúa en nombre de un usuario u otra entidad.
- Capaz de **percibir el entorno**, **tomar decisiones** y **actuar**.

### De uno a múltiples agentes

- En muchos entornos del mundo real **no existe sólo un agente** que actúa (y que influye en la evolución del entorno), sino **varios**.
- Las acciones de **todos los agentes** influyen en el cambio del estado del entorno.
- Para un agente, la consecución de sus objetivos ya **no sólo depende de él** (sino también de lo que hacen los demás).

### Propiedades recordadas de los Agentes

|Propiedad|Descripción|
|---|---|
|**Autonomía**|Un agente **NO** puede controlar las acciones de los demás. Operan independientemente sin control externo.|
|**Racionalidad**|Un agente **SÍ** puede predecir las acciones de los demás.|
|**Sociabilidad**|Un agente **SÍ** puede coordinarse con los demás. Interactúan con otros agentes para compartir información y coordinar acciones.|
|**Proactividad**|Persiguen objetivos de manera activa, adaptándose al entorno.|
|**Reactividad**|Responden a cambios en tiempo real, asegurando adaptabilidad y robustez.|

### ¿Qué es un Sistema Multiagente (SMA)?

- **NO hay una definición única.**
- En general se coincide en que un **sistema multiagente (SMA)** es un sistema compuesto por **múltiples agentes** que:
    - Actúan en un **entorno común**, y
    - Pueden **interactuar entre sí**.
- Hay definiciones más restrictivas que especifican características adicionales:
    - Los agentes trabajan juntos para resolver un problema.
    - Los agentes son inteligentes/racionales, autónomos, generalmente heterogéneos e independientes.
    - **No en todos los casos** se puede suponer estas características.

### Características generales de los agentes en un SMA

En el caso más general, los agentes de un SMA:

- Actuarán en representación de usuarios que pueden tener **diferentes objetivos y motivaciones**.
- Tendrán **diferentes capacidades y comportamientos** (quizás desconocidos para los demás).

### Del Nivel Micro al Macro

- Ya no sólo nos interesa cómo un agente puede tomar sus decisiones para realizar con éxito sus tareas.
- Sino **cómo puede hacerlo en un entorno con otros agentes**.
- **Interactuar** con otros agentes **puede ser necesario** para conseguir los objetivos.

### La Sociedad Humana como SMA

- La sociedad humana, así como estructuras que existen en ella, pueden entenderse como "sistemas multiagentes".
- Los humanos:
    - Somos inteligentes (por lo menos algunos), autónomos, independientes.
    - Tenemos nuestros propios objetivos y los perseguimos.
    - Vivimos y actuamos en un mismo entorno.
    - Interactuamos entre nosotros.
- **Fenómenos sociales** permiten elaborar modelos para SMA.
- Y **modelos de SMA** permiten estudiar fenómenos sociales (**simulación social**).

### Otros ejemplos de SMA

- Entornos de negocio electrónico
- Juegos multijugador
- El tráfico en una ciudad
- …

### Aplicaciones de SMA

- **Asistentes virtuales** — Ejemplos: Siri, Google Assistant, Alexa.
- **Optimización de batería** en dispositivos.
- **Monitoreo de salud personal** — uso en dispositivos portátiles para monitorizar señales fisiológicas.
- **Sistemas de información y correo electrónico**.
- **Agricultura de precisión** — coordinación de flotas de robots para optimización de siembra y cosecha.
- **Transporte inteligente** — coordinación de vehículos autónomos para reducir congestión y mejorar seguridad.
- **Gestión de emergencias médicas**.
- **Optimización de evacuaciones** en edificios inteligentes.

### Dificultades en Entornos Multiagente

En entornos Multiagente, las dificultades aumentan en tres dimensiones:

1. **Mayor incertidumbre:**
    
    - Más difícil estimar "lo que va a pasar".
    - Más difícil tomar decisiones.
    - _Ejemplo:_ Querer comprar un coche fiable sin saber cómo de fiar son los vendedores y sus coches.
2. **Posibles conflictos de intereses:**
    
    - Entre agentes.
    - Con posibles objetivos globales.
    - _Ejemplo:_ Tráfico — cada persona quiere ir lo antes posible a su destino, mientras que las autoridades quieren reducir emisiones, atascos y accidentes. ¿Cómo regularlo mejor? ¿El equilibrio de Nash?
3. **Posibilidad de ser más eficientes:**
    
    - Trabajar juntos.
    - Si supiéramos aprovechar nuestro potencial y colaborar (hasta cierto punto).
    - _Ejemplos:_ cardúmenes de peces que se organizan, pelotones en ciclismo.

### Desafíos de los SMA

- **Integración en entornos dinámicos:** adaptación a cambios y gestión de procesos distribuidos.
- **Interoperabilidad entre agentes heterogéneos:** asegurar la comunicación y colaboración efectiva entre diferentes sistemas y agentes.
- **Consideraciones éticas.**

### Propósito de los SMA

- Colaboración y coordinación entre múltiples agentes.

### Relevancia de los SMA en IA

- Surgen como **paradigma fundamental** para el desarrollo de sistemas inteligentes.
- Aprovechan el auge de la **computación distribuida**.
- Se adaptan a **entornos complejos e inciertos**.

---

## 5.2 Coordinación

### Definición

> "Proceso de organizar para que varios trabajen juntos adecuadamente"

- Necesaria para **asignación de tareas** y **solución conjunta de problemas**.
- En resolución de problemas distribuidos, los agentes combinan recursos y conocimientos.
- Proceso que garantiza **comportamiento coherente y competente**.
- **Evita conflictos** y maximiza la eficiencia global.
- Especialmente relevante en tareas distribuidas espacial o temporalmente.

### Mecanismos de Coordinación

> **Definición:** Herramientas que regulan las interacciones entre los agentes o entre ellos y el entorno con el fin de mejorar la eficiencia y efectividad de los sistemas en algún sentido.

- Buscamos mecanismos de coordinación que permitan mejorar el comportamiento (eficiencia y eficacia) de diferentes tipos de sistemas multiagente.

### Comportamiento Colaborativo, Cooperativo y Competitivo

|Tipo|Características|
|---|---|
|**Colaboración**|Comparten propiedad de resultados, alta comunicación y sincronización.|
|**Cooperación**|Objetivos parcialmente alineados, introducción de incentivos.|
|**Competición**|Objetivos divergentes. Enfrentamiento derivado de metas contrapuestas y la disputa por recursos escasos.|

### Competición y Cambio hacia Cooperación: El Equilibrio de Nash

- En un contexto donde varios jugadores interactúan, un **equilibrio de Nash** se alcanza cuando **ningún jugador puede obtener un beneficio mayor cambiando unilateralmente su estrategia**, siempre que los demás jugadores mantengan las suyas constantes.
- En el equilibrio de Nash, cada jugador elige la **mejor estrategia posible** dado lo que están haciendo los otros jugadores.
- El equilibrio de Nash **puede ser subóptimo** para el sistema global.
- Mecanismos para superarlo:
    - Coordinación descentralizada.
    - Evitar monopolios.
    - Compartir información selectivamente.
    - Diseñar sistemas de incentivos y confianza.

---

## 5.3 Tipos de Sistemas Multiagente

### Grado de Abertura de un SMA

Desde el punto de vista de la coordinación, un factor importante es el **grado de abertura** de un SMA:

#### Sistema Cerrado

- Entorno cerrado.
- El comportamiento de **TODOS** los agentes es controlable de forma directa (diseñador único del sistema).
- Roles e interacciones estrictamente controlados.
- Coordinación predeterminada y centralizada o distribuida.
- Ámbito industrial: alta fiabilidad y protocolos fijos.
- **Ejemplos:**
    - **Sistemas de fabricación:** agentes controlan maquinaria y línea de producción.
    - **Robótica de almacén:** cobots (robots colaborativos) para gestionar inventario.
    - **Misiones espaciales:** control central para lograr objetivos críticos.
- En sistemas cerrados, la coordinación se basa en **Resolución de Problemas Distribuidos:**
    - Los agentes tienen información y capacidades **parciales**.
    - Subdivisión en subproblemas, síntesis de resultados y optimización conjunta.
    - Evita que cada agente trabaje aisladamente.

#### Sistema Abierto

- Entorno totalmente abierto.
- El comportamiento de los agentes es **desconocido** y **no se puede influir directamente** en él (múltiples diseñadores de agentes).
- Agentes heterogéneos y diseñados de forma independiente.
- Pueden unirse o abandonar el sistema libremente.
- **No existe un ente central con control absoluto.**
- **Desafíos de los Sistemas Abiertos:**
    - Alineación de objetivos entre agentes con potenciales conflictos.
    - Comunicación efectiva en entornos descentralizados.
    - Cooperación vs. competición con múltiples partes interesadas.
- **Ejemplos:**
    - **Internet:** rastreadores, sistemas de recomendación, etc.
    - **Redes inteligentes (Smart Grids):** sistemas de energía distribuidos.
    - **Vehículos autónomos conectados:** flujo de tráfico sin controlador central.
    - **Mercados digitales:** comercio electrónico y bolsas de valores.

### Taxonomía Arquitectónica de los SMA

#### Sistemas Centralizados, Distribuidos y Descentralizados

|Tipo|Descripción|
|---|---|
|**Centralizado**|Un único agente decide (no siempre es realmente "multiagente").|
|**Distribuido**|Varios agentes con división de objetivos y tareas.|
|**Descentralizado**|Múltiples partes interesadas, información local, sin control global.|

#### Arquitecturas Centralizadas

- Un tomador de decisiones principal.
- Entidades periféricas sin autonomía.
- Frecuente **cuello de botella** y menor flexibilidad en entornos cambiantes.

#### Arquitecturas Distribuidas

- Varios agentes cooperan para resolver problemas.
- Se derivan de modelos centralizados monolíticos, pero usan **descomposición de tareas**.
- Aseguran **escalabilidad y resiliencia** si el número de agentes crece.

#### Arquitecturas Descentralizadas

- Adecuadas para entornos con múltiples partes interesadas (competitivos o cooperativos).
- Basadas en **teoría de juegos, heurísticas y metaheurísticas**.
- **No suelen garantizar calidad formal** de la solución (por la complejidad).
- **Desafíos en sistemas descentralizados:**
    1. Falta de información global veraz (posible manipulación).
    2. Mecanismos a prueba de estrategias (evitar conductas deshonestas).
    3. Información limitada (protección de datos, ventaja competitiva).
    4. Equilibrios de Nash y posible suboptimalidad.
    5. Objetivos emergentes vs. objetivos predefinidos.

### Clasificación de Arquitecturas en Sistemas Multiagente

#### Arquitectura Plana o Horizontal

- **Definición:** Todos los agentes operan al mismo nivel sin jerarquías.
- **Ventajas:**
    - Robustez aumentada sin puntos únicos de falla.
    - Fomenta cooperación y negociación directa.
- **Desafíos:**
    - Difícil lograr decisiones colectivas eficientes.
    - Posibles redundancias y conflictos de recursos.

#### Arquitectura Jerárquica

- **Definición:** Agentes organizados en niveles de autoridad claramente definidos.
- **Ventajas:**
    - Facilita coordinación y toma de decisiones eficiente.
    - Descomposición clara de problemas y roles.
- **Desafíos:**
    - Rigidez puede limitar flexibilidad.
    - Fallos en niveles altos impactan gravemente el sistema.

#### Arquitectura Federada

- **Definición:** Agentes agrupados en federaciones semi-independientes que cooperan entre sí.
- **Ventajas:**
    - Eficiencia de jerarquías con robustez de estructuras planas.
    - Especialización y adaptación a tareas específicas.
- **Desafíos:**
    - Requiere comunicación y coordinación efectiva entre federaciones.

#### Arquitectura de Malla o Mesh

- **Definición:** Estructura de red donde cada nodo está interconectado con todos los demás nodos, formando un patrón de conexiones similar a una rejilla. Proporciona alta fiabilidad y es comúnmente utilizada en despliegues a gran escala por operadores y proveedores de servicios.
- **Ventajas:**
    - Alta resiliencia y flexibilidad.
    - Fallos individuales tienen impacto limitado.
- **Desafíos:**
    - Posibles ineficiencias y redundancias en la comunicación.

### Tipos de SMA según apertura e individualismo

```
Sistemas abiertos ←————————————————→ Sistemas cerrados

[Sociedades de agentes]  [Equipos de agentes]  [Organizaciones]  [Sistemas de componentes]
 (tráfico, P2P, …)       (fútbol, supply       (sistemas         (gestión, flotas, …)
                          chains, …)             empresariales, …)

 Objetivos individuales ←————————→ Objetivos Globales
 Sin control global ←————→ Existencia de autoridad global ←→ Control global total
```

#### Sistema Social (Sociedades de Agentes)

- Objetivos individuales.
- Mucho individualismo / poca noción del conjunto.
- No existe un control global.
- **Coordinación:** La búsqueda de comportamientos sociales para superar las dificultades del entorno.

#### Sistema Grupos (Grupos / Organizaciones / Equipos)

- Más noción del conjunto / menos individualismo.
- Objetivos individuales y globales.
- Existencia de una autoridad global.
- **Coordinación:** Buscar la forma de convertir acciones individuales en acciones conjuntas efectivas.

#### Sistemas Monolíticos (Sistemas de Componentes)

- Sólo noción del conjunto / nulo individualismo.
- Objetivos comunes.
- Total control global.
- **Coordinación:** Buscar la forma de juntar las acciones individuales para conseguir un fin determinado.

### Coordinación de Diferentes Tipos de SMA — Perspectivas

**En sistemas abiertos (sociedades de agentes):**

> _"Co-ordination is a way of Adapting to the environment"_ — von Martial

- Cada agente trabaja para conseguir sus propios objetivos.
- ¿Cómo puede un agente mejorar en un entorno cambiante y parcialmente desconocido?
- Emergencia de estructuras organizativas que ayuden a (quasi) todos.
- **Métodos bottom-up.**

**En sistemas intermedios (equipos / organizaciones):**

> _"Coordination is governing interaction"_ — Wegener

- Coexisten objetivos individuales y globales.
- ¿Cómo se puede influir en el comportamiento de agentes autónomos?
- Diseñar estructuras organizativas para mejorar la efectividad global (y adaptarlas a la población de agentes).
- "Especificar las reglas del juego".
- **Métodos bottom-up y top-down.**

**En sistemas cerrados (sistemas de componentes):**

> _"The integration and harmonious adjustment of individual work efforts towards the accomplishment of a larger goal"_ — B. Singh

- TODOS los agentes trabajan en colaboración para conseguir un objetivo global común.
- ¿Cómo organizar de forma efectiva las acciones de los agentes?
- Diseñar protocolos/planes de actuación conjunta (optimización).
- **Métodos top-down.**

---

## 5.4 Interacción entre Agentes

Un aspecto **fundamental** en los sistemas multiagente es la **interacción entre los agentes**.

### Tipos de Agentes según Interacción

|Tipo|Características|Referencia|
|---|---|---|
|**Agentes cooperativos**|Normalmente tienen objetivos comunes (p.e. pertenecen a una misma organización). Resolución de problemas cooperativa distribuida.|→ Tema 7|
|**Agentes competitivos**|Los agentes son auto-interesados y tienen objetivos diferentes. Teoría de juegos.|→ Temas 9-12|
|**Híbridos**|Pueden tener unos objetivos compartidos pero otros no.|—|

### Comunicación entre Agentes

En sus interacciones, es necesario que haya una **comunicación efectiva** entre los agentes. Deben tener un entendimiento común de:

- **Protocolos de interacción.**
- **Lenguajes de comunicación.**
- **Terminología utilizada.**

Características de la comunicación:

- **Esencial** para la coordinación.
- Dos tipos principales:
    - **Implícita:** acciones en el entorno.
    - **Explícita:** mensajes directos.
- La **comunicación excesiva** puede disminuir la coherencia.

### Comunicación entre Agentes Basada en Conocimiento

Una forma avanzada de interacción que facilita el intercambio de información significativa y precisa.

Las **ontologías** proporcionan una estructura formal para representar el conocimiento compartido entre los agentes, esencial para asegurar la interoperabilidad y el entendimiento mutuo en entornos complejos.

#### Definición de Ontología

> Una ontología es un modelo que define un conjunto de conceptos y categorías en un dominio y las relaciones entre ellos. Sirve como un vocabulario común que todos los agentes pueden entender y utilizar para intercambiar datos e información de manera eficiente.

#### Componentes Clave de las Ontologías

|Componente|Descripción|
|---|---|
|**Clases**|Categorías de objetos o conceptos dentro del dominio.|
|**Relaciones**|Maneras en que las clases pueden estar conectadas, mostrando cómo se relacionan los conceptos entre sí.|
|**Instancias**|Objetos concretos que son ejemplos de las clases definidas.|
|**Axiomas**|Reglas y afirmaciones que definen la lógica del dominio y cómo se deben interpretar las relaciones e instancias.|

#### Uso de Ontologías en la Comunicación entre Agentes

- **Interoperabilidad:** Al adherirse a una ontología común, los agentes de diferentes sistemas o con diferentes diseños internos pueden comunicarse sin ambigüedades, interpretando los mensajes de manera coherente y precisa.
- **Consulta y Razonamiento:** Los agentes pueden realizar consultas complejas dentro de la red, usando la ontología para inferir nueva información o deducir relaciones no explícitas a partir de los datos disponibles.
- **Adaptabilidad:** Las ontologías permiten a los sistemas adaptarse a nuevos datos o situaciones modificando la ontología para incluir nuevos conceptos o relaciones, facilitando así la evolución del sistema de conocimiento sin romper la compatibilidad.
- **Implementación en SMA — Protocolos de Comunicación:** Los agentes utilizan protocolos específicos que incorporan el uso de ontologías para formatear sus mensajes, asegurando que la comunicación sea entendida a un nivel semántico.

### Tipos de Comunicación en Sistemas Multiagente

1. **Comunicación Entre Pares (Punto a Punto):** Comunicación directa entre dos agentes, permitiendo intercambios específicos y privados.
2. **Difusión (Broadcast):** Mensajes enviados desde un agente a todos los demás en el sistema, útil para notificaciones amplias y actualizaciones generales.
3. **Comunicación Grupal o Multidifusión:** Mensajes dirigidos a un conjunto específico de agentes, facilitando la colaboración entre grupos definidos.
4. **Comunicaciones Generativas (Pizarra Compartida):** Uso de un espacio común (como una pizarra) donde los mensajes pueden ser escritos y leídos por varios agentes, promoviendo un entorno colaborativo dinámico.

> _Más detalles en el Tema 6._

### Comunicación en SMA con Base en Rangos de Comunicación

Se asume la existencia de un **rango de comunicación definido** que determina con quién puede interactuar directamente. Los agentes dentro de este rango son considerados **"vecinos"** y pueden comunicarse sin intermediarios.

#### Representación mediante Grafos de Comunicación

- **Nodos:** Cada nodo en el grafo representa un agente en el sistema.
- **Aristas:** Una arista entre dos nodos indica que los agentes pueden comunicarse directamente (están dentro del rango de comunicación el uno del otro).

#### Propiedades de los Grafos

|Propiedad|Descripción|
|---|---|
|**Conectividad**|El grafo puede ser completamente conectado (todos en distancia directa) o parcialmente conectado (algunos requieren comunicación multi-hop).|
|**Ponderación**|Las aristas pueden ser ponderadas basadas en el costo de la comunicación o la latencia, reflejando la eficiencia de la conexión directa.|
|**Dinámica**|Los grafos pueden ser estáticos (conexiones fijas) o dinámicos (aristas que se ajustan en respuesta a movimientos de agentes o cambios en el ambiente).|

### Métodos de Comunicación en Sistemas Multiagente

|Método|Descripción|
|---|---|
|**Comunicación de Salto Único (Uni-hop)**|Mensajes enviados directamente de un agente a otro sin intermediarios. Ideal para redes confiables y de corto alcance.|
|**Comunicación de Múltiples Saltos (Multi-hop)**|Los mensajes se transmiten a través de varios agentes intermedios. Adecuado para redes grandes o dispersas, aumentando la cobertura y la fiabilidad pero con mayor latencia.|
|**Comunicación Basada en Rutas**|Utiliza rutas predeterminadas para la transmisión de mensajes, optimizando el flujo de información y la eficiencia de la red en entornos estructurados.|
|**Comunicación Dinámica**|Adapta las rutas de comunicación en respuesta a cambios en la red, proporcionando flexibilidad y robustez ante condiciones cambiantes.|

---

## 5.5 Desarrollo de Sistemas Multiagente

Para el desarrollo son necesarios:

- **Estándares**
- **Metodologías**
- **Herramientas / Plataformas**

### Estándar FIPA

- **Foundation for Intelligent Physical Agents (FIPA)** — http://www.fipa.org/
- Especificaciones para **facilitar la interoperabilidad** entre agentes heterogéneos.
- Se organiza en:
    - **Arquitectura Abstracta** de las Plataformas de Agente.
    - **Comunicación entre Agentes.**
    - **Gestión de Agentes** — Servicios de gestión de agentes en las plataformas FIPA.
    - **Transporte de Mensajes** — Representación del mensaje y protocolos de transporte.

#### FIPA — Arquitectura Abstracta

|Componente|Función|
|---|---|
|**Agent Management System (AMS)**|Creación, modificación, eliminación de agentes (**páginas blancas**).|
|**Directory Facilitator (DF)**|Búsqueda de servicios por funcionalidad (**páginas amarillas**).|
|**Message Transport System (MTS)**|Sistema para el transporte de mensajes. Comunica agentes en la misma o en distinta plataforma.|
|**Agentes**|Ejecutan en una plataforma de agentes.|

#### FIPA — Lenguajes de Comunicación

- **FIPA ACL (Agent Communication Language):**
    - Estructura de un mensaje (emisor, receptor, **contenido**, protocolo, etc.).
- **Lenguajes de Contenido:**
    - Representación de los contenidos de los mensajes (p.e. "la temperatura de la sala S1 es 20℃").
- **Protocolos de Interacción:**
    - Subastas, Contract-Net, etc.

> _Más sobre comunicación entre agentes en el Tema 6._

### Metodologías

- **Ingeniería del Software Orientado a Agentes.**
- Las metodologías suelen proponer un conjunto de **modelos y directrices de uso**.
- **Enfoques:**
    - Inspiradas en desarrollo Orientado a Objetos (se extienden o adaptan para Orientación a Agentes).
    - Adaptaciones de la ingeniería del conocimiento u otras técnicas.
- **Suelen incluir nociones (y modelos) como:**
    - Agentes, roles, interacciones, organizaciones.
- **Ejemplos:** AAII, Gaia, Tropos, Prometheus, …

### Plataformas de Agentes

- Principalmente proporcionan **conectividad entre agentes**, abstrayendo los detalles de comunicación (p.e. si se usa FIPA).
- Suelen proporcionar una **API** para acceder a los servicios.
- Servicios adicionales para el desarrollo y mantenimiento (p.e. interfaces gráficas).

#### JADE (Java Agent DEvelopment Framework)

- Plataforma compatible con FIPA más utilizada.
- Se puede distribuir en diferentes máquinas con mismo o diferente SO.
- **Open source.**
- https://jade.tilab.com/

### Plataformas de Modelado y Simulación Basada en Agentes

#### NetLogo

- Entorno de programación para Simulación Basada en Agentes.
- Open source.
- También versión en web.
- https://ccl.northwestern.edu/netlogo/

#### Repast

- Entorno de programación para Simulación Basada en Agentes.
- Open source.
- https://repast.github.io/

---
