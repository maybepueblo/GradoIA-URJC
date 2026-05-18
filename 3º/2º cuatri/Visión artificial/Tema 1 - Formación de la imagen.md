256x256x256 es por conveniencia y generalización, podría ser 512x512x512 pero no es de interés


Nota: un polígono es convexo cuando siempre se pueden unir dos puntos y estar dentro de la figura

Fotodetector: pilla la luz y forma la imagen
## 1. Descripción Física de la Luz y Tipos de Imágenes

La luz ha sido estudiada a través de diversas teorías a lo largo de la historia hasta llegar al modelo actual:

- **Newton (Siglo XVII):** Observó que un prisma descompone la luz solar en bandas de colores. Su hipótesis afirmaba que la luz estaba compuesta por corpúsculos (partículas) que viajaban a diferentes velocidades, dando lugar a los colores.
    
- **Huygens (Siglo XVII):** Propuso la teoría ondulatoria de la luz.
    
- **Maxwell (1865):** Postuló que la luz es una onda electromagnética que se propaga a una velocidad constante de aproximadamente **300.000 km/s**. Consiste en un campo eléctrico y uno magnético que varían en el tiempo retroalimentándose mutuamente.
    
- **Einstein (1905):** Propuso la naturaleza dual (onda-partícula) mediante la introducción de los **fotones** para explicar el efecto fotoeléctrico, sentando las bases de la física cuántica.
    

### Espectro Electromagnético

Las ondas electromagnéticas se agrupan en bandas según su energía (E) y se describen mediante la longitud de onda ($\lambda$) y la frecuencia ($v$). Se relacionan con las siguientes fórmulas: $E=h~v$ (donde $h$ es la constante de Planck: $6,62\cdot10^{-34}J.s$) $\lambda=c/v$ (donde $c$ es la velocidad de la luz: $3\cdot10^{8}m/s$)

El **espectro visible** es la región que el ojo humano puede percibir, típicamente en longitudes de onda entre **400 nm y 700 nm** (algunos hasta 380-780 nm).

### Propiedades Físicas

- **Reflexión:** Ocurre en el límite de dos medios (ej. aire-vidrio). Parte de la energía se refleja y parte se absorbe. Por la Ley de Reflexión, el ángulo de incidencia es igual al ángulo de reflexión.
    
- **Refracción:** La luz atraviesa de un medio a otro y se desvía un cierto ángulo. El índice de refracción es el cociente entre la velocidad de la luz en el vacío y en el medio material (siempre > 1).
    
- **Dispersión:** Es la descomposición de la luz en sus componentes monocromáticos (colores) al cambiar de medio, debido a la variación del índice de refracción para las distintas longitudes de onda.
    

### Clasificación de Tipos de Imágenes

Las imágenes pueden formarse a partir de diferentes bandas del espectro o energías:

- **Radiación EM:** Rayos Gamma (Tomografía PET), Rayos X (medicina, inspección de seguridad), Ultravioleta (actividad solar), Luz Visible (fotografías), Infrarrojo (termografía, visión térmica), Microondas y Ondas de Radio.
    
- **Otras fuentes:** Acústica (ondas sonoras), Ultrasonido (ecografías), Electrónica (microscopía).
    
- **Otras modalidades:** Imágenes 3D (estéreo o Kinect por infrarrojo) e imágenes sintéticas (generadas por ordenador).
    

---

## 2. ¿Qué es el Color?

El color no es una característica física absoluta, sino una **propiedad percibida** que nos permite distinguir luces con diferentes longitudes de onda. El diagrama espectral indica cómo se distribuye la potencia de una señal sobre sus distintas frecuencias. Distintas distribuciones espectrales pueden generar la misma sensación de color en el ser humano.

El color se define por tres atributos fundamentales:

1. **Matiz (Hue):** Es la frecuencia dominante en el diagrama espectral.
    
2. **Saturación (Saturation):** Diferencia entre la frecuencia dominante y el resto. Un color muy saturado es vivo; si es poco saturado, se aproxima al blanco.
    
3. **Brillo o Luminosidad (Brightness):** Define los niveles de blanco y negro, calificando el color como claro u oscuro. Cuando la visión carece de matiz y saturación, se habla de percepción acromática.
    

---

## 3. Psicofisiología de la Visión Humana

El interior del ojo contiene la **retina**, un tejido con fotorreceptores responsables de captar las imágenes:

- **Bastones (Rods):** Existen unos 100 millones distribuidos por toda la retina. Tienen su máxima respuesta a 507 nm (cian-verdoso). Operan en condiciones de baja iluminación y son responsables de la visión nocturna (monocromática).
    
- **Conos (Cones):** Hay aproximadamente 6 millones, concentrados fuertemente en la fóvea (centro del campo visual). Son los responsables de la visión en color y existen tres tipos sensibles a longitudes de onda cortas, medias y largas. Existe un gran solapamiento en sus curvas de absorción.
    

**Percepción Acromática e Ilusiones Ópticas:** El brillo real de un objeto y el brillo _percibido_ por el cerebro no siempre coinciden. El cerebro humano procesa las imágenes usando reglas lógicas basadas en la iluminación aparente y en los contrastes locales para rellenar vacíos, lo que puede provocar la percepción de geometrías erróneas (ilusiones ópticas).

---

## 4. Espacios de Representación del Color

### Teoría Aditiva Triestímulo

Basada en que disponemos de 3 tipos de conos, esta teoría afirma que podemos recrear cualquier color visible mezclando luz de 3 fuentes "ideales" (roja, verde y azul). El **Diagrama CIE** grafica la combinación matemática exacta (gamut) para lograr cualquier color del espectro.

### Espacio RGB

Es un modelo **aditivo** que mezcla luces Rojo (Red), Verde (Green) y Azul (Blue).

- Es un sistema "dependiente del dispositivo", ya que los sensores o monitores exactos influyen en la gama resultante (de ahí nacen estándares como sRGB).
    
- Digitalmente, se suele representar usando 3 bytes por píxel (uno por canal), obteniendo 256 niveles por color y posibilitando más de **16 millones de combinaciones**.
    

### Espacio HSV / HSI / HSB

Sistema cilíndrico diseñado para alinear la representación digital con la percepción humana pura.

- **H (Matiz):** Variable de 0° a 360°.
    
- **S (Saturación):** Variable de 0% a 100%.
    
- **V/B (Valor/Brillo):** Variable de 0% a 100%. Las fórmulas de transformación entre RGB y HSV son computacionalmente no lineales (basadas en los máximos y mínimos de los canales R, G y B).
    

Existen múltiples espacios alternativos optimizados para ciertas tareas técnicas, como **XYZ**, **YUV/YcrCb** (compresión de vídeo) o **CMYK** (sustractivo para impresión).

---

## 5. Proceso de Formación de Imágenes

La creación de una imagen depende de 4 pilares: la iluminación, la geometría de la escena, las propiedades de la superficie del objeto y la óptica de la cámara.

El proceso se puede modelar físicamente con los siguientes pasos consecutivos:

1. **Emisión:** Una fuente emite luz incidente sobre un punto: $E(x,y,z,\lambda)$.
    
2. **Reflexión:** La superficie refleja parte de la luz dependiendo de su reflectividad local: $r(x,y,z,\lambda)$.
    
3. **Captura Óptica:** La energía conjunta que incide sobre la lente es $c(x,y,z,\lambda)=E(x,y,z,\lambda)\times r(x,y,z,\lambda)$.
    
4. **Proyección:** El modelo óptico (pinhole o lente) proyecta el mundo 3D sobre las coordenadas planas 2D del sensor: $c_{p}(x^{\prime},y^{\prime},\lambda)=P(c(x,y,z,\lambda))$.
    
5. **Sensibilidad Sensorial:** El sensor filtra e integra esa luz a lo largo del espectro de acuerdo con su propia sensibilidad física $V(\lambda)$ obteniendo la función continua de la imagen: $g_{c}(x^{\prime},y^{\prime})=\int c_{P}(x^{\prime},y^{\prime},\lambda)V(\lambda)d\lambda$.
    
6. **Digitalización:** La señal analógica pasa por un conversor A/D (si la cámara no es digital por sí misma). Esto implica dos sub-procesos:
    
    - _Muestreo (Sampling):_ Discretización espacial en una matriz de píxeles: $(x^{\prime},y^{\prime})\rightarrow(x_{i}^{\prime},y_{j}^{\prime})$.
        
    - _Cuantización (Quantization):_ Discretización de los valores de amplitud luminosa: $g_{c}(x_{i}^{\prime},y_{j}^{\prime})\rightarrow\hat{g}_{c}(x_{i}^{\prime},y_{j}^{\prime})$.
        
## 6. Modelo Simplificado de Cámara: Pinhole (Cámara Oscura)

El modelo de cámara estenopeica o _pinhole_ es la base matemática de la mayoría de las cámaras modernas.

- **Principio Físico**: Consiste en una caja cerrada con un pequeño orificio. Un único rayo de luz procedente de un punto en el mundo 3D pasa por el orificio y se proyecta en el plano de la imagen.
    
- **Inversión de la Imagen**: En una cámara real, la imagen proyectada en el fondo de la caja está invertida tanto vertical como horizontalmente.
    
- **Matemática de la Proyección**: Utilizando la semejanza de triángulos, se establece que si un punto en el espacio tiene coordenadas $(x, y, z)$ y la distancia focal (distancia del orificio al plano) es $f$, su proyección $(x', y')$ es:
    
    - $x' = f \cdot (x / z)$
        
    - $y' = f \cdot (y / z)$
        
- **Limitación**: Un orificio muy pequeño reduce la cantidad de luz (imagen oscura), mientras que uno muy grande produce imágenes desenfocadas debido a que múltiples rayos de un mismo punto inciden en diferentes lugares del sensor.
    

---

## 7. Modelo de Lente Fina

Para solucionar el problema de luminosidad del _pinhole_, se utilizan **lentes**, que refractan (doblan) la luz para que múltiples rayos de un punto converjan en un solo punto del sensor.

- **Punto de Enfoque**: Existe una distancia específica donde los rayos convergen perfectamente. Si el sensor no está a esa distancia, se produce el "círculo de confusión" (desenfoque).
    
- **Ecuación de la Lente Gausiana**: Relaciona la distancia del objeto ($z$), la distancia de la imagen ($z'$) y la distancia focal de la lente ($f$):
    
    - $1/z + 1/z' = 1/f$
        
- **Propiedad**: Los rayos que entran paralelos al eje óptico pasan por el foco ($F$); los que pasan por el centro de la lente no se desvían.
    

---

## 8. Parámetros de la Óptica de Cámaras

La calidad y características de la imagen dependen de tres factores críticos:

1. **Distancia Focal ($f$)**: Determina el aumento y el campo de visión (_Field of View_). A mayor $f$, mayor aumento pero menor ángulo de visión.
    
2. **Apertura ($D$ o $f/n$):** Controlada por el diafragma. Regula cuánta luz entra. Una apertura mayor (número f pequeño) permite captar imágenes en oscuridad pero reduce la profundidad de campo.
    
3. **Profundidad de Campo (DoF):** Es el rango de distancias en el mundo real que aparecen nítidamente enfocadas en la imagen. Se reduce al aumentar la apertura o al acercarse mucho al objeto.
    

---

## 9. Aberraciones de las Lentes

Las lentes reales no son perfectas y presentan distorsiones:

- **Aberración Cromática**: Debido a que el índice de refracción varía con la longitud de onda, los diferentes colores no enfocan en el mismo punto exacto, creando "bordes de colores".
    
- **Aberraciones Geométricas (Distorsión)**:
    
    - **Distorsión Radial**: Muy común en lentes gran angular. Se divide en distorsión de barril (líneas hacia afuera) y de cojín (líneas hacia adentro).
        
    - **Aberración Esférica**: Los rayos que pasan por los bordes de una lente esférica enfocan en puntos distintos a los que pasan por el centro.
        

---

## 10. Fotorreceptores Digitales (Sensores)

El sensor convierte los fotones en electrones (voltaje) mediante el efecto fotoeléctrico.

- **CCD (_Charge Coupled Device_)**: Tecnología tradicional. Alta calidad y bajo ruido, pero mayor consumo de energía y procesamiento más lento.
    
- **CMOS (_Complementary Metal-Oxide-Semiconductor_)**: Tecnología dominante hoy. Cada píxel tiene su propio conversor. Es más rápido, barato de fabricar y consume menos energía.
    
- **Factor de Llenado (_Fill Factor_)**: Es la proporción del área del píxel que realmente detecta luz. Se suelen usar "microlentes" sobre cada píxel para dirigir la luz hacia la zona sensible y mejorar la eficiencia.
    

---

## 11. Modelo Proyectivo y Calibración de Cámaras

Para que un ordenador entienda la geometría, usamos modelos matriciales.

- **Parámetros Intrínsecos**: Son internos de la cámara. Incluyen la distancia focal ($f$), el punto principal (centro del sensor) y factores de escala de los píxeles.
    
- **Parámetros Extrínsecos**: Definen la posición (traslación) y orientación (rotación) de la cámara respecto al mundo real.
    
- **Calibración**: Es el proceso matemático de encontrar estos parámetros. Se suele hacer fotografiando un patrón conocido (como un tablero de ajedrez) desde diferentes ángulos para corregir la distorsión y conocer la geometría de la cámara.
    

---

## 12. Imágenes Digitales: Digitalización

Una imagen en un ordenador es una aproximación discreta de la realidad mediante dos pasos:

1. **Muestreo (Espacial)**: Dividir la imagen continua en una rejilla de **píxeles**. La resolución (ej. $1920 \times 1080$) define cuánto detalle se conserva.
    
2. **Cuantización (Amplitud)**: Asignar un valor numérico a la intensidad de cada píxel. Lo más común es usar **8 bits**, lo que permite 256 niveles de intensidad (de 0 para negro a 255 para blanco).
--- 
## 13. Proyección Perspectiva y Geometría Proyectiva

La proyección perspectiva es el modelo matemático que describe cómo el mundo 3D se transforma en una imagen 2D.

- **Coordenadas Homogéneas**: Para representar proyecciones (que son transformaciones no lineales) mediante álgebra lineal (matrices), se añaden coordenadas adicionales. Un punto $(x, y)$ en 2D se convierte en $(wx, wy, w)$. Esto permite representar puntos en el infinito y simplifica los cálculos de traslación y proyección.
    
- **Puntos de Fuga**: Una propiedad clave de la proyección perspectiva es que las líneas paralelas en el mundo 3D convergen en un único punto en la imagen, llamado punto de fuga, a menos que sean paralelas al plano de la imagen.
    

## 14. Modelo Proyectivo de Cámara (Matriz de Proyección)

El modelo de cámara se consolida en una única matriz de proyección $P$ que relaciona un punto del mundo $X$ con un punto de la imagen $x$ mediante la relación $x = PX$.

- **Parámetros Intrínsecos ($K$)**: Representan las propiedades internas de la cámara:
    
    - **Distancia focal ($f_x, f_y$)**: En unidades de píxeles.
        
    - **Punto principal ($c_x, c_y$)**: El centro óptico en el sensor.
        
    - **Factor de cizalladura (_skew_)**: Para sensores cuyos píxeles no son perfectamente rectangulares.
        
- **Parámetros Extrínsecos ($R, t$)**: Definen la posición y orientación de la cámara en el espacio respecto a un sistema de coordenadas global:
    
    - **Rotación ($R$)**: Matriz $3 \times 3$ que indica la orientación.
        
    - **Traslación ($t$)**: Vector que indica la posición del centro de la cámara.
        

## 15. Calibración de Cámaras

La calibración es el proceso de determinar numéricamente los parámetros intrínsecos y extrínsecos de una cámara específica.

- **Metodología de Zhang**: Es el estándar actual; utiliza un patrón plano (normalmente un tablero de ajedrez) capturado desde múltiples ángulos.
    
- **Importancia**: Es vital para aplicaciones que requieren mediciones precisas, como la reconstrucción 3D, la navegación de robots o la realidad aumentada, ya que permite eliminar las distorsiones de la lente y conocer la escala real del mundo.
    
- **Corrección de Distorsión Radial**: Durante la calibración se calculan los coeficientes ($k_1, k_2, ...$) necesarios para "enderezar" las líneas que la óptica de la lente curva.