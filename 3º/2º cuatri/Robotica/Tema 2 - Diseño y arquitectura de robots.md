## Definición de la tarea y del entorno de trabajo

### Definición de la Tarea
La **tarea** especifica qué realizará el robot:
- Transporte de objetos
- Manipulación de herramientas
- Interacción con personas
- Entretenimiento y ocio
- Otras actividades específicas

**Parámetros clave a definir:**
- Precisión y rapidez requeridas
- Grado de autonomía del robot
- Interacción con humanos u otros robots (colaboración humano-robot)
### Definición del Entorno de Trabajo
El **entorno** determina dónde operará el robot:
- Interior o exterior
- Tamaño del área de trabajo
- Condiciones ambientales: temperatura, luz, ruido, humedad
- Factores ambientales extremos (si existen)
- Interacción con otros elementos (obstáculos, personas)
- Alimentación: conectado a electricidad o autónomo
- Conectividad: conectado a Internet u offline
### Importancia de estas Definiciones
Son **críticas** porque:
- Determinan la morfología, sensores y actuadores necesarios
- Permiten optimizar la selección de componentes
- Facilitan la programación del robot
- Definen la estructura general del sistema
- Cada robot debe diseñarse **a medida** para una tarea y entorno específicos
- Es difícil generalizar; los diseños rara vez son versátiles

---
## Morfología del robot
La **morfología** se refiere a la estructura física y tipo de movimiento del robot. Determina sus capacidades y limitaciones operacionales.
### Tipos de robots con ruedas
**Características generales:** Se mueven eficientemente en superficies planas

|Tipo|Descripción|Ventajas|
|---|---|---|
|**Orugas**|Sistema de orugas|Útiles en terrenos difíciles|
|**Diferencial**|Dos ruedas independientes|Fácil de controlar|
|**Omnidireccional**|Múltiples ruedas direccionables|Buena maniobrabilidad|
|**Articulado**|Estructura flexible|Mucha flexibilidad de movimiento|

### ROBOTS MANIPULADORES
**Características:** Tienen articulaciones y eslabones que emulan un brazo humano

- Mayor número de grados de libertad = mayor flexibilidad y alcance
- Tipos principales: SCARA, de ejes paralelos, cartesiano, brazo articulado
- **Limitación:** Movilidad limitada, ideal para trabajo estático
### ROBOTS MODULARES
**Características especiales:**

**Serpiente:** Múltiples articulaciones en serie
- Flexible para inspeccionar tuberías y espacios reducidos

**Cubos modulares:** Bloques que se pueden unir y separar
- Configurables para diferentes tareas
- Exploración dinámica y espacial

### ROBOTS BIOINSPIRADOS
**Basados en naturaleza:** Imitan estructuras de seres vivos

|Tipo|Inspiración|Aplicaciones|
|---|---|---|
|**Humanoides**|Anatomía humana|Interacción con humanos|
|**Insecto**|Insectos|Exploración y monitoreo|
|**Acuáticos**|Peces/animales acuáticos|Ambientes marinos|
|**Enjambre**|Comportamiento colectivo|Coordinación multi-robot|

### COMPARATIVA DE MORFOLOGÍAS

|Morfología|Movilidad|Estabilidad|Entorno|Aplicaciones|
|---|---|---|---|---|
|**Ruedas**|Alta|Moderada|Terrenos planos|Logística, ciencia|
|**Manipulador**|Limitada|Alta|Estático|Industria, medicina|
|**Serpiente**|Flexible|Moderada|Espacios reducidos|Inspección tuberías|
|**Cubo**|Configurable|Alta|Dinámico|Exploración espacial|
|**Humanoide**|Moderada|Baja|Ambiente humano|Interacción humana|
|**Insecto**|Variable|Moderada|Cualquiera|Exploración, monitoreo|

### EJEMPLOS APLICADOS
1. **Inspección de tuberías subterráneas:** Serpiente, insecto
2. **Entrega de material médico en hospital:** Humanoide, brazo con ruedas
3. **Exploración de bosque para datos ambientales:** Oruga, insecto
4. **Inspección de estructuras dañadas:** Ruedas, dron, brazo extensible
5. **Distribución de paquetes en almacén:** Ruedas, brazo con ruedas

---

## Arquitectura de un robot
La **arquitectura** es la estructura general que organiza los componentes y sistemas del robot.
### COMPONENTES PRINCIPALES

```
┌─────────────────────────────────┐
│      ARQUITECTURA DEL ROBOT     │
├─────────────────────────────────┤
│ • Unidad de control (CPU)       │
│ • Elementos terminales          │
│ • Sistema de alimentación       │
│ • Sistema de comunicaciones     │
│ • Sensores                      │
│ • Actuadores                    │
└─────────────────────────────────┘
```

**Ejemplo: NAO Robot humanoid**
- CPU con conexión WiFi
- Cámaras (x2)
- Sensor de proximidad
- Manos prensiles
- Batería Li-Po
- Altavoces (x2)

---
## Unidad de control
**Función:** Controla todas las funciones, movimientos y cálculos del robot
### Tipos de procesadores

| Tipo                 | Definición                  | Características                           | Uso en Robótica                |
| -------------------- | --------------------------- | ----------------------------------------- | ------------------------------ |
| **Microprocesador**  | CPU de propósito general    | Arquitectura CISC/RISC, alta flexibilidad | Control general                |
| **Microcontrolador** | CPU para tareas específicas | RISC, bajo consumo                        | Control de sensores/actuadores |
| **FPGA**             | Circuito lógico programable | Matriz de puertas, muy flexible           | Procesado en tiempo real       |
| **GPU**              | Procesador para gráficos    | Núcleos paralelos, muy rápido             | Procesamiento imágenes, IA     |

**Comparativa detallada:**

|Característica|Microprocesador|Microcontrolador|FPGA|GPU|
|---|---|---|---|---|
|**Velocidad**|Media|Baja|Alta|Muy alta|
|**Consumo**|Medio|Bajo|Medio|Alto|
|**Flexibilidad**|Alta|Moderada|Muy alta|Alta|
|**Costo**|Medio|Bajo|Medio|Alto|
|**Programación**|Múltiples lenguajes|C/C++/ASM|VHDL/Verilog|CUDA/OpenCL|

---

## Elementos terminales
**Función:** Elementos que el robot utiliza para interactuar con el entorno
### De sujeción (para agarrar objetos)
- **Pinzas:** Dos dedos móviles
- **Ventosas de vacío:** Succión por presión negativa
- **Electroimanes:** Atracción magnética
### De herramienta (para realizar tareas)
- Soplete para soldadura
- Atornillador
- Pistola de pintura
- Cañón de chorro de agua

---

## Sistema de alimentación
**Función:** Suministra energía a todos los componentes
### Opciones disponibles
**Baterías (Li-ion, Li-Po):**
- Ligeras y compactas
- Económicas
- Autonomía limitad
**Celdas de combustible:**
- Alta densidad energética
- Larga autonomía
- Muy caras
**Alimentación por cable:**
- Para robots fijos o industriales
- Limita movimiento
### Cálculo de autonomía

$$Autonomía (h) = \frac{Capacidad_{bateria} (Wh)}{Consumo_{robot} (W)}$$

---
## Sistemas de comunicaciones
**Función:** Transmitir datos entre el robot y otros sistemas
### CONEXIONES POR CABLE
- **USB:** Común en laboratorio
- **Ethernet:** Robots industriales
### CONEXIONES INALÁMBRICAS
**Corto/medio alcance (interior):**
- WiFi
- Bluetooth
**Largo alcance (exterior):**
- RF (radiofrecuencia)
- 4G / 5G
### MEDIDA DE ANCHO DE BANDA
$$Ancho\ de\ banda\ (Mbps) = \frac{Tamaño\ datos\ (MB)}{Tiempo\ transmisión\ (s)}$$
---

## Sensores
Los sensores permiten al robot **recibir información del entorno**. Existen múltiples tipos:
### Posición y desplazamiento
- Sensor de proximidad
- Potenciómetro
- **Encoder** (convertidor de movimiento rotacional en señales eléctricas)
### Encoder: tipos y funcionamiento
**Encoders Absolutos:**
- Proporcionan posición exacta
- Generan código binario único
- Tabla de 8 sectores (0-45°, 45-90°, etc.)
**Encoders Incrementales:**
- Detectan cambios de posición
- Miden velocidad: $Velocidad = \frac{N_{pulsos}}{Pulsos_{revolucion} \cdot t_{total}} \cdot 2\pi$
- Miden aceleración: $Aceleracion = \frac{N_{pulsos_{t1}} - N_{pulsos_{t0}}}{Pulsos_{revolucion} \cdot (t1-t0)^2} \cdot 2\pi$
### Movimiento y velocidad
**Acelerómetro:**
- Mide aceleración lineal en 1-3 direcciones (X, Y, Z)
- Detecta cambios de velocidad
- Usos: orientación, movimientos lineales, vibraciones
**Giróscopo:**
- Mide velocidad angular alrededor de ejes
- Usa efecto de Coriolis
- Usos: estabilización, control de orientación
**IMU (Unidad de Medición Inercial):**
- Combina acelerómetro + giróscopo + magnetómetro
- Proporciona orientación 3D completa
### Fuerza y tacto
- **Galgas extensiométricas:** Detectan deformación
- **Sensores piezoeléctricos:** Generan voltaje al deformarse
- Miden fuerzas de compresión/tracción
- Usos: manipulación delicada, detección de contacto
### Distancia
**Ultrasonidos:**
- Ondas sonoras de alta frecuencia
- Miden por tiempo de vuelo del eco
- Ventajas: baratos, precisos en cortas distancias
- Desventajas: sensibles a superficies absorbentes
**Infrarrojos:**
- Luz infrarroja
- Sensores pasivos (detectan radiación)
- Sensores activos (emiten y detectan reflejo)
- Ventajas: rápidos, compactos
- Desventajas: sensibles a reflectancia y luz ambiental
**LIDAR:**
- Pulsos láser
- Alta resolución y alcance
- Nubes de puntos 3D
- Ventajas: precisión, cobertura 360°
- Desventajas: caros, sensibles a polvo/lluvia
### Ambientales
- **Temperatura:** Termistores
- **Luz:** LDR (Light Dependent Resistor)
- **Humedad:** Sensores capacitivos (DHT11)
- **Gases:** Sensores químicos (MQ-2 para humo)
### Visión
- Cámaras RGB (color)
- Cámaras térmicas
- Cámaras de profundidad (RGBD - Kinect)
- Cámaras hiperespectrales
- Procesamiento de imágenes: formas, colores, profundidad, movimiento
### Posicionamiento
**GPS (Sistema de Posicionamiento Global):**
- Utiliza satélites
- Coordenadas globales
- Aplicaciones exteriores
**Métodos alternativos:**
- IMU (Inertial Measurement Unit)
- Cámaras + visión
- LIDAR
- Odometría (encoders en ruedas)

---

## Actuadores
Los actuadores permiten al robot **interactuar con el entorno**. Se clasifican en:
### Luz
- Pantallas LCD: texto e información
- LEDs: indicadores de estado
- Displays de 7 segmentos: caracteres alfanuméricos
**Función:** Comunicar estado visual
### Sonido
- **Zumbadores:** Sonidos simples, alertas
- **Altavoces:** Sonidos complejos, mensajes de voz
**Función:** Comunicar estado acústico
### Motores

#### Motores DC (Corriente continua)
**Función:** Convierten energía eléctrica en movimiento rotacional
**Tipos:**
1. **Con escobillas:**
    - Económicos y fáciles de controlar
    - Las escobillas se desgastan
2. **Sin escobillas (brushless):**
    - Eficientes, mayor vida útil
    - Más caros
3. **De imán permanente:**
    - Compactos y ligeros
    - Eficiencia moderada

**Características fundamentales:**
Velocidad angular (ω) y par (T) tienen relación inversa: $$T = K_t \cdot I$$ $$V = K_e \cdot \omega + I \cdot R$$

Donde:
- $K_t$ = constante de torque
- $K_e$ = constante de voltaje
- $R$ = resistencia interna
- $I$ = corriente
- $V$ = voltaje

**Control de velocidad mediante PWM (Modulación por Ancho de Pulso):**

$$V_{efectiva} = V_{max} \cdot Duty\ Cycle$$
El ciclo de trabajo determina la velocidad:
- 20% = velocidad baja
- 50% = velocidad media
- 80% = velocidad alta
**Rendimiento del motor:**
$$\eta = \frac{P_{mecanica}}{P_{electrica}} = \frac{T \cdot \omega}{V \cdot I}$$

$$P_{mecanica} = T \cdot \omega$$ $$P_{electrica} = V \cdot I$$ $$Perdidas = R \cdot I^2$$
**Ejemplo de cálculo:**
Dado: $K_t = 0.2 \frac{N \cdot m}{A}$, $K_e = 0.1 \frac{V \cdot s}{rad}$, $R = 5Ω$, $V = 24V$, $T = 0.6Nm$

- Corriente: $I = \frac{0.6}{0.2} = 3A$
- Velocidad: $\omega = \frac{24 - 3 \cdot 5}{0.1} = 90 \frac{rad}{s}$
- Rendimiento: $\eta = \frac{0.6 \cdot 90}{24 \cdot 3} = 0.75 = 75\%$

Pasar de radianes a revoluciones por minuto $$90\frac{rad}{s}·\frac{1 rev}{2\pi rad}·\frac{60s}{1min}=800rpm$$
#### Servomotores (Servos)
**Función:** Controlan **con precisión la posición** mediante realimentación
**Características:**
- Contienen motor, potenciómetro (realimentación) y circuito de control
- La posición depende de la duración del pulso PWM
- Comparan posición actual con referencia
- Ajustan automáticamente para corregir errores
**Funcionamiento:** $$Error = Referencia - Posicion\ Actual$$
El controlador ajusta la potencia del motor para minimizar el error.
**Tipos:**
1. **Estándar:**
    - Movimiento limitado (180-270°)
    - Modelismo y posicionamiento simple
2. **Rotación continua:**
    - Giran indefinidamente
    - Control de velocidad en robots móviles
3. **Industriales:**
    - Alta precisión y potencia
    - Automatización y brazos robóticos
**Señal de control PWM:**
La duración del pulso determina el ángulo:
- 1 ms → 0°
- 1.5 ms → 90°
- 2 ms → 180°
- Período típico: 20 ms
#### Motores paso a paso (Stepper Motors)
**Función:** Convierten pulsos eléctricos en movimientos **discretos y precisos**
**Características:**
- El eje gira en incrementos fijos cuando recibe pulsos
- Se controlan en **lazo abierto** (sin realimentación)
- Muy precisos en posicionamiento
**Funcionamiento:**
- El **orden de la secuencia de pulsos** determina el sentido de giro
- La **frecuencia de pulsos** determina la velocidad de rotación
- Cada paso produce un ángulo fijo de rotación
**Aplicaciones:** Impresoras 3D, máquinas CNC, robótica de precisión
**Cálculo del ángulo de paso:**
$$\theta = \frac{360°}{Pasos\ por\ vuelta}$$
**Problema crítico:** Sin realimentación, un paso perdido crea error acumulativo permanente.
**Ejemplo:**
- Resolución: 200 pasos/vuelta
- Ángulo por paso: $\theta = \frac{360°}{200} = 1.8°$
- Si se pierde un paso: error de +1.8° (permanente)
---
## Comparativa de motores

| Motor                       | Velocidad   | Fuerza/Par | Control Posición | Control Velocidad |
| --------------------------- | ----------- | ---------- | ---------------- | ----------------- |
| **DC**                      | ▲ Alta      | ▼ Baja     | ▼ Malo           | ▼ Malo            |
| **Brushless**               | ▲▲ Muy alta | ▼ Baja     | ▼ Malo           | ▬ Medio           |
| **Servo estándar**          | ▼ Baja      | ▲ Alta     | ▲▲ Absoluto      | ▲▲ Absoluto       |
| **Servo rotación continua** | ▼ Baja      | ▲ Alta     | ▼ Malo           | ▬ Medio           |
| **Motor paso a paso**       | ▬ Medio     | ▬ Medio    | ▲▲ Absoluto      | ▲▲ Absoluto       |
