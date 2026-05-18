## El Ciclo "Ver-Pensar-Actuar"
Es el núcleo del funcionamiento de cualquier robot móvil.
- **Percepción (Ver):** El robot percibe el entorno y extrae información de los datos brutos (_raw data_) para construir un mapa local.
- **Localización y Mapeo (Pensar):** Con el mapa local y el conocimiento previo, el robot estima su posición y construye un mapa global.
- **Planificación y Control (Actuar):** Se planifica una trayectoria basada en las tareas asignadas. El control de movimiento traduce esto en señales para los actuadores, resultando en una actuación controlada en el mundo real.

---
## Robots Terrestres: Ruedas y Orugas
Son los más populares por su eficiencia y sencillez.
- **Tipos de ruedas:**
	- **Motriz:** Conectada a actuador, proporciona fuerza de tracción.
	- **Pasiva (*caster*)**: No está conectada al actuador, facilita equilibrio y apoyo.
	- **Mecanum:** Equipada con rodillos a ángulo de 45º respecto al plano de rotación, permite movimientos laterales, diagonales y rotación in situ
	- **Oruga:** Correa continua que se desplaza sobre conjunto de rodillos o ruedas, permite distribuir la carga, mejorando tracción y estabilidad.
- **Configuraciones de Ruedas:**
    - **Diferencial:** Dos ruedas motrices independientes; es fácil de controlar pero sensible a pequeñas variaciones de velocidad.
    - **Ackermann:** Utilizada en automóviles; ofrece gran estabilidad en altas velocidades pero tiene poca maniobrabilidad en espacios reducidos.
    - **Omnidireccional (Mecanum):** Ruedas con rodillos a $45^{\circ}$ que permiten movimientos laterales, diagonales y rotación sobre su eje.
    - **Orugas:** Ideales para terrenos difíciles, ya que distribuyen mejor la carga y mejoran la tracción.
- **Cinemática y Odometría:** Se presentan las ecuaciones para calcular la posición $(x, y)$ y orientación $(\theta)$ de un robot diferencial a partir de las velocidades angulares de sus ruedas. La **odometría** estima esta posición a lo largo del tiempo, aunque acumula errores por deslizamientos o irregularidades del terreno

---
## Robots con Piernas
Se utilizan para superar obstáculos inaccesibles para las ruedas.
- **Complejidad:** Requieren coordinar múltiples grados de libertad (GDL) y sistemas de percepción avanzados.
- **Tipos de Marcha:**
    - **Estática:** El robot es estable incluso si se detiene; siempre tiene al menos tres apoyos.
    - **Dinámica:** Más rápida y eficiente, pero el robot debe estar en constante movimiento para no caerse (menos de tres apoyos).
- **Modelado:** Se utilizan modelos de **péndulo invertido** o de **muelle-masa** para simular la locomoción bípeda.

---
## Robots Aéreos y Acuáticos
- **Aéreos:** Vehículos no tripulados (UAV) que se mueven en 3D. Se clasifican en **multirotores** (baja autonomía), **ala fija** (vuelos largos) e **híbridos**. Su control depende de los ángulos de rotación: _Pitch_ (cabeceo), _Roll_ (alabeo) y _Yaw_ (guiñada).
- **Acuáticos:** Operan en medios más densos que el aire, enfrentando corrientes y efectos de flotabilidad. Incluyen submarinos para inmersión profunda y robots inspirados en animales acuáticos para mayor maniobrabilidad.
