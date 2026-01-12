## 5.1 Introducción a las redes profundas
### 1. Definición y composición
Una red profunda se define fundamentalmente por tener **más de una capa oculta**. La intuición detrás de estas redes, si bien compleja, se puede entender cómo se componen funciones simples.
- **Composición de redes "Shallow" (Poco profundas)**: Si tomamos dos redes neuronales de una sola capa oculta y conectamos la salida de la primera (y) a la entrada de la segunda, componemos funciones.
	- Sin embargo, matemáticamente, una red de dos capas ocultas es más flexible que la composición de dos redes *shallow*. La composición impone restricciones en los pesos por el producto escalar de los parámetros ($ψ = θ⋅ϕ$), mientras que una red profunda real tiene libertad total en sus parámetros.
	- **Analogía del plegado:** Cada capa de la red puede interpretarse como una operación que "pliega" el espacio de entrada. Cuantas más capas, más pliegues complejos se pueden realizar para separar las clases (regiones lineales)
### 2. Notación general
Para formalizar el paso de información en una red profunda con *K* capas, usamos la siguiente notación recursiva:
- **Pre-activación ($z_k$)**: Valor antes de pasar por la función de activación
- **Activación ($h_k$)**: Valor después de la función no lineal $a()$
- **Pesos ($\ohm$) y sesgos ($\beta$)**:

La ecuación general para una capa $K$ es:$$h_k=a[\beta_{K-1}+\ohm_{K-1}h_{K-1}]$$
La salida final siendo:$$y=\beta_K+\ohm_Kh_K$$
### 3. Redes profundas (Deep) vs No profundas (Shallow)
¿Por qué usar redes profundas si el Teorema de Aproximación Universal dice que una sola capa es suficiente? Hay 5 argumentos claves:
1. **Capacidad de aproximación:** Ambas cumplen el teorema, pero la eficiencia cambia.
2. **Número de regiones lineales (Eficiencia de parámetros)**:
	- En una red shallow con $D$ unidades, el número máximo de regiones lineales es $R = D+1$. Los parámetros crecen linealmente ($P≈3D$)
	- En una red profunda con $K$ capas y $D$ unidades cada una, el número de regiones crece **exponencialmente**: $R = (D+1)^K$
	- *Ejemplo:* Con ~470 parámetros, una red shallow ($K=1$) crea ~100 regiones. Una profunda ($K=5$) crea **161.501 regiones**
3. **Eficiencia de profundidad**: Existen funciones que requieren un número exponencialmente mayor de neuronas en una red plana para lograr la misma aproximación que una red profunda.
4. **Estructura de los datos (CNNs):** Para entradas grandes como imágenes (1M píxeles), las redes totalmente conectadas no son prácticas. La profundidad permite integrar gradualmente la información local (como en redes convolucionales).
5. **Entrenamiento y generalización**: Empíricamente, las redes profundas (hasta ~20 capas) entrenan más rápido (menos épocas) y generalizan mejor que las redes anchas y poco profundas.
## 5.2 Optimización con redes profundas
El entrenamiento de redes profundas presenta desafíos específicos que requieren técnicas avanzadas de inicialización y regularización.
### 1. Backpropagation
El algoritmo para calcular el gradiente. Se basa en la regla de la cadena sobre el grafo de cómputo.
- **Derivada respecto a la salida ($y$):** Empezamos calculando $\frac{∂J}{∂y}$ (derivada de la función de pérdida)
- **Retropropagación:** Vamos hacia atrás capa por capa. Para una capa lineal $z = \ohm h+\beta$:
	- El gradiente respecto a los pesos $\ohm$ depende de la entrada de esa capa ($h^T$):$$\frac{∂L}{∂\ohm}=\frac{∂L}{∂y}·h^T$$
	- El gradiente fluye hacia la capa anterior multiplicando por la transpuesta de los pesos:$$\frac{∂L}{∂h_{anterior}}=\ohm^T·\frac{∂L}{∂z_{actual}}$$
**Problema de la escala**: Si las entradas $x$ tienen magnitudes muy diferentes, los gradientes tendrán magnitudes muy diferentes, dificultando la optimización.
### 2. Inicialización de parámetros
Una correcta inicialización es crítica. Si inicializamos todos los pesos a 0, la red sufre de **simetría**: todas las neuronas ocultas aprenden lo mismo
- **Estrategia:** Sesgos ($\beta$) a 0. Pesos ($\ohm$) aleatorios con media 0 y varianza $\sigma_\ohm²$ 
**El problema de la varianza**
Al avanzar por la red (forward pass) la varianza de las activaciones cambia según la varianza de los pesos.
- Relación de varianzas (asumiendo parte lineal de Tanh):$$\sigma_{k+1}²=D_h·\sigma_\ohm²·\sigma_k²$$
	Donde $D_h$ es el número de neuronas (fan-in)
- **Exploding Gradients**: Si $D_h · \sigma_\ohm² > 1$, la señal se dispara ($10^{100}$)
- **Vanishing Gradients:** Si $D_h · \sigma_\ohm² < 1$, la señal se desvanece a 0.
**Métodos de inicialización**
Para evitar estos problemas, buscamos que la varianza se mantenga constante ($≈1$) entre capas.
1. **Inicialización de Xavier (o Glorot):**
	- Diseñada para activaciones tipo **Tanh** o Sigmoide (en su zona lineal).
	- Fórmula: $\sigma_\ohm²=\frac{1}{D_h}$ (si solo consideramos entrada) o promedio de entradas/salidas:$$\sigma_\ohm²=\frac{2}{D_{entrada}+D_{salida}}$$
	- Para distribución uniforme:$U[-\sqrt{\frac{6}{D_{in}+D_{out}}}, \sqrt{\frac{6}{D_{in}+D_{out}}}]$
2. **Inicialización de He (Kaiming He)**
	- Diseñada para activaciones ReLU.
	- Como ReLU anula la mitad de las activaciones (las negativas se vuelven 0), la varianza se reduce a la mitad en cada paso. Necesitamos compensar multiplicando por 2.
	- Fórmula $$\sigma_\ohm²=\frac{2}{D_h}$$
### 3. Normalización
Para mitigar el problema de que la distribución de las entradas de cada capa cambie constantemente durante el entrenamiento ("Covariate Shift"), se introduce una capa de normalización.
- **Funcionamiento (Training):** Para cada mini-batch, se calcula la media $\mu$ y varianza $\sigma$ de las activaciones. Se normaliza:$$\overline{h}=\frac{h-\mu}{\sigma}$$
	Luego se escala y desplaza con parámetros aprendibles $γ$ y $\beta$:$$Salida=\overline{h}·γ+\beta$$
- **Inferencia:** No se usa la media del batch, sino un promedio móvil de las medias y varianzas calculadas durante el entrenamiento.
### 4. Regularización
Técnicas para evitar el overfitting ("Make function smoother") y mejorar la generalización.
#### A. Ensembling y Snapshot Ensembles
- **Bagging:** Entrenar múltiples modelos independientes y promediar reduce la varianza. En Deep Learning es muy costoso entrenar muchas redes.
- **Snapshot Ensembling:** Permite hacer un "ensemble" con un solo entrenamiento. Se usa un *learning rate* cíclico que visita varios mínimos locales. Se guardan los parámetros "snapshots" en esos mínimos y se promedian las predicciones al final.
### B. Dropout (Apagado aleatorio)
Técnica extremadamente popular que simula entrenar un gran número de sub-redes diferentes.
- **Entrenamiento:** En cada paso, cada neurona se apaga (se pone a 0) con probabilidad *p* (usualmente 0.5). Se usa una máscara de Bernoulli.$$h_{drop}=h·m, m∼Bernoulli(0.5)$$
- **Inferencia (Test time):**
	- *Método estándar:* Se usan todas las neuronas, pero se deben escalar los pesos (o las activaciones) por el factor $p$ (o 1/$p$ en entrenamiento) para mantener la esperanza matemática de la señal igual que en el entrenamiento.
	- *Monte Carlo Dropout:* Se puede mantener el Dropout encendido durante inferencia y realizar múltiples pasadas para estimar la **incertidumbre** del modelo (funciona como un ensemble bayesiano)

**Resumen de fórmulas clave para el examen:**
1. **Varianza Xavier:** $σ2=2/(Din​+Dout​)$ (Para Tanh).
2. **Varianza He:** $σ2=2/Din​$ (Para ReLU).
3. **Batch Norm:** $σx−μ​γ+β$.
4. **Regla de Dropout (Inferencia):** Escalar pesos por p si no se hizo "Inverted Dropout" durante el entrenamiento.