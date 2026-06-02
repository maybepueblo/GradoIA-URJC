### Aprendizaje Automático II · Grado en IA · Universidad Rey Juan Carlos
**Basado en:** Diapositivas del Tema 7 + *Understanding Deep Learning*, Capítulos 14 y 15 (Prince, MIT Press)

---

## Índice

1. [7.1 · Aprendizaje de Representaciones](#1.Aprendizaje de Representaciones)
   - 1.1 ¿Qué aprende una CNN profunda? El espacio latente
   - 1.2 ¿Qué es una representación?
   - 1.3 Representaciones jerárquicas profundas
   - 1.4 Transfer Learning (Aprendizaje por Transferencia)
   - 1.5 Multi-task Learning (Aprendizaje Multi-tarea)
   - 1.6 Self-supervised Learning (Aprendizaje Auto-supervisado)
   - 1.7 Domain Adaptation (Adaptación de Dominio)
2. [7.2 · Modelos Generativos](#2-modelos-generativos)
   - 2.1 Taxonomía del aprendizaje no supervisado
   - 2.2 Variables latentes
   - 2.3 ¿Qué hace bueno a un modelo generativo?
   - 2.4 Métricas para evaluar modelos generativos
   - 2.5 Generative Adversarial Networks (GANs)
   - 2.6 Función de pérdida de la GAN
   - 2.7 Entrenamiento de la GAN: el problema minimax
   - 2.8 DCGAN: GAN convolucional profunda
   - 2.9 Problemas de entrenamiento: mode collapse y vanishing gradients
   - 2.10 Wasserstein GAN (WGAN)
   - 2.11 GANs condicionadas
   - 2.12 CycleGAN y traducción de imágenes
   - 2.13 StyleGAN
3. [Resumen y referencia rápida](#3-resumen-y-referencia-rápida)

---

## 1.Aprendizaje de Representaciones

### 1.1 ¿Qué aprende una CNN profunda? El espacio latente

Para entender por qué el aprendizaje de representaciones importa, es útil mirar concretamente qué aprende AlexNet al ser entrenada en ImageNet.

#### Kernels de la primera capa convolucional

Los 96 kernels de 11×11×3 de la primera capa convolucional de AlexNet son interpretables directamente: han aprendido detectores de **bordes orientados**, **gradientes de color** y **patrones de frecuencia espacial** — similares a los campos receptivos de las células simples de la corteza visual primaria (V1) biológica.

**Por qué esto es así:** en la correlación cruzada, el filtro $\boldsymbol{\omega}$ y el parche de entrada $\mathbf{p}$ producen la respuesta máxima cuando $\boldsymbol{\omega} \cdot \mathbf{p} = \|\boldsymbol{\omega}\|\|\mathbf{p}\|\cos\alpha$ es máximo, lo que ocurre cuando $\alpha=0$, es decir, cuando el parche de entrada es igual al kernel. El filtro *detecta el patrón que tiene la misma forma que sus pesos*. Si el kernel tiene forma de borde vertical, la neurona produce la máxima activación donde la imagen tiene un borde vertical.

#### Capas más profundas: emergen detectores de objetos

En las capas intermedias y profundas, los kernels ya no son directamente visualizables (son combinaciones de features previas), pero al observar las **activaciones** (los mapas de respuesta a imágenes reales) se observa algo fascinante:

- En capas intermedias (ej. capa conv5): algunas neuronas se activan específicamente ante **partes de objetos** (ojos, ruedas, texturas específicas).
- En las capas FC profundas: neuronas que responden a **objetos completos** (caras, coches, pájaros).
- Todo esto emerge **sin que se hayan proporcionado etiquetas** para esas partes u objetos intermedios — solo se usaron etiquetas de clase final para el entrenamiento supervisado.

#### El espacio latente y el embedding

La **última capa fully connected** (4096-dimensional en AlexNet antes del clasificador) produce un **descriptor** o **embedding** de cada imagen: un vector en $\mathbb{R}^{4096}$ que captura el contenido semántico de la imagen.

Este espacio de 4096 dimensiones se llama **espacio latente** o *embedding space*. En él:

- Imágenes del mismo objeto son vecinas (distancia L2 pequeña).
- La distancia L2 en el espacio latente mide similitud semántica, **no** similitud de píxeles.
- La distancia L2 funciona incluso cuando el contenido de la imagen varía en pose y escala — algo que directamente en el espacio de píxeles sería imposible.

Este resultado experimental demuestra que la red ha aprendido una **representación** del contenido semántico que abstrae las variaciones irrelevantes (iluminación, viewpoint, escala).

---

### 1.2 ¿Qué es una representación?

Una **representación** es un sistema formal que:
- **Hace explícitas** ciertas entidades y tipos de información.
- **Puede ser manipulada** por un algoritmo para lograr alguna meta de procesamiento de información.

Las representaciones difieren en qué información hacen explícita y qué algoritmos permiten sobre ellas.

> Una red de neuronas profunda **es una representación** de un problema que emerge del proceso de entrenamiento.

La red no solo resuelve la tarea para la que fue entrenada — también construye, de forma implícita, una representación interna del mundo que puede ser útil para otras tareas relacionadas.

---

### 1.3 Representaciones jerárquicas profundas

#### ¿Por qué funcionan bien las representaciones profundas?

Las representaciones profundas emergen al construir modelos del mundo suficientemente complejos, con datos en cantidad razonable (aunque siempre limitada). Los modelos profundos ofrecen dos ingredientes clave:

1. **Representaciones jerárquicas:** el deep learning aprende representaciones organizadas en múltiples niveles de abstracción, análogos a la jerarquía que usamos en el lenguaje (entidad → animal → mamífero → felino → gato doméstico).

2. **Mecanismos potentes de regularización:** la profundidad, el peso compartido y la localidad imponen fuertes sesgos inductivos que actúan como regularizadores implícitos.

#### La jerarquía de representaciones en CNNs (observada empíricamente)

| Capa | Tipo de representación detectada |
|:---|:---|
| Conv 1 | Bordes, gradientes de color, frecuencias (Edges + Blobs) |
| Conv 3 | Texturas, patrones locales |
| Conv 5 | Partes de objetos (Object Parts) |
| FC 8 | Clases de objetos completos (Object Classes) |

Esta jerarquía es similar a la que utiliza el sistema visual humano (V1 → V2 → V4 → IT cortex).

#### Ventaja de las representaciones jerárquicas

> Una red neuronal profunda puede descubrir características que **generalizan mejor** a muestras no vistas, por lo que requieren menos datos de entrenamiento.

Recordatorio de la **eficiencia de profundidad** (Tema 5): hay funciones que requieren una red shallow con un número exponencialmente mayor de unidades para lograr una aproximación equivalente a la de una red profunda. Las representaciones jerárquicas explotan esta propiedad.

#### Representaciones supervisadas vs. no supervisadas

Las representaciones aprendidas por una red profunda están guiadas por la tarea de aprendizaje utilizada:

- **Supervisada:** la representación dependerá del clasificador/función de pérdida. Estará optimizada para discriminar entre las clases de entrenamiento, pero puede ser menos general.
- **No supervisada:** será más general (no está sesgada hacia una tarea concreta) y se podrá reutilizar con mayor facilidad en otras tareas downstream.

---

### 1.4 Transfer Learning (Aprendizaje por Transferencia)

#### Motivación: eficiencia de datos

El principal reto en deep learning es la **necesidad de grandes cantidades de datos etiquetados**. Etiquetar datos es caro y lento. Transfer learning permite aprovechar representaciones ya aprendidas en datasets grandes para resolver nuevas tareas con pocos datos.

#### Definición

**Transfer Learning:** el modelo resuelve 2 o más tareas diferentes, pero muchos factores que explican las variaciones en la Tarea 1 (T1) también lo hacen en la Tarea 2 (T2).

- Se aplica a aprendizaje supervisado donde la entrada es parecida pero la salida es de diferente naturaleza.
- La idea: entrenar una representación con los muchos datos de T1 y reutilizarla en T2 con pocos datos.

**Ejemplo concreto:** T1 = clasificación de gatos/perros (muchos datos), T2 = clasificación de hormigas/avispas (pocos datos). La representación de bordes, texturas y formas aprendida en T1 es directamente útil en T2.

#### ¿Por qué funcionan las tareas relacionadas?

El trabajo *Taskonomy* (Zamir et al., CVPR 2018) estudió cuantitativamente las relaciones entre 48 tareas de visión:

- Las tareas tienen **relaciones densas**: muchas tareas comparten factores explicativos.
- Existe **redundancia**: algunas tareas se pueden resolver bien a partir de otras.
- Esto implica **eficiencia de supervisión**: transferir desde tareas relacionadas permite lograr buenos resultados con solo el 2% de los datos necesarios para entrenar desde cero.

**Ejemplo del paper:** estimar normales de superficie a partir de 2% de los datos usando una red pre-entrenada en reshading o segmentación produce resultados similares a entrenar desde cero con el 100% de los datos.

#### Protocolo de Transfer Learning

**Opción A — Feature extraction (extractor de características):**
```
[Modelo pre-entrenado en T1 (congelado)] → [Nuevas capas FC para T2 (entrenadas)]
```
Solo se entrenan las capas nuevas. Adecuado cuando T2 tiene muy pocos datos.

**Opción B — Fine-tuning:**
```
[Modelo pre-entrenado en T1 (descongelado parcialmente o totalmente)] → [Entrenamiento en T2]
```
Todo el modelo (o las capas más profundas) se ajusta en T2. Adecuado cuando T2 tiene más datos y las distribuciones son suficientemente similares.

**Regla práctica:**
- Datos T2 pequeños + T1 y T2 similares → Feature extraction.
- Datos T2 grandes + T1 y T2 similares → Fine-tuning del modelo completo.
- Datos T2 pequeños + T1 y T2 muy diferentes → Solo capas iniciales (features más generales).

---

### 1.5 Multi-task Learning (Aprendizaje Multi-tarea)

#### Definición

**Multi-task Learning (MTL):** estrategia de aprendizaje en la que múltiples tareas se resuelven **simultáneamente** con un único modelo. Se construye una representación compartida de tal manera que cada tarea ayuda a las otras a aprender mejor.

**Diferencia con Transfer Learning:**
- Transfer Learning: primero una tarea, luego la otra (secuencial).
- Multi-task Learning: todas las tareas al mismo tiempo (paralelo).

#### Beneficios potenciales

- Menor tiempo de entrenamiento (un solo modelo en lugar de varios).
- Menor tiempo de inferencia (una sola pasada hacia adelante).
- Modelos más compactos (representación compartida).
- Mayor tasa de acierto en cada tarea individual.
- Mayor eficiencia por muestra (cada ejemplo contribuye al aprendizaje de todas las tareas).
- Mejor representación (más regularizada por el conjunto de tareas).

#### Arquitecturas típicas

**Encoder compartido con múltiples decoders/cabezas:**
```
Input → [Encoder compartido] → [Cabeza tarea 1] → Output 1
                             → [Cabeza tarea 2] → Output 2
                             → [Cabeza tarea N] → Output N
```

La función de pérdida total es una suma ponderada de las pérdidas individuales:
$$L_{\text{total}} = \sum_{k=1}^{N} w_k \cdot L_k$$

donde $w_k$ es el peso de la tarea $k$. Los pesos pueden ser fijos o aprendidos.

#### Cuándo falla MTL: Transferencia Negativa

MTL **no siempre** mejora frente a aprender con una sola tarea. Puede ocurrir **transferencia negativa** cuando:

- Las tareas aprenden a ritmos diferentes → unas dominan el entrenamiento.
- Una tarea domina la pérdida total → otras no se aprenden bien.
- Los gradientes de diferentes tareas interfieren (gradientes conflictivos).
- La superficie de la función de coste se vuelve más complicada.

También depende de:
- **Tamaño de la red:** ¿hay suficientes parámetros para todas las tareas?
- **Localización de los estimadores de cada tarea** en la arquitectura.

#### Ejemplos reales

**Ejemplo 1 — Análisis de imágenes en interiores** (Standley et al., ICML 2020): 48 tareas de visión (segmentación semántica, estimación de profundidad, normales de superficie, keypoints, bordes Canny, etc.). Resultados: MTL mejora algunas combinaciones pero empeora otras → es necesario elegir qué tareas aprender juntas.

**Ejemplo 2 — Estimación de pose de cabeza** (Valle et al., PAMI 2021): las tareas de orientación de la cabeza (yaw, pitch, roll), localización de landmarks y visibilidad de landmarks se benefician mutuamente.
- Single task: NME promedio = 2.54
- Multi-task (Pre+Pose): NME promedio = **2.24** (-12% error)

---

### 1.6 Self-supervised Learning (Aprendizaje Auto-supervisado)

#### Motivación

El etiquetado manual de datos es caro y limitado. El aprendizaje auto-supervisado permite aprender representaciones de gran cantidad de datos **no etiquetados**.

#### Definición

**Self-supervised Learning:** el modelo se entrena con **etiquetas generadas automáticamente** a partir de los propios datos (sin anotación humana). Estas etiquetas se obtienen mediante *tareas pretext* (tareas de pretexto) diseñadas para que sean:
- Difíciles de resolver (requieren aprender buenas representaciones).
- Generables automáticamente (la etiqueta sale del dato mismo).

**Flujo general:**
```
Datos sin etiquetar → [Pretext Task Training → Representación aprendida]
                   → [Fine-tuning supervisado en tarea downstream con pocos datos]
```

#### Tipos de tareas pretext

**1. Tareas basadas en imágenes:**

| Tarea | Referencia | Descripción |
|:---|:---|:---|
| Predicción de rotación | Gidaris ICLR18 | Predecir el ángulo de rotación (0°, 90°, 180°, 270°) de una imagen rotada. |
| Inpainting | Pathak CVPR16 | Reconstruir una región enmascarada de la imagen. |
| Colorización | Zhang ECCV16 | Predecir el color de una imagen en escala de grises. |
| Predicción de posición de parche | Doersch ICCV15 | Predecir la posición relativa de dos parches de la misma imagen. |
| Puzzle jigsaw | Noroozi ECCV16 | Ordenar parches de una imagen mezclados aleatoriamente. |

**2. Tareas basadas en contexto en vídeos:**

| Tarea | Referencia | Descripción |
|:---|:---|:---|
| Aprender a ver moviéndose | Aggrawal ICCV15 | Aprender la estructura 3D del mundo a partir del movimiento de la cámara. |
| Verificación de orden temporal | Misra ECCV16 | Clasificar si una secuencia de frames está en orden correcto o invertido. |

**3. Aprendizaje semi-supervisado y auto-supervisado** (Zhai et al., S4L, ICCV 2019):
Combinar pérdida auto-supervisada (sin etiquetas) con pérdida supervisada (con etiquetas):
$$\mathcal{L} = w_{\text{sup}} \mathcal{L}_{\text{sup}} + w_{\text{rot}} \mathcal{L}_{\text{rot}}$$

donde $\mathcal{L}_{\text{sup}}$ es la pérdida supervisada (datos etiquetados) y $\mathcal{L}_{\text{rot}}$ es la pérdida de predicción de rotación (todos los datos, sin etiquetas).

#### Aprendizaje contrastivo (Contrastive Learning)

El aprendizaje contrastivo es el paradigma dominante en self-supervised learning moderno. La idea: **acercar en el espacio de embedding las representaciones de pares de datos similares** y **alejar los pares no similares**.

**Tarea de aprendizaje por contraste:**

Dado un conjunto de pares $\{(x_i, y_i)\}_{i=1}^N$ (donde $(x_i, y_i)$ son vistas distintas del mismo dato — p. ej. dos augmentaciones diferentes de la misma imagen), se define una red de embedding $\theta: x \mapsto \theta(x)$ y la pérdida:

$$\ell = -\log \frac{\exp(\text{sim}(x_+, y_+)/\tau)}{\exp(\text{sim}(x_+, y_+)/\tau) + \sum_{i=1}^{k}\exp(\text{sim}(x_+, y_-^i)/\tau)}$$

Esta es la **N-pair contrastive loss** (también conocida como InfoNCE loss), donde:
- $(x_+, y_+)$ es el par positivo (mismo dato, vistas distintas).
- $(x_+, y_-^i)$ son los pares negativos (datos distintos).
- $\text{sim}(\cdot, \cdot)$ es la similitud coseno.
- $\tau$ es la temperatura (hiperparámetro que controla la sharpness).

**Arquitectura típica (SimCLR-style):**
```
Imagen → Augmentation 1 → CNN → MLP → embedding z₁ ─┐
                                                      ├─ Contrastive Loss
Imagen → Augmentation 2 → CNN → MLP → embedding z₂ ─┘
```

**Resultados:** en ImageNet Linear Benchmark (top-1 accuracy):
- Métodos no contrastivos (2015-2018): 30-38%
- Métodos contrastivos (2019): **54-71%** (DINO, DCv2)

El método **DINO** (Caron et al., 2023), basado en Vision Transformers, alcanza 75.3% usando k-NN, comparable a métodos supervisados con supervisión parcial, lo que demuestra la potencia del aprendizaje contrastivo moderno.

---

### 1.7 Domain Adaptation (Adaptación de Dominio)

#### Definición

**Domain Adaptation:** aprovecha los datos etiquetados en el **dominio fuente** para entrenar un modelo que funcione bien con datos (etiquetados o no) en un **dominio objetivo diferente**.

**Ejemplo:** un detector de vehículos entrenado en imágenes diurnas de calidad (dominio fuente) que debe funcionar en imágenes nocturnas de baja resolución (dominio objetivo). Reentrenar desde cero sería costoso; Domain Adaptation reutiliza el conocimiento del dominio fuente.

**Diferencia con Transfer Learning:** en TL generalmente las distribuciones de entrada son similares pero las tareas (salidas) son diferentes. En DA la tarea es la misma pero las distribuciones de datos son diferentes (shift del dominio).

#### Adversarial Domain Adaptation (Ganin et al., JMLR 2017)

La idea: aprender representaciones que sean útiles para la tarea **y** que no distingan entre dominios.

**Arquitectura:**
```
Entrada x → Extractor de features Gf(·; θf)
              ├─→ Predictor de etiquetas Gy(·; θy) → pérdida Ly (supervisada)
              └─→ Clasificador de dominio Gd(·; θd) → pérdida Ld (adversarial)
```

El truco clave: la **capa de inversión del gradiente** (*gradient reversal layer*). Durante el forward pass, pasa la señal normal. Durante el backward pass, **invierte el signo del gradiente** multiplicándolo por $-\lambda$. Esto hace que el extractor de features $G_f$ aprenda a **engañar** al clasificador de dominio — es decir, aprende a producir features que no revelan de qué dominio proviene el dato. Al mismo tiempo, las features siguen siendo discriminativas para la tarea objetivo (pérdida $L_y$ normal).

Objetivo global:
$$\hat{\theta}_f, \hat{\theta}_y = \underset{\theta_f, \theta_y}{\arg\min} \; L_y - \lambda L_d$$
$$\hat{\theta}_d = \underset{\theta_d}{\arg\min} \; L_d$$

**Aplicaciones:** análisis facial (adaptar entre diferentes condiciones de iluminación, cámara, demografía), detección de objetos (adaptar de imágenes sintéticas a reales, de día a noche, etc.).

---

### Síntesis del aprendizaje de representaciones

El aprendizaje de representaciones es el concepto central en el desarrollo del ML moderno. Los conceptos de Transfer Learning, Multi-task Learning, Self-supervised Learning y Domain Adaptation son diferentes **manifestaciones** de la misma idea fundamental: que la **representación del problema** es la clave del rendimiento y puede reutilizarse entre tareas.

---

## 2. Modelos Generativos

### 2.1 Taxonomía del aprendizaje no supervisado

El aprendizaje no supervisado aprende sobre la estructura de un dataset **en ausencia de etiquetas**. Sus objetivos son variados:

- Generar nuevas muestras plausibles del dataset.
- Manipular, eliminar ruido, interpolar o comprimir ejemplos.
- Revelar la estructura interna (clustering).
- Detectar outliers.

**Jerarquía:**
```
Unsupervised learning
  └─ Generative models (pueden sintetizar nuevos ejemplos)
       └─ Probabilistic generative models (también asignan probabilidad)
            └─ Latent variable models (mapean datos ↔ variables latentes)
```

Los cuatro modelos principales del libro:
- **GANs** (cap. 15): generativos, no probabilísticos.
- **VAEs** (cap. 17): probabilísticos, con variables latentes.
- **Normalizing flows** (cap. 16): probabilísticos, invertibles.
- **Diffusion models** (cap. 18): probabilísticos, lentos al generar.

---

### 2.2 Variables latentes

**Estrategia general:** definir una función entre los ejemplos $\mathbf{x}$ y un conjunto de **variables latentes** $\mathbf{z}$ (no observadas directamente):
- Las variables latentes capturan la **estructura subyacente** de los datos.
- Tienen menor dimensión que $\mathbf{x}$.

**Generación:** si encontramos $\Pr(\mathbf{z})$, podemos:
1. Generar aleatoriamente nuevas variables latentes: $\mathbf{z}^* \sim \Pr(\mathbf{z})$.
2. Mapearlas al espacio original: $\mathbf{x}^* = g[\mathbf{z}^*, \boldsymbol{\theta}]$.

**Relación probabilística:**
$$\Pr(\mathbf{x}) = \int \Pr(\mathbf{x} \mid \mathbf{z}) \, \Pr(\mathbf{z}) \, d\mathbf{z}$$

Esto es una **mezcla infinita** de distribuciones simples, lo que permite describir distribuciones complejas a partir de componentes sencillas.

---

### 2.3 ¿Qué hace bueno a un modelo generativo?

Las propiedades deseables de un modelo generativo basado en variables latentes son:

| Propiedad | Descripción |
|:---|:---|
| **Muestreo eficiente** | Generar muestras con poco coste computacional, aprovechando el paralelismo del hardware. |
| **Calidad de las muestras** | Las muestras deben ser indistinguibles de los datos reales. |
| **Cobertura** | Las muestras deben representar toda la distribución de entrenamiento, no solo un subconjunto. |
| **Espacio latente coherente** | Cada $\mathbf{z}$ genera un ejemplo plausible. Cambios suaves en $\mathbf{z}$ generan cambios suaves en $\mathbf{x}$. |
| **Espacio latente desentrelazado** | Cada dimensión de $\mathbf{z}$ corresponde a una propiedad interpretable de los datos. |
| **Cálculo eficiente de la verosimilitud** | Si el modelo es probabilístico, la probabilidad de un nuevo ejemplo se debe calcular rápidamente. |

**Comparación de modelos** (ninguno cumple todos los criterios):

| Modelo | Eficiente | Calidad | Cobertura | Espacio latente coherente | Desentrelazado | Verosimilitud eficiente |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **GANs** | ✓ | ✓ | ✗ | ✓ | ? | n/a |
| **VAEs** | ✓ | ✗ | ? | ✓ | ? | ✗ |
| **Flows** | ✓ | ✗ | ? | ✓ | ? | ✓ |
| **Diffusion** | ✗ | ✓ | ? | ✗ | ✗ | ✗ |

Las GANs son las que producen muestras de mayor calidad visual y son computacionalmente eficientes, pero no pueden calcular probabilidades y tienen problemas de cobertura.

---

### 2.4 Métricas para evaluar modelos generativos

#### Verosimilitud en test (Test likelihood)

Para modelos probabilísticos, medir la verosimilitud $\sum_i \log \Pr(\mathbf{x}_i | \boldsymbol{\phi})$ en el conjunto de test. Captura qué tan bien el modelo generaliza y su cobertura.

**Limitación:** no aplica a las GANs (no son probabilísticas) y es costosa de calcular para VAEs y diffusion models.

#### Inception Score (IS)

Mide la calidad y diversidad de imágenes generadas mediante un modelo de clasificación preentrenado (Inception). Basa en dos criterios:
1. Cada imagen $\mathbf{x}^*$ generada debe pertenecer claramente a una sola clase → $\Pr(y|\mathbf{x}^*)$ muy concentrada.
2. El conjunto de imágenes generadas debe cubrir todas las clases por igual → $\Pr(y)$ uniforme.

$$IS = \exp\!\left(\frac{1}{I}\sum_{i=1}^{I} D_{KL}\big(\Pr(y_i|\mathbf{x}^*_i) \| \Pr(y)\big)\right)$$

Mayor IS → mejor. Limitaciones: solo válido para ImageNet; no detecta falta de diversidad dentro de una clase; sensible al modelo Inception utilizado.

#### Fréchet Inception Distance (FID)

Mide la distancia entre la distribución de muestras generadas y la distribución de muestras reales, ambas representadas mediante sus activaciones en la red Inception (capa Pool-3):

1. Pasa muestras reales y generadas por Inception y extrae las features (vector de activaciones en una capa profunda).
2. Aproxima ambas distribuciones como Gaussianas multivariantes ($\mu_r, \Sigma_r$) y ($\mu_g, \Sigma_g$).
3. Calcula la distancia de Fréchet:

$$FID = \|\boldsymbol{\mu}_r - \boldsymbol{\mu}_g\|^2 + \text{tr}\!\left(\boldsymbol{\Sigma}_r + \boldsymbol{\Sigma}_g - 2(\boldsymbol{\Sigma}_r \boldsymbol{\Sigma}_g)^{1/2}\right)$$

Menor FID → muestras más realistas y diversas. Tiene en cuenta tanto calidad como diversidad, pero la comparación ocurre en el espacio semántico de la red Inception — información no capturada por esa red no contribuye al FID.

#### Manifold Precision/Recall

Disentangle calidad y cobertura:
- **Precisión:** fracción de muestras generadas que caen dentro del manifold de datos reales. Mide el realismo.
- **Recall:** fracción de datos reales que caen dentro del manifold de muestras generadas. Mide la cobertura.

Los manifolds se aproximan poniendo una hiperesfera alrededor de cada muestra con radio = distancia al k-ésimo vecino más cercano.

---

### 2.5 Generative Adversarial Networks (GANs)

#### Intuición y motivación

Una GAN es un modelo generativo no supervisado que aprende a generar muestras **estadísticamente indistinguibles** de los datos de entrenamiento. No construye una distribución de probabilidad explícita — solo aprende un mecanismo generador.

**Idea central:** si una red clasificadora no puede distinguir entre los ejemplos generados y los reales, entonces los ejemplos generados *deben ser* plausibles.

**Componentes:**

- **Generador** $g[\mathbf{z}, \boldsymbol{\theta}]$: red de neuronas que transforma una variable latente $\mathbf{z}_j$ muestreada de una distribución simple (ej. $\mathcal{N}(0,I)$ o uniforme) en una muestra $\mathbf{x}_j^* = g[\mathbf{z}_j, \boldsymbol{\theta}]$.
- **Discriminador** $f[\mathbf{x}, \boldsymbol{\phi}]$: red de neuronas entrenada para distinguir ejemplos reales $\mathbf{x}$ de los generados $\mathbf{x}^*$. Devuelve un escalar mayor cuando cree que la entrada es real.

**Dinámica de entrenamiento (juego adversarial):**
1. El discriminador intenta mejorar la distinción entre reales y generados.
2. El generador intenta engañar al discriminador para que clasifique sus muestras como reales.
3. Se alternan los pasos de actualización del generador y el discriminador.

---

### 2.6 Función de pérdida de la GAN

#### Función de pérdida del discriminador

Las etiquetas son $y=1$ para reales y $y=0$ para generadas. Se usa la pérdida de entropía cruzada binaria:

$$\hat{\boldsymbol{\phi}} = \underset{\boldsymbol{\phi}}{\arg\min} \left[\sum_j -\log\!\left(1 - \text{sig}[f[\mathbf{x}_j^*, \boldsymbol{\phi}]]\right) - \sum_i \log\!\left(\text{sig}[f[\mathbf{x}_i, \boldsymbol{\phi}]]\right)\right]$$

Separando reales ($i$) y generados ($j$):
- El primer término: minimizar la probabilidad de que las muestras generadas sean clasificadas como reales.
- El segundo término: maximizar la probabilidad de que los reales sean clasificados como reales.

Sustituyendo $\mathbf{x}_j^* = g[\mathbf{z}_j, \boldsymbol{\theta}]$:

$$\hat{\boldsymbol{\phi}} = \underset{\boldsymbol{\phi}}{\arg\min} \left[\sum_j -\log\!\left(1 - \text{sig}[f[g[\mathbf{z}_j, \boldsymbol{\theta}], \boldsymbol{\phi}]]\right) - \sum_i \log\!\left(\text{sig}[f[\mathbf{x}_i, \boldsymbol{\phi}]]\right)\right]$$

#### Función de pérdida del generador

El generador quiere que el discriminador se equivoque → quiere **maximizar** la misma pérdida del discriminador respecto a las muestras generadas (minimizar la cross-entropy con signo cambiado):

$$L[\boldsymbol{\theta}] = \sum_j \log\!\left(1 - \text{sig}[f[g[\mathbf{z}_j, \boldsymbol{\theta}], \boldsymbol{\phi}]]\right)$$

Esta es la pérdida que el generador **minimiza** (equivale a maximizar la probabilidad que el discriminador asigna a sus muestras como reales).

---

### 2.7 Entrenamiento de la GAN: el problema minimax

El problema de entrenamiento combina los dos objetivos en un único problema **minimax**:

$$\hat{\boldsymbol{\theta}}, \hat{\boldsymbol{\phi}} = \underset{\boldsymbol{\theta}}{\arg\max}\; \underset{\boldsymbol{\phi}}{\arg\min} \left[\sum_j -\log\!\left(1-\text{sig}[f[g[\mathbf{z}_j,\boldsymbol{\theta}],\boldsymbol{\phi}]]\right) - \sum_i \log\!\left(\text{sig}[f[\mathbf{x}_i,\boldsymbol{\phi}]]\right)\right]$$

- El discriminador ($\boldsymbol{\phi}$) **minimiza** la pérdida.
- El generador ($\boldsymbol{\theta}$) **maximiza** la misma pérdida (equivalente a minimizar la cross-entropy cambiada de signo para los datos generados).

**Procedimiento de entrenamiento en cada iteración:**
1. Muestrear un batch de variables latentes $\{\mathbf{z}_j\}$ de la distribución prior.
2. Pasar por el generador → obtener muestras $\{\mathbf{x}_j^*\}$.
3. Muestrear un batch de datos reales $\{\mathbf{x}_i\}$.
4. Con ambos batches, actualizar el discriminador (1 o más pasos de descenso de gradiente en $L[\boldsymbol{\phi}]$).
5. Actualizar el generador (1 paso de descenso de gradiente en $L[\boldsymbol{\theta}]$, que implica backprop a través del discriminador).

Si el entrenamiento converge, el generador produce muestras de la misma distribución que los datos reales, y el discriminador (que se descarta) asigna probabilidad 0.5 a todo (no puede distinguir).

---

### 2.8 DCGAN: GAN convolucional profunda

La **Deep Convolutional GAN** (Radford et al., 2015) fue la primera arquitectura GAN especializada en generar imágenes de calidad.

#### Arquitectura del generador

```
z (100×1, distribución uniforme)
  ↓ Proyección + reshape (FC)
4×4×1024
  ↓ Conv traspuesta (stride 2) + BN + ReLU
8×8×512
  ↓ Conv traspuesta (stride 2) + BN + ReLU
16×16×256
  ↓ Conv traspuesta (stride 2) + BN + ReLU
32×32×128
  ↓ Conv traspuesta (stride 2) + tanh
64×64×3 → imagen generada x*
```

La **función tanh** en la última capa mapea los valores al rango $[-1, 1]$ para luego convertirlos a $[0, 255]$ como imagen RGB.

#### Arquitectura del discriminador

Convolucional estándar (imagen → escalar), terminando en sigmoid para la probabilidad de ser real.

#### Trucos que hacen que funcione

Para que el DCGAN entrene de forma estable fue necesario:

1. Usar **convoluciones con stride** (no max pooling) para el downsampling en el discriminador, y **convoluciones traspuestas** en el generador.
2. **Batch Normalization** en todas las capas excepto en la primera del generador y la última del discriminador.
3. Usar **Leaky ReLU** (en lugar de ReLU estándar) en el discriminador. La Leaky ReLU tiene pendiente pequeña (0.1) para valores negativos, evitando neuronas muertas.
4. Optimizador **Adam** pero con parámetro de momento bajo (β₁=0.5 en lugar del habitual 0.9).

---

### 2.9 Problemas de entrenamiento: mode collapse y vanishing gradients

#### Análisis formal de la pérdida GAN

Cuando el discriminador es óptimo, la función de pérdida minimiza una medida de distancia entre las distribuciones de muestras generadas $\Pr(\mathbf{x}^*)$ y datos reales $\Pr(\mathbf{x})$. Concretamente, el mínimo de la pérdida del discriminador es la **divergencia Jensen-Shannon**:

$$D_{JS}[\Pr(\mathbf{x}^*) \| \Pr(\mathbf{x})] = \frac{1}{2}D_{KL}\!\left[\Pr(\mathbf{x}^*)\, \Bigg\|\, \frac{\Pr(\mathbf{x}^*)+\Pr(\mathbf{x})}{2}\right] + \frac{1}{2}D_{KL}\!\left[\Pr(\mathbf{x})\, \Bigg\|\, \frac{\Pr(\mathbf{x}^*)+\Pr(\mathbf{x})}{2}\right]$$

- El **primer término** ($D_{KL}$ con $\Pr(\mathbf{x}^*)$): penaliza regiones con muestras pero sin datos reales → **enforces quality** (calidad).
- El **segundo término** ($D_{KL}$ con $\Pr(\mathbf{x})$): penaliza regiones con datos reales pero sin muestras → **enforces coverage** (cobertura).

El segundo término **no depende del generador** (que solo controla $\Pr(\mathbf{x}^*)$). Esto explica el **mode dropping**: el generador no tiene incentivo a cubrir todos los modos de la distribución real — le basta con generar un subconjunto de muestras realistas.

#### Problemas principales

**1. Mode dropping:** algunos modos de la distribución de datos no se generan. Por ejemplo, en una GAN entrenada en caras, nunca se generan caras con barba.

**2. Mode collapse:** el generador ignora la variable latente $\mathbf{z}$ y genera siempre el mismo subconjunto limitado de imágenes (a veces solo una o pocas). El generador ha encontrado un "truco" para engañar al discriminador sin necesidad de variedad.

**3. Vanishing gradients del generador:** si el discriminador es demasiado bueno (puede distinguir perfectamente los generados de los reales), la función sigmoid del discriminador tiene pendiente casi cero en la posición de las muestras generadas → los gradientes que llegan al generador son prácticamente cero → el generador no puede mejorar.

**Evidencia empírica:** si se congela el generador y se sigue entrenando solo el discriminador, los gradientes del generador disminuyen exponencialmente — lo que demuestra que la calidad del discriminador y el generador deben evolucionar en equilibrio delicado.

**Causa fundamental del vanishing gradient:** las distribuciones de las muestras generadas y los datos reales a menudo son **disjuntas** en el espacio de datos de alta dimensión (cada una ocupa una subvariedad de baja dimensión sin solapamiento). Cuando son disjuntas, la distancia JS es constante (igual a $\log 2$) independientemente de cuán cerca estén las distribuciones → gradiente cero → el generador no puede mejorar.

---

### 2.10 Wasserstein GAN (WGAN)

#### Motivación

La distancia Jensen-Shannon tiene gradiente cero cuando las distribuciones son disjuntas. Se necesita una métrica de distancia que:
- Esté bien definida aunque las distribuciones sean disjuntas.
- Decrezca suavemente a medida que las distribuciones se acercan.

#### Distancia de Wasserstein

La distancia de Wasserstein (o *earth mover's distance*) es la cantidad de "trabajo" necesario para transportar la masa de probabilidad de una distribución para crear la otra. El "trabajo" se define como masa × distancia.

**Para distribuciones discretas (forma primal):**

$$D_W(\Pr(x) \| q(x)) = \min_{\mathbf{P}} \sum_{i,j} P_{ij} \cdot |i-j|$$

sujeto a que:
- $\sum_j P_{ij} = \Pr(x=i)$ (restricción de distribución inicial)
- $\sum_i P_{ij} = q(x=j)$ (restricción de distribución destino)
- $P_{ij} \geq 0$ (masas no negativas)

donde $P_{ij}$ es el *plan de transporte* que indica cuánta masa se mueve de $i$ a $j$.

**Forma dual (equivalente):**

$$D_W(\Pr(x) \| q(x)) = \max_f \left[\sum_i \Pr(x=i) f_i - \sum_j q(x=j) f_j\right]$$

sujeto a: $|f_{i+1} - f_i| < 1$ (la función $f$ es Lipschitz-1).

**Para distribuciones continuas (forma dual):**

$$D_W(\Pr(\mathbf{x}) \| q(\mathbf{x})) = \max_{f[\mathbf{x}]}\left[\int \Pr(\mathbf{x}) f[\mathbf{x}]\,d\mathbf{x} - \int q(\mathbf{x}) f[\mathbf{x}]\,d\mathbf{x}\right]$$

sujeto a que la constante de Lipschitz de $f[\mathbf{x}]$ sea menor que 1 (el gradiente de $f$ tenga norma menor que 1 en todo punto):

$$\left|\frac{\partial f[\mathbf{x}, \boldsymbol{\phi}]}{\partial \mathbf{x}}\right| < 1$$

**Ventaja clave:** la distancia de Wasserstein proporciona gradientes útiles incluso cuando las distribuciones son completamente disjuntas — en este caso, la distancia es la distancia geométrica entre las dos subvariedades, que decrece suavemente al acercarlas.

#### WGAN: pérdida y entrenamiento

En la WGAN, el discriminador (ahora llamado **crítico**, ya que no produce una probabilidad sino un escalar real) aprende la función $f[\mathbf{x}, \boldsymbol{\phi}]$ que maximiza la distancia de Wasserstein:

**Pérdida del crítico** (maximizar → minimizar el negativo):
$$L[\boldsymbol{\phi}] = \sum_j f[g[\mathbf{z}_j, \boldsymbol{\theta}], \boldsymbol{\phi}] - \sum_i f[\mathbf{x}_i, \boldsymbol{\phi}]$$

Las muestras generadas deben tener baja puntuación y los reales alta puntuación. El crítico **maximiza** la diferencia.

**Pérdida del generador** (maximizar la puntuación de las muestras generadas):
$$L[\boldsymbol{\theta}] = \sum_j \log\!\left(1 - \text{sig}[f[g[\mathbf{z}_j, \boldsymbol{\theta}], \boldsymbol{\phi}]]\right)$$

**Restricción Lipschitz:** para cumplir la condición de gradiente ≤ 1, la solución original recorta (*clips*) los pesos del crítico al intervalo $[-c, c]$ (ej. $[-0.01, 0.01]$) después de cada actualización.

**Alternativa:** WGAN-GP (Gulrajani et al., 2017) usa una penalización del gradiente (*gradient penalty*) en lugar del clipping, que es más estable:
$$\text{penalty} = \left(\|\nabla_{\hat{\mathbf{x}}} f[\hat{\mathbf{x}}, \boldsymbol{\phi}]\|_2 - 1\right)^2$$

donde $\hat{\mathbf{x}}$ son puntos interpolados entre muestras reales y generadas.

**Comparación WGAN vs GAN estándar:**

En la GAN estándar, la función que aprende el discriminador se satura (sigmoid) → gradientes desaparecen. En la WGAN, el crítico aprende una función lineal sin saturación → gradientes lineales y útiles incluso cuando las distribuciones son lejanas.

**Ventajas del WGAN:**
- Entrenamiento más estable.
- Se puede entrenar el crítico muchas veces por cada actualización del generador sin que los gradientes desaparezcan.
- La pérdida del crítico es una métrica significativa de la calidad de generación (correlaciona con la calidad visual).

---

### 2.11 GANs condicionadas

Las GANs básicas generan muestras aleatorias sin control sobre sus atributos. Las GANs condicionadas introducen un **vector de condicionamiento** $\mathbf{c}$ que guía la generación.

#### Conditional GAN (cGAN)

El generador recibe $(\mathbf{z}, \mathbf{c})$ y el discriminador recibe $(\mathbf{x}, \mathbf{c})$:
- **Generador:** $g[\mathbf{z}, \mathbf{c}, \boldsymbol{\theta}]$ → muestra con el atributo $\mathbf{c}$.
- **Discriminador:** clasifica si el par (imagen, atributo) es real o generado.

Permite controlar atributos continuos (edad, pose) o discretos (clase de objeto).

#### Auxiliary Classifier GAN (ACGAN)

El discriminador tiene dos cabezas:
1. Real/generado: sigmoid → probabilidad de ser real.
2. Predicción de clase: softmax → probabilidad de cada clase.

El discriminador debe tanto distinguir real/generado **como** predecir correctamente la clase. Esto fuerza al generador a producir imágenes coherentes con la clase condicionada.

#### Pix2Pix

Caso especial donde el condicionante $\mathbf{c}$ es una imagen completa (traducción imagen a imagen). La arquitectura usa una U-Net como generador y se entrena con:

- **Content loss** (pérdida $\ell_1$): la imagen generada debe ser similar a la imagen destino real.
- **Adversarial loss** (GAN): la imagen generada debe ser indistinguible de imágenes reales del dominio destino.

El discriminador es **PatchGAN**: solo clasifica parches locales de la imagen (no la imagen completa), lo que obliga al generador a producir texturas locales realistas.

Aplicaciones: colorización, mapa→satélite, boceto→fotorrealismo, segmentación→foto.

---

### 2.12 CycleGAN y traducción de imágenes no emparejadas

**Problema:** tenemos dos conjuntos de imágenes de dominios distintos (ej. caballos y cebras) pero **sin correspondencia entre ellas** (no sabemos qué caballo corresponde a qué cebra).

**Idea clave:** si podemos convertir una imagen del dominio A al dominio B, y luego convertir el resultado de vuelta al dominio A, **deberíamos recuperar la imagen original** (*cycle consistency loss*).

**CycleGAN** (Zhu et al., 2017) entrena dos generadores en paralelo:
- $g_1$: A → B (ej. caballo → cebra)
- $g_2$: B → A (ej. cebra → caballo)

**Función de pérdida total** (tres componentes):

1. **Content loss** (L1): similaridad estructural entre input y output.
2. **Adversarial loss**: imágenes generadas indistinguibles de las reales del dominio objetivo.
3. **Cycle-consistency loss**: $\|g_2[g_1[\mathbf{c}]] - \mathbf{c}\|_1$ pequeña. Si A → B → A no recupera la imagen original, la transformación no es consistente.

**Aplicaciones:** caballo↔cebra, foto↔Monet, verano↔invierno, manzana↔naranja.

---

### 2.13 StyleGAN

StyleGAN (Karras et al., 2019) es una GAN de alta calidad para síntesis fotorrealista de rostros y otros objetos. Introduce varias innovaciones sobre DCGAN:

#### Arquitectura

**Pipeline generativa principal:** convierte una variable latente en imágenes, empezando en resolución baja (4×4) y yendo hasta alta resolución (1024×1024) mediante bloques de upsampling.

**Mapeo de estilo:** en lugar de inyectar $\mathbf{z}$ directamente en el generador, primero se mapea a una **variable intermedia** $\mathbf{w}$ mediante una red FC de 8 capas: $\mathbf{z} \to \mathbf{w}$. Esta variable $\mathbf{w}$ controla el "estilo" de la imagen a través de **AdaIN** (Adaptive Instance Normalization) en cada capa del generador.

**AdaIN** modifica la media y varianza de las activaciones de cada capa según el estilo $\mathbf{w}$:
$$\text{AdaIN}(\mathbf{h}, \mathbf{y}) = \mathbf{y}_s \frac{\mathbf{h} - \mu(\mathbf{h})}{\sigma(\mathbf{h})} + \mathbf{y}_b$$

donde $(\mathbf{y}_s, \mathbf{y}_b)$ se aprenden como transformación lineal de $\mathbf{w}$.

**Ruido por canal:** en cada nivel de resolución, se añade ruido Gaussiano $\boldsymbol{\epsilon}$ multiplicado por un escalar aprendido $\boldsymbol{\psi}$. Este ruido controla la variación estocástica de fine detail (pelo, poros de la piel, texturas finas) sin afectar al estilo global.

#### Propiedades del espacio de estilos $\mathbf{w}$

El espacio de $\mathbf{w}$ está más **desentrelazado** que el espacio de $\mathbf{z}$: cada dimensión de $\mathbf{w}$ tiende a corresponder a un atributo semánticamente interpretable (identidad facial, expresión, pose, estilo de imagen, iluminación).

- **Estilos coarse** (primeras capas, baja resolución): controlan la pose, forma facial, estilo general.
- **Estilos medios** (capas intermedias): controlan rasgos faciales, pelo, ojos.
- **Estilos finos** (capas finales, alta resolución): controlan colores específicos, microestructuras.

#### Style mixing

Al cambiar solo algunas capas del generador con el estilo de una imagen diferente, se puede mezclar estilos: tomar la identidad/pose de una imagen y el color/textura de otra.

---

## 3. Resumen y referencia rápida

### Estrategias de aprendizaje de representaciones

| Estrategia | Cuándo usar | Cómo funciona |
|:---|:---|:---|
| **Transfer Learning** | Pocos datos para la tarea objetivo, datos abundantes para tarea relacionada | Pre-entrenar en T1, fine-tune o feature extraction en T2 |
| **Multi-task Learning** | Múltiples tareas relacionadas disponibles | Encoder compartido + múltiples cabezas, pérdida combinada |
| **Self-supervised Learning** | Datos no etiquetados abundantes | Tareas pretext autogeneradas (rotación, colorización, contrastive) |
| **Domain Adaptation** | Misma tarea, distribución de datos diferente | Representación invariante al dominio (adversarial gradient reversal) |

### Taxonomía de modelos generativos

```
Unsupervised learning
└── Generative models
    ├── GANs (cap. 15): muestras de alta calidad, no probabilísticos
    └── Probabilistic generative models
        ├── VAEs (cap. 17): verosimilitud aproximada (ELBO)
        ├── Normalizing flows (cap. 16): verosimilitud exacta, invertibles
        └── Diffusion models (cap. 18): máxima calidad, lentos
```

### Pérdidas de la GAN

**Pérdida del discriminador** (minimizar):
$$L[\boldsymbol{\phi}] = \sum_j -\log\!\left(1-\text{sig}[f[\mathbf{x}_j^*, \boldsymbol{\phi}]]\right) - \sum_i \log\!\left(\text{sig}[f[\mathbf{x}_i, \boldsymbol{\phi}]]\right)$$

**Pérdida del generador** (minimizar):
$$L[\boldsymbol{\theta}] = \sum_j \log\!\left(1-\text{sig}[f[g[\mathbf{z}_j, \boldsymbol{\theta}], \boldsymbol{\phi}]]\right)$$

**Pérdida del crítico WGAN** (minimizar el negativo = maximizar):
$$L[\boldsymbol{\phi}] = \sum_j f[g[\mathbf{z}_j, \boldsymbol{\theta}], \boldsymbol{\phi}] - \sum_i f[\mathbf{x}_i, \boldsymbol{\phi}]$$

### Problemas y soluciones en GANs

| Problema | Causa | Solución |
|:---|:---|:---|
| Mode dropping | Función de pérdida no penaliza falta de cobertura | WGAN, mini-batch discrimination |
| Mode collapse | Generador aprende a engañar con pocas muestras | Batch norm, mini-batch discrimination |
| Vanishing gradients | Discriminador demasiado bueno, distribuciones disjuntas | WGAN (distancia Wasserstein con gradientes lineales) |
| Entrenamiento inestable | Equilibrio delicado generador-discriminador | BN, Leaky ReLU, Adam con β₁ bajo, WGAN-GP |

### Comparativa rápida: GAN vs WGAN

| Aspecto | GAN estándar | WGAN |
|:---|:---|:---|
| Función que aprende el discriminador | Probabilidad sigmoid (clasificación) | Valor escalar real (sin saturación) |
| Distancia minimizada | Jensen-Shannon divergence | Wasserstein distance |
| Gradiente cuando distribuciones disjuntas | Cero | Informativo (lineal) |
| Restricción en el discriminador/crítico | Ninguna | Lipschitz-1 (clipping o gradient penalty) |
| Pasos del crítico por paso del generador | 1 | Varios (5 típicamente) |
| Correlación pérdida↔calidad visual | Débil | Alta |

---

## Referencias

- Prince, S.J.D. (2023). *Understanding Deep Learning*. MIT Press. Capítulos 14 y 15. [Acceso libre]
- Goodfellow, I., Pouget-Abadie, J., Mirza, M., et al. (2014). Generative Adversarial Networks. *NeurIPS*.
- Radford, A., Metz, L. & Chintala, S. (2015). Unsupervised Representation Learning with Deep Convolutional Generative Adversarial Networks. *ICLR 2016*.
- Arjovsky, M., Chintala, S. & Bottou, L. (2017). Wasserstein GAN. *ICML 2017*.
- Gulrajani, I., Ahmed, F., Arjovsky, M., Dumoulin, V. & Courville, A. (2017). Improved Training of Wasserstein GANs. *NeurIPS*.
- Isola, P., Zhu, J.Y., Zhou, T. & Efros, A.A. (2017). Image-to-Image Translation with Conditional Adversarial Networks (Pix2Pix). *CVPR 2017*.
- Zhu, J.Y., Park, T., Isola, P. & Efros, A.A. (2017). Unpaired Image-to-Image Translation using Cycle-Consistent Adversarial Networks (CycleGAN). *ICCV 2017*.
- Karras, T., Laine, S. & Aila, T. (2019). A Style-Based Generator Architecture for Generative Adversarial Networks (StyleGAN). *CVPR 2019*.
- Zamir, A.R., Sax, A., Shen, W.B., et al. (2018). Taskonomy: Disentangling Task Transfer Learning. *CVPR 2018*.
- Tian, Y., et al. (2020). Contrastive Learning: A General Self-supervised Learning Approach.
- Caron, M., et al. (2023). DINO: Emerging Properties in Self-Supervised Vision Transformers.
- Ganin, Y., et al. (2017). Domain-Adversarial Training of Neural Networks. *JMLR*.
- Standley, T., et al. (2020). Which Tasks Should Be Learned Together in Multi-task Learning? *ICML 2020*.
- Valle, R., et al. (2021). Multi-task head pose estimation in the wild. *PAMI 2021*.
- Levine, S. (2021). Deep Learning: CS 182. Lectures 17 & 18. UC Berkeley. [YouTube]
- Welch Labs. The moment we stopped understanding AI. [YouTube]
