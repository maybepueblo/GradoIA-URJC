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