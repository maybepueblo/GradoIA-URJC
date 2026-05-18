Histograma como análisis de una imagen, no podemos replicar la imagen a partir de ello

### suavizado vs bordes
suavizar equivale a integrar y buscar bordes es derivar, encontrando cambios fuertes en el nivel
### ¿Qué es el procesamiento digital de imágenes?

El procesamiento de imágenes consiste en transformar una imagen de entrada en otra imagen diferente con el fin de facilitar la tarea posterior del sistema de Visión Artificial (VA). Entre sus principales aplicaciones se encuentran:

- Mejorar la distribución de los niveles de gris mediante transformaciones puntuales.
    
- Eliminar el ruido presente en la imagen usando filtrado paso bajo.
    
- Realzar estructuras específicas de la escena mediante filtrado paso alto.
    

**Recordatorio de Imagen Digital:**

- Una imagen digital en escala de grises de dimensiones $f\times c$ se define matemáticamente como una función $l:F\times C\rightarrow D$.
    
- Donde $D=\{0,...,d-1\}$ representa la resolución digital, $F$ es el conjunto de filas y $C$ el conjunto de columnas.
    
- En el rango de 8 bits: $I(f,c)=0$ corresponde al color negro, $I(f,c)=255$ al color blanco, y los valores intermedios $0<I(f,c)<255$ corresponden a tonos de gris.
    
- Toda operación sobre una imagen se puede definir formalmente como $g(i,j)=T(f(i,j))$, donde $f$ es la imagen de entrada, $g$ la imagen procesada, $(i,j)$ las coordenadas del píxel, y $T$ es la operación aplicada.
    

### Tipos de procesamiento: puntual, local y global

Las operaciones sobre las imágenes se clasifican según el tamaño de la vecindad sobre la que se calcula el nuevo valor del píxel:

- **Operaciones globales:** La vecindad sobre la que actúa la operación comprende absolutamente toda la imagen.
    
- **Operaciones locales:** La vecindad está restringida a un grupo cercano de unos cuantos píxeles alrededor del píxel objetivo.
    
- **Operaciones puntuales:** La vecindad es estrictamente el propio píxel en el que se centra la ventana (vecindad $1\times 1$).
    

### Histograma de una imagen

El histograma representa la distribución de las intensidades (niveles de gris) dentro de la imagen. * **Definición formal:** Sea $I(i,j)$ una imagen, su histograma es $h(m)=card(\{(i,j)|I(i,j)=m\}),\forall m\in\{0,...,d-1\}$.

- **Propiedades clave:**
    
    - El número total de píxeles $N$ es la suma de todos los valores del histograma: $N=\sum_{m=0}^{d-1}h(m)$.
        
    - Puede expresarse como una Función de Densidad de Probabilidad (fdp) al normalizarse: $p(k)=\frac{h(k)}{\sum_{m=0}^{d-1}h(m)}$.
        
    - Si dividimos la imagen en regiones disjuntas, el histograma total es la suma de los histogramas de dichas regiones: $h(m)=\sum_{i=1}^{r}h_{R_{i}}$.
        
- _Nota:_ En imágenes a color se utilizan lógicas idénticas, trabajando con histogramas separados para cada canal.
    

### Operaciones puntuales

Las operaciones puntuales son las transformaciones más sencillas porque solo dependen del valor de gris del píxel original. Siguen la fórmula $s=T(r)$, donde $r$ es la entrada y $s$ la salida. Por norma general, se asume que la función de transformación $T$ debe ser una **función monótona no decreciente** (para evitar invertir la relación de brillo de la imagen original). La transformación de **identidad** es simplemente $T(r)=r$.

- **Imagen negativa:** * Se utiliza principalmente para realzar regiones blancas o grises que se encuentran ocultas en zonas muy oscuras.
    
    - La fórmula es $s=T(r)=(d-1)-r$. En una imagen típica de 8 bits, esto es $T(r)=255-r$.
        
- **Umbralización:**
    
    - Sirve para separar (segmentar) los objetos o zonas de interés del fondo.
        
    - La fórmula básica es $s=T(r)=\begin{cases}d-1&si&r>umbral\\ 0&si&r\le umbral\end{cases}$.
        
    - Existen variantes como: cortar un rango y mantener el resto, o umbralizar por un límite superior e inferior.
        
- **Corrección gamma:** * Es un ajuste de brillo que compensa la respuesta no lineal que tienen las pantallas y monitores (CRT, LED) al mostrar la imagen.
    
    - Mientras que los sensores de las cámaras captan la luz de forma lineal, se requiere la función Gamma para redistribuir los bits antes de su visualización, asignando mayor cantidad de bits a los tonos oscuros, ya que el ojo humano es más sensible a los cambios en sombras que en brillos.
        
    - La fórmula es: $T(r)=(d-1)\cdot(\frac{r}{(d-1)})^{\gamma}$.
        

_(Bonus)_ También existen operaciones puntuales de Potencia (Parábola $c_{1}v^{2}+c_{2}v+c_{3}$ para oscurecer medios tonos) y Raíz ($C_{1}V^{0.5}+C_{2}$ para aclarar medios tonos).

### Contraste y rango dinámico de una imagen

- **Rango dinámico:** Es el espectro real de valores de intensidad que existen en la imagen en concreto, desde su intensidad más oscura hasta su intensidad más clara.
    
- **Contraste:** Es la diferencia matemática de intensidades entre el valor máximo y el valor mínimo presente en la imagen. Como norma general, a mayor rango dinámico, la imagen posee mayor contraste.
    
- **Aumento de contraste (Transformación Lineal):** Si una imagen tiene bajo contraste, se puede expandir ("estirar") su histograma aplicando $T(r)=M\cdot\frac{(r-min)}{(mix-min)}$, lo que provoca que los niveles de gris ocupen todo el rango disponible de 0 a M.
    

### Operaciones aritméticas y lógicas entre imágenes

Estas operaciones modifican los niveles de gris usando matemáticas simples (y lógicas en código, como sumas o restricciones en OpenCV para evitar _overflows_ saturando los límites en 0 y 255):

- **Sumar/Restar una constante:**
    
    - Suma: $T(r)=r+a$ (saturando a 255).
        
    - Resta: $T(r)=r-a$ (saturando a 0).
        
- **Multiplicar/Dividir por una constante:**
    
    - Multiplicación: $T(r)=2r$ (saturando a 255).
        
    - División: $T(r)=r/2$.
        
- **Resta de imágenes:** Es vital en sistemas de vídeo para detectar movimiento.
    
- **Media de imágenes:** Se utiliza para eliminar o atenuar el ruido gaussiano. Si la imagen sufre un ruido $v_{i,j}\sim N(\mu=0,\sigma^{2})$, al promediar $K$ capturas distintas de la misma escena, la imagen media resultante $\overline{g}(i,j)=\frac{1}{K}\sum_{r=1}^{K}g_{r}(i,j)$ tenderá al valor real sin ruido: $E[\overline{g}(i,j)]=I(i,j)$.
    

### Ecualización de un histograma

La ecualización es un procedimiento matemático totalmente automático para calcular una transformación $T[r]$ que cumpla dos objetivos simultáneos: que el rango dinámico se estire al máximo, y que los diferentes niveles de gris queden distribuidos de la manera más uniforme posible.

- **Principio matemático:** Transforma la función de distribución original $P_{R}$ en una distribución uniforme $P_{S}=1$. Se basa en forzar que el área a la izquierda del punto $r$ en la distribución original coincida con el área a la izquierda del punto $s$ transformado: $\int_{0}^{r}P_{R}(\lambda)d\lambda=\int_{0}^{s}P_{s}(\lambda)d\lambda=\int_{0}^{s}d\lambda=s$.
    
- **Caso Discreto:** En la práctica, se utilizan las frecuencias acumuladas de los píxeles. La transformación se logra mediante la sumatoria: $T[r]=(d-1)\sum_{i=0}^{r}\frac{h(i)}{\sum_{k}h(k)}$.
    
- Se implementa muy fácilmente en librerías estándar como OpenCV mediante llamadas como `cv2.calcHist` y `cv2.equalizeHist`.
### Operaciones de vecindad local
A diferencia de las operaciones puntuales que vimos en la parte anterior, las operaciones de vecindad no modifican el píxel basándose únicamente en su propio valor, sino que utilizan información de su entorno.
- Una operación de vecindad se define formalmente como $g(i,j)=T(f,i,j)$.
- En esta fórmula, $f$ es la imagen de entrada, $g$ es la imagen procesada resultante y $T$ representa la operación matemática definida sobre una vecindad (normalmente una región rectangular) centrada en las coordenadas $(i,j)$.
- Para procesar toda la imagen, la operación $T$ se aplica sistemáticamente a cada píxel $(i,j)$ desplazando la ventana de vecindad.
### Filtrado lineal y no lineal
Dependiendo de cómo se calcule el nuevo valor del píxel utilizando los vecinos, las operaciones se dividen en dos grandes grupos:
- **Operaciones Lineales (filtrado espacial):** La transformación $T$ consiste en realizar una combinación lineal matemática de los niveles de gris de los píxeles vecinos al $(i,j)$.
- **Operaciones No Lineales:** La transformación $T$ aplica una función que no es lineal (como calcular el máximo, el mínimo, o la mediana) sobre los niveles de gris de los vecinos de $(i,j)$.
### Correlación y convolución
Son las dos operaciones matemáticas fundamentales para aplicar filtrados lineales espaciales mediante una matriz numérica llamada "máscara" o "kernel" de tamaño $(2p+1)\times(2q+1)$.
- **Correlación:** Consiste en una suma de multiplicaciones directas entre los pesos de la máscara $w(s,t)$ y los píxeles subyacentes de la imagen $f$.
    - Fórmula: $g(i,j)=\sum_{s=-p}^{p}\sum_{t=-q}^{q}w(s,t)f(i+s,j+t)$.
- **Convolución:** Se denota matemáticamente como $g=w^{*}f$.
    - Fórmula: $g(i,j)=\sum_{s=-p}^{p}\sum_{t=-q}^{q}w(s,t)f(i-s,j-t)$.
    - La principal diferencia con la correlación es que los signos negativos en los índices de la imagen $(i-s, j-t)$ provocan que la convolución sea exactamente igual que la correlación, pero invirtiendo la máscara tanto en el eje vertical como en el horizontal.
**Propiedades matemáticas de la convolución:**
- Es lineal y conmutativa ($f^{*}g=g^{*}f$), lo que significa que a nivel matemático no hay diferencia entre operar la imagen o la máscara.    
- Es asociativa: $f^{*}(g^{*}h)=(f^{*}g)^{*}h$. Esto permite unificar varios filtros en uno solo antes de aplicarlos a la imagen.
**Implementación de filtros separables:**
- Una máscara matricial $h$ de dimensiones $m\times n$ se considera "separable" si su rango algebraico es igual a 1 ($rango(h)=1$).
- Esto implica que la máscara puede descomponerse en el producto de un vector columna $h_i$ por un vector fila $h_j$.
- Por la propiedad asociativa, convolucionar la imagen con una máscara separable es equivalente a hacer $h_j^{*}(h_i^{*}I)$.
- **Ventaja crucial:** Descomponer el filtro reduce drásticamente el coste computacional, pasando de requerir $m \cdot n$ operaciones por píxel a solo $(m+n)$ operaciones.
### Filtrado en el dominio espacial (Detalles de implementación)
A la hora de llevar la convolución al software (como por ejemplo en OpenCV), surgen dos problemas que hay que atajar:
1. **Problema de los bordes:** Cuando el filtro llega a los límites de la imagen, la máscara "sobresale" y faltan píxeles. La solución estándar es extrapolar, por ejemplo, dejando el borde exterior inventado en color negro (ceros).
2. **Problema del rango dinámico:** Al sumar multiplicaciones, el resultado numérico puede salirse de los límites de color (como superar 255). Para evitarlo, se aplican dos correcciones a la ecuación lineal: un _factor divisor_ (para dividir el resultado numérico) y un _factor bias_ (un valor constante que se suma al resultado final).
### Filtrado de suavizado (o paso bajo)
Los filtros de suavizado se utilizan para dejar pasar las "frecuencias bajas" (zonas de la imagen con sombreados y color uniforme) y atenuar o eliminar las "frecuencias altas" (zonas donde hay cambios bruscos de intensidad, como los bordes). Son esenciales porque el ruido fotográfico suele comportarse precisamente como una alta frecuencia.

Tipos de ruido clásicos que se intentan eliminar:
- **Ruido "sal y pimienta":** Píxeles aleatorios distribuidos en blanco y negro puro.
- **Ruido impulsivo:** Aparición aleatoria de píxeles puramente blancos.
- **Ruido gaussiano:** Variaciones aleatorias leves en los niveles de gris que siguen una curva estadística gaussiana .

Existen tres métodos principales de suavizado:
#### 1. Filtro de media (Promediado o "Box Filter")
- Es un filtro lineal que consta de una máscara llena de "unos" multiplicada por una fracción (ej: $\frac{1}{9}$ para una máscara 3x3) .
- Todos los componentes sumados dan como resultado 1, lo que garantiza que si se aplica sobre una zona gris uniforme, el color se mantiene intacto sin oscurecerse ni aclararse.
- Es un filtro matemáticamente separable.
- _Desventaja:_ No simula bien el desenfoque real de una lente óptica; transforma puntos blancos en "cuadrados" borrosos en lugar de círculos degradados.
#### 2. Filtro gaussiano
- Para solucionar los problemas visuales del filtro de media, el filtro Gaussiano asigna más importancia matemática a los píxeles que están más cerca del centro de la máscara.
- Utiliza la distribución normal en 2D: $G(y,x)=\frac{1}{2\pi\sigma^{2}}\cdot e^{-\frac{1}{2}\cdot\frac{y^{2}+x^{2}}{\sigma^{2}}}$.
- Posee la gran ventaja de ser un filtro separable.
- **Diseño del tamaño:** Como el 99,7% de la probabilidad matemática en una gaussiana está contenida en el rango de $-3\sigma$ a $3\sigma$, el tamaño $n$ de la máscara de filtrado debe ser siempre $n \ge 6\sigma$.
- **Intensidad:** El nivel de difuminado o "fuerza del suavizado" se controla ajustando la varianza ($\sigma$); a mayor varianza, más borrosa queda la imagen. Es ideal para atenuar ruido gaussiano.
#### 3. Filtro de mediana
- Se trata de un filtro puramente **no lineal**.
- Su funcionamiento es algorítmico: toma todos los niveles de gris de los píxeles abarcados por la ventana, los ordena matemáticamente de menor a mayor valor (Sort) y sustituye el píxel central original directamente por el valor de la "mediana" estadística .
- Es el filtro más efectivo y recomendado específicamente para eliminar el ruido de tipo "sal y pimienta", ya que simplemente descarta los valores extremos (blancos o negros puros) sin emborronar en exceso la imagen general.
¡Por fin tenemos la información completa! Gracias por enviarlo en este formato, ahora sí puedo extraer absolutamente cada detalle técnico de tus diapositivas.

A continuación, te presento el resumen final del Tema 2, estructurado exactamente según tu índice y convertido en una guía de estudio universitaria de alto rendimiento.
### Filtrado paso alto
Mientras que los filtros paso bajo (suavizado) equivalen matemáticamente a "integrar" o hacer la media en una imagen, los filtros **paso alto** se utilizan para realzar el detalle fino, lo que equivale a **derivar**.
- **Objetivo:** Identificar discontinuidades en la imagen, es decir, cambios bruscos en el nivel de gris.
- **Importancia:** En los bordes reside la mayor parte de la información sobre los objetos de la escena de forma compacta.
- **Causas de la aparición de bordes:**
    - Cambios en la reflectancia (información de apariencia o textura).
    - Discontinuidades de profundidad (límites físicos de los objetos).
    - Cambios en la orientación de la superficie (forma y volumen).
    - Sombras proyectadas.
### Bordes y derivadas (primera y segunda)
Las derivadas informan de cómo ocurren los cambios de intensidad espacial:
- **Derivada primera:** Debe ser cero en zonas de intensidad constante, y distinta de cero en los bordes. Visualmente, **los picos** de la función derivada indican la posición de los bordes. Una transición suave (rampa) produce bordes gruesos, mientras que una brusca (escalón) produce bordes finos.
- **Derivada segunda:** Matemáticamente es aún más precisa para localizar el borde exacto, ya que los bordes aparecen en los **cruces por cero** de la función.

_Nota de implementación:_ Al aplicar filtros de derivadas, pueden obtenerse números negativos. Para visualizarlos como imagen digital estándar (0-255), se suele normalizar sumando 128 para situar el cero matemático en un tono gris medio.

### ¿Cómo afecta el ruido al derivar?
El ruido fotográfico arruina el cálculo de las derivadas, provocando multitud de "picos" falsos de alta frecuencia.
- **La Solución:** Siempre se debe **suavizar primero** la imagen (usualmente con un filtro Gaussiano $g$) y derivar después.
- **Derivada de una Gaussiana (DoG):** Aplicando la propiedad asociativa de la convolución, es mucho más eficiente calcular una única máscara que contenga la "derivada de la gaussiana" y aplicarla directamente: $\frac{d}{dx}(f*g)=f*(\frac{d}{dx}g)$.
- **Importancia de la Escala ($\sigma$):** El tamaño de la desviación típica $\sigma$ del suavizado determina qué bordes se detectarán:
    - Un $\sigma$ pequeño conservará y detectará todos los detalles y bordes finos (pero será más sensible al ruido).
    - Un $\sigma$ grande eliminará el detalle fino y detectará únicamente los grandes bordes estructurales.
### Máscaras de bordes basadas en primera derivada
La aproximación discreta de la derivada en $X$ se expresa como $I_x \approx \frac{1}{2}(f(x+1,y)-f(x-1,y))$. Existen máscaras de convolución estandarizadas:
- **Roberts:** Utiliza máscaras pequeñas de $2\times2$ (diagonales).
- **Prewitt:** Máscaras de $3\times3$ que derivan en un eje (ej. usando $[-1, 0, 1]$) y aplican un **promediado tipo caja** simple en la dirección ortogonal (ej. $\frac{1}{3}[1, 1, 1]^T$) para atenuar ruido.
- **Sobel:** Es una mejora de Prewitt. Deriva en un eje y aplica un **promediado gaussiano** ($\frac{1}{4}[1, 2, 1]^T$) en la dirección ortogonal, comportándose mucho mejor frente al ruido. _Fila típica en X: `[-1, 0, 1; -2, 0, 2; -1, 0, 1]`_.
### Máscaras de bordes basadas en segunda derivada
- **Operador Laplaciano ($\nabla^2 f$):** Es un operador que suma matemáticamente las dos derivadas segundas de la imagen en $X$ e $Y$: $\frac{\partial^2 f}{\partial x^2} + \frac{\partial^2 f}{\partial y^2}$. Su gran ventaja es que es **isotrópico**, es decir, da la misma respuesta independientemente de la dirección física del borde. (Matriz base central de -4 rodeada de 1s ortogonales).
- **Laplaciana de una Gaussiana (LoG):**
    Dado que la segunda derivada es extremadamente sensible al ruido, el filtro LoG combina el suavizado previo gaussiano y la laplaciana en una única matriz. Matemáticamente y visualmente se le conoce como el **"Sombrero Mejicano"**.
### Otros métodos basados en derivada primera
#### 1. Filtrado basado en el Gradiente
El gradiente es un vector que apunta geométricamente en la dirección del máximo crecimiento del nivel de gris.
- Se calcula primero $I_x$ e $I_y$.
- **Magnitud del borde:** Calculada como la norma del vector $||\nabla I|| = \sqrt{I_x^2 + I_y^2}$. Se utiliza para establecer umbrales (ej. si la magnitud es $>100$, es un borde válido).
- **Orientación del borde:** Se obtiene calculando el ángulo $\theta = arctan(I_y / I_x)$.
#### 2. Algoritmo de Canny (1986)
Considerado el estándar de oro para detectar bordes robustos en Visión Artificial. Es un procedimiento completo compuesto por los siguientes pasos vitales:
1. **Suavizado:** Convolución inicial de la imagen con una Gaussiana ($\sigma$) para eliminar ruido.
2. **Gradiente:** Cálculo de la magnitud y argumento (dirección $\theta$) usando filtros base (como Sobel).
3. **Supresión de no máximos:** Adelgaza los bordes a un solo píxel de ancho. Analiza la magnitud en la dirección del gradiente $\theta$ y descarta el píxel si no es el máximo local frente a sus dos vecinos directos.
4. **Umbralización por histéresis:** En vez de usar un umbral fijo, utiliza dos cotas, un límite inferior ($\tau_0$) y uno superior ($\tau_1$). Todo valor $>\tau_1$ se etiqueta como "borde fuerte y seguro". Los valores intermedios entre $\tau_0$ y $\tau_1$ se etiquetan como borde _solamente_ si están conectados espacialmente (son vecinos continuos) de un borde fuerte.
### Morfología Matemática
#### Conceptos básicos
La morfología matemática es un tipo de filtrado **no lineal** que opera en el dominio espacial. A diferencia de los filtros de suavizado que operan con sumas, la morfología se basa puramente en **operaciones de teoría de conjuntos** (uniones, intersecciones) sobre la "forma" de los objetos presentes en la imagen.
Sus utilidades principales son:
- Limpiar o arreglar imperfecciones en la segmentación.
- Destacar la estructura interna o el esqueleto de los objetos.
- Describir propiedades topológicas (como extraer el área o el perímetro).

Se compone de tres elementos matemáticos:
1. **Conjunto (A):** Es la propia imagen (generalmente binaria, donde el objeto de interés son los píxeles negros).
2. **Operador morfológico:** La regla matemática a aplicar.
3. **Elemento Estructurante (EE o B):** Es una pequeña matriz o "máscara" de prueba con una forma específica (cuadrada, cruz, línea) que tiene un "origen" definido (que no tiene por qué estar en su centro de gravedad). El resultado de la operación cambia radicalmente dependiendo de la forma del EE.
#### Operadores: erosión, dilatación, apertura y cierre
Existen dos operadores primarios y dos operadores compuestos:
- **Dilatación ($A\oplus B$):** * Matemáticamente, busca los puntos donde el EE y la imagen original coinciden (intersectan).
    - En imágenes binarias equivale a combinar con la compuerta lógica **OR** los píxeles de la imagen con los del elemento estructurante.
    - _Efecto visual:_ Engrosa los objetos, hace que crezcan. Es especialmente útil para unir caracteres de texto que se han roto (como letras incompletas en un software de OCR). Es una operación conmutativa.
- **Erosión ($A\ominus B$):**
    - Matemáticamente, exige que el EE esté completamente contenido dentro del objeto de la imagen.
    - En binario, equivale a aplicar la compuerta lógica **AND**.
    - _Efecto visual:_ Adelgaza o "come" los bordes de los objetos. Es una operación dual a la dilatación.
- **Apertura ($(A\ominus B)\oplus B$):** * Consiste en aplicar primero una Erosión y, acto seguido, aplicar una Dilatación con el mismo EE.
    - _Efecto visual:_ Hace desaparecer los puntos aislados, el ruido y las estructuras o puentes muy finos, preservando el tamaño del resto del objeto.
- **Cierre ($(A\oplus B)\ominus B$):** Consiste en aplicar primero una Dilatación y después una Erosión.
    - _Efecto visual:_ Sirve para rellenar agujeros o huecos indeseados del interior de los objetos.
#### Otros operadores
Las operaciones morfológicas permiten diseñar lógicas avanzadas. Por ejemplo, la **extracción de bordes** morfológicos se realiza así:
- _Borde externo:_ Dilatar la imagen y restarle la imagen original.
- _Borde interno:_ Tomar la imagen original y restarle la imagen erosionada.
#### Morfología en niveles de gris
Los mismos operadores binarios se extienden a imágenes de grises cambiando los operadores lógicos AND/OR por funciones de Mínimo y Máximo.
- **Dilatación en gris (Max):** Busca el valor máximo en la vecindad. El efecto visual es que la imagen **se aclara** de forma general, reduciendo o eliminando las formas oscuras pequeñas.
- **Erosión en gris (Min):** Busca el valor mínimo. Su efecto es que la imagen **se oscurece**, ensanchando las formas o manchas oscuras.
---
### Operaciones Geométricas sobre Imágenes
Modifican el dominio geométrico (las coordenadas), no los niveles de color como las puntuales. Su fórmula general es $g(i', j') = f(T^{-1}(i', j'))$.
#### Escalado de imágenes: problemas y soluciones
Es vital para crear "pirámides de imágenes" a diferentes resoluciones cuando el sistema necesita buscar objetos (como caras o peatones) sin importar su tamaño.
- **Reducción (Submuestreo):** Si intentamos reducir el tamaño eliminando 1 de cada 2 píxeles a lo bruto, sufriremos el temido **Aliasing** (escalonamiento o moiré). Esto se produce al incumplir el _Teorema de Shannon-Nyquist_, que estipula que la frecuencia de muestreo debe ser superior al doble de la frecuencia máxima de la señal de entrada.
    - _Solución:_ Eliminar las altas frecuencias aplicando un **filtrado paso bajo (Gaussiano)** antes de submuestrear la imagen.
- **Ampliación (Zoom):** Si intentamos mapear píxeles pequeños a un lienzo grande ($T$ directa), quedarán "huecos" vacíos. La solución es la función inversa ($T^{-1}$): recorrer el lienzo destino vacío y preguntar "¿qué valor había en la imagen original para este punto decimal?". Existen tres métodos de **Interpolación**:
    1. _Vecino más cercano:_ Duplica el píxel original más próximo (causa aliasing/cuadrados enormes).
    2. _Bilineal:_ Hace un promedio matemático ponderado entre los 4 píxeles más cercanos.
    3. _Bicúbica:_ Utiliza una superficie polinómica considerando los 16 vecinos ($4\times4$) más cercanos. Produce un difuminado mucho más suave, minimizando los defectos horizontales y verticales frente a la bilineal.
#### Transformaciones Afines
Son aquellas que preservan el paralelismo: si dos líneas eran paralelas en la entrada, lo serán en la salida.
- Poseen **6 grados de libertad** (incógnitas a, b, c, d, $t_x$, $t_y$).
- Para calcular la matriz afín a nivel algebraico, necesitamos emparejar exactamente **3 puntos** (coordenadas) de la imagen de entrada con 3 de la de salida.
- Incluyen: Traslación, Escalado, Rotación e Inclinación (Shear).
- _Propiedad de Composición:_ Se pueden encadenar varias afines multiplicando sus matrices correspondientes. (Ejemplo: trasladar al origen, rotar, devolver a posición original) .
#### Homografías (Transformaciones Proyectivas)
Permiten cambiar el plano de perspectiva por completo (ej. corregir una foto tomada de lado para verla de frente).
- Se modelan con **8 grados de libertad**.
- A diferencia de las afines, para resolver las ecuaciones de una homografía (la matriz H de 3x3) se necesitan obligatoriamente **4 puntos origen y 4 puntos destino**.
- No preservan el paralelismo, requieren dividir finalmente entre una tercera coordenada homogénea calculada $(e \cdot i + f \cdot j + 1)$ para obtener las coordenadas euclídeas reales.
### Introducción. Idea intuitiva
El procesamiento en el dominio de la frecuencia surge de las ideas matemáticas de Joseph Fourier (1812), quien demostró que es posible aproximar funciones (como una función escalón) mediante una serie infinita de sumas de cosenos y senos.
- **Idea intuitiva:** Cualquier función continua se puede aproximar mediante sumas de cosenos y senos si ajustamos convenientemente sus coeficientes.
- **Filtrado en el dominio de la frecuencia:** A diferencia del filtrado espacial (que manipula directamente los píxeles en el plano x-y), aquí se transforma la imagen $f(x,y)$ al dominio de la frecuencia obteniendo $F(u,v)$. En este nuevo dominio, las coordenadas $u$ y $v$ representan las frecuencias de aparición (repetición) de los píxeles en las direcciones horizontal y vertical. Una vez filtrada la imagen en este dominio, se aplica la transformada inversa para devolverla al dominio espacial.
### Series de Fourier. Transformada de Fourier
- **Series de Fourier (SF):** Se utilizan para representar funciones _periódicas_ como una suma de senos y cosenos de diferentes frecuencias pesados por unos coeficientes.
- **Transformada de Fourier (TF):** Es la extensión natural de las series de Fourier a señales _no periódicas_. En el caso de imágenes (funciones finitas no periódicas), se asume matemáticamente que son periódicas con un periodo igual al ancho de la imagen para poder aplicar la transformación.
- **Reversibilidad:** El proceso es bidireccional; una función expresada en el dominio de Fourier puede reconstruirse al 100% (sin pérdida de información) volviendo al dominio espacial usando la Transformada Inversa.
### Transformada de Fourier discreta 2D
Dado que una imagen digital $f(x,y)$ toma valores discretos en una matriz de tamaño $M \times N$, se emplea la versión discreta 2D.
- **Fórmula directa:** $F(u,v) = \frac{1}{MN} \sum_{x=0}^{M-1}\sum_{y=0}^{N-1}f(x,y)e^{-j2\pi(\frac{ux}{M}+\frac{vy}{N})}$.
- **Fórmula inversa:** $f(x,y) = \sum_{u=0}^{M-1}\sum_{v=0}^{N-1}F(u,v)e^{j2\pi(\frac{ux}{M}+\frac{vy}{N})}$.
- **Naturaleza Compleja:** La transformación da como resultado una matriz de números complejos con parte real e imaginaria ($R(u,v) + iI(u,v)$). Esto se divide en dos imágenes clave:
    1. **Espectro de Fourier (Módulos):** $|F(u,v)|$. Contiene información sobre los valores de intensidad (las amplitudes de las sinusoides).
    2. **Fase:** $\Phi(u,v)$. Contiene la información topológica sobre las posiciones de los píxeles (y por ende, la posición de los bordes).
### Transformada rápida de Fourier (FFT)
El cálculo directo de la fórmula de Fourier es muy costoso a nivel computacional (Complejidad $O(n^4)$). La **Fast Fourier Transform (FFT)** es un algoritmo de optimización vital que reduce el coste a $O(n^2 \log n)$. Se basa en tres pilares:
1. Exige que el tamaño de la imagen sea cuadrado y potencia de 2 ($n=2^k$).
2. Precalcula los términos exponenciales constantes y los guarda en una tabla.
3. Utiliza una técnica de "divide y vencerás" calculando por separado los términos pares e impares, reduciendo drásticamente las sumas necesarias.
### Propiedades de la transformada de Fourier
- **Separabilidad:** La transformada 2D se puede calcular aplicando primero una transformada 1D en un eje (filas) y luego otra 1D en el eje resultante (columnas).
- **Traslación:** Por defecto, el origen $(0,0)$ de la transformada está en una esquina. Multiplicando la imagen original por $(-1)^{x+y}$, se traslada el espectro de frecuencias al centro geométrico de la matriz $(N/2, M/2)$ para facilitar su visualización.
- **Simetría:** La TF de una imagen real es simétrica conjugada ($|F(u,v)| = |F(-u,-v)|$) respecto al origen.
- **Rotación:** Si la imagen espacial se rota un determinado ángulo, su espectro de Fourier se rotará geométricamente en ese mismo ángulo exacto.
- **Valor promedio:** El valor en el origen de frecuencias $F(0,0)$ es directamente proporcional (dividido entre $N^2$) a la media matemática del nivel de gris de toda la imagen.
- **Teorema de convolución (Crucial):** Filtrar una imagen espacialmente (convolución de imagen y máscara $I*h$) es matemáticamente equivalente a multiplicar "punto a punto" sus respectivas Transformadas de Fourier: $F(I*h) = F(I) \cdot F(h)$.
### Aplicación al filtrado de imágenes
En un espectro centrado, las frecuencias bajas (zonas uniformes) se concentran en el centro, y las altas (bordes y detalles finos) se dispersan hacia el exterior.
- **Filtrado paso bajo:** Elimina las altas frecuencias poniendo sus coeficientes a cero y respeta las bajas. El resultado es un desenfoque o difuminado de la imagen original.
- **Filtrado paso alto:** Elimina las bajas frecuencias (el centro) poniéndolas a cero y respeta las altas (el exterior). El resultado es una extracción o realce de los bordes.
- **Filtrado paso banda:** Pone a cero las frecuencias dejando únicamente un anillo inalterado ("pasa una banda"). Es excelente para aislar y eliminar ruidos estructurales con patrones fijos y repetitivos de la imagen.
### Otras aplicaciones de la transformada de Fourier
- **Compresión de imágenes (JPG):** El formato JPEG fragmenta la imagen en bloques de $8\times 8$ píxeles y le aplica una transformada de cosenos (hermana de la de Fourier). Logra descartar información invisible al ojo humano reduciendo la precisión y el número de componentes almacenados.
- **Análisis de texturas:** Si una imagen contiene una textura con un patrón estructural repetitivo, su Transformada de Fourier mostrará picos de magnitud muy pronunciados (máximos locales) o líneas que evidencian la dirección y periodicidad dominante de esa textura.