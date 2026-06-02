### Aprendizaje Automático II · Grado en IA · Universidad Rey Juan Carlos

**Basado en:** Diapositivas del Tema 5 (partes 1 y 2) + _Understanding Deep Learning_, Capítulo 4 (Prince, MIT Press)

---
## Índice

1. [Motivación: de redes shallow a redes profundas](#1-motivaci%C3%B3n)
2. [5.1 · Composición de redes shallow](#2-composici%C3%B3n-de-redes-shallow)
    - 2.1 Red shallow: repaso
    - 2.2 Componer dos redes shallow en serie
    - 2.3 Equivalencia con una red de dos capas ocultas
    - 2.4 La red profunda es más general
    - 2.5 Analogía del plegado del espacio
    - 2.6 Composición en 2D
    - 2.7 Hiperparámetros
    - 2.8 Notación matricial compacta
3. [5.2 · Optimización con redes profundas](#3-optimizaci%C3%B3n-con-redes-profundas)
    - 3.1 Backpropagation
    - 3.2 Inicialización de parámetros
    - 3.3 Normalización (Batch Normalization)
    - 3.4 Regularización y Dropout
4. [Redes no profundas vs. profundas: comparativa](#4-redes-no-profundas-vs-profundas)
5. [Resumen ejecutivo y tarjetas de fórmulas](#5-resumen-y-f%C3%B3rmulas)

---

## 1. Motivación

Una **red neuronal shallow** tiene exactamente una capa oculta. Como demostró el teorema de aproximación universal, con suficientes unidades ocultas puede aproximar cualquier función continua. Pero "suficientes" puede ser un número exponencialmente grande.

Las **redes profundas** (deep neural networks, DNN) tienen **más de una capa oculta**. La intuición sobre cómo funcionan es más compleja, pero ofrecen ventajas cruciales:

- Generan muchas más **regiones lineales** por parámetro.
- Algunas funciones del mundo real son mucho más eficientemente representadas con profundidad (eficiencia de profundidad).
- Facilitan el procesamiento jerárquico de entradas estructuradas (imágenes, texto…).
- En la práctica, los mejores resultados en Visión por Computadora, PLN, aprendizaje por refuerzo, etc. se obtienen con redes de 50 a 1000 capas.

---

## 2. Composición de redes shallow

### 2.1 Red shallow: repaso

Una red shallow con **1 entrada, 3 unidades ocultas y 1 salida** se define:

$$h_1 = a[\theta_{10} + \theta_{11},x]$$ $$h_2 = a[\theta_{20} + \theta_{21},x]$$ $$h_3 = a[\theta_{30} + \theta_{31},x]$$ $$y = \phi_0 + \phi_1 h_1 + \phi_2 h_2 + \phi_3 h_3$$

donde $a[\cdot]$ es la **función de activación**, habitualmente la **ReLU**:

$$\text{ReLU}(z) = \max(0, z) = \begin{cases} 0 & z < 0 \ z & z \geq 0 \end{cases}$$

Cada unidad oculta crea una función lineal del input que se _recorta_ a cero donde es negativa. Con 3 unidades ocultas podemos tener hasta **4 regiones lineales** en la función de salida. Los puntos de articulación (joints) están donde cada $\theta_{d0} + \theta_{d1}x = 0$.

**Activaciones:** valores $h_d$ después de aplicar ReLU.  
**Preactivaciones:** valores $\theta_{d0} + \theta_{d1}x$ antes de aplicar ReLU.

---

### 2.2 Componer dos redes shallow en serie

Tomamos la salida $y$ de la **Red 1** como entrada de la **Red 2**:

**Red 1** (entrada $x$, salida $y$): $$h_1 = a[\theta_{10} + \theta_{11},x], \quad h_2 = a[\theta_{20} + \theta_{21},x], \quad h_3 = a[\theta_{30} + \theta_{31},x]$$ $$y = \phi_0 + \phi_1 h_1 + \phi_2 h_2 + \phi_3 h_3$$

**Red 2** (entrada $y$, salida $y'$): $$h_1' = a[\theta_{10}' + \theta_{11}',y], \quad h_2' = a[\theta_{20}' + \theta_{21}',y], \quad h_3' = a[\theta_{30}' + \theta_{31}',y]$$ $$y' = \phi_0' + \phi_1' h_1' + \phi_2' h_2' + \phi_3' h_3'$$

**¿Qué efecto tiene esta composición?**

Supongamos que la Red 1 produce tres regiones alternantes de pendiente positiva/negativa. Esto significa que **tres rangos distintos de $x$ producen el mismo rango de $y$**. La Red 2 aplica su función sobre ese rango de $y$, y el resultado se _duplica tres veces_, generando potencialmente **9 regiones lineales** en la función final $y'(x)$ — mucho más de lo que una red shallow de 6 unidades podría generar con los mismos parámetros.

#### Analogía del plegado

Podemos pensar en la composición de dos redes como un proceso de **plegado**:

1. La **Red 1** _dobla_ el espacio de entrada $x$ sobre sí mismo: múltiples valores de $x$ mapean al mismo valor de $y$.
2. La **Red 2** aplica su función sobre el espacio ya plegado.
3. El resultado es que la función de la Red 2 aparece **replicada** en todos los puntos que fueron plegados juntos.

Este "plegado" crea dependencias complejas y simetrías entre las regiones lineales de la función final — algo que una red con una sola capa oculta no puede reproducir eficientemente.

---

### 2.3 Equivalencia con una red de dos capas ocultas

#### Derivación algebraica paso a paso

La salida de la Red 1 es: $$y = \phi_0 + \phi_1 h_1 + \phi_2 h_2 + \phi_3 h_3$$

Las preactivaciones de la Red 2 usan $y$ como input. Sustituyendo la expresión de $y$:

$$\theta_{10}' + \theta_{11}' y = \theta_{10}' + \theta_{11}'(\phi_0 + \phi_1 h_1 + \phi_2 h_2 + \phi_3 h_3)$$ $$= (\theta_{10}' + \theta_{11}'\phi_0) + \theta_{11}'\phi_1 h_1 + \theta_{11}'\phi_2 h_2 + \theta_{11}'\phi_3 h_3$$

Entonces las unidades ocultas de la Red 2, en términos de las unidades de la Red 1, son: $$h_1' = a[\theta_{10}' + \theta_{11}'\phi_0 + \theta_{11}'\phi_1 h_1 + \theta_{11}'\phi_2 h_2 + \theta_{11}'\phi_3 h_3]$$ $$h_2' = a[\theta_{20}' + \theta_{21}'\phi_0 + \theta_{21}'\phi_1 h_1 + \theta_{21}'\phi_2 h_2 + \theta_{21}'\phi_3 h_3]$$ $$h_3' = a[\theta_{30}' + \theta_{31}'\phi_0 + \theta_{31}'\phi_1 h_1 + \theta_{31}'\phi_2 h_2 + \theta_{31}'\phi_3 h_3]$$

Renombramos los parámetros: $\psi_{10} = \theta_{10}' + \theta_{11}'\phi_0$, $\psi_{11} = \theta_{11}'\phi_1$, $\psi_{12} = \theta_{11}'\phi_2$, $\psi_{13} = \theta_{11}'\phi_3$, etc.

$$h_1' = a[\psi_{10} + \psi_{11} h_1 + \psi_{12} h_2 + \psi_{13} h_3]$$ $$h_2' = a[\psi_{20} + \psi_{21} h_1 + \psi_{22} h_2 + \psi_{23} h_3]$$ $$h_3' = a[\psi_{30} + \psi_{31} h_1 + \psi_{32} h_2 + \psi_{33} h_3]$$

$$y' = \phi_0' + \phi_1' h_1' + \phi_2' h_2' + \phi_3' h_3'$$

Esto es exactamente la estructura de una **red con dos capas ocultas**: primero se calculan $h_1, h_2, h_3$ a partir de $x$, y luego $h_1', h_2', h_3'$ a partir de $h_1, h_2, h_3$.

Combinando todo en una sola ecuación: $$y' = \phi_0' + \phi_1' a[\psi_{10} + \psi_{11} a[\theta_{10}+\theta_{11}x] + \psi_{12} a[\theta_{20}+\theta_{21}x] + \psi_{13} a[\theta_{30}+\theta_{31}x]]$$ $$\quad + \phi_2' a[\psi_{20} + \psi_{21} a[\theta_{10}+\theta_{11}x] + \psi_{22} a[\theta_{20}+\theta_{21}x] + \psi_{23} a[\theta_{30}+\theta_{31}x]]$$ $$\quad + \phi_3' a[\psi_{30} + \psi_{31} a[\theta_{10}+\theta_{11}x] + \psi_{32} a[\theta_{20}+\theta_{21}x] + \psi_{33} a[\theta_{30}+\theta_{31}x]]$$

Esta es la expresión completa de la red de dos capas ocultas: relaciona directamente $x$ con $y'$.

---

### 2.4 La red profunda es más general

La composición de dos redes shallow es un **caso especial** de una red de dos capas ocultas con restricciones adicionales.

#### ¿Qué restricciones?

En la composición, los pesos de la segunda capa oculta $\psi_{ij}$ están forzados a ser un **producto exterior**:

$$\boldsymbol{\Psi} = \begin{bmatrix} \theta_{11}'\phi_1 & \theta_{11}'\phi_2 & \theta_{11}'\phi_3 \ \theta_{21}'\phi_1 & \theta_{21}'\phi_2 & \theta_{21}'\phi_3 \ \theta_{31}'\phi_1 & \theta_{31}'\phi_2 & \theta_{31}'\phi_3 \end{bmatrix} = \begin{bmatrix} \theta_{11}' \ \theta_{21}' \ \theta_{31}' \end{bmatrix} \cdot \begin{bmatrix} \phi_1 & \phi_2 & \phi_3 \end{bmatrix}$$

Formalmente: $\boldsymbol{\psi} = \boldsymbol{\theta}' \cdot \boldsymbol{\phi}$ (producto escalar).

En una red de dos capas ocultas **sin restricciones**, los 9 pesos $\psi_{ij}$ pueden tomar cualquier valor de forma independiente. Por tanto:

> **La red de dos capas ocultas es más flexible (expresiva) que la composición de dos redes shallow.**

---

### 2.5 Analogía del plegado del espacio

Esta analogía (del libro _Understanding Deep Learning_) ayuda a visualizar qué hace cada capa:

1. **Primera red/capa:** "dobla" el espacio de entrada. Múltiples puntos de $x$ se mapean al mismo valor de $y$. La función output de la primera red crea esta correspondencia muchos-a-uno.
    
2. **Segunda red/capa:** aplica su función sobre el espacio ya plegado. Como múltiples valores de $x$ producen el mismo $y$, el efecto de la segunda red se duplica en esas regiones.
    
3. Al "desdoblar" mentalmente el resultado, vemos que la función de la segunda red aparece **replicada con posibles inversiones y reescalados** según las pendientes de las regiones de la primera red.
    

Esta intuición explica por qué la profundidad genera regiones lineales con una estructura interna de dependencias y simetrías que no existe en las redes shallow.

---

### 2.6 Composición en 2D

Cuando la entrada es bidimensional $\mathbf{x} = (x_1, x_2)^T$, el comportamiento es análogo pero más rico visualmente. La primera red divide el plano $\mathbb{R}^2$ en regiones poligonales convexas mediante hiperplanos (líneas en 2D). La segunda red aplica su función sobre esas regiones ya divididas, creando subdivisiones adicionales.

Por ejemplo: si la primera red crea 7 regiones y la segunda tiene 2 regiones lineales (en su dominio de entrada), la composición puede generar hasta $7 \times 2 - 1 = 13$ regiones (las regiones planas de la primera red no se subdividen).

#### Comparación clave: profundidad vs. anchura

|Configuración|Parámetros|Regiones (mínimas con ReLU)|
|:--|:-:|:-:|
|Red profunda: 2 capas, 3 unidades/capa|20|≥ 9|
|Red shallow: 1 capa, 6 unidades|19|≤ 7|

Con apenas 1 parámetro más, la red profunda puede generar al menos el doble de regiones lineales. Este contraste se amplifica enormemente al escalar la red.

---

### 2.7 Hiperparámetros

Los **hiperparámetros** son valores que se eligen _antes_ de entrenar la red y determinan su arquitectura. No son los parámetros que aprende el modelo (pesos y sesgos), sino los que fijan la familia de funciones que el modelo puede representar.

#### Hiperparámetros principales en redes profundas

|Hiperparámetro|Significado|Notación|
|:--|:--|:-:|
|Número de capas ocultas|**Profundidad** de la red|$K$|
|Número de unidades en cada capa|**Anchura** de la red|$D_1, D_2, \ldots, D_K$|

El número total de unidades ocultas es una medida de la **capacidad** de la red.

Para hiperparámetros fijos (ej. $K=2$ capas con $D_k=3$ unidades), el modelo describe una **familia de funciones**; los parámetros determinan la función particular dentro de esa familia. Considerando también los hiperparámetros, las redes neuronales representan una **familia de familias de funciones**.

#### Optimización de hiperparámetros

Se pueden explorar distintas arquitecturas re-entrenando con diferentes hiperparámetros. Esto se llama:

- **Optimización de hiperparámetros** (_hyperparameter optimization_)
- **Búsqueda de hiperparámetros** (_hyperparameter search_)
- **_Neural Architecture Search_ (NAS)**, que puede automatizarse (ej. Auto-PyTorch)

---

### 2.8 Notación matricial compacta

#### Motivación

Escribir cada neurona individualmente se vuelve inmanejable con redes grandes. La notación matricial permite expresar capas enteras en una sola ecuación.

#### Derivación: de ecuaciones escalares a vectoriales

Partimos de las ecuaciones de la primera capa oculta:

$$h_1 = a[\theta_{10} + \theta_{11},x], \quad h_2 = a[\theta_{20} + \theta_{21},x], \quad h_3 = a[\theta_{30} + \theta_{31},x]$$

En forma vectorial-matricial:

$$\begin{bmatrix} h_1 \ h_2 \ h_3 \end{bmatrix} = a!\left(\begin{bmatrix}\theta_{10}\\theta_{20}\\theta_{30}\end{bmatrix} + \begin{bmatrix}\theta_{11}\\theta_{21}\\theta_{31}\end{bmatrix} x\right) \quad \Longrightarrow \quad \mathbf{h} = a[\boldsymbol{\beta}_0 + \boldsymbol{\Omega}_0, \mathbf{x}]$$

La segunda capa oculta:

$$\begin{bmatrix} h_1' \ h_2' \ h_3' \end{bmatrix} = a!\left(\begin{bmatrix}\psi_{10}\\psi_{20}\\psi_{30}\end{bmatrix} + \begin{bmatrix}\psi_{11}&\psi_{12}&\psi_{13}\\psi_{21}&\psi_{22}&\psi_{23}\\psi_{31}&\psi_{32}&\psi_{33}\end{bmatrix} \begin{bmatrix} h_1 \ h_2 \ h_3 \end{bmatrix}\right) \quad \Longrightarrow \quad \mathbf{h}' = a[\boldsymbol{\beta}_1 + \boldsymbol{\Omega}_1, \mathbf{h}]$$

La capa de salida:

$$y' = \phi_0' + [\phi_1'; \phi_2'; \phi_3']\begin{bmatrix} h_1' \ h_2' \ h_3' \end{bmatrix} \quad \Longrightarrow \quad \mathbf{y} = \boldsymbol{\beta}_2 + \boldsymbol{\Omega}_2, \mathbf{h}'$$

#### Notación estándar (estandarización de nombres)

|Símbolo|Significado|Dimensiones|
|:-:|:--|:-:|
|$\mathbf{h}_k$|Vector de activaciones en la capa $k$|$D_k \times 1$|
|$\boldsymbol{\beta}_k$|Vector de sesgos (biases) para la capa $k+1$|$D_{k+1} \times 1$|
|$\boldsymbol{\Omega}_k$|Matriz de pesos de la capa $k$ a la $k+1$|$D_{k+1} \times D_k$|
|$a[\cdot]$|Función de activación (aplicada elemento a elemento)|—|

#### Ecuaciones generales de una red de $K$ capas ocultas

$$\mathbf{h}_1 = a[\boldsymbol{\beta}_0 + \boldsymbol{\Omega}_0, \mathbf{x}]$$ $$\mathbf{h}_2 = a[\boldsymbol{\beta}_1 + \boldsymbol{\Omega}_1, \mathbf{h}_1]$$ $$\mathbf{h}_3 = a[\boldsymbol{\beta}_2 + \boldsymbol{\Omega}_2, \mathbf{h}_2]$$ $$\vdots$$ $$\mathbf{h}_K = a[\boldsymbol{\beta}_{K-1} + \boldsymbol{\Omega}_{K-1}, \mathbf{h}_{K-1}]$$ $$\mathbf{y} = \boldsymbol{\beta}_K + \boldsymbol{\Omega}_K, \mathbf{h}_K$$

En forma compacta (composición anidada):

$$\mathbf{y} = \boldsymbol{\beta}_K + \boldsymbol{\Omega}_K, a!\Big[\boldsymbol{\beta}_{K-1} + \boldsymbol{\Omega}_{K-1}, a\big[\ldots, a[\boldsymbol{\beta}_0 + \boldsymbol{\Omega}_0, \mathbf{x}] \ldots\big]\Big]$$

Los parámetros del modelo son: $\phi = {\boldsymbol{\beta}_k, \boldsymbol{\Omega}_k}_{k=0}^{K}$.

#### Ejemplo con dimensiones explícitas

Red con $D_i=3$ entradas, $D_1=4$, $D_2=2$, $D_3=3$ capas ocultas, $D_o=2$ salidas:

```
x (3×1)
  ↓ Ω₀ (4×3), β₀ (4×1)
z₀ = Ω₀x + β₀  (4×1)   →   h₁ = a(z₀)  (4×1)
  ↓ Ω₁ (2×4), β₁ (2×1)
z₁ = Ω₁h₁ + β₁ (2×1)   →   h₂ = a(z₁)  (2×1)
  ↓ Ω₂ (3×2), β₂ (3×1)
z₂ = Ω₂h₂ + β₂ (3×1)   →   h₃ = a(z₂)  (3×1)
  ↓ Ω₃ (2×3), β₃ (2×1)
y  = Ω₃h₃ + β₃ (2×1)
```

La dimensión de $\boldsymbol{\Omega}_k$ es siempre $D_{k+1} \times D_k$ (filas = unidades de destino, columnas = unidades de origen).

---

## 3. Optimización con redes profundas

### 3.1 Backpropagation

#### Motivación

Para entrenar una red necesitamos calcular $\frac{\partial L}{\partial \boldsymbol{\Omega}_k}$ y $\frac{\partial L}{\partial \boldsymbol{\beta}_k}$ para cada capa $k$. El algoritmo **backpropagation** (retropropagación del gradiente) hace esto de forma eficiente usando la regla de la cadena, propagando los gradientes desde la salida hacia la entrada.

#### Grafo de cómputo

Una red neuronal puede representarse como un **grafo de cómputo**: un grafo dirigido acíclico donde cada nodo es una operación matemática y las aristas llevan los valores (tensores) entre operaciones. Los parámetros ($\boldsymbol{\Omega}_k$, $\boldsymbol{\beta}_k$) son nodos adicionales del grafo.

#### Derivadas clave en cada capa

Para una capa genérica con preactivación $\mathbf{z}_k = \boldsymbol{\Omega}_k \mathbf{h}_k + \boldsymbol{\beta}_k$ y activación $\mathbf{h}_{k+1} = a(\mathbf{z}_k)$:

**Derivada de la preactivación respecto a $\mathbf{h}_k$** (cómo fluye el gradiente hacia atrás a través de la capa lineal): $$\frac{\partial \mathbf{z}_k}{\partial \mathbf{h}_k} = \boldsymbol{\Omega}_k^T$$

**Derivada de la activación respecto a la preactivación** (cómo fluye a través de la ReLU): $$\frac{\partial a(\mathbf{z}_k)}{\partial \mathbf{z}_k} = \text{diag}\big(\mathbb{I}[z_{k,1}>0],; \mathbb{I}[z_{k,2}>0],; \ldots\big) = \begin{bmatrix} \mathbb{I}[z_{k,1}>0] & 0 & \cdots \ 0 & \mathbb{I}[z_{k,2}>0] & \cdots \ \vdots & & \ddots \end{bmatrix}$$

donde $\mathbb{I}[\cdot]$ es la función indicadora (1 si el argumento es verdadero, 0 si no). La derivada de la ReLU es 1 donde la preactivación es positiva y 0 donde es negativa.

**Derivada de la preactivación respecto a los pesos** (para actualizar los parámetros): $$\frac{\partial \mathbf{z}_k}{\partial \boldsymbol{\Omega}_k} = \mathbf{h}_k^T$$

**Derivada de la preactivación respecto a los sesgos**: $$\frac{\partial \mathbf{z}_k}{\partial \boldsymbol{\beta}_k} = \mathbf{I}$$

#### Algoritmo backprop paso a paso (ejemplo)

Tomamos la red ejemplo con 3 capas ocultas de dimensiones $D_1=4$, $D_2=2$, $D_3=3$ y salida $D_o=2$:

**Forward pass** (se calculan y guardan todos los valores intermedios): $$\mathbf{z}_0 = \boldsymbol{\Omega}_0\mathbf{x}+\boldsymbol{\beta}_0 ;\to; \mathbf{h}_1 = a(\mathbf{z}_0) ;\to; \mathbf{z}_1 = \boldsymbol{\Omega}_1\mathbf{h}_1+\boldsymbol{\beta}_1 ;\to; \mathbf{h}_2 = a(\mathbf{z}_1) ;\to; \ldots ;\to; \mathbf{y}$$

**Backward pass** (se propagan gradientes hacia atrás):

_Paso 1:_ Empezamos con la derivada de la función de pérdida respecto a la salida: $$\frac{\partial L}{\partial \mathbf{y}}$$

_Paso 2:_ Derivadas respecto a los parámetros de la última capa lineal ($\boldsymbol{\Omega}_3, \boldsymbol{\beta}_3$) con $\mathbf{y} = \boldsymbol{\Omega}_3\mathbf{h}_3 + \boldsymbol{\beta}_3$: $$\frac{\partial L}{\partial \boldsymbol{\Omega}_3} = \frac{\partial L}{\partial \mathbf{y}} \cdot \mathbf{h}_3^T \qquad \frac{\partial L}{\partial \boldsymbol{\beta}_3} = \frac{\partial L}{\partial \mathbf{y}}$$

_Paso 3:_ Gradiente respecto a $\mathbf{h}_3$: $$\frac{\partial L}{\partial \mathbf{h}_3} = \boldsymbol{\Omega}_3^T \cdot \frac{\partial L}{\partial \mathbf{y}}$$

_Paso 4:_ Gradiente respecto a $\mathbf{z}_2$ (a través de la ReLU de la tercera capa oculta): $$\frac{\partial L}{\partial \mathbf{z}_2} = \text{diag}\big(\mathbb{I}[\mathbf{z}_{2}>0]\big) \cdot \frac{\partial L}{\partial \mathbf{h}_3}$$

_Pasos 5–N:_ Se continúa hacia atrás de forma análoga hasta llegar a la primera capa.

**Regla general** para cada capa $k$ (propagando hacia atrás): $$\frac{\partial L}{\partial \mathbf{h}_k} = \boldsymbol{\Omega}_k^T \cdot \frac{\partial L}{\partial \mathbf{z}_k}$$ $$\frac{\partial L}{\partial \mathbf{z}_{k-1}} = \text{diag}!\big(\mathbb{I}[\mathbf{z}_{k-1}>0]\big) \cdot \frac{\partial L}{\partial \mathbf{h}_k}$$ $$\frac{\partial L}{\partial \boldsymbol{\Omega}_k} = \frac{\partial L}{\partial \mathbf{z}_k} \cdot \mathbf{h}_k^T$$ $$\frac{\partial L}{\partial \boldsymbol{\beta}_k} = \frac{\partial L}{\partial \mathbf{z}_k}$$

> **Idea clave:** backprop es simplemente la regla de la cadena aplicada de forma sistemática y eficiente reutilizando los gradientes intermedios. Sin backprop, habría que calcular cada gradiente de forma independiente, lo que sería $O(N^2)$ en el número de parámetros. Con backprop es $O(N)$.

---

### 3.2 Inicialización de parámetros

#### ¿Por qué importa la inicialización?

La inicialización de los parámetros determina el **punto de partida** de la optimización. Una mala inicialización puede provocar:

- **Gradientes explosivos** (_exploding gradients_): los gradientes crecen exponencialmente al propagarse hacia atrás → la red diverge.
- **Gradientes que desaparecen** (_vanishing gradients_): los gradientes se hacen exponencialmente pequeños → los pesos de las primeras capas apenas se actualizan.

#### ¿Por qué no inicializar todo a 0?

Si todos los pesos $w_{ij}=0$, todas las unidades ocultas de una capa recibirán el mismo gradiente y producirán la misma actualización. Esto es el problema de la **simetría**: todas las neuronas de la misma capa se comportarán idénticamente durante todo el entrenamiento, haciendo que la capa entera sea equivalente a una sola neurona. Se puede demostrar que si inicializamos dos unidades con los mismos pesos, y entrenamos la red hasta convergencia, los pesos seguirán siendo iguales (por la simetría del gradiente), así que la red nunca rompe esa simetría.

La solución estándar: inicializar los pesos **aleatoriamente** y los sesgos a cero.

#### Análisis de la varianza de las preactivaciones

Queremos entender cómo varía la magnitud de las señales a medida que avanzan por la red.

**Configuración estándar:**

- Sesgos: $\boldsymbol{\beta}_k = \mathbf{0}$
- Pesos: $w_{ij} \sim \mathcal{N}(0, \sigma_\Omega^2)$ (distribución Normal de media 0 y varianza $\sigma_\Omega^2$)

**Preactivación de la $i$-ésima neurona en la capa $k$:** $$z_k(i) = \sum_{j=1}^{D_h} w_{ij} , h_k(j)$$

**Esperanza de la preactivación** (usando $E[w_{ij}]=0$ y la linealidad de la esperanza): $$E[z_k(i)] = \sum_{j=1}^{D_h} E[w_{ij}] \cdot E[h_k(j)] = 0$$

Con media cero en los pesos, la media de las preactivaciones es 0. ✓

**Varianza de la preactivación:**

Partimos de: $$z_k(i)^2 = \left(\sum_j w_{ij} h_k(j)\right)^2 = \sum_j (w_{ij} h_k(j))^2 + 2\sum_{r<t} w_{ir} h_k(r) \cdot w_{it} h_k(t)$$

Aplicando esperanza: $$E[z_k(i)^2] = \sum_j E[w_{ij}^2] E[h_k(j)^2] + 2\sum_{r<t} E[w_{ir}] E[h_k(r)] E[w_{it}] E[h_k(t)]$$

Los términos cruzados se anulan porque $E[w_{ir}] = 0$. Usando que la varianza de los pesos es $E[w_{ij}^2] = \sigma_\Omega^2$ (cuando la media es 0, la varianza es la esperanza del cuadrado): $$E[z_k(i)^2] = \sum_j \sigma_\Omega^2 \cdot E[h_k(j)^2] = \sigma_\Omega^2 \sum_j E[h_k(j)^2]$$

Si todas las activaciones de la capa $k$ tienen la misma varianza $\sigma_k^2$, entonces $E[h_k(j)^2] = \sigma_k^2$ (cuando la media es 0), y: $$\boxed{\sigma_{z_k}^2 = D_h \cdot \sigma_\Omega^2 \cdot \sigma_k^2}$$

#### Problema con varianzas muy diferentes

Si $D_h \cdot \sigma_\Omega^2 \neq 1$:

- Si $D_h \cdot \sigma_\Omega^2 < 1$: la varianza **decrece** con la profundidad → vanishing gradients.
- Si $D_h \cdot \sigma_\Omega^2 > 1$: la varianza **crece** con la profundidad → exploding gradients.

Ambas situaciones son problemáticas para el entrenamiento.

#### Inicialización de Xavier (para activación tanh)

Propuesta por Glorot & Bengio (2010). Asume que en el inicio del entrenamiento, las preactivaciones están en la región lineal de la función de activación (válido para tanh cerca del origen).

**Forward pass** — queremos $\sigma_{k+1}^2 = \sigma_k^2$ (varianza constante entre capas): $$\sigma_{k+1}^2 = D_h \cdot \sigma_\Omega^2 \cdot \sigma_k^2 = \sigma_k^2 \implies \boxed{\sigma_\Omega^2 = \frac{1}{D_h}}$$

**Backward pass** — queremos que la varianza de los gradientes también sea constante: $$\sigma_k^2 = D_{h'} \cdot \sigma_\Omega^2 \cdot \sigma_{k+1}^2 = \sigma_{k+1}^2 \implies \sigma_\Omega^2 = \frac{1}{D_{h'}}$$

donde $D_{h'}$ es el número de unidades en la capa siguiente.

**Compromiso:** si $D_h \neq D_{h'}$, usamos la media armónica: $$\sigma_\Omega^2 = \frac{2}{D_h + D_{h'}} \quad \text{(número de entradas + salidas de la capa)}$$

Si se usa distribución uniforme $U(-a, a)$ (que tiene varianza $a^2/3$): $$a = \sqrt{\frac{6}{D_h + D_{h'}}} \implies w_{ij} \sim U!\left(-\sqrt{\frac{6}{D_h+D_{h'}}}, \sqrt{\frac{6}{D_h+D_{h'}}}\right)$$

#### Inicialización de He (para activación ReLU)

Propuesta por He et al. (2015). La ReLU no es lineal: corta a cero la mitad de sus entradas (en promedio). Esto reduce la varianza a la mitad en comparación con la activación tanh en la región lineal.

**Derivación:** Con ReLU, la integral sólo recorre la mitad positiva: $$\sigma_{z_k}^2 = \sigma_\Omega^2 \sum_j E[\text{ReLU}(z_{k-1}(j))^2] = \sigma_\Omega^2 \sum_j \int_0^\infty z^2 ,\text{Pr}(z),dz = \sigma_\Omega^2 \cdot D_h \cdot \frac{\sigma_{z_{k-1}}^2}{2}$$

La relación entre varianzas es: $$\sigma_{z_k}^2 = \frac{1}{2} D_h \cdot \sigma_\Omega^2 \cdot \sigma_{z_{k-1}}^2$$

**Forward pass** — para $\sigma_{z_k}^2 = \sigma_{z_{k-1}}^2$: $$\frac{1}{2} D_h \cdot \sigma_\Omega^2 = 1 \implies \boxed{\sigma_\Omega^2 = \frac{2}{D_h}}$$

**Backward pass:** $$\boxed{\sigma_\Omega^2 = \frac{2}{D_{h'}}}$$

**Compromiso** si $D_h \neq D_{h'}$: $$\sigma_\Omega^2 = \frac{4}{D_h + D_{h'}}$$

#### Resumen comparativo de inicializaciones

|Inicialización|Función de activación|$\sigma_\Omega^2$|
|:--|:-:|:-:|
|Ceros|Cualquiera|0 ❌ (simetría)|
|Normal estándar $\mathcal{N}(0,1)$|Cualquiera|1 (sin ajustar $D_h$)|
|$\mathcal{N}(0, 1/D_h)$|tanh|$1/D_h$ (reduce varianza)|
|**Xavier** (Glorot & Bengio, 2010)|tanh, sigmoid|$2/(D_h+D_{h'})$|
|**He** (He et al., 2015)|**ReLU**|$2/D_h$|

---

### 3.3 Normalización (Batch Normalization)

#### El problema de los valores grandes

Incluso con buena inicialización, durante el entrenamiento las activaciones pueden adquirir magnitudes muy diferentes entre dimensiones. Esto causa que el gradiente respecto a los pesos de las primeras capas tenga componentes de magnitudes muy distintas:

$$\frac{\partial L}{\partial \boldsymbol{\Omega}_0} = \frac{\partial L}{\partial \mathbf{z}_0} \cdot \mathbf{x}^T$$

Si algunas componentes de $\mathbf{x}$ son mucho mayores que otras, el gradiente tendrá componentes de magnitudes muy diferentes → la función de pérdida tendrá contornos muy alargados (ovalados) → el descenso de gradiente necesita muchos más pasos para converger.

**Solución básica:** estandarizar las entradas $\mathbf{x}$ y las etiquetas $\mathbf{y}$ (en regresión) para que tengan media 0 y desviación típica 1: $$\bar{x}_i = \frac{x_i - E[x]}{\sqrt{E[(x-E[x])^2]}} \approx \frac{x_i - \frac{1}{N}\sum_{i=1}^N x_i}{\sqrt{\frac{1}{N}\sum_{i=1}^N (x_i - \bar{x})^2}}$$

Pero este problema puede ocurrir en **cualquier capa intermedia**, no sólo en la entrada.

#### Batch Normalization (Ioffe & Szegedy, 2015)

La idea: normalizar las activaciones de cada capa tras cada paso hacia adelante.

**Media y varianza del mini-batch** (calculadas con los $B$ datos del mini-batch, para el componente $i$ del vector de activaciones $\mathbf{h}_1$): $$\mu_1(i) \approx \frac{1}{B} \sum_{j=1}^{B} h_1(i,j) \qquad \sigma_1(i) \approx \sqrt{\frac{1}{B} \sum_{j=1}^{B} (h_1(i,j) - \mu_1(i))^2}$$

**Activación normalizada** (con dos parámetros aprendibles $\gamma$ y $\beta$ que permiten al modelo reescalar y desplazar): $$\bar{h}_1(i) = \frac{h_1(i) - \mu_1(i)}{\sigma_1(i)} \cdot \gamma + \beta$$

Los parámetros $\gamma$ y $\beta$ se aprenden mediante backpropagation junto con los pesos de la red. Esto permite que la red aprenda la escala y el desplazamiento óptimos para cada capa, mientras la normalización estabiliza el entrenamiento.

**Posición en la red:** la capa de batch normalization se inserta típicamente entre la capa lineal y la función de activación:

```
Capa lineal → BatchNorm (γ, β) → a() → Capa lineal → ...
```

**Durante la inferencia:** no tenemos un mini-batch. Se usan la media y varianza calculadas durante el entrenamiento (mediante una media móvil de las estadísticas del mini-batch a lo largo del entrenamiento).

**Ventajas de Batch Normalization:**

- Reduce la sensibilidad a la inicialización de pesos.
- Permite usar tasas de aprendizaje más altas.
- Actúa como regularizador (reduce ligeramente el overfitting).
- Mitiga el problema de vanishing/exploding gradients.

**Desventaja principal:** la media y varianza se calculan sobre el mini-batch → los valores de $\mu$ y $\sigma$ cambian en cada iteración, lo que complica el cálculo del gradiente. Hay que recalcular estas estadísticas en cada paso del gradiente.

---

### 3.4 Regularización y Dropout

#### Métodos de regularización en redes profundas

Los mismos métodos de regularización que en otras técnicas de ML se aplican a redes neuronales. La diferencia es que ahora también tenemos técnicas específicas para redes neuronales.

Mapa de métodos (Simon Prince, _Understanding Deep Learning_):

- **Regularización explícita:** L2 (weight decay), early stopping.
- **Aumentar datos:** data augmentation, label smoothing, ruido en entradas/salidas.
- **Combinar modelos:** ensembling, Dropout, Bayesian approach.
- **Regularización implícita:** encontrar mínimos más planos (flat minima).

#### Bagging de redes neuronales

**Bagging** (Bootstrapping Aggregating, Breiman 1996): entrenar $M$ clasificadores en subconjuntos distintos del dataset y combinar sus predicciones por votación.

En redes neuronales, el entrenamiento ya incorpora varias fuentes de aleatoriedad:

- Inicialización aleatoria de pesos.
- Permutación aleatoria en la generación de mini-batches.
- Descenso de Gradiente Estocástico (SGD).

Se podría hacer Bagging de la misma red cambiando la semilla aleatoria, pero eso requiere $M$ entrenamientos completos → muy costoso.

**Alternativa:** usar **snapshots** — guardar los parámetros de la red en distintos momentos del entrenamiento y usarlos como ensemble. Con ciclos de learning rate adecuados (Snapshot Ensembles, Huang et al., 2017), se obtienen modelos suficientemente diferentes en un solo entrenamiento.

#### Dropout

Propuesto por Srivastava et al. (2014), es la técnica de regularización más popular específica de redes neuronales.

**Idea:** durante el entrenamiento, aleatoriamente "apagar" (poner a cero) algunas neuronas en cada paso hacia adelante (_forward pass_). Esto equivale a entrenar simultáneamente un ensemble exponencialmente grande de sub-redes que comparten pesos.

**Durante el entrenamiento:** $$\tilde{h}_{i,j} = h_{i,j} \cdot m_{i,j}, \qquad m_{i,j} \sim \text{Bernoulli}(p)$$

donde $m_{i,j}=1$ con probabilidad $p$ (el parámetro de Dropout, típicamente $p=0.5$) y $m_{i,j}=0$ con probabilidad $1-p$.

**Implementación en código:**

```python
# Entrenamiento (Andrej Karpathy)
p = 0.5  # probabilidad de mantener una neurona activa

def train_step(X):
    H1 = np.maximum(0, np.dot(W1, X) + b1)
    U1 = np.random.rand(*H1.shape) < p  # máscara de dropout
    H1 *= U1  # apagar neuronas
    H2 = np.maximum(0, np.dot(W2, H1) + b2)
    U2 = np.random.rand(*H2.shape) < p
    H2 *= U2
    out = np.dot(W3, H2) + b3
    # ... backward pass (no mostrado)
```

**Durante la inferencia:** No usamos máscara de dropout; todas las neuronas están activas.

**Problema:** en entrenamiento, en promedio sólo $p$ fracción de las neuronas están activas, así que $z_k(i) = \sum_j w_{ij} h_k(j)$ tendrá en promedio la mitad del valor esperado en inferencia.

**Solución 1 — Escalar pesos en inferencia:** En inferencia dividir los pesos por $p$: $\boldsymbol{\Omega}_k^{\text{test}} = p \cdot \boldsymbol{\Omega}_k^{\text{train}}$.

**Solución 2 — Inverted Dropout (preferida):** escalar las activaciones durante el entrenamiento, dividiendo por $p$: $$m_{i,j} \sim \text{Bernoulli}(p) / p$$ (1/p con probabilidad $p$, 0 en otro caso)

Con esta solución, la escala esperada de las activaciones es la misma en entrenamiento e inferencia, y el código de inferencia no necesita modificaciones:

```python
# Inferencia (sin cambios!)
def predict(X):
    H1 = np.maximum(0, np.dot(W1, X) + b1)
    H2 = np.maximum(0, np.dot(W2, H1) + b2)
    out = np.dot(W3, H2) + b3
    return out
```

**Efecto de Dropout:** elimina puntos estimados que están lejos de los datos y no contribuyen a la pérdida de entrenamiento. Fuerza a las neuronas a aprender representaciones más robustas e independientes (porque no pueden depender de la presencia de otras neuronas específicas).

---

## 4. Redes no profundas vs. profundas

Comparación sistemática de las ventajas de la profundidad:

### Argumento 1: Capacidad de aproximar funciones diferentes

Ambos tipos de redes obedecen el **teorema de aproximación universal** (UAT): con suficiente capacidad (unidades ocultas), cualquier red neuronal puede aproximar cualquier función continua.

**Argumento para la profundidad:** si las capas adicionales calculan la función identidad, una red profunda puede replicar exactamente a una red shallow. Por tanto, la profundidad no resta expresividad; puede añadirla.

Formalmente (sección 4.5.1 de UDL): si la segunda de las dos redes compuestas calcula la identidad, la composición replica a la primera red. Luego la red de dos capas ocultas puede aproximar cualquier función continua arbitrariamente bien con suficiente capacidad.

### Argumento 2: Número de regiones lineales por parámetro

**Red shallow** con $D$ unidades ocultas, 1 entrada, 1 salida: $$\text{Regiones máximas} = D+1 \qquad \text{Parámetros} = 3D+1$$

**Red profunda** con $K$ capas ocultas de $D$ unidades, 1 entrada, 1 salida: $$\text{Regiones máximas} = (D+1)^K \qquad \text{Parámetros} = 3D+1 + (K-1) \cdot D(D+1)$$

**Ejemplo numérico:** 5 capas ocultas, 10 unidades/capa:

- Parámetros: $3(10)+1 + 4 \cdot 10(11) = 31 + 440 = 471$
- Regiones: $(10+1)^5 = 11^5 = 161{,}051$

Para una red shallow con los mismos 471 parámetros: $D = (471-1)/3 = 156.67 \approx 156$ → 157 regiones.

El cociente es brutal: **161,051 vs. 157** regiones con prácticamente el mismo número de parámetros.

Con $K=5$, $D=50$ unidades/capa, $D_i=10$ dimensiones de entrada:

- Parámetros: $\approx 10{,}801$
- Regiones: $> 10^{40}$

**Matiz importante:** las regiones en redes profundas no son independientes. Tienen complejas dependencias y simetrías (recordemos la analogía del plegado). No está claro que el mayor número de regiones sea una ventaja a menos que las funciones del mundo real que queremos aproximar tengan simetrías similares.

### Argumento 3: Eficiencia de profundidad

Existen funciones que pueden aproximarse con una red profunda de tamaño razonable, pero que requieren una red shallow de tamaño **exponencialmente mayor**.

Esto se conoce como **eficiencia de profundidad** (_depth efficiency_). Hay resultados teóricos (Telgarsky 2016, Eldan & Shamir 2016, Cohen et al. 2016) que demuestran la existencia de estas funciones.

**Limitación:** no sabemos si las funciones del mundo real que queremos aproximar son de este tipo. Es una ventaja teórica cuya relevancia práctica es desconocida, aunque empíricamente se observan mejoras al añadir profundidad.

### Argumento 4: Entradas estructuradas muy grandes

Las imágenes como entrada pueden tener $\sim 10^6$ píxeles. Una red completamente conectada de una sola capa oculta necesitaría millones de parámetros por neurona → inmanejable.

Solución: **procesar regiones locales de la imagen en paralelo** e **integrar gradualmente la información** de regiones cada vez más grandes. Este procesamiento local-a-global requiere múltiples capas → lleva a las **redes convolucionales** (CNNs), donde además se comparten pesos entre distintas posiciones de la imagen.

### Argumento 5: Entrenamiento y generalización

**Entrenamiento:**

- Con redes moderadamente profundas (hasta ~20 capas), el entrenamiento es generalmente más fácil que con redes shallow equivalentes.
- Más allá de ~20 capas, el entrenamiento se vuelve más difícil (gradientes que desaparecen/explotan) → se necesitan trucos: inicialización cuidadosa, batch normalization, conexiones residuales (ResNet), etc.
- Las redes sobre-parametrizadas profundas tienen una familia grande de soluciones aproximadamente equivalentes que son más fáciles de encontrar.

**Generalización:**

- Las redes profundas generalizan mejor a datos nuevos que las shallow equivalentes.
- Esto no está completamente comprendido teóricamente.
- Empíricamente, los mejores resultados en casi todas las tareas se logran con redes de decenas o cientos de capas.

**Evidencia empírica (figura 20.2 del libro):** cuatro redes completamente conectadas entrenadas en MNIST-1D con 1, 2, 3 y 4 capas ocultas. Todas alcanzan 0% de error en training, pero las más profundas lo hacen en muchas menos épocas.

---

## 5. Resumen y fórmulas

### Arquitectura de una red profunda

Una red con $K$ capas ocultas, $D_k$ unidades en la capa $k$, entrada $D_i$-dimensional y salida $D_o$-dimensional se define por las ecuaciones de forward pass:

$$\mathbf{h}_k = a!\left[\boldsymbol{\beta}_{k-1} + \boldsymbol{\Omega}_{k-1},\mathbf{h}_{k-1}\right] \quad k = 1,\ldots,K \qquad (\mathbf{h}_0 \equiv \mathbf{x})$$ $$\mathbf{y} = \boldsymbol{\beta}_K + \boldsymbol{\Omega}_K,\mathbf{h}_K$$

Dimensiones de las matrices: $$\boldsymbol{\Omega}_0 \in \mathbb{R}^{D_1 \times D_i}, \quad \boldsymbol{\Omega}_k \in \mathbb{R}^{D_{k+1} \times D_k} ;(k=1,\ldots,K-1), \quad \boldsymbol{\Omega}_K \in \mathbb{R}^{D_o \times D_K}$$

### Backpropagation: fórmulas

Para la capa $k$ con $\mathbf{z}_k = \boldsymbol{\Omega}_k \mathbf{h}_k + \boldsymbol{\beta}_k$ y $\mathbf{h}_{k+1} = a(\mathbf{z}_k)$:

$$\frac{\partial L}{\partial \boldsymbol{\Omega}_k} = \frac{\partial L}{\partial \mathbf{z}_k} \cdot \mathbf{h}_k^T$$

$$\frac{\partial L}{\partial \boldsymbol{\beta}_k} = \frac{\partial L}{\partial \mathbf{z}_k}$$

$$\frac{\partial L}{\partial \mathbf{h}_k} = \boldsymbol{\Omega}_k^T \cdot \frac{\partial L}{\partial \mathbf{z}_k}$$

$$\frac{\partial L}{\partial \mathbf{z}_{k-1}} = \text{diag}!\big(\mathbb{I}[\mathbf{z}_{k-1}>0]\big) \cdot \frac{\partial L}{\partial \mathbf{h}_k}$$

### Inicialización de pesos

|Método|Fórmula|Uso|
|:--|:-:|:--|
|Xavier (varianza)|$\sigma_\Omega^2 = \frac{2}{D_h + D_{h'}}$|tanh, sigmoid|
|Xavier (uniforme)|$w \sim U!\left(-\sqrt{\frac{6}{D_h+D_{h'}}}, \sqrt{\frac{6}{D_h+D_{h'}}}\right)$|tanh, sigmoid|
|He (varianza)|$\sigma_\Omega^2 = \frac{2}{D_h}$|**ReLU**|

### Varianza de preactivaciones

**Propagación forward (activación tanh, región lineal):** $$\sigma_{k+1}^2 = D_h \cdot \sigma_\Omega^2 \cdot \sigma_k^2$$

**Propagación forward (activación ReLU):** $$\sigma_{z_k}^2 = \frac{1}{2} D_h \cdot \sigma_\Omega^2 \cdot \sigma_{z_{k-1}}^2$$

### Regiones lineales

|Red|Parámetros|Regiones máximas|
|:--|:-:|:-:|
|Shallow: $D$ unidades, 1 entrada, 1 salida|$3D+1$|$D+1$|
|Profunda: $K$ capas de $D$ unidades, 1 entrada, 1 salida|$3D+1+(K-1)D(D+1)$|$(D+1)^K$|

### Dropout

**Entrenamiento:** $\tilde{h} = h \cdot m$, con $m \sim \text{Bernoulli}(p)$.  
**Inverted Dropout:** $m \sim \text{Bernoulli}(p)/p$ → inferencia sin cambios.

### Batch Normalization

$$\mu(i) = \frac{1}{B}\sum_j h(i,j), \qquad \sigma(i) = \sqrt{\frac{1}{B}\sum_j (h(i,j)-\mu(i))^2}$$ $$\bar{h}(i) = \frac{h(i) - \mu(i)}{\sigma(i)} \cdot \gamma + \beta$$

---

## Referencias

- Prince, S.J.D. (2023). _Understanding Deep Learning_. MIT Press. Capítulo 4. [Acceso libre en línea]
- Glorot, X. & Bengio, Y. (2010). Understanding the difficulty of training deep feedforward neural networks. _AISTATS 2010_.
- He, K., Zhang, X., Ren, S. & Sun, J. (2015). Delving Deep into Rectifiers: Surpassing Human-Level Performance on ImageNet Classification. _ICCV 2015_.
- Srivastava, N., Hinton, G., Krizhevsky, A., Sutskever, I. & Salakhutdinov, R. (2014). Dropout: A Simple Way to Prevent Neural Networks from Overfitting. _JMLR_.
- Ioffe, S. & Szegedy, C. (2015). Batch Normalization: Accelerating Deep Network Training by Reducing Internal Covariate Shift. _ICML 2015_.
- Huang, G., Li, Y., Pleiss, G., Liu, Z., Hopcroft, J.E. & Weinberger, K.Q. (2017). Snapshot Ensembles: Train 1, Get M for Free. _ICLR 2017_.
- Levine, S. (2021). Deep Learning: CS 182. Lecture 7. UC Berkeley. [YouTube]