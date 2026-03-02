## Este tema
Aquí:
1. Se desarrolla y define el concepto de agente como un ente que actúa en un entorno
2. Se presentan las posibles características, tanto de agentes como de entornos y la interacción entre ambos.
3. Se da una introducción breve a los sistemas multi-agente (SMA) y a los retos, problemas y dificultades que se estudian y analizan en el área de los sistemas multi-agente.
## Introducción y objetivos
Las tendencias actuales en informática exigen sistemas caracterizados por la ubicuidad (presentes en todas partes, véase [[Inteligencia Ambiental y Computación Ubicua]]), adaptabilidad, delegación de tareas e inteligencia, así como una orientación clara hacia la interacción humana. 
- Esto ha impulsado un nuevo paradigma donde los sistemas informáticos asumen tareas que antes requerían intervención humana directa.
## Qué es un agente
Decimos que es un sistema informático que actúa de forma **autónoma** en un entorno para cumplir los objetivos con los que fue diseñado. Percibe dicho entorno a través de **sensores** y actúa sobre él mediante **actuadores**(véase [[Robótica]]). 

*Ejemplo ->* Robot aspiradora, que usa cámaras y sensores de choque para percibir la habitación, y motores para moverse y limpiar, operando sin control humano continuo.
## Características y agentes inteligentes
Para que un agente sea considerado inteligente, debe poseer las siguientes características:
- **Autonomía:** El agente determina su comportamiento y toma decisiones por sí mismo, pudiendo incluso adaptar o aprender de su experiencia sin intervención humana.
- **Reactividad:** Mantiene interacción continua con un entorno dinámico e incierto, detectando cambios y respondiendo a ellos adecuadamente.
- **Proactividad:** No solo reacciona, sino que genera sus propias metas y toma iniciativa para alcanzarlas a largo plazo.
- **Capacidad social:** Interactúa, se comunica y colabora (o negocia/argumenta) con otros agentes o humanos para lograr sus metas.
- **Racionalidad:** Busca realizar siempre la "mejor" acción posible para satisfacer sus objetivos basándose en su conocimiento y percepciones 
	Esto no es omnisciencia, un agente no conoce todo el universo, pero toma la decisión matemáticamente óptima dada la información imperfecta que posee.
- **Otras características deseables:** Veracidad (no mentir), benevolencia (perseguir siempre el objetivo encomendado), movilidad (física o en red) y adaptabilidad.
## Arquitectura abstracta de un agente
El diseño de un agente se aleja de la ejecución secuencial clásica y se basa en componentes interconectados:
- **Sensores y actuadores**: Definen qué puede percibir y qué acciones físicas o lógicas puede ejecutar
- **Memoria**: Almacena el conocimiento y la historia del mundo, actualizándose continuamente.
- **Objetivos**: El propósito que guía el comportamiento
- **Función de selección-acción**: Es la "mente" del agente. Relaciona memoria, percepciones, objetivos y acciones disponibles para elegir el siguiente paso.
**El ciclo de vida (programa básico) de un agente sigue estos pasos ordenados:**
1. Percibir el estado actual del entorno mediante la función `percibir()` que conecta a sus sensores.
2. Determinar el componente llamando a la función de selección-acción: `a = selección_acción(p, m, 0, A)`.
3. Ejecutar la acción elegida `ejecutar(a)` lo que referencia a los actuadores.
## El entorno de un agente
Es todo aquello que rodea al mismo, sobre lo que influye o por lo que es influenciado.
- **Propiedades claves del entorno**:
	- **Accesible vs. Inaccesible:** Depende de si el agente percibe el estado total (accesible), es decir que determina de forma inequívoca el estado, o solo una parte (inaccesible o parcialmente accesible)
	- **Determinista vs. No determinista:** Si las acciones del agente garantizan un resultado único (determinista), o si existe incertidumbre sobre los efectos (no determinista).
		- Cuando hay varios agentes, el entorno es determinista si el siguiente estado del sistema es completamente determinado por las acciones de todos los agentes en un momento dado.
		- Se entiende bien el concepto de determinista con el ajedrez, un entorno determinista, donde si tú (agente) decides mover el caballo a la casilla f3, este se moverá ahí mismo. No existe ráfaga de viento o tropiezo que impida al caballo de llegar. Tu acción es por ende directa e infalibre (no hay incertidumbre)
		- Un entorno no determinista sería el parchís, donde tú puedes tirar un dado, pero el resultado puede ser un 1, un 3, o un 6. No tienes un control certero y absoluto sobre el resultado, ahí está lo que llamamos incertidumbre.
	- **Estático vs. Dinámico:** Si el entorno solo cambia por el agente (estático), por otros procesos (dinámico) o si los cambios externos son totalmente previsibles al ser realizados por parte Interfacede otros agentes (semi-dinámicos)
	- **Discreto vs. Continuo:** Dependiendo de si existe un número finito de percepciones y acciones. Si lo hay, es discreto, si no, continuo.
		- Conducir es continuo y las damas por ejemplo, discretas.
**Espacio de estados**
En algunos entornos, la dinámica del mismo y las acciones del agente se entienden como transiciones en un grafo, siendo los nodos los estados y los arcos las acciones y sus consecuencias.
	- En otros entornos complejos, pueden existir transiciones sin la acción explícita del agente.
	- Y en otros aún más complejos, de la historia (el recorrido pasado)
**Modelización matemática del entorno y del agente**:
- El entorno se modela como un espacio de estados con la tupla $E=⟨S,A,T⟩$.
- $S$ representa las posibles situaciones (estados) y $A$ las acciones disponibles.
- **Recorrido ($R$)**: Secuencia histórica de estados y acciones ($s_0, a_0, s_1, a_1...$) desde el arranque.
- **Transición ($T$)**: La función $T: R(ag, E) \times A \rightarrow P(S)$ determina cómo cambia el entorno basándose en la historia y la acción actual. Al devolver un conjunto $P(S)$, modela entornos no deterministas.
- **Agente ($ag$):** Se define como una política de toma de decisiones $ag: R(ag, E) \times A \rightarrow [0, 1]$ 
	- Esto significa que el agente asigna una probabilidad matemática a cada acción. Si decide con certeza absoluta, la probabilidad es 1, comportándose de forma determinista.
## Cómo especificar los objetivos de un agente
Para saber si un agente tiene éxito, definimos una medida de rendimiento $Ren_E(r)$ que asigna un valor sobre un recorrido $r$ de un agente en el entorno $E$. A mayor, mejor.
- **Agentes basados en Tareas:**
	- **De mantenimiento**: Evitan que el entorno llegue a estados "negativos" (conjunto $B$). Su rendimiento cae a 0 si pisan un estado prohibido
	- **De metas:** Buscan alcanzar un subconjunto de estados deseables (conjunto $M$). Su rendimiento es 1 si llegan a la meta, o se mide por su eficiencia (ej. mínimo número de acciones).
- **Agentes basados en Utilidad:**
	- Operan con **preferencias** descritas por una función de utilidad $U(s)$ (cuánto "gusta" un estado) y una función de coste $C(s, a)$ (cuánto "cuesta" una acción)
	- La utilidad global del recorrido suele ser la suma de las utilidades de los estados menos la suma del coste de las acciones. 
- **El agente óptimo:** En entornos con incertidumbre, no podemos garantizar un recorrido concreto. Por ello, se calcula la **utilidad esperada** (multiplicando la probabilidad de cada recorrido por su rendimiento). El agente óptimo (racional) es aquel que elige sistemáticamente la política que maximiza esta utilidad esperada. 
	- Esto se representa con la fórmula $$E[Ren(ag, E)]=\sum r\in R(ag, E) \space p(r|ag, E) · Ren_E(r)$$$$\sum 𝑠𝑖∈R \sum 𝑟∈R(𝑎𝑔,𝐸) 𝑝(𝑟|𝑎𝑔, 𝐸, 𝑠𝑖) ∙ 𝑅𝑒𝑛𝐸 𝑟$$
	- Donde $p(r|ag, E, s_i)$ es la probabilidad de que ocurra el recorrido si el agente ag está puesto en el entorno E en el estado si
	- Y $p(r|ag, E)$ es la probabilidad de que ocurra el recorrido r si el agente ag está puesto en el entorno E (en algún estado inicial)
## Sistemas multiagente
Cuando múltiples agentes habitan el mismo entorno, las reglas cambian:
- **De Micro a Macro:** Las acciones individuales configuran el estado global. Un agente ya no solo interactúa con un entorno inerte, sino que depende de las acciones de los demás para cumplir con sus objetivos.
- Dado que no puedo controlar a otros agentes (por su autonomía), debe predecirlos y coordinarse con ellos (sociabilidad)
## Retos en agente y sistemas multiagente
- En el diseño individual (**Agentes**)
	- Ética -> Explicabilidad y alineación con valores
	- Metodologías y arquitecturas -> Diferentes tipos de problemas
	- Toma de decisión -> Algoritmos para selección-acción
- A nivel global (**SMA**)
	- Diseño de mecanismos de comunicación -> Ontologías, véase [[Representación del Conocimiento y Razonamiento I]]
	- Comportamientos emergentes (confianza, reputación...)
	- Toma de decisiones colectivas (negociación, coaliciones...)
## Netlogo
Entorno para programar y ejecutar simulaciones de sistemas uni o multiagente. Su interfaz gráfica consta de:
- **Interface**: Permite controlar parámetros y ejecutar la simulación con botones `setup` (configura todo) y `go` (ejecuta continuamente)
- **Info:** Proporciona explicaciones sobre el modelo.
- **Code:** Contiene el código fuente que define las reglas.
