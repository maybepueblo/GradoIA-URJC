![[infografiaTema1RCR2.png]]
## Origen y Evolución
- **Contexto histórico:** Originalmente el objetivo de la IA era crear sistemas que resolvieran problemas simulando el pensamiento humano. Las técnicas que había por los 70 (STRIPS o GPS) demostraron no ser suficientes para ciertos problemas.
- **Cambio de paradigma**: Un sistema depende más de la cantidad de conocimiento experto adquirido que de su mecanismo de inferencia.
- **El nivel de conocimiento:** A.Newel lo propone para solucionar confusiones entre conocimiento puro y programarlo. Se añade por encima del nivel simbólico computacional clásico (físico, lógico, simbólico) para separar conceptualmente el conocimiento (extraído del experto) de su representación (su codificación en un lenguaje).
## Sistemas Basados en el Conocimiento (SBC) y Programación Declarativa
- **Sistemas Tradicionales vs SBCs**: En los tradicionales, vemos el conocimiento incrustado y mezclado con las estructuras de control. Esto es lo opuesto en SBCs, donde el conocimiento está representado de forma explícita y separada del mecanismo de control.
- **Sistemas Expertos (SE):** Tipo de SBC donde el conocimiento viene de un experto humano, se usa como sinónimo este término.
- **Características y Ventajas:** Trabajan sobre conocimiento de dominio específico, simulan el razonamiento humano (con heurísticas y aproximaciones), son explicables y permiten reutilizar el conocimiento.
- **Desventajas:** Adquirir conocimiento es tedioso (cuesta mucho y toma tiempo) y se limita al sistema a ese dominio de diseño.
-  **Programación Declarativa:** No como la algoritmica (paso a paso cómo hacer algo != pensar humano), con esta expresamos explícitamente el conocimiento.
	- Es abstracto, flexible, facil de entender y manejar conocimiento no algorítmico o aproximado
## SBC vs Aprendizaje Automático (AA)
El **AA** come mucho dato y genera modelos difíciles de explicar.

Aquí, se dice que son tecnologías complementarias: un SBC inicia el sistema basado en reglas humanas y se mejora con AA (ajuste de parámetros o aprender por refuerzo a partir de lo sabido)
	- El SBC nos da explicabilidad mientras que el AA se adapta matemáticamente a nuevos datos en tiempo real.
## Estructura Arquitectónica de un SBC
- **Base de conocimiento:** Se almacenan reglas y saberes expertos
- **Base de hechos:** Guardamos datos específicos del problema actual
- **Motor de inferencia:** El mecanismo que procesa el conocimiento y los hechos para sacar conclusiones
- **Interfaz:** Compuesta por subsistemas: usuario, explicación (decisiones justificadas) y adquisición conocimiento (comunica al sistema con el ingeniero)
## La Ingeniería del Conocimiento (IC)
- Disciplina que contiene metodologías y técnicas para diseñar SBCs, equivalente a [[Ingeniería del Software]] clásica, pero menos desarrollada.
- El **Ingeniero del Conocimiento** evaluar lo viable, extrae el saber del dominio, elige cómo representarlo y construye el sistema final.
## Fases de Desarrollo de un SBC
Tiene 6 etapas ordenadas:
1. **Estudio de viabilidad:** Se ve si el proyecto es posible (existen expertos, de acuerdo entre ellos y que explican bien) y si está justificado (estado del arte, necesidad de replicar conocimiento o evitar pérdidas, incluso uso en entornos hostiles)
2. **Adquirir conocimiento:** Lo más dificil. Extraemos info de expertos, docs, BDs o simuladores. Hay retos como el conocimiento tácito, barreras de comunicación y límites en el lenguaje. Se usan técnicas como entrevistas, observación, brainstorming, cuestionarios o emparrillado.
3. **Conceptualización (Análisis):** Modelo conceptual (no computable) para entender el dominio. Ordena el saber previo independiente al código. Usamos ontologías, árboles de decisión, tablas concepto-atributo-valor y diagramas.
4. **Formalización (Diseño):** Ahora modelo formal semicomputable, se acerca al pov del sistema. Organizamos y damos métodos de inferencia usando formalismos como lógica, reglas, grafos o técnicas para incertidumbre (RB, Fuzzy logic, MYCIN, no monotono).
5. **Implementar:** Se construye el modelo computable. Se elige un entorno de desarrollo que ofrezca los formalismos e inferencias necesarios, permite editar, controlar, prototipar rápidamente y usarlo fácilmente para validar con expertos.
6. **Evaluación:** Subjetiva y difícil de probar en lab comparada al software normal por la incertidumbre. Requiere expertos para evaluar. Se mide:
	- **Correción (verificación):** Sintaxis y estructura sin redundancias ni vacíos (se hace en los tres modelos: conceptual, formal y computable)
	- **Validez:** Semántica adecuada según el experto (también en los tres modelos)
	- **Usabilidad y utilidad**