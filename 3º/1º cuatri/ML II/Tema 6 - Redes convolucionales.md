### Aprendizaje Automático II · Grado en IA · Universidad Rey Juan Carlos

**Basado en:** Diapositivas del Tema 6 + _Understanding Deep Learning_, Capítulos 10 y 11 (Prince, MIT Press)

---

## Índice

1. [Motivación: problemas de las MLPs para imágenes](#1-motivaci%C3%B3n)
2. [6.1 · CNNs en 1D](#2-cnns-en-1d)
    - 2.1 Invarianza y equivarianza a transformaciones
    - 2.2 Convolución matemática en 1D
    - 2.3 Correlación cruzada y su uso en CNNs
    - 2.4 Capa convolucional 1D
    - 2.5 Padding, stride, tamaño del kernel, dilatación
    - 2.6 Canales (feature maps)
    - 2.7 Número de parámetros y tamaño de salida
    - 2.8 Campo receptivo (receptive field)
    - 2.9 Ejemplo: red convolucional para MNIST 1D
    - 2.10 Sesgo inductivo y por qué las CNNs generalizan mejor
    - 2.11 Backpropagation en capas convolucionales
3. [6.2 · CNNs en 2D](#3-cnns-en-2d)
    - 3.1 Convolución 2D
    - 3.2 Canales en 2D y número de parámetros
    - 3.3 Downsampling (reducción de resolución)
    - 3.4 Upsampling (aumento de resolución)
    - 3.5 Convolución traspuesta
    - 3.6 Convolución 1×1
    - 3.7 Arquitecturas clásicas: LeNet, AlexNet, VGGNet
    - 3.8 Redes para salida imagen: segmentación semántica
    - 3.9 Redes Residuales (ResNets)
    - 3.10 U-Net y Stacked Hourglass Networks
4. [Resumen y tablas de referencia rápida](#4-resumen-y-referencia-r%C3%A1pida)

---

## 1. Motivación

### Problemas de las MLPs (redes completamente conectadas) para imágenes

Las redes completamente conectadas (MLPs) tienen tres problemas fundamentales cuando se usan con imágenes:

**1. Tamaño inmanejable del número de parámetros**

Una imagen típica de 224×224 píxeles RGB tiene $224 \times 224 \times 3 = 150{,}528$ dimensiones de entrada. Si usamos una sola capa oculta con más parámetros que la entrada (lo habitual para que la red tenga suficiente capacidad), necesitaríamos al menos: $$150{,}528 \times 150{,}528 \approx 22{,}658 \text{ millones de parámetros}$$

Esto es completamente inmanejable en términos de memoria, cómputo y cantidad de datos necesarios para evitar overfitting.

**2. No aprovechan la estructura espacial**

Los píxeles cercanos en una imagen están estadísticamente correlacionados — los bordes, texturas y formas se definen por relaciones de vecindad. Sin embargo, una MLP totalmente conectada no tiene noción de "cerca": trata la relación entre cada par de píxeles de forma idéntica.

La consecuencia es que si permutáramos todos los píxeles de la misma manera en training y test, la MLP obtendría exactamente los mismos resultados. Estamos desaprovechando la estructura espacial.

**3. No son estables ante transformaciones geométricas**

Si un objeto aparece ligeramente desplazado en la imagen, todos los valores de entrada de la red cambian. Una MLP tiene que aprender independientemente qué aspecto tiene cada objeto en cada posible posición de la imagen. Esto es enormemente ineficiente.

### Solución: redes convolucionales

Las **CNNs** resuelven estos tres problemas mediante dos propiedades fundamentales:

- **Localidad:** cada parámetro afecta solo a una región rectangular de la imagen, no a toda la imagen. El kernel convolucional "mira" solo una vecindad local.
- **Compartición de pesos:** los mismos parámetros (el mismo kernel) se aplican en todas las posiciones de la imagen. No hay que aprender independientemente qué aspecto tiene una textura en cada posición.

Esto implica mucho menos parámetros, capacidad de aprovechar relaciones espaciales, y estabilidad natural ante traslaciones.

---

## 2. CNNs en 1D

### 2.1 Invarianza y equivarianza a transformaciones

Antes de definir la convolución, necesitamos precisar matemáticamente qué propiedades queremos que tenga la red.

#### Invarianza

Una función $f[\mathbf{x}]$ es **invariante** a una transformación $t[\cdot]$ si: $$f[t[\mathbf{x}]] = f[\mathbf{x}]$$

La salida de la función es la misma independientemente de la transformación aplicada a la entrada. **Ejemplo:** en clasificación de imágenes, queremos que la red diga "tres" tanto si el dígito está a la izquierda de la imagen como si está a la derecha. La clase predicha debe ser invariante a la traslación.

#### Equivarianza

Una función $f[\mathbf{x}]$ es **equivariante** (o covariante) a una transformación $t[\cdot]$ si: $$f[t[\mathbf{x}]] = t[f[\mathbf{x}]]$$

La salida se transforma de la misma manera que la entrada. **Ejemplo:** en segmentación de imágenes, si la imagen se desplaza a la derecha, la segmentación (qué píxeles pertenecen a cada objeto) también debe desplazarse a la derecha. La segmentación es equivariante a la traslación.

**¿Qué propiedad tienen las capas convolucionales?** Son **equivariantes** a la traslación por construcción (la demostración está en el Problema 10.1 del libro). El pooling (especialmente max pooling) introduce invarianza parcial a pequeñas traslaciones.

---

### 2.2 Convolución matemática en 1D

La convolución matemática discreta 1D entre dos funciones $f(x)$ y $g(y)$, definidas en los dominios $x \in {0,\ldots,a-1}$ e $y \in {0,\ldots,b-1}$, produce una nueva función $s(r) = f * g$ donde $r \in {0,\ldots,s-1}$ con $s = a+b-1$:

$$s(r) = \sum_{k=0}^{a-1} f(a-1-k) \cdot g_e(k + r - (a-1))$$

donde $g_e$ es $g$ extendida con ceros fuera de su dominio: $$g_e(y) = \begin{cases} g(y) & \text{si } y \in {0,\ldots,b-1} \ 0 & \text{en otro caso} \end{cases}$$

**Intuición geométrica del algoritmo:** en la convolución se **invierte** la máscara $f(x)$ (se da la vuelta) y luego "se pasa" (se desliza) por la función $g$ extendida con ceros. En cada posición $r$ se multiplica elemento a elemento y se suman los resultados.

**Ejemplo numérico:**

- $f(x) = [3, 4, 5]$ (3 elementos, $a=3$)
- $g(y) = [1, 2, 3, 4, 5]$ (5 elementos, $b=5$)
- Tamaño de salida: $s = 3 + 5 - 1 = 7$
- $f$ invertida: $[5, 4, 3]$
- Se desliza por $g$ extendida con ceros: $[0, 0, 1, 2, 3, 4, 5, 0, 0]$

Calculando cada valor de $s(r)$:

- $r=0$: $5 \cdot 0 + 4 \cdot 0 + 3 \cdot 1 = 3$
- $r=1$: $5 \cdot 0 + 4 \cdot 1 + 3 \cdot 2 = 10$
- $r=2$: $5 \cdot 1 + 4 \cdot 2 + 3 \cdot 3 = 22$
- $r=3$: $5 \cdot 2 + 4 \cdot 3 + 3 \cdot 4 = 34$
- $r=4$: $5 \cdot 3 + 4 \cdot 4 + 3 \cdot 5 = 46$
- $r=5$: $5 \cdot 4 + 4 \cdot 5 + 3 \cdot 0 = 40$
- $r=6$: $5 \cdot 5 + 4 \cdot 0 + 3 \cdot 0 = 25$

Resultado: $s = [3, 10, 22, 34, 46, 40, 25]$

---

### 2.3 Correlación cruzada y su uso en CNNs

#### Correlación cruzada

La **correlación cruzada** es similar a la convolución pero **sin invertir** la máscara. El kernel (filtro) $\boldsymbol{\omega}$ se desliza directamente por la señal de entrada multiplicando elemento a elemento y sumando:

$$z_i = \omega_1 x_{i-1} + \omega_2 x_i + \omega_3 x_{i+1} = \sum_{j=1}^{K} \omega_j , x_{i+j-\lceil K/2 \rceil}$$

para un kernel de tamaño $K=3$.

#### ¿Qué se usa en redes convolucionales?

En la práctica, las CNNs implementan **correlación cruzada**, no convolución matemática en el sentido estricto. Sin embargo, como los valores del kernel son **aprendidos** durante el entrenamiento (no son fijos), esto es irrelevante desde el punto de vista práctico: si el algoritmo necesita una máscara "dada la vuelta", simplemente aprende los pesos en ese orden.

> **Convención importante:** a partir de este punto, y siguiendo la convención universal en deep learning (incluida PyTorch, TensorFlow y el libro Understanding Deep Learning), usaremos el término "convolución" para referirnos a lo que matemáticamente es una correlación cruzada.

#### Interpretación geométrica de la respuesta del filtro

En cada posición, la correlación cruzada calcula el **producto escalar** entre el kernel $\boldsymbol{\omega}$ y el parche de entrada $\mathbf{p} = (x_i, \ldots, x_{i+K-1})^T$:

$$\boldsymbol{\omega} \cdot \mathbf{p} = |\boldsymbol{\omega}| |\mathbf{p}| \cos\alpha$$

donde $\alpha$ es el ángulo entre $\boldsymbol{\omega}$ y $\mathbf{p}$. Asumiendo $|\boldsymbol{\omega}|$ y $|\mathbf{p}|$ fijos, la máxima respuesta del filtro ocurre cuando $\alpha = 0$, es decir, cuando el parche de entrada $\mathbf{p}$ tiene exactamente la misma forma que el kernel $\boldsymbol{\omega}$. Esto significa que **el filtro detecta el patrón que tiene forma similar a sus pesos**.

---

### 2.4 Capa convolucional 1D

Una capa convolucional 1D con kernel de tamaño 3, stride 1 y zero padding calcula la $i$-ésima activación como:

$$h_i = a!\left[\beta + \omega_1 x_{i-1} + \omega_2 x_i + \omega_3 x_{i+1}\right] = a!\left[\beta + \sum_{j=1}^{3} \omega_j , x_{i+j-2}\right]$$

donde $a[\cdot]$ es la función de activación (habitualmente ReLU), $\boldsymbol{\omega} = [\omega_1, \omega_2, \omega_3]^T$ es el kernel y $\beta$ es el sesgo.

#### Comparación con capa MLP

||Capa convolucional|Capa fully connected (MLP)|
|:--|:--|:--|
|$i$-ésima activación|$h_i = a!\left[\beta + \sum_{j=1}^{K} \omega_j x_{i+j-2}\right]$|$h_i = a!\left[\beta_i + \sum_{j=1}^{D} \omega_{ij} x_j\right]$|
|Parámetros por neurona|$K$ pesos + 1 sesgo compartidos|$D$ pesos propios + 1 sesgo propio|
|Total parámetros ($D$ neuronas, $D$ entradas)|$K + 1$|$D^2 + D$|

**La capa convolucional es un caso especial de la capa FC:** la matriz de pesos de la FC equivalente tiene la mayoría de sus pesos a cero, y los no nulos son iguales entre sí (pesos compartidos). La convolución impone dos restricciones sobre la FC general: **sparsidad** (conexiones locales) y **compartición de pesos** (el mismo filtro en todas las posiciones).

---

### 2.5 Padding, stride, tamaño del kernel, dilatación

#### Zero Padding (relleno con ceros)

Cuando el kernel se extiende más allá de los extremos de la señal de entrada, hay dos opciones:

- **Zero padding:** las posiciones fuera del rango se tratan como si tuvieran valor 0. Permite mantener el mismo tamaño de salida que de entrada (si el padding es adecuado).
- **Convoluciones "válidas" (valid):** solo se computan posiciones donde el kernel cabe completamente dentro de la entrada. La salida es más pequeña que la entrada.

#### Stride (paso)

El stride $S$ indica cuántas posiciones desplaza el kernel en cada paso:

- **Stride 1:** se calcula la salida en cada posición → salida del mismo tamaño que la entrada (con zero padding).
- **Stride 2:** se calcula en posiciones alternas → salida de aproximadamente la mitad del tamaño.
- El stride es la forma más común de hacer **downsampling** dentro de una capa convolucional.

#### Kernel size (tamaño del kernel)

El tamaño $K$ del kernel determina cuántos elementos de la entrada se combinan para cada salida:

- Kernel más grande → combina información de un área más grande → más capacidad de capturar patrones de mayor escala.
- Pero kernel más grande $K$ implica $K$ parámetros más por canal de salida.
- Típicamente se usan kernels de tamaño impar (3, 5, 7) para que el kernel se centre simétricamente en la posición de salida.

#### Dilatación (dilated / atrous convolutions)

Las **convoluciones dilatadas** permiten combinar información de un área grande sin aumentar el número de parámetros, intercalando ceros entre los valores del kernel:

- **Dilation = 0 (libro) / Dilation = 1 (PyTorch):** kernel estándar, sin espaciado. Un kernel de tamaño 3 combina posiciones ${i-1, i, i+1}$.
- **Dilation = 1 (libro) / Dilation = 2 (PyTorch):** un cero entre cada par de pesos. Un kernel de tamaño 3 combina posiciones ${i-2, i, i+2}$. El campo receptivo es 5 pero con solo 3 parámetros.

> **Atención a la convención:** el libro _Understanding Deep Learning_ define dilation como el número de ceros insertados entre los valores del kernel. PyTorch define dilation como la distancia en píxeles entre elementos del kernel. Por tanto, dilation(libro) + 1 = dilation(PyTorch).

**Visualmente (kernel de tamaño 3):**

```
Dilation libro=0 (PyTorch=1): [ω₁, ω₂, ω₃]          → posiciones {i-1, i, i+1}
Dilation libro=1 (PyTorch=2): [ω₁,  0, ω₂,  0, ω₃]  → posiciones {i-2, i, i+2}
```

---

### 2.6 Canales (feature maps)

#### Motivación

Una sola convolución necesariamente **pierde información**: hace una media ponderada de los valores de entrada y pasa el resultado por ReLU (que corta todo lo negativo). Cualquier patrón que no sea similar al kernel tendrá una respuesta pequeña o nula.

**Solución:** aplicar múltiples convoluciones en paralelo con diferentes kernels, cada una buscando un patrón diferente. Cada convolución genera un **canal** (también llamado **feature map**).

#### Caso: $C_i$ canales de entrada, 1 canal de salida

Si la entrada tiene $C_i$ canales y el kernel tiene tamaño $K$, la salida de cada posición es una suma ponderada de **todos los canales de entrada** en las $K$ posiciones vecinas:

$$h_i = a!\left[\beta + \sum_{c=1}^{C_i} \sum_{j=1}^{K} \omega_{cj} , x^{(c)}_{i+j-2}\right]$$

Los parámetros necesarios: $\boldsymbol{\Omega} \in \mathbb{R}^{C_i \times K}$ (pesos) + $\beta \in \mathbb{R}$ (sesgo) = $C_i \cdot K + 1$ parámetros totales.

#### Caso general: $C_i$ canales de entrada, $C_o$ canales de salida

Se aplican $C_o$ filtros independientes (uno por canal de salida). Cada filtro tiene sus propios pesos $\boldsymbol{\Omega} \in \mathbb{R}^{C_i \times K}$ y su propio sesgo.

Parámetros totales: $\boldsymbol{\Omega} \in \mathbb{R}^{C_i \times C_o \times K}$ y $\boldsymbol{\beta} \in \mathbb{R}^{C_o}$: $$\boxed{\text{Parámetros} = C_i \cdot C_o \cdot K + C_o}$$

---

### 2.7 Número de parámetros y tamaño de salida

#### Fórmula del tamaño de salida

Para una capa convolucional 1D con:

- $C_i$ canales de entrada de longitud $D_i$
- $C_o$ canales de salida
- Kernel de tamaño $K$
- Stride $S$
- Zero padding $P$ (celdas añadidas a cada lado)

El tamaño de la salida en la dimensión espacial es:

$$\boxed{D_o = \left\lfloor \frac{D_i - K + 2P}{S} + 1 \right\rfloor}$$

**Casos especiales:**

- Same padding (salida misma longitud que entrada, stride 1): $P = \lfloor K/2 \rfloor$
- Valid (sin padding): $P = 0$, $D_o = \lfloor (D_i - K)/S \rfloor + 1$

**Ejemplo:** entrada $D_i = 40$, $K=3$, $S=2$, $P=0$ (valid): $$D_o = \lfloor (40 - 3)/2 \rfloor + 1 = \lfloor 37/2 \rfloor + 1 = 18 + 1 = 19$$

#### Lectura de la representación matricial de pesos

La capa convolucional es un caso especial de una capa FC. Su matriz de pesos tiene la estructura de una **matriz de Toeplitz** (o de Toeplitz por bloques en el caso multicanal): muchos ceros y los pesos no nulos repetidos en diagonal.

---

### 2.8 Campo receptivo (receptive field)

El **campo receptivo** de una unidad oculta en la capa $k$ es la región de la **entrada original** $\mathbf{x}$ que influye en el valor de esa unidad.

#### Cálculo del campo receptivo con kernels de tamaño 3, stride 1

Con kernel de tamaño 3 y stride 1 en todas las capas:

- Capa 1 ($H_1$): cada neurona mira 3 posiciones de la entrada → campo receptivo = 3
- Capa 2 ($H_2$): cada neurona mira 3 posiciones de $H_1$, y cada una de esas ya mira 3 de la entrada → campo receptivo = 3 + 2 = 5
- Capa 3 ($H_3$): campo receptivo = 5 + 2 = 7
- Capa $k$: campo receptivo = $2k + 1$ (para stride 1, kernel 3)

**Regla general** para kernel $K$ y stride $S=1$: el campo receptivo crece en $K-1$ posiciones por capa.

**Con stride > 1:** cada capa con stride $S$ multiplica el campo receptivo. Con stride 2 y kernel 3:

- Capa 1: campo receptivo = 3
- Capa 2: cada neurona mira 3 posiciones de $H_1$, pero estas están separadas 2 posiciones en $\mathbf{x}$ → campo receptivo = $3 + 2 \cdot 2 = 7$

**Importancia:** el campo receptivo determina cuánta información espacial integra cada neurona. Para que la red pueda usar contexto global, el campo receptivo de las capas más profundas debe ser suficientemente grande.

#### Cómo ampliar el campo receptivo

Hay varias estrategias:

1. Aumentar el tamaño del kernel (más parámetros).
2. Aumentar el stride (reduce la resolución de la salida).
3. Apilar más capas.
4. Usar **convoluciones dilatadas** (más campo receptivo sin más parámetros ni reducción de resolución).

---

### 2.9 Ejemplo: red convolucional para MNIST 1D

#### Dataset MNIST 1D

El dataset MNIST-1D es una versión simplificada del MNIST: 10 plantillas (dígitos 0-9) de 40 puntos 1D. Se generan instancias de entrenamiento aplicando transformaciones aleatorias (traslación, rotación, ruido) a las plantillas.

**Por qué es útil:** permite comparar CNNs vs MLPs en una escala manejable.

#### Arquitectura CNN

```
x ∈ ℝ^40  (1 canal de entrada)
  ↓ Conv(K=3, Co=15, S=2, P=0) → H₁ ∈ ℝ^{19×15}
  ↓ Conv(K=3, Co=15, S=2, P=0) → H₂ ∈ ℝ^{9×15}
  ↓ Conv(K=3, Co=15, S=2, P=0) → H₃ ∈ ℝ^{4×15}
  ↓ Flatten → vector de 60 elementos
  ↓ FC(60 → 10)
  ↓ Softmax → f ∈ ℝ^10 (probabilidades de clase)
```

Verificación de dimensiones ($D_o = \lfloor(D_i - K)/S\rfloor + 1$):

- $H_1$: $\lfloor(40-3)/2\rfloor + 1 = 19$ ✓
- $H_2$: $\lfloor(19-3)/2\rfloor + 1 = 9$ ✓
- $H_3$: $\lfloor(9-3)/2\rfloor + 1 = 4$ ✓

**Conteo de parámetros:**

- $\boldsymbol{\Omega}_0 \in \mathbb{R}^{1 \times 15 \times 3}$, $\boldsymbol{\beta}_0 \in \mathbb{R}^{15}$: $1 \cdot 15 \cdot 3 + 15 = 60$ params
- $\boldsymbol{\Omega}_1 \in \mathbb{R}^{15 \times 15 \times 3}$, $\boldsymbol{\beta}_1 \in \mathbb{R}^{15}$: $15 \cdot 15 \cdot 3 + 15 = 690$ params
- $\boldsymbol{\Omega}_2 \in \mathbb{R}^{15 \times 15 \times 3}$, $\boldsymbol{\beta}_2 \in \mathbb{R}^{15}$: $15 \cdot 15 \cdot 3 + 15 = 690$ params
- FC: $60 \cdot 10 + 10 = 610$ params
- **Total: $\approx 2{,}050$ parámetros**

#### Red MLP equivalente

Una MLP con el mismo número de capas ocultas y un número similar de unidades ocultas:

- 3 capas ocultas con 285, 135 y 60 unidades respectivamente
- **Total: $\approx 59{,}065$ parámetros** (¡29× más que la CNN!)

#### Resultados comparativos

|Modelo|Parámetros|Error en test|
|:--|:-:|:-:|
|CNN (3 capas conv + FC)|~2,050|~17%|
|MLP (3 capas fully connected)|~59,065|~40%|

La CNN con 29× menos parámetros obtiene más del doble de precisión en el test.

---

### 2.10 Sesgo inductivo y por qué las CNNs generalizan mejor

#### ¿Qué es el sesgo inductivo?

El **sesgo inductivo** es el conjunto de suposiciones que el modelo utiliza para predecir salidas dado inputs que no ha visto durante el entrenamiento. Es el "a priori" estructural que el modelo impone sobre las soluciones que puede encontrar.

#### El sesgo inductivo de las CNNs

La arquitectura CNN impone dos suposiciones sobre la función a aprender:

1. **Localidad:** la respuesta en cada posición depende solo de un vecindario local de la entrada, no de toda la señal.
2. **Equivarianza a la traslación:** la misma característica (borde, textura, patrón) se procesa de la misma manera independientemente de dónde aparezca en la entrada.

Estas suposiciones son correctas para las imágenes: un borde es un borde tanto si está en la esquina superior izquierda como en el centro. En MNIST 1D, los dígitos son plantillas trasladadas aleatoriamente, así que esta suposición es exactamente correcta.

#### Por qué la CNN generaliza mejor aunque la MLP puede replicarla

La MLP con suficiente capacidad puede representar exactamente la misma función que la CNN (la CNN es un caso especial de la MLP). Sin embargo:

- La MLP busca en un espacio de funciones enorme (59,065 parámetros libres).
- La CNN busca solo en el subconjunto de funciones que procesan cada posición igual (2,050 parámetros).
- Todas las funciones en el subconjunto de la CNN son plausibles para el problema.
- La estructura convolucional actúa como un **regularizador que impone una penalización infinita** sobre la mayoría de las soluciones de la MLP.

> Otra forma de verlo: la CNN comparte información entre posiciones. En MNIST 1D, aprende cómo se ve cada categoría independientemente de su posición. La MLP tiene que aprenderlo por separado en cada posición.

---

### 2.11 Backpropagation en capas convolucionales

#### Configuración del ejemplo

Consideramos una red simple:

```
x (6×1) → Conv1D(K=3, Co=1, S=1, P=0) → z₀ (4×1) → a() → h₁ (4×1) → FC → y (1×1)
```

El kernel es $\boldsymbol{\omega}_0 = (w_1, w_2, w_3)^T$ y la convolución produce: $$\mathbf{z}_0 = \begin{bmatrix} w_1 x_1 + w_2 x_2 + w_3 x_3 + \beta_0 \ w_1 x_2 + w_2 x_3 + w_3 x_4 + \beta_0 \ w_1 x_3 + w_2 x_4 + w_3 x_5 + \beta_0 \ w_1 x_4 + w_2 x_5 + w_3 x_6 + \beta_0 \end{bmatrix}$$

En notación matricial: $\mathbf{z}_0 = \mathbf{W} \mathbf{x} + \beta_0 \mathbf{1}$ donde $\mathbf{W}$ es la **matriz de Toeplitz**: $$\mathbf{W} = \begin{bmatrix} w_1 & w_2 & w_3 & 0 & 0 & 0 \ 0 & w_1 & w_2 & w_3 & 0 & 0 \ 0 & 0 & w_1 & w_2 & w_3 & 0 \ 0 & 0 & 0 & w_1 & w_2 & w_3 \end{bmatrix}$$

Suponemos conocido el gradiente $\frac{\partial L}{\partial \mathbf{z}_0} = (a, b, c, d)^T$.

#### Gradiente respecto a la entrada $\mathbf{x}$

$$\frac{\partial L}{\partial \mathbf{x}} = \frac{\partial \mathbf{z}_0}{\partial \mathbf{x}} \cdot \frac{\partial L}{\partial \mathbf{z}_0} = \mathbf{W}^T \cdot \frac{\partial L}{\partial \mathbf{z}_0}$$

$$\mathbf{W}^T = \begin{bmatrix} w_1 & 0 & 0 & 0 \ w_2 & w_1 & 0 & 0 \ w_3 & w_2 & w_1 & 0 \ 0 & w_3 & w_2 & w_1 \ 0 & 0 & w_3 & w_2 \ 0 & 0 & 0 & w_3 \end{bmatrix}$$

Resultado: $$\frac{\partial L}{\partial \mathbf{x}} = \begin{bmatrix} w_1 a \ w_2 a + w_1 b \ w_3 a + w_2 b + w_1 c \ w_3 b + w_2 c + w_1 d \ w_3 c + w_2 d \ w_3 d \end{bmatrix} = r(\boldsymbol{\omega}_0) * \frac{\partial L}{\partial \mathbf{z}_0}$$

donde $r(\boldsymbol{\omega}_0) = (w_1, w_2, w_3)^T$ es el kernel **sin invertir** (en este caso el kernel es igual a su reverso, pero en general sería el kernel original).

> **Resultado clave:** el gradiente hacia atrás respecto a la entrada $\mathbf{x}$ es una **convolución del gradiente** $\frac{\partial L}{\partial \mathbf{z}_0}$ con el kernel original $r(\boldsymbol{\omega}_0)$ (con zero padding para recuperar la dimensión original). El backprop también es una operación de convolución.

#### Gradiente respecto al kernel $\boldsymbol{\omega}_0$

$$\frac{\partial \mathbf{z}_0}{\partial \boldsymbol{\omega}_0} = \begin{bmatrix} x_1 & x_2 & x_3 & x_4 \ x_2 & x_3 & x_4 & x_5 \ x_3 & x_4 & x_5 & x_6 \end{bmatrix}$$

$$\frac{\partial L}{\partial \boldsymbol{\omega}_0} = \frac{\partial \mathbf{z}_0}{\partial \boldsymbol{\omega}_0} \cdot \frac{\partial L}{\partial \mathbf{z}_0} = \begin{bmatrix} x_1 & x_2 & x_3 & x_4 \ x_2 & x_3 & x_4 & x_5 \ x_3 & x_4 & x_5 & x_6 \end{bmatrix} \begin{bmatrix} a \ b \ c \ d \end{bmatrix} = r!\left(\frac{\partial L}{\partial \mathbf{z}_0}\right) * \mathbf{x}$$

donde la convolución es de tipo "valid" del filtro $(d, c, b, a)^T$ con la entrada $\mathbf{x}$.

> **Resultado clave:** el gradiente respecto al kernel es también una convolución: es la correlación cruzada entre el gradiente $\frac{\partial L}{\partial \mathbf{z}_0}$ y la entrada $\mathbf{x}$.

**Resumen del backprop en capas convolucionales:**

- Gradiente hacia $\mathbf{x}$: convolución del gradiente $\frac{\partial L}{\partial \mathbf{z}_0}$ con el kernel (con padding completo).
- Gradiente hacia $\boldsymbol{\omega}$: correlación cruzada ("valid") entre la entrada $\mathbf{x}$ y el gradiente $\frac{\partial L}{\partial \mathbf{z}_0}$.
- Gradiente hacia $\beta$: suma de todos los elementos de $\frac{\partial L}{\partial \mathbf{z}_0}$.

---

## 3. CNNs en 2D

### 3.1 Convolución 2D

Para imágenes 2D, el kernel es ahora un objeto bidimensional. Para un kernel $\boldsymbol{\Omega} \in \mathbb{R}^{K \times K}$ aplicado a una imagen 2D con elementos $x_{ij}$, la activación de salida en la posición $(i,j)$ es:

$$h_{ij} = a!\left[\beta + \sum_{m=1}^{K} \sum_{n=1}^{K} \omega_{mn} , x_{i+m-\lceil K/2 \rceil, j+n-\lceil K/2 \rceil}\right]$$

Para $K=3$: $$h_{ij} = a!\left[\beta + \sum_{m=1}^{3}\sum_{n=1}^{3} \omega_{mn} x_{i+m-2, j+n-2}\right]$$

El kernel se traslada tanto horizontal como verticalmente a través de la imagen 2D, generando una salida en cada posición (figura: imagen de entrada → kernel deslizante → mapa de activación).

#### Tamaño de salida en 2D

Para una imagen de entrada $H_i \times W_i$ con kernel $K_H \times K_W$, stride $(S_H, S_W)$ y padding $(P_H, P_W)$: $$H_o = \left\lfloor \frac{H_i - K_H + 2P_H}{S_H} + 1 \right\rfloor, \qquad W_o = \left\lfloor \frac{W_i - K_W + 2P_W}{S_W} + 1 \right\rfloor$$

En la práctica suele usarse $K_H = K_W = K$ (kernel cuadrado) y $S_H = S_W = S$.

---

### 3.2 Canales en 2D y número de parámetros

Para una imagen RGB (3 canales), el kernel es un tensor $\boldsymbol{\Omega} \in \mathbb{R}^{3 \times K \times K}$: 3 planos 2D de pesos, uno por canal de entrada. La preactivación en cada posición es la suma de las convoluciones de cada plano de $\boldsymbol{\Omega}$ con su canal de entrada correspondiente, más el sesgo.

**Caso general:**

- $C_i$ canales de entrada, kernel $K \times K$, **1 canal de salida:** $\boldsymbol{\Omega} \in \mathbb{R}^{C_i \times K \times K}$, $\beta \in \mathbb{R}$ → $C_i \cdot K^2 + 1$ parámetros.
- $C_i$ canales de entrada, $C_o$ canales de salida: $\boldsymbol{\Omega} \in \mathbb{R}^{C_i \times C_o \times K \times K}$, $\boldsymbol{\beta} \in \mathbb{R}^{C_o}$ → $C_i \cdot C_o \cdot K^2 + C_o$ parámetros.

$$\boxed{\text{Parámetros conv 2D} = C_i \cdot C_o \cdot K^2 + C_o}$$

**Ejemplo:** primera capa de una red que procesa imágenes RGB ($C_i=3$) con 64 filtros ($C_o=64$) de tamaño $3\times 3$: $3 \cdot 64 \cdot 9 + 64 = 1{,}728 + 64 = 1{,}792$ parámetros.

---

### 3.3 Downsampling (reducción de resolución)

A medida que la red se hace más profunda, queremos reducir la resolución espacial para aumentar el campo receptivo y reducir el coste computacional. Hay tres métodos principales:

#### 1. Stride 2 (submuestreo directo)

Usar stride 2 en la convolución (o simplemente quedarse con uno de cada dos píxeles). La resolución se reduce a la mitad en cada dimensión. No tiene parámetros adicionales.

#### 2. Max pooling

Se divide el mapa de activación en bloques de 2×2 (o $P\times P$) y se retiene solo el **valor máximo** de cada bloque:

$$h_{\text{pool},i,j} = \max_{(m,n) \in \text{bloque}(i,j)} h_{m,n}$$

**Ventaja:** induce **invarianza parcial a traslación** dentro del bloque. Si la entrada se desplaza un píxel, el máximo del bloque puede ser el mismo valor en una posición diferente, haciendo que la salida sea igual. Esto es útil cuando queremos detectar si una característica _está presente_ en una región, independientemente de su posición exacta.

**Desventaja:** pérdida de información de localización precisa (útil para clasificación, pero problemático para segmentación pixel a pixel).

#### 3. Mean pooling (average pooling)

Igual que max pooling pero tomando la **media** en lugar del máximo: $$h_{\text{pool},i,j} = \frac{1}{|P|^2}\sum_{(m,n) \in \text{bloque}(i,j)} h_{m,n}$$

Produce representaciones más suaves. Históricamente fue el método original (LeCun 1989); el max pooling lo reemplazó porque empíricamente obtiene mejores resultados.

|Método|Parámetros|Invarianza|Uso típico|
|:--|:-:|:-:|:--|
|Stride 2|0|Parcial|Siempre|
|Max pooling|0|Mayor|Clasificación|
|Average pooling|0|Menor (suavizado)|Clasificación, reducción final|

---

### 3.4 Upsampling (aumento de resolución)

En redes que producen una salida del mismo tamaño que la entrada (como segmentación semántica), necesitamos después de hacer downsampling volver a aumentar la resolución.

#### 1. Duplicación de elementos (nearest neighbor)

Duplicar cada elemento cuatro veces (2×2 copia de cada pixel). Es el método más simple y más rápido, sin parámetros.

#### 2. Max unpooling

Se usa donde previamente se realizó max pooling. Se guarda la posición del máximo durante el forward pass (max pooling), y en el upsampling se coloca el valor en esa posición y se ponen ceros en el resto del bloque 2×2. Requiere recordar las posiciones de los máximos.

#### 3. Interpolación bilineal

Para cada posición entre puntos de la cuadrícula de baja resolución, se interpola linealmente en ambas dimensiones. No tiene parámetros y produce resultados más suaves que la duplicación simple.

#### 4. Convolución traspuesta (transposed convolution / deconvolution)

Ver sección siguiente.

---

### 3.5 Convolución traspuesta

La **convolución traspuesta** (también llamada "deconvolución" aunque este nombre es incorrecto técnicamente) es la operación inversa de la convolución en términos de dimensiones de entrada/salida.

#### Motivación

Si una convolución con stride 2 reduce una señal de 8 elementos a 4, queremos una operación que lleve 4 elementos de vuelta a 8.

#### Cómo funciona

Con una convolución normal de stride 2 y kernel 3, la relación entrada-salida es: $$\mathbf{z} = \mathbf{W}\mathbf{x}, \qquad \mathbf{W} \in \mathbb{R}^{4 \times 8}$$

La convolución traspuesta usa $\mathbf{W}^T \in \mathbb{R}^{8 \times 4}$, multiplicando el input de baja resolución por la matriz traspuesta: $$\mathbf{y} = \mathbf{W}^T \mathbf{z}, \qquad \mathbf{y} \in \mathbb{R}^8$$

Visualmente: en la convolución normal cada salida recibe contribuciones de 3 inputs. En la traspuesta, cada input contribuye a 3 outputs, y donde los outputs se solapan, se suman.

#### Propiedades importantes

- La convolución traspuesta **no es la inversa matemática** de la convolución. En general, $\mathbf{W}^T\mathbf{W}\mathbf{x} \neq \mathbf{x}$ (a menos que $\mathbf{W}^T\mathbf{W} = \mathbf{I}$).
- Cuando se usa en una red, el filtro **se aprende de nuevo** durante el entrenamiento (no es el filtro original del downsampling).
- Puede producir **artefactos en tablero de ajedrez** (_checkerboard artifacts_) cuando los pesos del kernel no se inicializan cuidadosamente.

#### Equivalencia con convolución 2D como capa lineal

Una convolución 2D se puede expresar como multiplicación matricial. Si aplanamos la entrada por filas (vectorizamos), la convolución es equivalente a multiplicar por una **matriz circulante por bloques** sparse con valores repetidos. La convolución traspuesta es la multiplicación por la transpuesta de esta matriz.

---

### 3.6 Convolución 1×1

La convolución con kernel de tamaño $1\times1$ (o $1$ en 1D) **no combina información espacial**: solo combina los $C_i$ canales de entrada en cada posición de forma independiente.

Equivale a aplicar la **misma red fully connected** (con $C_i$ entradas y $C_o$ salidas) en cada posición espacial de forma independiente.

**Usos:**

- Cambiar el número de canales entre capas (reducir o aumentar $C_i \rightarrow C_o$) sin afectar la resolución espacial.
- En arquitecturas como ResNet y GoogLeNet para reducir la dimensionalidad antes de la convolución 3×3 (bottleneck).
- Combinar información entre canales.

Parámetros de una convolución 1×1: $C_i \cdot C_o + C_o$.

---

### 3.7 Arquitecturas clásicas para clasificación de imágenes

#### LeNet (LeCun et al., 1989)

La primera CNN entrenada con backpropagation. Usada para reconocimiento de dígitos escritos a mano (zip codes de la USPS).

**Características:**

- Imágenes 16×16 en escala de grises (versión original) o 28×28 (MNIST).
- Activación: tanh (no ReLU, que vendría después).
- Pooling: average pooling.
- Dataset: 7,291 entrenamiento, 2,007 test. Éxito: ~95%.
- Primer uso sistemático de: topología espacial, compartición de pesos, submuestreo (pooling) y FC al final como clasificador.

#### ImageNet Dataset y el desafío ILSVRC

ImageNet es el benchmark que impulsó la revolución del deep learning en visión:

- 1,281,167 imágenes de entrenamiento, 50,000 validación, 100,000 test.
- 1,000 clases.
- Imágenes 224×224 RGB.
- Dificultad: gran variación en rigidez, número de instancias, desorden, tamaño, textura, color y forma.

Evolución del error top-5 en el ILSVRC:

- 2011 (Lin et al., red shallow): ~28%
- 2012 (AlexNet): 16.4%
- 2014 (VGG): 6.8%
- 2015 (ResNet, 152 capas): 3.6%
- 2017 (SENet): 2.3%
- Rendimiento humano: ~5.1%

#### AlexNet (Krizhevsky, Sutskever, Hinton — 2012)

El punto de partida de la era moderna del deep learning en visión.

**Arquitectura:**

```
224×224×3 → Conv(11×11, S=4, 96 canales) → MaxPool → 
Conv(5×5, 256 canales) → MaxPool →
Conv(3×3, 384) → Conv(3×3, 384) → Conv(3×3, 256) → MaxPool →
FC(4096) → FC(4096) → FC(1000) → Softmax
```

**Características principales:**

- 650K neuronas, ~60M parámetros, 630M conexiones.
- **Primer modelo convolucional profundo** en usar ReLU (más rápido que tanh/sigmoid).
- **Group convolutions:** los canales se dividen entre 2 GPUs (limitación de hardware, 2 NVIDIA GTX 580).
- **Data augmentation:** 5 crops + flip en test, resultados promediados.
- **Regularización:** L2 weight decay + Dropout ($p=0.5$) en las dos últimas capas FC.
- **Ensemble de 7 CNNs:** top-5 error = 16.4%, top-1 = 38.1%.
- La mayor parte de los 60M parámetros está en las **capas FC** del final.

#### VGGNet (Simonyan & Zisserman — 2015, ICLR)

Demostró que la profundidad es el factor clave para el rendimiento.

**Principio de diseño:** usar exclusivamente filtros 3×3 con stride 1, intercalados con max pooling 2×2 con stride 2. En cada pooling: **resolución ÷ 2, canales × 2**.

**¿Por qué solo filtros 3×3?**

Dos capas convolucionales 3×3 tienen el mismo campo receptivo que una capa 5×5, pero:

- Más no linealidad (dos aplicaciones de ReLU en lugar de una).
- Menos parámetros: $2 \times C^2 \times 9 = 18C^2$ vs $C^2 \times 25 = 25C^2$.

Tres capas conv 3×3 tienen el campo receptivo de una sola 7×7, con aún mayor ahorro en parámetros.

**Versión D (VGG-16, 16 capas con pesos):** 144M parámetros, top-5 error = 6.8%.  
**Versión E (VGG-19, 19 capas con pesos):** top-5 error = 6.1%.

Ensemble 7 CNNs: top-5 = 7.5%, top-1 = 24.7%.

---

### 3.8 Redes para salida imagen: segmentación semántica

En **segmentación semántica** el objetivo es asignar una etiqueta de clase a cada píxel de la imagen. La salida tiene la misma resolución espacial que la entrada.

#### Arquitectura Encoder-Decoder

La solución más común es una arquitectura en forma de reloj de arena (_hourglass_):

1. **Encoder (parte descendente):** aplica capas convolucionales + pooling para reducir la resolución progresivamente mientras aumenta el número de canales. Aprende representaciones abstractas de alto nivel con gran campo receptivo. Típicamente basado en una red de clasificación (VGG, ResNet...).
    
2. **Decoder (parte ascendente):** aplica upsampling + convoluciones traspuestas para recuperar progresivamente la resolución espacial hasta llegar al tamaño original de la imagen.
    

#### Ejemplo: Red de Noh et al. (2015)

```
Input 224×224 →
  Encoder (VGG-D adaptado, 16 capas conv):
    224×224→112×112→56×56→28×28→14×14→7×7
    (Conv+ReLU+MaxPool en cada etapa, canales: 3→64→128→256→512→512)
  FC(4096) → FC(4096): combina info global de toda la imagen
  FC → 7×7×512: reconstituye representación espacial
  Decoder (imagen especular del encoder):
    MaxUnpooling + Conv(traspuesta sin stride) en cada etapa
    7×7→14×14→28×28→56×56→112×112→224×224
  Conv 1×1 → 224×224×21 (21 clases)
  Softmax por posición → mapa de probabilidades de clase
```

---

### 3.9 Redes Residuales (ResNets)

#### El problema: las redes muy profundas se vuelven más difíciles de entrenar

Añadir más capas (más allá de ~20 en VGG-style) **empeora** el rendimiento, tanto en train como en test. Esto es sorprendente porque se esperaría que más parámetros pudieran al menos mantener el rendimiento (si las capas extra aprenden la identidad).

**Experimento de He et al. (2016):** en CIFAR-10, una red de 56 capas obtiene mayor error que una de 20 capas, tanto en entrenamiento como en test. El problema no es el overfitting — es que el **optimizador no puede entrenar bien redes tan profundas**.

**Fenómeno de gradientes fragmentados (shattered gradients):** en redes profundas, una pequeña modificación de los parámetros de la primera capa produce un gradiente de salida completamente diferente. Los gradientes vecinos (para inputs similares) se vuelven incorrelados, haciendo que la superficie de pérdida sea como "una montaña de agujas" en lugar de una función suavemente descendent. El descenso de gradiente no puede progresar en estas condiciones.

**Observación clave de He et al.:** si las capas extra de la red de 34 capas aprendieran la función identidad, su rendimiento sería al menos igual que el de 18 capas. Pero el optimizador no logra aprender la identidad en capas profundas.

#### La idea de los bloques residuales

En lugar de que cada capa aprenda directamente la función deseada $H(\mathbf{x})$, que aprenda el **residuo**: $$F(\mathbf{x}) = H(\mathbf{x}) - \mathbf{x}$$

Y entonces $H(\mathbf{x}) = F(\mathbf{x}) + \mathbf{x}$. En el grafo computacional, esto se implementa con una **conexión residual** (skip connection) que suma la entrada a la salida de la capa:

```
     x
    / \
   /   \
  F(x)  x  (residual connection)
   \   /
    \ /
    F(x) + x = H(x)
      |
     ReLU
```

**¿Por qué es más fácil aprender el residuo?** Si la capa óptima es la identidad (o casi), entonces $F(\mathbf{x}) \approx 0$. Es más fácil empujar los pesos a 0 que hacer que la capa compute exactamente la identidad.

#### Ecuaciones de un bloque residual

Red estándar (sin conexión residual): $$\mathbf{h}_k = f_k[\mathbf{h}_{k-1}, \boldsymbol{\phi}_k]$$

Red con conexiones residuales (ResNet): $$\mathbf{h}_k = \mathbf{h}_{k-1} + f_k[\mathbf{h}_{k-1}, \boldsymbol{\phi}_k]$$

La salida final "desenvuelta" es una suma de la entrada más múltiples redes menores: $$\mathbf{y} = \mathbf{x} + f_1[\mathbf{x}] + f_2[\mathbf{x} + f_1[\mathbf{x}]] + f_3[\ldots] + f_4[\ldots]$$

Esto puede interpretarse como un **ensemble de redes de diferentes profundidades** cuyas salidas se suman.

Adicionalmente, el gradiente respecto a la primera capa es: $$\frac{\partial \mathbf{y}}{\partial f_1} = \mathbf{I} + \frac{\partial f_2}{\partial f_1} + \cdots$$

El término identidad $\mathbf{I}$ garantiza que siempre hay al menos un camino con gradiente no nulo, mitigando el problema de vanishing gradients.

#### Arquitectura ResNet

**Bloque básico (ResNet-18, ResNet-34):**

```
x → BN → ReLU → Conv(3×3) → BN → ReLU → Conv(3×3) → ⊕ → output
  ↘_____________________________________________↗ (residual connection)
```

**Bloque bottleneck (ResNet-50, ResNet-101, ResNet-152):** para reducir el coste computacional en redes más profundas, se usa un bloque de tres capas:

```
x → BN→ReLU→Conv(1×1, reduce canales ÷4)  → BN→ReLU→Conv(3×3) → BN→ReLU→Conv(1×1, aumenta canales ×4) → ⊕ → output
  ↘_______________________________________________________________________________↗
```

El bloque bottleneck tiene complejidad similar al bloque all-3×3 pero permite redes más profundas.

**Estilo de diseño ResNet (siguiendo VGG):**

- Solo convoluciones 3×3 (stride 1).
- Max pooling 2×2, stride 2.
- Cada vez que se hace pooling, se dobla el número de filtros.
- 1 única capa FC al final.
- **Batch Normalization** después de cada convolución.
- **Sin Dropout** (el BN hace esa función).
- Data augmentation extensivo.

#### ¿Por qué batch normalization es imprescindible en ResNets?

Con la inicialización de He, la varianza de las activaciones es constante a través de las capas lineales. Pero en los nodos de suma de las conexiones residuales: $$\text{Var}(\mathbf{h}_k) = \text{Var}(\mathbf{h}_{k-1} + f_k[\mathbf{h}_{k-1}])$$

Si $\mathbf{h}_{k-1}$ y $f_k[\mathbf{h}_{k-1}]$ son independientes e identicamente distribuidos: $$\text{Var}(\mathbf{h}_k) = \text{Var}(\mathbf{h}_{k-1}) + \text{Var}(f_k) = 2 \cdot \text{Var}(\mathbf{h}_{k-1})$$

La varianza se **duplica** en cada bloque residual. Después de $K$ bloques, la varianza es $2^K$ veces la inicial, lo que produce exploding gradients.

Batch normalization compensa esto normalizando las activaciones después de cada nodo de suma, manteniendo la varianza aproximadamente constante.

#### Variantes del bloque básico

He et al. (2016) estudiaron el orden óptimo de las operaciones:

**Versión a (orden original):** Conv → BN → ReLU → Conv → BN → ⊕ → ReLU

- Limitación: solo puede añadir valores no negativos (ReLU antes de la suma).

**Versión b (pre-activation, recomendada):** BN → ReLU → Conv → BN → ReLU → Conv → ⊕

- Puede añadir valores positivos y negativos al residuo.
- Añadir una capa lineal al principio de la red para el caso de que la entrada sea todo negativo.
- Esta variante es la que obtiene mejores resultados y es la que se usa en ResNet-200.

#### Resultados

Con ResNets, el rendimiento mejora **monotónicamente** con la profundidad (algo que no sucedía con redes plain):

- ResNet-18: ~30% error en ImageNet plain-18 vs ~30% ResNet-18 (similar)
- ResNet-34: error mucho menor que la versión plain
- ResNet-152: ganó ILSVRC 2015 con 3.6% top-5 error

---

### 3.10 U-Net y Stacked Hourglass Networks

#### U-Net (Ronneberger et al., 2016)

U-Net es una red encoder-decoder para segmentación de imágenes biomédicas que añade una innovación crucial respecto al encoder-decoder básico: **conexiones skip entre el encoder y el decoder**.

**Arquitectura:**

```
Input (572×572)
  Encoder:
    Conv+ReLU→Conv+ReLU→MaxPool (×4 niveles, 572→284→140→68→32×32)
    Canales: 1→64→128→256→512→1024 (bottleneck)
  Decoder:
    Transposed Conv (upsampling ×2) + Concatenar con feature map del encoder correspondiente + Conv+ReLU→Conv+ReLU (×4)
  Output: Conv 1×1 → 388×388×2 (segmentación)
```

**Innovación principal — conexiones skip (crop and concatenate):** En cada nivel del decoder, se concatena el feature map del decoder con el feature map correspondiente del encoder (recortado para que tengan el mismo tamaño). Esto permite al decoder acceder tanto a:

- Información de **alto nivel** (qué objeto es) que viene del bottleneck.
- Información de **bajo nivel** (bordes, texturas, localización precisa) que viene directamente del encoder.

**Ventajas:**

- Excelente localización espacial precisa en la segmentación.
- Funciona bien con pocos datos de entrenamiento (crítico en imágenes médicas).
- La arquitectura simétrica proporciona caminos de gradiente cortos entre entrada y salida.

**Uso típico:** segmentación de imágenes médicas (células, órganos), donde la precisión de la delimitación es crítica.

#### Stacked Hourglass Networks (Newell et al., 2016)

Diseñada específicamente para **estimación de pose humana** (detectar las articulaciones del cuerpo humano en una imagen).

**Conceptos clave:**

1. **Bloque Hourglass:** un solo módulo encoder-decoder (con estructura similar a U-Net, usando conexiones skip por suma en lugar de concatenación). Produce mapas de calor (heatmaps) de las localizaciones de las articulaciones.
    
2. **Apilamiento de bloques (stacking):** se apilan múltiples bloques hourglass en serie. La salida de un hourglass alimenta al siguiente. Esto permite refinar iterativamente la estimación de pose.
    
3. **Supervisión intermedia:** cada bloque hourglass produce su propia predicción de pose, y se calcula una pérdida en cada uno. Esto facilita el entrenamiento de la red completa por propagación de gradientes.
    

**Intuición:** el primer hourglass procesa la imagen de forma global, estimando una pose inicial aproximada. Los siguientes hourglasses refinan esta estimación incorporando el contexto que viene de la predicción anterior.

---

## 4. Resumen y referencia rápida

### Propiedades de las capas convolucionales

|Propiedad|Descripción|
|:--|:--|
|Localidad|Cada parámetro afecta solo a una región local|
|Compartición de pesos|El mismo kernel se aplica en todas las posiciones|
|Equivarianza a traslación|Si la entrada se traslada, la salida también se traslada|
|Reducción de parámetros|$K + 1$ vs $D^2 + D$ para la FC equivalente|

### Fórmulas clave

**Tamaño de salida (1D y 2D):** $$D_o = \left\lfloor \frac{D_i - K + 2P}{S} + 1 \right\rfloor$$

**Número de parámetros:**

|Tipo|Parámetros (pesos + sesgos)|
|:--|:--|
|Conv 1D, $C_i$ entradas, $C_o$ salidas, kernel $K$|$C_i \cdot C_o \cdot K + C_o$|
|Conv 2D, $C_i$ entradas, $C_o$ salidas, kernel $K\times K$|$C_i \cdot C_o \cdot K^2 + C_o$|
|Conv 1×1, $C_i$ entradas, $C_o$ salidas|$C_i \cdot C_o + C_o$|
|FC, $D_i$ entradas, $D_o$ salidas|$D_i \cdot D_o + D_o$|

**Campo receptivo** (kernel K, stride 1, sin dilatación): $$\text{RF}_k = \text{RF}_{k-1} + (K-1) \qquad \text{con } \text{RF}_1 = K$$

**Backpropagation en convolución 1D:** $$\frac{\partial L}{\partial \mathbf{x}} = r(\boldsymbol{\omega}) * \frac{\partial L}{\partial \mathbf{z}} \qquad \frac{\partial L}{\partial \boldsymbol{\omega}} = r!\left(\frac{\partial L}{\partial \mathbf{z}}\right) * \mathbf{x}$$

### Métodos de downsampling y upsampling

|Operación|Método|Parámetros|Aprendible|
|:--|:--|:-:|:-:|
|Downsampling|Stride 2|0|No|
|Downsampling|Max pooling|0|No|
|Downsampling|Average pooling|0|No|
|Upsampling|Duplicación|0|No|
|Upsampling|Max unpooling|0|No|
|Upsampling|Interpolación bilineal|0|No|
|Upsampling|Convolución traspuesta|$C_i \cdot C_o \cdot K^2$|Sí|

### Arquitecturas históricas clave

|Año|Modelo|Capas|Parámetros|Top-5 error|
|:-:|:-:|:-:|:-:|:-:|
|1989|LeNet|5|~60K|N/A|
|2012|AlexNet|8|~60M|16.4%|
|2015|VGGNet-19|19|144M|6.1%|
|2015|ResNet-152|152|~60M|3.6%|
|2016|ResNet-200|200|~64M|3.0%|
|~2021|Human|—|—|~5.1%|

### Invarianza vs equivarianza (resumen)

|Propiedad|Definición|Ejemplo|
|:--|:--|:--|
|Invarianza|$f[t[\mathbf{x}]] = f[\mathbf{x}]$|Clasificación: misma clase si imagen se traslada|
|Equivarianza|$f[t[\mathbf{x}]] = t[f[\mathbf{x}]]$|Segmentación: si imagen se traslada, la seg. también|

Las **capas convolucionales** son equivariantes a traslación. El **max pooling** introduce invarianza parcial.

### Bloque residual básico (ResNet)

```
         x
        / \
       /   \
  F(x) = BN → ReLU → Conv → BN → ReLU → Conv
       \   /
        ⊕
        |
       ReLU
     H(x) = F(x) + x
```

La red aprende $F(\mathbf{x}) = H(\mathbf{x}) - \mathbf{x}$ (los residuos), lo que facilita aprender la identidad si fuese necesario.

---

## Referencias

- Prince, S.J.D. (2023). _Understanding Deep Learning_. MIT Press. Capítulos 10 y 11. [Acceso libre]
- LeCun, Y., Boser, B., Denker, J.S., et al. (1989). Backpropagation Applied to Handwritten Zip Code Recognition. _Neural Computation_, 1(4): 541–551.
- Krizhevsky, A., Sutskever, I., & Hinton, G. (2012). ImageNet Classification with Deep Convolutional Neural Networks. _NeurIPS_, 25: 1097–1105.
- Simonyan, K. & Zisserman, A. (2014). Very Deep ConvNets for Large-Scale Image Recognition. _ICLR 2015_.
- He, K., Zhang, X., Ren, S. & Sun, J. (2016). Deep Residual Learning for Image Recognition. _CVPR 2016_.
- He, K., Zhang, X., Ren, S. & Sun, J. (2016). Identity Mappings in Deep Residual Networks. _ECCV 2016_.
- Noh, H., Hong, S. & Han, B. (2015). Learning Deconvolution Network for Semantic Segmentation. _ICCV 2015_: 1520–1528.
- Ronneberger, O., Fischer, P. & Brox, T. (2015). U-Net: Convolutional Networks for Biomedical Image Segmentation. _MICCAI 2015_.
- Newell, A., Yang, K. & Deng, J. (2016). Stacked Hourglass Networks for Human Pose Estimation. _ECCV 2016_.
- Marcos, D., Volpi, M., Komodakis, N. & Tuia, D. (2017). Rotation Equivariant Vector Field Networks. _ICCV 2017_: 5058–5067.
- Levine, S. (2021). Deep Learning: CS 182. Lecture 6. UC Berkeley. [YouTube]