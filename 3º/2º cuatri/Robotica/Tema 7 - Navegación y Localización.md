## Introducción a la Navegación y Localización

La base del funcionamiento robótico se describe a través del **ciclo "Ver-Pensar-Actuar"**:

- **Ver (Percepción):** Implica extraer información útil a partir de datos en bruto (_raw data_) capturados del entorno.
    
- **Pensar (Conocimiento):** Consiste en construir un mapa local y global, estimar la posición del robot (localización) y planificar trayectorias basadas en las tareas asignadas.
    
- **Actuar (Control de movimiento):** Ejecución de la trayectoria calculada mediante señales de control y actuación controlada sobre el mundo real.
    

Se definen dos conceptos clave:

- **Localización:** Consiste en estimar la posición y orientación actual del robot en el espacio.
    
- **Navegación:** Es el proceso de decidir cómo llegar desde un punto A hasta un punto B de la forma más segura y eficiente posible.
    

Dado que no existen sensores perfectos, la robótica requiere fusionar información para lograr estos objetivos en aplicaciones como robots aspiradores, coches autónomos o exploración planetaria.

---

## 1. Navegación Reactiva

La navegación reactiva es un enfoque clásico donde el robot interactúa de forma continua con el entorno a través de un bucle cerrado entre sensores y actuadores.

### Características Principales

- Toma decisiones en tiempo real ("aquí y ahora") basándose únicamente en la información sensorial del momento.
    
- No utiliza un mapa ni una representación interna del mundo, modelando el entorno de forma puramente simbólica.
    
- Es un sistema computacionalmente ágil, rápido y barato, con una escala de tiempo a corto plazo (si se equivoca, lo corrige en la siguiente decisión) y sin capacidad de predicción.
    
- Divide el mundo en situaciones mutuamente excluyentes, donde cada situación tiene una acción o actuación asociada.
    

### Desafíos y Limitaciones

- Requiere mecanismos de arbitraje o prioridades para decidir qué hacer cuando dos o más situaciones se solapan o activan simultáneamente.
    
- Pueden existir vacíos de control si ninguna situación se activa ante un estímulo.
    
- Presenta una escalabilidad limitada, ya que las situaciones posibles crecen exponencialmente al añadir más sensores, lo que requiere un enorme esfuerzo de diseño y programación.
    
- Al carecer de un modelo global, el robot es sensible al ruido y puede quedarse atrapado en bucles.
    
- No puede modelar situaciones que dependan de un estado interno (por ejemplo, comerse una manzana solo si se tiene hambre), lo que hace necesario definir estados.
    

### Máquinas de Estado Finito (FSM)

Para solucionar la necesidad de estados, se utilizan FSM, muy comunes en comportamientos robóticos simples.

- La navegación se modela mediante estados definidos (ej. "Avanzar recto", "Girar derecha") y transiciones condicionales basadas en eventos (ej. "Libre delante", "Obstáculo").
    
- Sus ventajas son que resultan sencillas de implementar, tienen un bajo coste computacional y son transparentes y fáciles de depurar.
    

---

## 2. Navegación Deliberativa: Mapas

A diferencia de la reactiva, la navegación deliberativa es robusta y flexible porque se basa en mapas y en la planificación, aunque requiere una localización precisa. Los mapas son necesarios para entender el entorno, localizar al robot y planificar trayectorias.

Para construir un mapa, el robot utiliza sensores que extraen características específicas (_features_, como bordes usando cámaras) o datos volumétricos (usando sensores LIDAR 2D). Los mapas muestran precisamente la relación entre estas características y la información volumétrica.

### Tipos de Mapas

El entorno se puede representar de forma exacta o relacional:

1. **Mapas Métricos:** Representan el espacio mediante coordenadas y mediciones (continuas o discretas), permitiendo una localización precisa, moverse con exactitud y planificar trayectorias finas.
    
2. **Mapas Topológicos:** Representan el mundo como un grafo de nodos y conexiones, mostrando solo la relación entre _features_ y hacia dónde ir, siendo muy útiles para entornos grandes y navegación simbólica de alto nivel. Sin embargo, por sí solos no explican cómo moverse detalladamente dentro de un nodo ni cómo reaccionar ante cambios.
    
3. **Mapas Métrico-Topológicos (Topomaps):** Combinan ambos enfoques. La parte topológica indica a dónde ir y la métrica explica cómo moverse.
    

### Mapas Basados en Celdas (Metric Grid Maps)

Es una forma clásica de discretizar un mapa métrico para equilibrar el nivel de detalle y el coste computacional. Existen tres enfoques para dividir el espacio en celdas:

- **Exact cell decomposition:** Divide el espacio basándose en la geometría y características del entorno, tendiendo a parecerse a un mapa topológico.
    
- **Fixed cell decomposition:** Utiliza un patrón fijo de celdas cuadradas, lo cual puede dar problemas en zonas estrechas si el tamaño de celda no es el adecuado.
    
- **Adaptive cell decomposition:** Utiliza celdas de tamaño variable, creando celdas grandes en espacios vacíos y celdas pequeñas cerca de los obstáculos.
    

---

## 3. Occupancy Grid Maps (Mapas Dinámicos)

Cuando no hay conocimiento previo del entorno, es un problema asumir un tamaño de mapa inicial, por lo que se emplean mapas dinámicos. Una técnica clásica es el **Occupancy Grid Map** (Elfes, 1987), que se basa en celdas de tamaño fijo.

- **Codificación visual:** Los píxeles negros representan paredes/obstáculos, los blancos indican espacio libre y los grises muestran áreas sin explorar.
    
- **Hipótesis de partida:** El mundo es estático, las celdas son independientes entre sí y una celda solo puede estar completamente libre o completamente ocupada.
    

### Funcionamiento Matemático y Lógico

El sistema registra la posición del robot y sus mediciones sensoriales, actualizando un contador para cada celda que entra en el campo de visión del sensor:

- Se utiliza una matriz de mapa $M$ y una matriz de contadores $C$.
    
    - $M=[\begin{matrix}M_{0,0}&\cdot\cdot\cdot&M_{m,0}\\ \vdots&\vdots&\vdots\\ M_{0,n}&\cdot\cdot\cdot&M_{m,n}\end{matrix}]$
        
    - $C=[\begin{matrix}C_{0,0}&\cdot\cdot\cdot&C_{m,0}\\ \vdots&\vdots&\vdots\\ C_{0,n}&\cdot\cdot\cdot&C_{m,n}\end{matrix}]$
        
- Cuando se observa una celda $(x,y)$, su contador $C_{x,y}$ se incrementa a $C_{x,y}+1$.
    
- Si el sensor detecta un obstáculo en esa celda, el valor $M_{x,y}$ se incrementa en $1$.
    
- Si el sensor detecta que está libre, el valor $M_{x,y}$ se reduce en $1$.
    
- Si $C_{x,y}=0$, la celda es desconocida (gris) y el robot debe explorarla.
    
- Si $C_{x,y}>0$, la probabilidad de ocupación se calcula con la fórmula:
    
    $P(Occ_{x,y})=\frac{M_{x,y}+C_{x,y}}{2C_{x,y}}$.
    
- Un valor positivo en la probabilidad indica que es más probable que esté ocupada, mientras que un valor negativo indica que es más probable que esté libre. Las celdas se colorean de blanco o negro en función de este resultado.
    

---

## 4. El Problema de la Localización

El documento concluye exponiendo una paradoja fundamental en la robótica deliberativa: **un robot no puede localizarse sin un mapa, pero tampoco puede construir un mapa sin tener información de su localización exacta (coordenadas x, y)**.

- La información puramente volumétrica suele ser insuficiente para localizarse de golpe, ya que un mismo conjunto de mediciones puede encajar en múltiples pasillos o habitaciones del mapa.
    
- Depender exclusivamente de la odometría (cálculo de posición basado en el giro de las ruedas) genera malos resultados, ya que los errores se acumulan rápidamente desviando la trayectoria.
    
- La solución óptima requiere el uso de marcadores únicos para estimar la localización y el desarrollo de sistemas que permitan construir el mapa a la vez que el robot se localiza en él.

# 