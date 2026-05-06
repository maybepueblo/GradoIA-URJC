**1. Introducción y el Ciclo "Ver-Pensar-Actuar"** La percepción es la fase de "Ver", donde el robot utiliza sensores para obtener datos crudos (Raw data) del entorno, extrae información relevante, y construye un mapa local para estimar su posición y crear un mapa global. Esta fase de percepción alimenta a la fase de "Pensar" (planificación de trayectorias y tareas) y finalmente a la fase de "Actuar" (control de movimiento y ejecución de la trayectoria) en el mundo real. La visión artificial en robótica busca que el robot perciba, interprete y "comprenda" su entorno a través de imágenes o secuencias de vídeo, requiriendo procesamiento en tiempo real, robustez ante cambios en el entorno y bajo consumo de recursos.

**2. Aplicaciones y Casos de Uso de la Visión en Robótica**

La visión artificial tiene diversas aplicaciones críticas en robótica:

- **Navegación y localización:** Permite a robots móviles y vehículos autónomos percibir objetos, entender la escena y localizarse (SLAM visual). Ejemplos incluyen detección de líneas, peatones y señales de tráfico.
    
- **Manipulación robótica:** Usada en robots industriales y brazos robóticos para detectar, reconocer, clasificar y manipular objetos.
    
- **Interacción con humanos:** Esencial en robots de servicio para reconocer personas, rostros, gestos y realizar seguimientos.
    

Los desafíos principales en estas aplicaciones incluyen la iluminación variable, condiciones adversas (reflejos, oclusiones) y la necesidad de procesamiento en tiempo real.

**3. Hardware para Percepción y Sensores**

El documento aborda los componentes de hardware que integran los sistemas de percepción, diferenciando entre:

- **Sensores Propioceptivos:** Miden el estado interno del robot (ej. Encoders, IMU, GPS).
    
- **Sensores Exteroceptivos:** Miden el entorno externo (ej. Cámaras, LIDAR, ultrasonidos).
    

Se detallan componentes específicos para robots acuáticos (cámaras frontales, traseras, ordenadores de visión, IMU, sensores de presión) y aéreos (cámaras FPV, cámaras digitales, LIDAR, controladores de vuelo, estabilizadores).

**4. Tipos de Cámaras en Robótica: RGB y RGB-D**

Se profundiza en el funcionamiento de las cámaras utilizadas en robótica:

- **Cámaras RGB:** Basadas en la síntesis aditiva del color, utilizan sensores CCD o CMOS con un filtro de Bayer, el cual interpola colores primarios para generar píxeles de color.
    
- **Cámaras RGB-D (Depth):** Combinan imágenes a color con información de profundidad. La profundidad, representada en escala de grises (donde la intensidad indica la distancia), se puede obtener mediante tres métodos principales:
    
    - **Luz estructurada:** Un proyector emite un patrón infrarrojo (IR) que es capturado por una cámara IR. La profundidad se calcula mediante triangulación, analizando la distorsión del patrón sobre los objetos en comparación con un patrón de referencia en una superficie plana conocida ($Z = \frac{f \cdot b}{d}$).
        
    - **Time-of-Flight (ToF):** Utiliza la velocidad de la luz para calcular la distancia. Se divide en **dToF (Direct ToF)**, que emite un pulso láser y mide el tiempo directo de retorno ($d = \frac{c \cdot t}{2}$) ; e **iToF (Indirect ToF)**, que emite una onda continua y modulada de luz IR y calcula la distancia midiendo el desfase entre la onda emitida y la reflejada. Ambos sistemas ToF pueden fallar en superficies especulares, reflectantes, negras profundas o bajo luz solar directa.
        
    - **Disparidad estéreo:** Explicado más adelante en el punto 7.
        

**5. Profundidad con LIDAR** Los sistemas LIDAR (Light Detection and Ranging) funcionan bajo el principio dToF, emitiendo pulsos láser breves, potentes y muy focalizados, barriendo la escena mediante espejos giratorios para generar una nube de puntos 3D. A diferencia de los sensores RGB-D, los LIDAR funcionan bien en exteriores gracias a la alta energía del pulso láser, el uso de filtros de banda estrecha y su geometría directa.

**6. Detección y Seguimiento de Objetos: Casos Prácticos** El documento presenta tres problemas prácticos y cómo abordarlos con técnicas de visión clásicas:

- **Sigue-líneas con visión:**
    
    1. Conversión a espacio de color HSV para una extracción de color más robusta ante cambios de iluminación.
        
    2. Segmentación por color y aplicación de máscara binaria, seguida de operaciones morfológicas (erosión/dilatación) para eliminar ruido.
        
    3. Detección de bordes usando filtros como Canny.
        
    4. Detección de líneas mediante la Transformada de Hough.
        
    5. Cálculo de desviación de la línea respecto al centro de la imagen para aplicar un control PID a los actuadores.
        
- **Seguimiento de una pelota de color:**
    
    1. Conversión a HSV y segmentación por color (similar al sigue-líneas).
        
    2. Detección de contornos (buscando el contorno cerrado más grande o usando HoughCircles) para obtener el centro y radio de la pelota.
        
    3. Seguimiento del objeto mediante **Flujo Óptico de Lucas-Kanade** (basado en el desplazamiento de puntos de interés entre fotogramas consecutivos) o mediante el **Filtro de Kalman** (que predice la posición futura basándose en el historial de velocidad y trayectoria, siendo más robusto ante oclusiones y ruido).
        
    4. Cálculo de actuación para centrar la cámara.
        
    
    - _Alternativa con Redes Neuronales:_ Usar algoritmos pre-entrenados como YOLO para la detección, seguido de seguimiento y cálculo de actuación, útil cuando la detección por color no es robusta o hay múltiples objetos.
        
- **Navegación y manipulación con marcadores (ArUco y Códigos de Barras):** Los marcadores ArUco (patrones blanco y negro con ID único) se usan para conocer la posición exacta (traslación y rotación en ejes x,y,z, roll, pitch, yaw) de un objeto en el espacio real, minimizando el error de proyección (ej. `estimatePoseSingleMarkers()`). Son útiles en realidad aumentada, aterrizaje de drones, o guiado de brazos robóticos. Se aplican técnicas como la umbralización adaptativa para su detección. También se mencionan los códigos de barras 1D (EAN) y 2D (QR) para identificación en robótica.
    

**7. Visión Estéreo** La visión estéreo imita la visión binocular humana usando dos cámaras separadas por una distancia conocida (baseline).

- **Principio:** Un objeto visto desde dos perspectivas tiene una diferencia de posición en cada imagen llamada **disparidad**. Esta disparidad es inversamente proporcional a la distancia del objeto: un objeto cercano tiene gran disparidad, uno muy lejano tiene disparidad cercana a cero. La fórmula fundamental es $Z = \frac{f \cdot b}{d}$ (donde Z=profundidad, f=focal, b=baseline, d=disparidad).
    
- **Proceso:**
    
    1. **Rectificación Estéreo:** Corrige el desalineamiento y aberraciones de las cámaras para que las imágenes estén perfectamente alineadas horizontalmente, facilitando el matching.
        
    2. **Cálculo del mapa de disparidad:** Consiste en encontrar la correspondencia de píxeles entre las dos imágenes. Puede hacerse basado en características (feature-based, ej. SIFT, SURF) o en regiones (region-based, ej. Block Matching).
        
    3. **Algoritmos avanzados:** El método SGBM (Semi-Global Block Matching) mejora el clásico Block Matching agregando optimización de suavidad (penaliza variaciones abruptas de disparidad) y evaluando correspondencias en múltiples direcciones, además de permitir estimación a nivel de subpíxel.
        

**8. Procesado de Imagen en Hardware (FPGA vs. CPU)** Finalmente, el documento aborda la implementación a nivel de hardware para acelerar el procesamiento de imágenes.

- **CPU:** Procesamiento secuencial (instrucciones por software). Diseño de hardware complejo y lento.
    
- **FPGA (Field Programmable Gate Array):** Dispositivo compuesto por bloques lógicos configurables (CLB) y conexiones que se pueden reprogramar _después_ de su fabricación para realizar tareas en **paralelo** (implementación directa en hardware).
    
- **Flujo de diseño en FPGA:** Requiere lenguajes de descripción de hardware (VHDL o Verilog). El proceso incluye la especificación, descripción en VHDL, síntesis, implementación y generación del Bitstream mediante herramientas software (ej. Vivado). Existen alternativas de alto nivel (como Simulink/MATLAB) que evitan escribir en VHDL, aunque generan diseños menos optimizados.
    
- **VHDL (Very High Speed Integrated Circuit Hardware Description Language):** Es un lenguaje para describir el comportamiento y estructura de un circuito. Un archivo VHDL se estructura en Librerías, Entidad (define entradas/salidas) y Arquitectura (define el comportamiento).
    
- **Ventajas en Procesamiento de Imagen:** Al recibir píxeles uno a uno de la cámara (streaming de video por VGA/HDMI, que requiere crear drivers específicos de sincronización como señales hsync/vsync), la FPGA puede procesarlos en tiempo real (ej. `thresholding` o eliminación de fondo). Para operaciones locales que requieren evaluar los píxeles vecinos (como un filtro de ruido de mediana 3x3), la FPGA utiliza memorias tipo buffer (Line Buffers) para almacenar píxeles de múltiples líneas y procesarlos simultáneamente en paralelo de forma ultra rápida.