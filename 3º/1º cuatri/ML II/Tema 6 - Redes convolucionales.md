## 6.1 Introducción y motivación
Las redes neuronales tradicionales (MLP - Multi-Layer Perceptrons) presentan limitaciones fundamentales cuando se trabaja con imágenes de alta dimensionalidad.

Problemas de las MLPs para imágenes:
1. **Explosión de parámetros**: Una imagen pequeña de $224$ x  $224$ píxeles RGB tiene 150.528 dimensiones. Una sola capa oculta totalmente conectada con el mismo número de neuronas requeriría aproximadamente 22 millones de parámetros, lo cual es computacionalmente inmanejable.
2. **Pérdida de estructura espacial:** En una MLP, se podría permutar aleatoriamente el orden de los píxeles y reentrenar la red obteniendo los mismos resultados, lo que indica que **no aprovecha la correlación estadística entre píxeles cercanos**
3. **Inestabilidad a transformaciones:** Las MLPs no son estables ante traslaciones u otras transformaciones geométricas; se necesitaría entrenar con el objeto en todas las posiciones posibles para que la red lo conozca.

<u>La solución: <b>Redes Convolucionales (CNNs)</b></u>
Las CNNs resuelven esto basándose en dos principios:
- **Conectividad local:** Los parámetros (pesos) solo afectan a una región rectangular local de la imagen
- **Compartición de pesos (Weight Sharing):** Se usan los mismos parámetros para todas las regiones de la imagen, asumiendo que una característica útil en una esquina lo es también en el centro.
## 6.2 Conceptos fundamentales: Invarianza y Equivarianza
Hemos de distinguir cómo reacciona una función $f[x]$ ante una transformación $t[]$ de la entrada.
- **Invarianza:** La salida no cambia al transformar la entrada.$$f[t[x]]=f[x]$$
	*Ejemplo:* Clasificación de imágenes (si rotas un gato, sigue siendo un "gato")
- **Equivarianza:** La salida se transforma de la misma manera que la entrada.$$f[t[x]]=t[f[x]]$$
	*Ejemplo:* Segmentación de imágenes (si mueves la imagen, la máscara de segmentación tiene que moverse de igual forma)

>[!NOTE] 
>Las capas convolucionales son **equivariantes** a la traslación. Las operaciones de *Pooling* (como Max Pooling) aportan invarianza parcial a pequeñas traslaciones.
## 6.3 La Operación de Convolución
Aunque matemáticamente se define como una inversión del filtro seguida de un producto escalar deslizante, en Deep Learning se usa la **correlación cruzada** (sin invertir el filtro), pero se le llama "convolución" por convención.

**Definición matemática (1D)**
La convolución de una entrada $x$ con un filtro (kernel) $\omega$ se define como la suma ponderada de los vecinos:$$z_i=(\omega * x)_i=\sum_j\omega_j·x_{i+j}$$
En términos de producto escalar, es la proyección del filtro sobre una ventana local de la entrada. La respuesta es máxima cuando la entrada local se parece al filtro ($w · p = ||w||||p||cos \alpha$)

<u>Hiperparámetros de la convolución</u>
1. **Kernel Size ($K$)**: Tamaño de la ventana deslizante. Un tamaño mayor integra información de un área más grande (mayor campo receptivo)
2. **Stride ($S$)**: El paso o desplazamiento del filtro
	- $S = 1$: Se procesan todas las posiciones
	- $S \gt 1:$ Reduce la dimensión de salida (downsampling)
3. **Padding ($P$)**: Relleno de ceros en los bordes
	- *Zero Padding:* Permite mantener el tamaño espacial de la entrada
	- *Valid:* Sin relleno, la salida es más pequeña que la entrada.
4. **Dilation:** Separación entre los elementos del kernel (agujeros). Permite ampliar el campo receptivo sin aumentar el número de parámetros.

**Cálculo de dimensiones**
Para una entrada de tamaño $D_{in}$, kernel $K$, padding $P$ y stride $S$, el tamaño de salida $D_{out}$ es:$$D_{out}=[\frac{D_{in}-K+2P}{S}]+1$$
O: $O=⌊\frac{I−K+2P​}{S}⌋+1$ 

**Canales**
Las CNNs procesan volúmenes de datos:
- Una capa convolucional tiene $C_{in}$ canales de entrada y genera $C_{out}$ canales de salida (mapas de características)
- **Número de parámetros:** Si el kernel es $K \times K$ (en 2D):$$Params : (C_{in}·K²+1)·C_{out}$$
	(*El +1 corresponde al sesgo o bias por filtro*)
## 6.5 Operaciones de muestreo (2D)

**Downsampling (Bajar resolución)**
Para reducir el tamaño espacial y ganar invarianza:
- **Stride > 1**: Quedarse con 1 de cada $N$ píxeles
- **Max Pooling:** Selecciona el valor máximo de la ventana. Aporta invarianza a pequeñas traslaciones y resalta las características más fuertes.
- **Average Pooling:** Calcula la media de la ventana

**Upsampling (Subir resolución)**
Usado en redes generativas o segmentación (U-Net):
- **Max Unpooling:** Restaura los valores a las posiciones donde estaban los máximos originales (requiere guardar indices del pooling)
- **Interpolación Bilineal**
- **Convolución Transpuesta (Deconvolution)**: Aprende un filtro para "deshacer" la convolución. **NOTA:** **NO es la inversa matemática,** sólo recupera el tamaño espacial pero aprende sus propios pesos.
## 6.6 Arquitecturas clásicas
1. **LeNet-5 (1989)**
	- Pionera en usar BP para dígitos manuscritos
	- Arquitectura: Convolución -> Pooling -> FC (Fully Connected)
	- Activación: Tanh
2. **AlexNet (2012) - Punto de inflexión**
	- Ganadora de ImageNet con error top-5 del 16.4%
	- **Innovaciones clave**
		- Uso de ReLU para acelerar entrenamiento
		- **Dropout** ($p = 0.5$) para regularizar
		- **Data Augmentation** masivo
		- Entrenamiento en GPUs
		- Filtros grandes en primeras capas (11x11)
3. **VGG (2015)**
	- Filosofía modular: Usa **exclusivamente filtros de** $3 \times 3$ y MaxPooling $2 \times 2$
	- ¿Por qué $3 \times 3$? Dos capas de $3 \times 3$ tienen el mismo campo receptivo que una de $5 \times 5$, pero con menos parámetros y más no linealidades (más capas ReLU)
	- Estructura típica: Al reducir la resolución a la mitad (pooling), se **duplica el número de canales** para mantener la capacidad de información
## 6.7 Redes Residuales (ResNets)

**El Problema de la Profundidad**
Al hacer redes muy profundas (>20 capas), el rendimiento empeora, no por overfitting, sino por **dificultad en la optimización** (gradientes que se desvanecen)

**La solución residual**
En lugar de aprender la función deseada $H(x)$ directamente, la red aprende el residuo $F(x) = H(x)-x$.
- **Bloque Residual** La entrada $x$ se suma a la salida de las convoluciones:$$Salida=ReLU(F(x)+x)$$
	Esto crea un "atajo" (skip connection) que permite que la identidad fluya fácilmente. Si las capas extra no son necesarias, la red puede aprender $F(x) \approx 0$, convirtiéndose en identidad.

**Detalles de arquitectura**
- Estilo VGG (filtros $3 \times 3$) pero con skip connection
- Sin Dropout
- **Uso crítico de Batch Normalization** Fundamental porque en las conexiones residuales ($x + F(x)$), la varianza de la señal se duplica en cada bloque. Sin normalización la señal crecería exponencialmente. 
## 6.8 Otras arquitecturas (Segmentación)
- **U-Net / Hourglass**: Redes con forma de "U" o reloj de arena. Usan una estructura de Encoder (bajada de resolución) y Decoder (subida de resolución) con conexiones puente (skip connections) entre el encoder y el decoder para recuperar detalles espaciales perdidos, ideal para generar imágenes de salida (ej. segmentación semántica)