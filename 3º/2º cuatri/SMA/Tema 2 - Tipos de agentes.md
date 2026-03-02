## Este tema
Si bien en el [[Tema 1 - Agentes, entornos, sistemas multiagente]] vimos la arquitectura básica de un agente y que existen para diferentes tareas, en esta tema veremos los diferentes tipos de agentes según cómo implementan su comportamiento.
## Introducción al programa básico de un agente
El comportamiento base de un agente se define por funciones fundamentales: percibir el estado actual del entorno ($p \in P$) mediante sensores, seleccionar una acción mediante su programa ($a \leftarrow selección\_acción(p, m, O, A)$) y ejecutarla en el entorno mediante actuadores.

Las decisiones se toman en función de su memoria ($m$), sus objetivos ($O$) y el conjunto de acciones posibles ($A$).
## Agentes Reactivos Simples
- **Características:** Los más básicos, carecen de memoria y eligen su siguiente acción basándose únicamente en la percepción actual. Su comportamiento inteligente surge de la interacción directa con el entorno.
- **Implementación:** Utilizan reglas de condición-acción donde los objetivos están implícitos en las propias reglas.
- **Limitaciones y soluciones**:
	- Son propensos a caer en bucles infinitos
	- 1. Seleccionar acciones de forma aleatoria puede desatascar estos bucles, aunque no parezca muy "inteligente". 
	- 2. Mejorar la percepción del entorno (pasar de agente ciego con $|P|=1$ a percibir estados distinguibles) mejora notablemente su rendimiento.
- **Arquitectura de Subsunción (R. Brooks)**: Propone organizar comportamientos simples en capas. Las capas inferiores representan comportamientoos primitivos (ej. evitar obstáculos) que inhiben ("subsumen") a las capas superiores cuando es necesario.
	- Si la capa 1 es "no chocar" y la capa 2 es "ir al tesoro", el instinto de no chocar anulará la orden de ir al tesoro si hay un muro delante.
## Agentes con Estado
- **Memoria Interna:** Mantienen y modifican su conocimiento propio (estado interno) durante su ciclo de vida, basándose en las percepciones ($e \leftarrow actualizar\_estado(p, e)$)
- **Modelo del mundo:** Pueden almacenar su historial de acciones/percepciones y mantener un modelo sobre cómo evoluciona el entorno.
- **Clasificación:
	- **Reactivos con estado:** Responden a estímulos usando el historial para evitar bucles, sin prever el futuro. No suelen usar modelo del mundo.
	- **Deliberativos:** Usan el modelo del mundo para deliberar y prever las consecuencias de sus acciones antes de actuar.
## Agentes de Planificación
- **Deliberación Guiada:** Son agentes basados en metas explícitas que mantienen un modelo simbólico del mundo (creencias)
- **Proceso:** Usan técnicas de inteligencia artificial (como el algoritmo $A*$) para planificar secuencias completas de acciones antes de actuar ($plan \leftarrow planificar(e,O,A)$)
- **Replanificación:** Si el entorno o los objetivos cambian, el plan inicial puede volverse inválido.
	1. El agente percibe tras cada acción
	2. Actualiza su estado
	3. Comprueba si el plan sigue siendo válido
	4. Si falla, ejecuta un proceso de replanificación (aquí entran otras materias como [[Algoritmos de Búsqueda II]])
## Agentes Híbridos
- **Definición:** Combinan la velocidad de los agentes reactivos con la capacidad de los agentes deliberativos o de planificación.
	- Dos o más, por ejemplo:
		- Uno deliberativo que contiene el mundo simbólico y desarrolla planes con toma de decisión a medio o largo plazo.
		- Uno reactivo, que reacciona a eventos sin razonamiento complejo.
- **Arquitectura:** Se estructuran en capas (ej. Máquinas de Touring de Ferguson: Capa de Modelado, Capa de Planificación, Capa Reactiva)
- **Control:** Un mecanismo decide qué subsistema y capa toma el control en cada instante, dando normalmente prioridad a los componentes reactivos ante emergencias.
## Agentes BDI (Belief, Desire, Intention)
- **Razonamiento Práctico**: Son agentes que evalúan qué hacer sopesando consideraciones conflictivas entre lo que desean y lo que creen, a diferencia del razonamiento puramente teórico.
- **Conceptos clave:**
	- **Creencias (Beliefs)**: Información y visión del mundo actual
	- **Deseos (Desires):** Opciones, valores y estados del mundo que el agente quiere alcanzar simultáneamente
	- **Intenciones (Intentions):** Deseos concretos con los que el agente ya se ha comprometido
	- **Planes:** Secuencias de acciones para cumplir dichas intenciones
- **Procesos principales:**
	1. **Deliberación** -> Identificar opciones (deseos) y filtrarlas para convertirlas en intenciones comprometidas.
	2. **Planificación (Means-end reasoning)**: Decidir el cómo cumplir esas intenciones. El resultado es un plan de acción.
- **Gestión del compromiso:**
	- **Mente cerrada (Single minded):** Persigue una intención hasta lograrla o hasta que sea imposible, sin mirar otras opciones.
	- **Mente abierta (Open-minded):** Reconsidera sus intenciones mientras actúa, ganando flexibilidad ante nuevas oportunidades *(Ejemplo: Un robot aspirador BDI se dirige a limpiar la cocina (intención original), pero si detecta que se derramó zumo en el pasillo (nueva creencia), abandona la cocina para limpiar el pasillo primero (reconsideración de intención))*.
	- **Meta-razonamiento:** Reconsiderar constantemente es costoso y puede impedir avanzar. El agente debe calcular cuán razonable es deternerse a replantear sus intenciones.
## Agentes Basados en Utilidad
- **Más allá de metas binarias:** A diferencia de los agentes de planificación donde un estado es "meta" (1) o "no meta" (0), estos agentes operan en entornos donde existen grados de deseabilidad , representados por una **función de utilidad** $U(s)$
- **Coste:** La preferencia sobre qué acciones tomar se formaliza con una función de coste, que actúa como una utilidad inversa.
- **Utilidad Esperada y Óptimo:** Un agente óptimo toma sus decisiones para maximizar la utilidad esperada de sus acciones futuras. Esto se formula matemáticamente ponderando la utilidad de los estados futuros por la probabilidad de alcanzarlos mediante una acción.$$a_k=argmax_{a_i\in A(s_p)}\sum_{j=1}^mp(s_j|ŕa_i)·EU_{max}(ŕa_is_j)$$
- **Racionalidad vs. Omnisciencia:** La racionalidad implica tomar la mejor acción dado el conocimiento e incertidumbre actual del agente, no significa que acierte perfectamente el futuro como si fuera omnisciente. 
## Agentes que aprenden
- **Adaptación:** Vitales en entornos cambiantes o desconocidos para mejorar continuamente su desempeño. Buscan ser más eficientes ("cómo hacerlo") o efectivos ("qué hacer").
- **Componentes de la arquitectura**:
	- **Análisis crítico** -> Evalúa los resultados reales obtenidos tras actuar comparándolos con las expectativas, usando una medida de evaluación.
	- **Revisión del modelo (aprendizaje)** -> Usa retroalimentación del crítico para actualizar el conocimiento del agente.
	- **Selección-acción (desempeño)** -> Elige la próxima acción basándose en el modelo ya ajustado/actualizado.
	- **Generador de descubrimiento** -> Propone acciones subóptimas a corto plazo para explorar nuevas situaciones beneficiosas a largo plazo, enfrentándose al dilema de exploración vs. explotación *(Ejemplo: Un recomendador como Spotify, en lugar de sugerir siempre la banda favorita del usuario (explotación), de vez en cuando sugiere un género totalmente distinto (exploración) para aprender si sus gustos se han expandido)*. 