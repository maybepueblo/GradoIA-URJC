1. Procesos de Decisión de Markov (MDP) y Q-Learning (Temas 3 y 4)

**Definición y bases de un MDP:**

- **Tupla MDP:** Todo MDP se define como ⟨S,A,T,R⟩ donde S son los estados, A las acciones, T(s,a,s′)  es el modelo de transición (probabilidades) y R(s,a,s′) es el modelo de recompensas.
- **Propiedad de Markov:** Proceso "sin memoria". La probabilidad de un estado futuro y su recompensa solo depende del estado y acción actuales: Pr(st+1​,rt+1​∣at​,st​).

**Cálculo con MDP conocido (Iteración de Valores / Ecuación de Bellman):**

- **Función Valor-Estado-Acción (**Q∗**):** Q∗(s,a)=∑s′∈S​T(s,a,s′)⋅[r(s,a,s′)+γ⋅maxb∈A(s′)​Q∗(s′,b)].
- **Valor de un estado (**V∗**):** V∗(s)=maxa∈A(s)​Q∗(s,a) (el valor de la mejor acción en ese estado).
- **Política óptima (**π∗**):** π∗(s)=argmaxa∈A(s)​Q∗(s,a) (la acción que te da ese valor máximo).
- 💡 **Truco:** Aquí multiplicas el corchete (recompensa inmediata + futuro descontado con γ) por la probabilidad exacta T de esa transición.

**Cálculo sin modelo conocido (Aprendizaje por Refuerzo / Q-Learning):**

- **Entornos Deterministas:** Q(s,a)=r+γ⋅maxb∈A(s′)​Q(s′,b).
- **Entornos No Deterministas:** Incluye la tasa de aprendizaje α. Se calcula actualizando el valor anterior con la nueva información: Q(s,a)=(1−α)⋅Q(s,a)+α(r+γ⋅maxb∈A(s′)​Q(s′,b)).
- 💡 **Truco:** Si el enunciado te da α, usa la fórmula no determinista ponderando el valor antiguo y el nuevo. Trabaja siempre en orden o de atrás hacia adelante según los datos que te den.

--------------------------------------------------------------------------------

2. Algoritmo de Subastas de Bertsekas (Tema 7)

- **Cálculo de Costes:** Para cada agente ai​ y tarea tj​: coste(ai​,tj​)=c(ai​,tj​)+precio(tj​). _(Ojo, el precio inicial suele ser 0)_.
- **Cálculo de la Puja:** Identifica la tarea de menor coste (tmejor​) y la segunda de menor coste (tsegunda​). La puja para la tarea óptima es: pujaai​​=coste(tsegunda​)−coste(tmejor​).
- **Actualización:** El nuevo precio de la tarea ganadora será precio(tj​)=precio(tj​)+pujaai​​, y se asigna a este agente. Si otro agente la tenía asignada, queda libre.
- 💡 **Truco:** ¡Vital! Si hay un empate entre dos o más tareas con el mismo coste mínimo, **el agente puja por la tarea con la menor numeración** (ej. T1 antes que T2).

--------------------------------------------------------------------------------

3. Confianza y Reputación (Tema 8)

- **Reputación basada en recomendadores (**raRA​**):** Suma de (experiencia × fiabilidad) dividida entre la suma de las fiabilidades de quienes recomiendan: raRA​=∑fb​∑(eb​⋅fb​)​.
- **Confianza Global (**ca​**):** Combina tu experiencia directa local (ea​) ponderada por tu fiabilidad en ti mismo (fa​), con la reputación calculada (raRA​): ca​=fa​⋅ea​+(1−fa​)⋅raRA​.
- 💡 **Truco:** Resuelve la fórmula en dos pasos. Primero calcula la reputación de los terceros resolviendo la fracción (cuidado con dividir bien solo por las fb​ de los recomendadores activos). Luego aplícalo en la ecuación global.

--------------------------------------------------------------------------------

4. Juegos Extensivos y Negociación (Tema 10)

- **Algoritmo de Zermelo (Inducción hacia atrás):** Ve a los últimos nodos de decisión (antes de los pagos finales). Elige la rama que le dé el mayor pago al jugador al que le toca decidir. Reemplaza ese nodo por los pagos elegidos y sube un nivel. Repite hasta la raíz.
- **Equilibrio Perfecto en Subjuegos (EPS):** El camino trazado por el Algoritmo de Zermelo te da el EPS único.
- 💡 **Truco:** Todo EPS es un Equilibrio de Nash, pero hay Equilibrios de Nash que no son EPS porque implican "amenazas no creíbles" en subjuegos a los que nunca se llegaría. Justifica siempre tus decisiones mirando quién maximiza su utilidad en cada turno.

--------------------------------------------------------------------------------

5. Sistemas de Votación (Tema 11)

_(Basado en nuestro repaso anterior)_

- **Pluralidad:** Cuenta solo la primera preferencia de cada votante. Gana quien tenga más.
- **Ganador de Condorcet:** Analiza duelos 1 vs 1 entre todos los candidatos. Gana el que vence a **todos** los demás por mayoría. Puede que no exista.
- **Pluralidad con Eliminación (Instant Runoff):** Si nadie tiene mayoría absoluta como 1ª opción, elimina al que tenga **menos** votos en primer lugar. Reasigna esos votos a la segunda opción de esos votantes. Repite hasta que alguien tenga mayoría absoluta.
- 💡 **Truco para Condorcet:** Sé metódico. Escribe "A vs B", "A vs C", "B vs C". Suma los bloques de votos de la tabla comprobando quién está por encima en cada columna.