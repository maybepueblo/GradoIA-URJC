## Este tema
Si bien en el [[Tema 2 - Tipos de agentes]], vimos agentes basados en utilidad que intentan realizar acciones que maximicen dicha utilidad de su recorrido en un entorno, ahora veremos en más detalle un caso concreto de estos: los agentes que toman decisiones y actúan en entornos modelables mediante **Procesos de Decisión de Markov**
## Introducción y conceptos básicos
Los agentes basados en utilidad buscan maximizar la utilidad de su recorrido a través de sus acciones. En este tema, el problema central es encontrar **la política de control óptima** de un agente autónomo para obtener la máxima recompensa acumulada a lo largo de su ciclo de vida. 
- **Asunciones del entorno:** Se modela bajo un entorno accesible (percepción total y discreta) y estacionario (las probabilidades no cambian con el tiempo). Además, el agente elige acciones de forma determinista.
- **Objetivo matemático**: Maximizar la suma de utilidades de los estados menos el coste de las acciones: $U(r)=\sum_{s_i\in s(r)}U(s_i)-\sum_{s_ia_i\in sa(r)}C(s_i,a_i)$ Siendo $S$ el conjunto de estados y $A$ el conjunto de posibles acciones.
## Procesos de Decisión de Markov (MDP)
Es un marco formal para modelar la toma de decisiones en entornos secuenciales no completamente deterministas. Se define matemáticamente mediante una tupla $<S,A,T,R>$:
- **$S$**: conjunto de estados posibles
- **$A$**: conjunto de acciones posibles
- **$T$ (Modelo de transición)**: Distribución de probabilidad $T: S \times A \times S \rightarrow [0..1]$ donde $T(s,a,s')=Pr(s'|a, s)$ denota la probabilidad de llegar a $s'$ al hacer la acción $a$ en $r$ 
- **$R$ (Modelo de recompensa)**: Función $r: S \times A \times S \rightarrow R$ que refleja la recompensa inmediata obtenida al transitar de $s$ a $s'$ tras ejecutar $a$. Equivale a la utilidad menos el coste: $R(s, a, s')=U(s')-C(s,a)$
- **Propiedad de Markov:** Esencial. Establece que la probabilidad de llegar a un estado y su recompensa dependen solo del estado y acción inmediatos anteriores, sin importar el historial (proceso sin memoria)
- **Política ($\pi$)**: Es la función $S \rightarrow A$ que dicta qué acción tomar en cada estado. La política óptima ($\pi^*$) es la que maximiza la recompensa acumulada esperada futura.
- **Factor de descuento ($\gamma$)**: Constante $0\leq\gamma \lt1$ que ajusta el peso de las recompensas futuras en la suma $r_t+\gamma r_{t+1}+\gamma^2 r_{t+2}+....$.
	- Se introduce $\gamma$ porque refleja el comportamiento real frente a la incertidumbre (preferimos recompensas seguras e inmediatas en vez de futuras inciertas) y garantiza que la suma matemática infinita de recompensas converja a un valor finito. Un $\gamma=0$ crea un agente "miope" y según se acerca a 1, el agente se vuelve más precavido pensando a largo plazo.
## Funciones de Valor y Ecuaciones de Optimalidad
Para calcular $\pi^*$, necesitamos funciones que evalúen sus opciones teniendo en cuenta que el entorno puede ser NO determinista (requeriendo calcular valores esperados probabilísticos $E[X]=\sum_{x_i\in X}x_i·p(x_i)$)
- **Función valor estado ($V^*(s)$):** La máxima recompensa acumulada esperada a partir de un estado $s$.
	- Ecuación: $V^*(s)=max_{a\in A(s)}Q^*(s, a)$ (0 si no hay acciones aplicables)
- **Función valor estado-acción ($Q^*(s,a)$):** La máxima recompensa acumulada esperada al ejecutar la acción $a$ en el estado $s$ y seguir la política óptima después.
	- Ecuación: $Q^*(s, a)=\sum_{s'\in S}T(s, a, s')·[r(s, a, s') + \gamma · V^*(s')]$ 
- **Cálculo de la política óptima ($\pi^*$)** Se extrae simplemente eligiendo la acción que devuelva el mayor valor $Q^*: \pi^*(s)=argmax_{a\in A(s)}Q^*(s,a)$.
- **Ecuación de optimalidad de Bellman:** Fusionando las fórmulas anteriores, define un sistema de ecuaciones con solución única iterativa:$$Q^*(s,a)=\sum_{s'\in S}T(s, a, s')·[r(s,a,s')+\gamma·max_{b\in A(s')}Q^*(s', b)]$$
## Algoritmo de Iteración de Valores
Es un algoritmo de programación dinámica diseñado para resolver MDP calculando los valores $Q^*$, y por extensión, $\pi^*$ y $V^*$.
1. **Inicialización:** Configurar $Q^*(s,a):=0$ para todos los estados s y sus acciones $a$ aplicables.
2. **Bucle principal (Repetir)**
	1. Guardamos el valor actual: `old := Q*(s, a)`
	2. Actualizamos el valor aplicando la ecuación de Bellman: $Q^*(s,a)=\sum_{s'\in S}T(s, a, s')·[r(s,a,s')+\gamma·max_{b\in A(s')}Q^*(s', b)]$
	3. Comprobamos el criterio de parada: Si la diferencia absoluta $|old - Q^*(s, a)| \gt [cite_start]\sigma$ siendo $\sigma$ un margen de error positivo, marcamos `seguir=true`.
3. **Condición de salida**: Hasta que `not(seguir)`(cuando los valores ya no cambian significativamente entre iteraciones).
4. **Retorno:** El algoritmo devuelve $Q^*$ estabilizado, permitiendo extraer $V^*(s)=max_{a\in A(s)}Q^*(s, a)$ y la política $Q^*: \pi^*(s)=argmax_{a\in A(s)}Q^*(s,a)$.
## Aplicación a Metas, Extensiones y Limitaciones
- **Adaptación a metas:** Los MDP pueden guiar agentes basados en metas configurando estratégicamente las recompensas. (Ejemplo: En un laberinto, asignar +100 por llegar a la salida (meta) y penalizar con un coste de paso de −1 cada movimiento que no sea la salida directa, forzando al algoritmo a buscar el camino más corto.)
- **Convergencia:** El algoritmo siempre converge hacia la política óptima correcta siempre que el factor de descuento $γ$<1.
- **Extensión POMDP:** Los _Partially Observable MDP_ abordan escenarios donde el agente no tiene certeza absoluta del estado resultante tras su acción, requiriendo manejarse con probabilidades de observación (ej. jugar al Póker).
- **Limitaciones críticas:** Las suposiciones de modelo completo, correcta percepción y estacionariedad son restrictivas frente a la realidad de entornos dinámicos e imperfectos. Además, en problemas reales complejos, la explosión combinatoria del número de estados y acciones genera graves problemas de memoria para computar la solución.