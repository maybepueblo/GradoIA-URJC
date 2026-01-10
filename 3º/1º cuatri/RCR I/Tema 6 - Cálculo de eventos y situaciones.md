## 1. El Problema de la Lógica Clásica

La Lógica de Primer Orden estándar es estática. Si decimos Encendida(Luz), es verdad para siempre. Pero en el mundo real, las cosas cambian (la luz se apaga). Para modelar esto, necesitamos formalismos que manejen la dinámica2222.

Existen dos grandes enfoques que veremos aquí:+1

1. **Cálculo de Eventos (Event Calculus - EC):** Se basa en una línea de tiempo lineal y narrativa (qué pasó y cuándo).
    
2. **Cálculo de Situaciones (Situation Calculus - SC):** Se basa en secuencias de acciones hipotéticas (qué pasaría si hago esto y luego aquello).
    

---

## Parte A: Cálculo de Eventos (Event Calculus)

### 1. Conceptos Fundamentales

El Cálculo de Eventos (EC) modela una **línea de tiempo única** sobre la que ocurren cosas. Se basa en **narrativas** (historias de lo que ha pasado)3.

Sus tres componentes básicos (Sorts) son 4:

1. **Eventos ($e$):** Acciones puntuales (ej: `encender_interruptor`).
    
2. **Fluents ($f$):** Propiedades que cambian con el tiempo (ej: `luz_encendida`).
    
3. **Instantes de tiempo ($t$):** Momentos concretos ($0, 1, 5, \dots$).
    

### 2. La Ley de Inercia del Sentido Común

Este es el principio vital del EC: "Las cosas se mantienen igual a menos que algo las cambie".

Si enciendo la luz en el tiempo 1, seguirá encendida en el tiempo 2, 3, 4... hasta que ocurra un evento de "apagar". El EC incorpora esta ley automáticamente5.

### 3. Basic Event Calculus (BEC)

Es la versión estándar (Shanahan, 1998). Vamos a explicar sus predicados clave con lenguaje humano 6666:

+1

- **Estados Iniciales:**
    
    - `InitiallyP(f)`: El fluent $f$ empieza siendo VERDADERO.
        
    - `InitiallyN(f)`: El fluent $f$ empieza siendo FALSO.
        
- **Lo que pasa:**
    
    - `Happens(e, t)`: El evento $e$ ocurre en el instante $t$.
        
- **Causa y Efecto:**
    
    - `Initiates(e, f, t)`: El evento $e$ hace que $f$ se vuelva **verdadero** (empieza a ser cierto).
        
    - `Terminates(e, f, t)`: El evento $e$ hace que $f$ se vuelva **falso** (termina).
        
- **Estado Actual:**
    
    - `HoldsAt(f, t)`: ¿Es verdad el fluent $f$ en el momento $t$? (Esta es la pregunta que solemos hacer al sistema).
        
- **Excepciones a la inercia (Avanzado):**
    
    - `Releases(e, f, t)`: El evento "libera" al fluent de la ley de inercia. A partir de aquí, el fluent puede cambiar solo (continuamente) sin eventos discretos.
        
    - `Trajectory(...)`: Modela cambios continuos (ej: si tiras una pelota, su altura cambia sola con el tiempo).
        

#### Los Axiomas del BEC (La lógica interna)

El sistema usa 7 axiomas (reglas) para deducir la verdad. Explicación simplificada de los más importantes 7:

1. **StoppedIn:** Un fluent se "detiene" si ocurre un evento que lo termina (Terminates) o lo libera (Releases) en medio de un intervalo.
    
2. **StartedIn:** Un fluent "empieza" si ocurre un evento que lo inicia.
    
3. **HoldsAt (Axioma BEC4 y BEC6):** Un fluent es verdadero en el tiempo $t$ si:
    
    - Era verdadero al principio y nada lo ha detenido (`InitiallyP` + no `StoppedIn`).
        
    - O bien, un evento lo inició antes de $t$ y nada lo ha detenido desde entonces (`Initiates` + no `StoppedIn`).
        

### 4. Ejemplo Práctico (La Luz)

- **Hechos:** La luz empieza apagada. `turn_on` inicia `light_on`. `turn_off` termina `light_on`.
    
- **Narrativa:** Alguien pulsa `turn_on` en $t=1$.
    
- **Pregunta:** ¿`HoldsAt(light_on, 5)`?
    
- **Razonamiento:** Como se inició en 1 y no hubo evento de apagado (`StoppedIn` es falso), la inercia dice que en 5 sigue encendida 8.
    

5. Otras Versiones del EC 9

- **OEC (Original):** Usa periodos de tiempo, no puntos. Más rígido.
    
- **SEC (Simplified):** Más simple, elimina conceptos complejos como fluents incompatibles.
    
- **DEC (Discrete):** Usa números enteros para el tiempo. Muy eficiente computacionalmente.
    

---

## Parte B: Cálculo de Situaciones (Situation Calculus)

### 1. Conceptos Fundamentales

A diferencia del EC (línea de tiempo), el Cálculo de Situaciones (SC) modela árboles de futuros posibles.

La idea clave es: Una "Situación" no es un momento en el reloj, es la historia completa de acciones que nos ha llevado hasta allí 10101010.+1

- **$S_0$**: La situación inicial (antes de hacer nada).
    
- **$do(a, s)$**: La función mágica. Devuelve la _nueva situación_ resultante de hacer la acción $a$ en la situación $s$.
    
    - _Ejemplo:_ `do(recoger_vaso, S0)` es una situación nueva.
        
    - _Ejemplo anidado:_ `do(beber, do(recoger_vaso, S0))` es la situación tras recogerlo y beber.
        

### 2. Componentes del Modelo

Para definir un mundo en SC necesitamos 11:

1. **Fluents Relacionales:** Propiedades que dependen de la situación. Se escriben como `holds(fluent, s)`.
    
    - Ej: `holds(robot_en_cocina, s)`.
        
2. **Predicado `Poss(a, s)`:** Define si es **posible/legal** hacer la acción $a$ en la situación $s$.
    
3. **Axiomas de Efecto:** Qué cambia tras una acción.
    
    - Positivos: La acción hace algo verdadero.
        
    - Negativos: La acción hace algo falso.
        

### 3. El Problema del Marco (The Frame Problem)

En SC, si defines que "Pintar el coche cambia su color", la lógica es tonta y olvida todo lo demás. Podría pensar que al pintar el coche, el coche deja de tener ruedas o el motor desaparece.

- **Problema:** Tienes que escribir reglas para decir qué cosas **NO cambian** (Axiomas de Marco).
    
- **Solución:** Escribir muchos axiomas de marco o generarlos automáticamente 12.
    

4. Tareas de Razonamiento en SC 13

Con este sistema podemos pedirle a la IA tres cosas:

1. **Proyección (Predicción):**
    
    - _"Si estoy en $S_0$ y ejecuto la secuencia [avanzar, girar, avanzar], ¿dónde estaré?"_
        
    - Se calcula: $KB \models \Phi(do(avanzar, do(girar, do(avanzar, S_0))))$.
        
2. **Testeo de Legalidad:**
    
    - _"¿Es posible ejecutar esa secuencia o alguna acción viola sus precondiciones?"_
        
    - Se comprueba `Poss(a, s)` paso a paso.
        
3. **Planificación (Planning):**
    
    - _"Estoy en $S_0$, encuéntrame la secuencia de acciones $\bar{a}$ para llegar a un objetivo (Goal)"_.
        
    - Es la tarea más potente: busca un camino en el árbol de situaciones.
        

4. Ejemplo Práctico: El Robot en las Estaciones 14

Las diapositivas presentan un robot que se mueve en una línea (estaciones 1 a 6).

- **Acciones:** `forward` (avanzar) y `turn` (dar la vuelta).
    
- **Precondiciones (`Poss`):**
    
    - Solo puedes hacer `forward` si no estás en el borde (si estás en la 6 mirando al Este, no puedes avanzar)15.
        
- **Efectos:**
    
    - Si haces `forward` mirando al Oeste, tu posición pasa de $N$ a $N-1$ 16.
        
    - Si haces `turn`, tu dirección cambia (de Este a Oeste)17.
        
- **Axiomas de Marco:**
    
    - Si haces `turn`, tu posición NO cambia (sigues en la misma estación)18. _Esto es vital para que el robot no se teletransporte al girar._
        

---

## Resumen Comparativo Final

| **Característica**    | **Cálculo de Eventos (EC)**                      | **Cálculo de Situaciones (SC)**               |
| --------------------- | ------------------------------------------------ | --------------------------------------------- |
| **Base del Tiempo**   | Línea de tiempo real ($0, 1, 2...$).             | Secuencias de acciones ($do(a,s)$).           |
| **Enfoque**           | **Narrativo:** Qué ha ocurrido.                  | **Hipotético:** Qué pasaría si...             |
| **Manejo de Inercia** | Automático (predicados `Initiates`, `Releases`). | Manual/Complejo (Axiomas de Marco).           |
| **Uso ideal**         | Monitorización, historias, tiempo continuo.      | Planificación de robots, control, proyección. |
