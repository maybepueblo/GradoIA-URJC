## Este tema
Si bien en [[Tema 3 - Agentes basados en Procesos de Decisión de Markov]] vimos todo lo que tiene que ver con agentes que tienen conocimiento completo del entorno, en muchos casos no conocemos esto mismo. 

Por ello, en este tema veremos agentes que NO tienen ese conocimiento pleno, pero que aprenden dicha política mediante aprendizaje por refuerzo. 
## Introducción y conceptos fundamentales
Aquí los agentes de Aprendizaje por Refuerzo (RL) actúan en entornos de decisiones secuenciales modelables como MDP pero sin **conocimiento completo del entorno**.
- **Elementos del entorno:** Un conjunto de estados $S$ (posiblemente desconocido), un conjunto de acciones $A$ (parcialmente conocido), un modelo de transición $T:S\times A\times S\rightarrow [0..1]$ (desconocido) y un modelo de recompensas $r:S\times A\times R\rightarrow R$ (desconocido)
- **Objetivo principal:** Aprender mediante "prueba y error" la **política óptima** que maximiza las recompensas acumuladas esperadas basándose en el refuerzo recibido.
- **Enfoques principales:**
	- **Métodos libres del modelo:** Solo se intenta aprender la política óptima directamente (ej. Q-learning)
	- **Métodos basados en el modelo**: Se aprende simultáneamente el modelo del entorno (transiciones y recompensas) y se usa para actualizar la política.
## Algoritmo "Q-Learning"
El núcleo de este método libre de modelo es aprender una función Q que aproxime la función real $Q^*$ actualizándola dinámicamente, episodio tras episodio. La política final del agente se determina eligiendo siempre la acción con mayor valor: $\pi (s)=argmax_{a\in A(s)}Q(s, a)$
	La función Q representa la calidad o recompensa futura esperada de tomar una acción específica en un estado específico. Esencialmente, el agente construye una tabla de consulta mental para saber qué hacer en cada situación.

**Proceso del Algoritmo Q-Learning en un entorno determinista**
1. Observamos el estado $s$ actual del entorno
2. Si $s$ es un estado desconocido, inicializamos el valor $Q(s,a)$ en la memoria para todas las acciones $a$ posibles en ese estado.
3. Seleccionamos una acción $a$ basada en una política de selección (ej. greedy) y la ejecutamos
4. Recibimos la recompensa $r$ y observamos el nuevo estado $s'$
5. Si el estado $s'$ es desconocido, inicializamos el valor $Q(s',b)$ para todas las acciones posibles en $s'$
6. Actualizamos el valor $Q$ usando la ecuación: $Q(s,a)=r+\gamma · max_{b\in A(s')}Q(s',b)$
7. Actualizamos el estado actual $s\leftarrow s'$ y repetimos el ciclo hasta llegar a un estado terminal.
## Selección de acciones: Exploración vs. Explotación
Es un desafio ver si explotamos el conocimiento actual o exploramos nuevas acciones que podrían ofrecer mejores recompensas. Si no se explora lo suficiente, el agente puede aprender una ruta funcional pero subóptima.
- **Política "Greedy"**, véase [[Algoritmos]] -> Elige siempre la acción con el mayor valor Q. Tiene el grave riesgo de sobre-explotar acciones tempranas decentes ignorando rutas potencialmente mejores.
- **Política "ϵ-greedy"** -> Equilibra el proceso eligiendo la mejor acción Q con probabilidad 1 - ϵ y una acción aleatoria con probabilidad ϵ.
- **Política "Softmax"** -> Asigna probabilidades a las acciones basándose en su valor Q, usando un parámetro de temperatura $τ$. La probabilidad de elegir la acción $a$ en el estado $s$ es:$$\frac{e^{Q(s,a)/τ}}{Σ_{b∈A(s)}​e^{Q(s,b)/τ}}​$$
	- Una temperatura $τ$ alta aumenta la probabilidad de exploración aleatoria.
	- Una temperatura $τ$ tendiendo a 0 favorece fuertemente las acciones con mayor valor Q.
- **Decadencia (Decay)**: Modificación del comportamiento humano donde $ϵ$ o $τ$ se reducen con el tiempo (explorar más al principio, explotar más al final)
## Estrategias de Inicialización
La forma en la que se inicializan los valores $Q(s,a)$ en la tabla también influye profundamente en la exploración:
- **Optimista:** Valores iniciales altos, por encima de los reales. Promueve fuertemente la exploración.
	- *Ejemplo* -> Si todo empieza en +20 pero las recompensas reales son bajas o negativas, el agente probará de forma repetida nuevas acciones buscando ese +20 ilusorio, asegurando una exploración exhaustiva antes de ajustar sus valores a la baja.
- **Pesimista:** Valores bajos, por debajo de los reales. Conduce a una menor exploración.
- **Neutra:** Inicialización equilibrada en 0, o asignando las recompensas si se conocen a priori.
## Entornos No Deterministas (El Algoritmo Genérico)
En estos entornos, ejecutar una acción $a$ en el estado $s$ puede llevar a múltiples estados ($s'$ o $s''$) con probabilidades desconocidas. La fórmula determinista falla aquí porque toma el máximo absoluto de la rama observada en lugar del valor esperado combinado probabilísticamente.

Para corregirlo, el algoritmo Q-Learning genérico usa el valor $Q(s,a)$ integrando la nueva información de forma paulatina mediante una constante de aprendizaje $\alpha$ (donde $0 \lt \alpha \leq 1$):
$$Q(s,a)=(1−α)⋅Q(s,a)+α[r+γ⋅max_{b∈A(s')}​Q(s',b)]$$
- Esta formula es una media ponderada entre la estimación anterior (el conocimiento acumulado) y la nueva observación.
- Un valor alto de $\alpha$ permite cambios rápidos, mientras que un valor bajo prioriza la precisión a largo plazo.
## Convergencia y limitaciones
El aprendizaje puede darse de manera online (en vivo) u offline (en simulación antes de aplicarlo al mundo real, lo cual es preferible). Q-Learning garantiza teóricamente converger a la función óptima $Q^*(s, a)$ si se cumplen cuatro condiciones:
1. El entorno es modelable como un MDP
2. La constante de aprendizaje $\alpha$ disminuye en el tiempo cumpliendo que $Σ_{i=0}^∞ ​α_i​=∞$ y $Σ_{i=0}^∞​ α_i^2​<∞$ (por ejemplo, $α=1/n(s,a)$)
3. Todas las parejas (estado, acción) se visitan un número infinito de veces.
4. El entorno es estacionario (las probabilidades de transición no varían en el tiempo)
	- **El gran problema:** Almacenar una tabla con valores para cada par estado-acción es inmanejable en dominios grandes (por ejemplo, el ajedrez tiene $10^{43}$ estados)
	- **Soluciones y extensiones**: Representaciones compactas, aprendizaje basado en el modelo y *Deep Q-learning* para manejar espacios continuos o gigantescos.
